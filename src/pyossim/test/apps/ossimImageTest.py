import sys
import pyossimtest

def main(args):
	init = pyossimtest.Init.instance()
	init.initialize()

	imgFileName = raw_input()
	f = open(imgFileName)

	bands = f.getBandSelection()
	print bands

if __name__ == "__main__":
	main(sys.argv)
