/* Minimal boost python example with cmake
 * 
 * https://github.com/aewallin/sandbox
 * 
*/
#include <iostream>
#include <boost/python.hpp>
namespace bp = boost::python;
#include <boost/python/numpy.hpp>
namespace bpn = boost::python::numpy;
#include <math.h>  
#include <omp.h>

// Pure c++, no need to include or reference boost-python here
class PairWiseDistaceDistribution {
public:
    PairWiseDistaceDistribution (bpn::ndarray input, int nbins, int binwidth) {
        _nbins = nbins;
        _binwidth = binwidth;
        
        _input_size = input.shape(0);
        //int* input_ptr = reinterpret_cast<int*>(input.get_data());
        _input = new std::vector<long int>(_input_size);
        for (int i = 0; i < _input_size; ++i)
            (*_input)[i] = bp::extract<long int>(input[i]); //*(input_ptr + i);
        //std::cout << "input.size() = " << _input->size() << " ";
        //std::cout << "(" << _input->at(0) << ", " << _input->at(1) << ", " << _input->at(2) << " " << _input->at(3) << ", ... )\n";
        
    }

    bpn::ndarray run() { 
        std::cout << "pwd run\n";
        int output[_nbins] = {}; 
        
        std::cout << "len(input) = " << _input->size() << "\n";
        
        std::cout << "nbins = " << _nbins << ", binwidth = " << _binwidth << "\n";
        //std::cout << "num_threds = " << omp_get_num_threads() << "\n";
        int num_threads;
    #pragma omp parallel for reduction(+:output[:_nbins])
        for (int i=0; i<(_input_size-1); ++i) // start-element
        {
            num_threads = omp_get_num_threads(); 

            for (int j = i+1; j< _input_size; ++j) //stop-element
            {
                long int distance = _input->at(j) - _input->at(i);
                int bin = int( floor( float(distance)/float(_binwidth) ) )-1;
                if (bin < _nbins && 0 <= bin ) {
                    output[bin] += 1;
                }
            }
        }
        std::cout << "num_threds = " << num_threads << "\n";

        
        
        // return a numpy ndarray
        Py_intptr_t shape[1] = { _nbins };
        bpn::ndarray result = bpn::zeros(1, shape, bpn::dtype::get_builtin<int>());
        std::copy( output, output+_nbins, reinterpret_cast<int*>(result.get_data()));
        return result;
    
    } // end run
    
    ~PairWiseDistaceDistribution() {
        delete _input;

    }
    
private:
    int _nbins;
    int _binwidth;
    int _input_size;
    std::vector<long int>* _input;

    
};

 
// wrapper to create python-module and python bindings for the class
BOOST_PYTHON_MODULE(pwdcalc) {
    bpn::initialize();
    bp::class_< PairWiseDistaceDistribution >("PWD", bp::init<bpn::ndarray, int,int>())
        .def("run", &PairWiseDistaceDistribution::run)
    ;

}
