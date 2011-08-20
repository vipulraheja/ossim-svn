import os 

f = open('out','r')
f1 = open('final','w')

for line in f:
	d = '%include "base/'
	a = str(line)
	d += a
	print(d)
