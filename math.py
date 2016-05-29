#!/usr/bin/python

import math

def work(p, l):
	if p > l:
		return 1
	return math.ceil(l / p)

def Tp(m, p):
	return sum([work(p, x) for x in range(1, m)]) + sum([work(p, x) for x in range(1, m-1)])

l = [1000, 5000, 10000, 15000, 20000, 30000, 40000, 80000]
q =  [1, 2, 4, 8]

T1 = {x: Tp(x, 1) for x in l} #T1 for various lengths 

TP = {m: [Tp(m, p) for p in q] for m in l}

for m in l: #length
	result = "length: " + str(m)
	index = 0
	for p in q: #processor
		result += ", processors: " + str(p) + ", speedup: " + str(T1[m]/TP[m][index])
		index += 1
	print result
