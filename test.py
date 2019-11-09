import pwdcalc
import numpy

nbins=100
binwidth=2
x = [int(x) for x in 100*numpy.random.randn(1024)]
x = numpy.array(x)
print x
x = x.astype(int)
print x[0:5]

pwd = pwdcalc.PWD(x,nbins,binwidth)
#pwd.set_input( x )
out = pwd.run()
print len(out)
print out
