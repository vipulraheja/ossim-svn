#include <oms/ImageData.h>
#include <ossim/imaging/ossimImageData.h>
#include <ossim/base/ossimCommon.h>

class oms::ImageData::PrivateData
{
public:
	PrivateData()
	:theImageData(0)
	{
	}
	PrivateData(ossimImageData* data)
	:theImageData(data)
	{
	}
	void* getBandBuffer(int idx)
	{
		return theImageData.valid()?theImageData->getBuf(idx):(void*)0;
	}
	const void* getBandBuffer(int idx)const
	{
		return theImageData.valid()?theImageData->getBuf(idx):(void*)0;
	}
	bool isBlank()
	{
		bool result = false;
		
		if(!theImageData.valid())
		{
			result = true;
		}
		else
		{
			ossimDataObjectStatus status = theImageData->getDataObjectStatus();
			if(status == OSSIM_EMPTY||
				status == OSSIM_NULL||
				!theImageData->getBuf())
			{
				result = true;
			}
		}
		
		return result;
	}
	ossimImageData* getOssimImageData()
	{
		return theImageData.get();
	}
	const ossimImageData* getOssimImageData()const
	{
		return theImageData.get();
	}
	int getBandSizeInBytes()const
	{
		return theImageData.valid()?(int)theImageData->getSizePerBandInBytes():(int)0;
	}
	ossimScalarType getOssimScalarType()const
	{
		return theImageData.valid()?theImageData->getScalarType():OSSIM_SCALAR_UNKNOWN;
	}
   int getScalarTypeBitSize()const
	{
		return theImageData.valid()?ossim::scalarSizeInBytes(theImageData->getScalarType())*8:0;
	}
	int getNumberOfElementsInEachBand()const
	{
		return theImageData.valid()?theImageData->getSizePerBand():0;
	}
	int getTotalNumberOfElements()const
	{
		return theImageData.valid()?theImageData->getSize():0;
	}
	int getNumberOfBands()const
	{
		return theImageData.valid()?theImageData->getNumberOfBands():0;
	}
	ossimIpt getOrigin()const
	{
		return theImageData.valid()?theImageData->getOrigin():ossimIpt(0,0);
	}
	template<class T>
	void copyOssimImageDataBandToBuffer(T* destinationBuffer, int bandIdx)const
	{
		if(theImageData.valid())
		{
			memcpy(destinationBuffer, theImageData->getBuf(bandIdx), theImageData->getSizePerBandInBytes()); 
	   }
	}
	template<class T>
	void copyBufferToOssimImageDataBand(const T* destinationBuffer, int bandIdx)
	{
		if(theImageData.valid())
		{
			if(theImageData->getBuf(bandIdx))
			{
				memcpy(theImageData->getBuf(bandIdx), destinationBuffer, theImageData->getSizePerBandInBytes()); 
			}
	   }
	}
	template <class T>
	void copyOssimImageDataToBuffer(T* destinationBuffer[])const
	{
		if(theImageData.valid())
		{
			int bandIdx = 0;
			int n = theImageData->getNumberOfBands();
			for(bandIdx = 0; bandIdx < n; ++bandIdx)
			{
				if(theImageData->getBuf(bandIdx))
				{
					memcpy(destinationBuffer[bandIdx], theImageData->getBuf(bandIdx), theImageData->getSizePerBandInBytes());
				}
			}
		}
	}
	ossimRefPtr<ossimImageData> theImageData;
};

oms::ImageData::ImageData(void* imageData)
:thePrivateData(new PrivateData(static_cast<ossimImageData*>(imageData)))
{
}

oms::ImageData::~ImageData()
{
	if(thePrivateData)
	{
		delete thePrivateData;
		thePrivateData = 0;
	}
}

void oms::ImageData::setOssimImageData(void* imageData)
{
	thePrivateData->theImageData = static_cast<ossimImageData*>(imageData);
}

void* oms::ImageData::getOssimImageData()
{
	return thePrivateData->theImageData.get();
}

const void* oms::ImageData::getOssimImageData()const
{
	return thePrivateData->getOssimImageData();
}

void* oms::ImageData::getBandBuffer(int idx)
{
	return thePrivateData->getBandBuffer(idx);
}

bool oms::ImageData::isBlank()const
{
	return thePrivateData->isBlank();
}

const void* oms::ImageData::getBandBuffer(int idx)const
{
	return thePrivateData->getBandBuffer(idx);
}

/**
 * WIll return the byte size for the band array
 */
int oms::ImageData::getBandSizeInBytes()const
{
	return thePrivateData->getBandSizeInBytes();
}

/**
 * Returns the scalar type for the band array. Please see ossimConstants.h for a complete list of the current scalar types supported
 */
ossimScalarType oms::ImageData::getOssimScalarType()const
{
	return thePrivateData->getOssimScalarType();
}

/**
 * Returns the bit size of the scalar type.  So if it is a ossim_uint8 then the bits returned
 * is 8 and for osism_uint32 it is 32.
 */
int oms::ImageData::getScalarTypeBitSize()const
{
	return thePrivateData->getScalarTypeBitSize();
}

/**
 * Returns the number of pixel/data elements for the band.
 */
int oms::ImageData::getNumberOfElementsInEachBand()const
{
	return thePrivateData->getNumberOfElementsInEachBand();
}

int oms::ImageData::getTotalNumberOfElements()const
{
	return thePrivateData->getTotalNumberOfElements();
}

int oms::ImageData::getNumberOfBands()const
{
	return thePrivateData->getNumberOfBands();
}

ossimIpt oms::ImageData::getOrigin()const
{
	return thePrivateData->getOrigin();
}

void oms::ImageData::copyOssimImageDataBandToBuffer( ossim_int8* destinationBuffer, int bandIdx)
{
        thePrivateData->copyOssimImageDataBandToBuffer(destinationBuffer, bandIdx);
}

void oms::ImageData::copyOssimImageDataBandToBuffer( ossim_uint8* destinationBuffer, int bandIdx)
{
	thePrivateData->copyOssimImageDataBandToBuffer(destinationBuffer, bandIdx);
}

void oms::ImageData::copyOssimImageDataBandToBuffer(ossim_sint16* destinationBuffer, int bandIdx)
{
	thePrivateData->copyOssimImageDataBandToBuffer(destinationBuffer, bandIdx);
}

void oms::ImageData::copyOssimImageDataBandToBuffer(ossim_uint16* destinationBuffer, int bandIdx)
{
	thePrivateData->copyOssimImageDataBandToBuffer(destinationBuffer, bandIdx);
}

void oms::ImageData::copyOssimImageDataBandToBuffer( ossim_float32* destinationBuffer, int bandIdx)
{
	thePrivateData->copyOssimImageDataBandToBuffer(destinationBuffer, bandIdx);
}

void oms::ImageData::copyOssimImageDataBandToBuffer( ossim_float64* destinationBuffer, int bandIdx)
{
	thePrivateData->copyOssimImageDataBandToBuffer(destinationBuffer, bandIdx);
}


