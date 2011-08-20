import os

import pyossim
import pyossimtest

class Image:
	m_img = pyossimtest.SingleImageChain()

	def Image(self):
		m_img = self.m_img 

	def open(self, file):
		return self.m_img.open(os.path.abspath(file))

	def selectBands(self, bands):
		result = False
		bandCount = len(bands)

		if bandCount > 0:
			bandList = pyossimtest.UintVector()

			for i in range(0, bandCount):
				bandList.append(bands[i])

			result = self.m_img.selectBands(bandList)

		return result

	def getBandSelection(self):
		bands = list()

		bandList = pyossimtest.UintVector(self.m_img.getBandSelection())
		print bandList

		bandCount = len(bandList)
		print "BandCount: " + str(bandCount)

		if bandCount > 0:
			bands = list()

			for i in range(0, bandCount):
				bands[i] = bandList.get(i)

		return bands

	def setHistogram(self, histogramFile):
		histogramPath = str(os.path.abspath(histogramFile))
		print histogramPath
		return self.m_img.setHistogram(histogramPath)

	def getHistogramFile(self):
		histogramFile = self.m_img.getHistogramFile()
		return histogramFile

	def setOverview(self, overviewFile):
		overviewPath = str(os.path.abspath(overviewFile))
		print overviewPath
		return self.m_img.setOverview(overviewPath)

	def getOverviewFile(self):
		overviewFile = self.m_img.getOverviewFile()
		return overviewFile


#a = Image()
#print a.m_img
#b = a.open("testImage.tif")
#bands = list((1,2,3,4,5,6))
#print bands
#c = a.selectBands(bands)
#print c
#d = a.getBandSelection()
#print d
#histogram = "testImage.his"
#e = a.setHistogram(histogram)
#print e
#f = a.getHistogramFile()
#print f

#overviewFile = "testImage.ovr"
#g = a.setOverview(overviewFile)
#print g
#h = a.getOverviewFile()
#print h
