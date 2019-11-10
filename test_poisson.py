import pwdcalc
import numpy
import matplotlib.pyplot as plt
import scipy.stats

nbins=300
binwidth=2

# constant probability for an event
rate = 0.1 
n_events = 1024*8
# gillespie algorithm, 
# time-intervals between random events with constant probability
intervals = (-1/rate)*numpy.log(numpy.random.random(n_events))

# figure with intervals between events
plt.figure()
count, bins, ignored = plt.hist(intervals, 150, normed=True)
# expexted exponential distribution
expnorm=1/rate
plt.plot( numpy.linspace(1,100,100), (1/expnorm)*numpy.exp( -1*numpy.linspace(1,100,100)*rate) )

# time-series of events
x = numpy.array( numpy.cumsum(intervals) )
x = x.astype(int)
# distance-distribution
pwd = pwdcalc.PWD(x,nbins,binwidth)
out = pwd.run()
print "output length ",len(out)
print "output bin-counts: ", out
# plot distribution
plt.figure()
plt.bar( numpy.linspace(binwidth,nbins*binwidth, nbins), out, width=binwidth)
plt.show()
