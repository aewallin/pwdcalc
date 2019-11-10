"""
    second order correlation functions for different types of light
    
"""
import numpy

def g2_coherent(tau, tau0):
    """
    Coherent light
    """
    return 1.0*numpy.ones(len(tau))

def g2_gaussian(tau, tau0):
    """
    Gaussian chaotic light
    tau0 = coherence time
    """
    return 1.0 + numpy.exp(-1.0*numpy.pi*pow(tau/tau0,2))
    
def g2_lorentzian(tau, tau0):
    """
    Gaussian chaotic light
    tau0 = lifetime
    """
    return 1.0 + numpy.exp(-2.0*tau/tau0)
    
if __name__ == "__main__":
    import matplotlib.pyplot as plt
    tau0 = 1
    tau = numpy.linspace(0,5,100)
    plt.figure()
    plt.plot( tau, g2_coherent(tau,tau0),'-', label="coherent")    
    plt.plot( tau, g2_gaussian(tau,tau0),'-', label="gaussian")    
    plt.plot( tau, g2_lorentzian(tau,tau0),'-', label="lorentzian")
    plt.grid()
    plt.ylabel('g_2')
    plt.xlabel('tau')
    plt.legend()
    plt.ylim((0,3))
    plt.show()
