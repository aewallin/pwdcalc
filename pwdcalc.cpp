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


// Pure c++, no need to include or reference boost-python here
class PairWiseDistaceDistribution {
public:
    PairWiseDistaceDistribution (int nbins, int binwidth) {
        _nbins = nbins;
        _binwidth = binwidth;
    }
    
    bpn::ndarray run() { 
        std::cout << "Hello World!\n";
        std::vector<int> v(_nbins, 0);
        std::cout << v.size() << "\n";
        /*
        #pragma omp parallel for reduction(+:myArray[:6])
        for (int i=0; i<50; ++i)
        {
            double a = 2.0; // Or something non-trivial justifying the parallelism...
            for (int n = 0; n<6; ++n)
            {
                myArray[n] += a;
            }
        }*/
        Py_intptr_t shape[1] = { v.size() };
        bpn::ndarray result = bpn::zeros(1, shape, bpn::dtype::get_builtin<int>());
        std::copy(v.begin(), v.end(), reinterpret_cast<int*>(result.get_data()));
        return result;
    
    } // end run
private:
    int _nbins;
    int _binwidth;
    
};

 
// wrapper to create python-module and python bindings for the class
BOOST_PYTHON_MODULE(pwdcalc) {
    bpn::initialize();
    bp::class_< PairWiseDistaceDistribution >("pwd", bp::init<int,int>())
        .def("run", &PairWiseDistaceDistribution::run)
    ;

}
