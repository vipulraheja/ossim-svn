//*******************************************************************. 
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author: Garrett Potts
//
//*************************************************************************
//
#include <ossim/imaging/ossimMemoryImageSource.h>
#include <ossim/base/ossimKeywordNames.h>
#include <ossim/base/ossimScalarTypeLut.h>
RTTI_DEF1(ossimMemoryImageSource, "ossimMemoryImageSource", ossimImageSource);

ossimMemoryImageSource::ossimMemoryImageSource()
   :ossimImageSource(0, 0, 1, true, false)
{
   m_boundingRect.makeNan();
}

void ossimMemoryImageSource::setImage(ossimRefPtr<ossimImageData> image)
{
   m_image = image.get();
	if(m_image.valid())
	{
		m_boundingRect = m_image->getImageRectangle();
	}
	else
	{
		m_boundingRect.makeNan();
	}
}

void ossimMemoryImageSource::setImage(ossimScalarType scalarType,
                                      ossim_uint32 numberOfBands,
                                      ossim_uint32 width,
                                      ossim_uint32 height)
{
   m_image = new ossimImageData(0,
                                 scalarType,
                                 numberOfBands,
                                 width,
                                 height);
   m_image->initialize();
   
   m_boundingRect = m_image->getImageRectangle();
}

void ossimMemoryImageSource::setRect(ossim_uint32 ulx,
                                     ossim_uint32 uly,
                                     ossim_uint32 width,
                                     ossim_uint32 height)
{
   if(m_image.valid())
   {
      m_image->setImageRectangle(ossimIrect(ulx, uly,
                                             ulx + (width-1),
                                             uly + (height-1)));
      m_boundingRect = m_image->getImageRectangle();
   }
}

ossim_uint32 ossimMemoryImageSource::getNumberOfInputBands() const
{
   if(m_image.valid())
   {
      return m_image->getNumberOfBands();
   }
   return 0;;
}

ossim_uint32 ossimMemoryImageSource::getNumberOfOutputBands() const
{
   return getNumberOfInputBands();
}

ossimScalarType ossimMemoryImageSource::getOutputScalarType() const
{
   if(m_image.valid())
   {
      return m_image->getScalarType();
   }
   
   return ossimImageSource::getOutputScalarType();
}

double ossimMemoryImageSource::getNullPixelValue(ossim_uint32 band)const
{
   if(m_image.valid())
   {
      if(band < getNumberOfInputBands())
      {
         return m_image->getNullPix(band);
      }
   }
   return ossimImageSource::getNullPixelValue(band);
}

double ossimMemoryImageSource::getMinPixelValue(ossim_uint32 band)const
{
   if(m_image.valid())
   {
      if(band < getNumberOfInputBands())
      {
         return m_image->getMinPix(band);
      }
   }
   return ossimImageSource::getMinPixelValue(band);
}

double ossimMemoryImageSource::getMaxPixelValue(ossim_uint32 band)const
{
   if(m_image.valid())
   {
      if(band < getNumberOfInputBands())
      {
         return m_image->getMaxPix(band);
      }
   }
   return ossimImageSource::getMaxPixelValue(band);
}

ossimIrect ossimMemoryImageSource::getBoundingRect(ossim_uint32 resLevel)const
{
   if(resLevel == 0)
   {
      if(m_image.valid())
      {
         return m_boundingRect;
      }
   }

   return ossimImageSource::getBoundingRect(resLevel);
}

ossimRefPtr<ossimImageData> ossimMemoryImageSource::getTile(const ossimIrect& rect,
                                                            ossim_uint32 /* resLevel */)
{
   if(!m_image.valid()) return 0;
   if(m_boundingRect.hasNans()) return 0;
   if(!m_result.valid())
   {
      m_result = new ossimImageData(0, getOutputScalarType(), getNumberOfOutputBands(), rect.width(), rect.height());
      m_result->initialize();       
   }

   m_result->setImageRectangle(rect);
   m_result->makeBlank();
   ossimIrect clampRect = m_image->getImageRectangle().clipToRect(rect);
	
   m_result->loadTile(m_image->getBuf(),
	                    m_boundingRect,
	                    OSSIM_BSQ);

	m_result->validate();
   return m_result;
}


bool ossimMemoryImageSource::canConnectMyInputTo(ossim_int32 /* myInputIndex */,
                                                 const ossimConnectableObject* /* object */)const
{
   return false;
}
   
void ossimMemoryImageSource::initialize()
{
}

ossim_uint32 ossimMemoryImageSource::getNumberOfDecimationLevels() const
{
   return 1;
}

void ossimMemoryImageSource::getDecimationFactor(ossim_uint32 resLevel,
                                                 ossimDpt& result) const
{
   if (resLevel == 0)
   {
      result.x = 1.0;
      result.y = 1.0;
   }
   else
   {
      result.x = 1.0 / (1<<resLevel);
      result.y = result.x;
   }
}

void ossimMemoryImageSource::getDecimationFactors(std::vector<ossimDpt>& decimations)const
{
   decimations.push_back(ossimDpt(1.0,1.0));
}


bool ossimMemoryImageSource::saveState(ossimKeywordlist& kwl, const char* prefix)const
{
   
   return ossimImageSource::saveState(kwl, prefix);
}

bool ossimMemoryImageSource::loadState(const ossimKeywordlist& kwl, const char* prefix)
{
   ossimString boundsString     = kwl.find(prefix, "rect");
   ossimString scalarTypeString = kwl.find(prefix, ossimKeywordNames::SCALAR_TYPE_KW);
   ossimString nBandsString     = kwl.find(prefix, ossimKeywordNames::NUMBER_BANDS_KW);
   
   m_boundingRect.makeNan();
   if(!boundsString.empty()&&!scalarTypeString.empty()&&!nBandsString.empty())
   {
      m_boundingRect.toRect(boundsString);
      ossimScalarType scalarType = ossimScalarTypeLut::instance()->getScalarTypeFromString(scalarTypeString);
      ossim_uint32 numberOfBands = nBandsString.toUInt32();
      
      if(scalarType!=OSSIM_SCALAR_UNKNOWN)
      {
         m_image = new ossimImageData(0, scalarType, numberOfBands, m_boundingRect.width(), m_boundingRect.height());
         m_image->setImageRectangle(m_boundingRect);
         m_image->initialize();
      }
   }

   return ossimImageSource::loadState(kwl, prefix);
}
