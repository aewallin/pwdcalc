import pwdcalc
import numpy

nbins = 10
binwidth = 1
#x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
x = range(0,1024) #[0:1:1024 ]
x = numpy.array(x)
print x
x = x.astype(int)
#print x[0:5]

pwd = pwdcalc.PWD(x,nbins,binwidth)
#pwd.set_input( x )
out = pwd.run()
print "len(output) ", len(out)
print "output ", out
