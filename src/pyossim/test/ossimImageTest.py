import sys
import pyossimtest

from Image import Image

def main(args):
	init = pyossimtest.Init.instance()
	init.initialize()

	imageFileName = raw_input()
	img = Image()

	if img.open(imageFileName):
		print "Opened: " + str(imageFileName)

	bands = list()
	bands = img.getBandSelection()
	print bands

	if bands is not None:
		for i in range(0, len(bands)):
			print "band[" + i + "]: " + bands[i]

if __name__ == "__main__":
	main(sys.argv)
