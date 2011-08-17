#!/usr/bin/python2.6

import sys
import pyossimtest

def main(args):
	a = raw_input()
	
	while a is not None:
		info = pyossimtest.Info()

		info.getImageInfo(str(a),False,False,True,True,True,False)

		a = raw_input()

if __name__ == "__main__":
	main(sys.argv)
