# pwdcalc
pair-wise distance distribution, in c++ with python wrapper

given an input vector of integers, e.g. [1, 2, 3, 6, 7, 9, 12, ..], compute a histogram of 
distances between elements in the vector.

Uses OpenMP parallel for, giving speedup on multi-core machines.

