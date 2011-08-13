#!/usr/bin/python2.6

import sys
import pyossimtest

def arraycopy(source, sourcepos, dest, destpos, numelem):
	dest[destpos:destpos+numelem] = source[sourcepos:sourcepos+numelem]

def main(args):
	newArgs = ""
	newArgs.join("pyossimtest.Info")

	arraycopy(args, 0, newArgs, 1, args.length)
	
	info = pyossimtest.Info()

	if info.initialize( 1, ["Image0034.jpg"] ):
		try:
			info.execute()
		except Exception as e:
			print "Caught exception: ", e

if __name__ == "__main__":
	main(sys.argv)
