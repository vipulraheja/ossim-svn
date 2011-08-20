import sys
import pyossimtest

from Image import Image

def main(args):
	try:

		# Initializing 
		init = pyossimtest.Init.instance()
		init.initialize()


		#Input and open image file
		imageFileName = raw_input()
		img = Image()

		if img.open(imageFileName):
			print "Opened: " + str(imageFileName)

		# Display bands selection
		bands = list()
		bands = img.getBandSelection()
		print bands

		if bands is not None:
			i = 0
			for i in range(0, len(bands)):
				print "band[" + i + "]: " + bands[i]

			i = 0
			for i in range(0, len(bands)):
				bands[i] = len(bands) - i + 1

			img.selectBands(bands)

		else:
			print "Image.getBandSelection returned Null"


		#Set the histogram
		ext = str("his")
		im = imageFileName.split('.')
		im[0] = im[0] + ext
		his = str(im[0])
	
		if img.setHistogram(his):
			his2 = img.getHistogramFile()
			print "Image.getHistogramFile() result: " + his2
		else:
			print "Image.getHistogramFile() returned false!"
	

		#Set the overview
		ext = str("ovr")
		im = imageFileName.split('.')
		im[0] = im[0] + ext
		ovr = str(im[0])
	
		if img.setOverview(ovr):
			ovr2 = img.getOverviewFile()
			print "Image.getOverviewFile() result: " + ovr2
		else:
			print "Image.getOverviewFile() returned false!"
	
	
	except(Exception):
		print "Caught Exception"
	
if __name__ == "__main__":
	main(sys.argv)
