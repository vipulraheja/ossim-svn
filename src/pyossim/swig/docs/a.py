import os 

f = open('o','r')

for line in f:
	d = 'cp /home/vipul/ossim-svn/src/ossim/src/ossim/imaging/'
	e = '.cpp /home/vipul/ossim-svn/src/pyossim/swig/imgsub/\n'
	a = str(line)
	b = a.find('.')
	c = a[:b]
	c += e
	d += c
	print d
	os.system(d)
