#include <oms/ImageStager.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>
#include <ossim/base/ossimProcessListener.h>
#include <ossim/base/ossimKeywordNames.h>
#include <ossim/base/ossimProcessInterface.h>
#include <ossim/imaging/ossimOverviewBuilderFactoryRegistry.h>
#include <ossim/imaging/ossimOverviewBuilderBase.h>
#include <ossim/imaging/ossimHistogramWriter.h>
#include <ossim/imaging/ossimImageHistogramSource.h>
#include <iostream>

class oms::ImageStager::PrivateData : public ossimProcessListener

{
public:
	PrivateData()
	:theUseFastHistogramStagingFlag(false),
   theStageHistogramFlag(false),
	theStageOverviewFlag(false),
	theCurrentProcessInterface(0),
	theCancelFlag(false),
   theEntryId(-1)
	{
		
	}
	void initHandler()
	{
		theHandler = ossimImageHandlerRegistry::instance()->open(theFilename);
	}
	void cancel()
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(theMutex);
		theCancelFlag = true;
	}
	bool isCanceled()const
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(theMutex);
		return theCancelFlag;
	}
	void setCancelFlag(bool flag)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(theMutex);
		theCancelFlag = flag;
	}
	void setDefaults()
	{
		if(!theHandler.valid())
		{
			initHandler();
         initEntry();
		}
      ossim::defaultTileSize(theOverviewTileSize);
		theStageHistogramFlag = false;
		theStageOverviewFlag = false;
		theHistogramFilename = "";
		theOverviewFilename = "";
		if(theHandler.valid())
		{
			theStageOverviewFlag  = !(theHandler->hasOverviews());
			theOverviewFilename   = theHandler->createDefaultOverviewFilename();
			theHistogramFilename  = theHandler->createDefaultHistogramFilename();
			theStageHistogramFlag = !(theHistogramFilename.exists());
		}
	}
   bool changeEntry(ossim_uint32 entryId)
   {
      bool result = false;
      if(theHandler.valid())
      {
         result = theHandler->setCurrentEntry(entryId);
         theOverviewFilename   = theHandler->createDefaultOverviewFilename();
         theHistogramFilename  = theHandler->createDefaultHistogramFilename();
 			theStageOverviewFlag  = !(theHandler->hasOverviews());
			theStageHistogramFlag = !(theHistogramFilename.exists());
     }
      if(result)
      {
         theEntryId = entryId;
      }
      
      return result;
   }
   
   void setOverviewTileSize(int width, int height)
   {
      theOverviewTileSize = ossimIpt(width, height);
   }
	bool buildOverviews()
	{
      bool result = false;
      if(!initEntry()) return result;
		ossimRefPtr<ossimOverviewBuilderBase> builder = ossimOverviewBuilderFactoryRegistry::instance()->createBuilder("ossim_tiff_box");
		if(!builder.valid())
		{
			return result;
		}
      
      ossimPropertyInterface* builderProp = (ossimPropertyInterface*)builder.get();
      builderProp->setProperty(ossimKeywordNames::OUTPUT_TILE_SIZE_KW, theOverviewTileSize.toString());
		builder->setInputSource(theHandler.get());
		
		builder->addListener((ossimProcessListener*)this);
		if(theOverviewFilename.path().isWriteable())
		{
         result = true;
			theCurrentProcessInterface = builder.get();
			builder->setOutputFile(theOverviewFilename);
			builder->execute();
		}
		builder->removeListener((ossimProcessListener*)this);	
		theCurrentProcessInterface = 0;
      
      return result;
	}
	bool buildHistograms()
	{
      if(!initEntry()) return false;
		ossimRefPtr<ossimImageHistogramSource> histoSource = new ossimImageHistogramSource;
		ossimRefPtr<ossimHistogramWriter> writer = new ossimHistogramWriter;
		histoSource->connectMyInputTo(0, theHandler.get());
		histoSource->enableSource();
      if (theUseFastHistogramStagingFlag)
      {
         histoSource->setComputationMode(OSSIM_HISTO_MODE_FAST);
      }
		writer->connectMyInputTo(0, histoSource.get());
		
		writer->setFilename(theHistogramFilename);
		writer->addListener((ossimProcessListener*)this);
		theCurrentProcessInterface = writer.get();
		writer->execute();
		writer->removeListener((ossimProcessListener*)this);
      writer->disconnect();
      histoSource->disconnect();
		theCurrentProcessInterface = 0;
      
      return true;
	}
   virtual void processProgressEvent(ossimProcessProgressEvent& event)
	{
		if(isCanceled())
		{
			if(theCurrentProcessInterface)
			{
				theCurrentProcessInterface->abort();
			}
		}
	}
   bool initEntry()
   {
      if(!theHandler.valid())
      {
         return false;
      }
      if(theHandler->getCurrentEntry() != theEntryId)
      {
         if(theEntryId >= 0)
         {
            if(!theHandler->setCurrentEntry(theEntryId))
            {
               return false;
            }
         }
      }
      
      return true;
   }
   
	ossimRefPtr<ossimImageHandler> theHandler;
	ossimFilename theFilename;
	ossimFilename theHistogramFilename;
   bool theUseFastHistogramStagingFlag;
	bool theStageHistogramFlag;
	ossimFilename theOverviewFilename;
	bool theStageOverviewFlag;
	ossimProcessInterface* theCurrentProcessInterface;
	bool theCancelFlag;
	mutable OpenThreads::Mutex theMutex;
   ossimIpt theOverviewTileSize;
   ossim_int32 theEntryId;
};

oms::ImageStager::ImageStager()//const std::string& filename, ossim_int32 entryId)
:thePrivateData(new PrivateData)
{
//	thePrivateData->theFilename = ossimFilename(filename);
//   thePrivateData->theEntryId  = entryId;
//   thePrivateData->initHandler();
//   thePrivateData->initEntry();
}

oms::ImageStager::~ImageStager()
{
	if(thePrivateData)
	{
		delete thePrivateData;
		thePrivateData = 0;
	}
}

bool oms::ImageStager::open(const std::string& filename)
{
	thePrivateData->theFilename = ossimFilename(filename);
	thePrivateData->theHandler = 0;
   thePrivateData->theEntryId = -1;
   
   thePrivateData->setDefaults();
   return thePrivateData->theHandler.valid();
}

bool oms::ImageStager::setEntry(ossim_uint32 entryId)
{
   return thePrivateData->changeEntry(entryId);
}

std::string oms::ImageStager::getFilename()const
{
	return thePrivateData->theFilename;
}

void oms::ImageStager::setUseFastHistogramStagingFlag(bool flag)
{
	thePrivateData->theUseFastHistogramStagingFlag = flag;
}

void oms::ImageStager::setHistogramStagingFlag(bool flag)
{
	thePrivateData->theStageHistogramFlag = flag;
}

void oms::ImageStager::setOverviewStagingFlag(bool flag)
{
	thePrivateData->theStageOverviewFlag = flag;
}

void oms::ImageStager::setHistogramFilename(const std::string& file)
{
	thePrivateData->theHistogramFilename = ossimFilename(file);
}

std::string oms::ImageStager::getHistogramFilename()const
{
	return thePrivateData->theHistogramFilename;
}

void oms::ImageStager::setOverviewFilename(const std::string& file)
{
	thePrivateData->theOverviewFilename = ossimFilename(file);
}

std::string oms::ImageStager::getOverviewFilename()const
{
	return thePrivateData->theOverviewFilename;
}

void oms::ImageStager::disableAll()
{
	thePrivateData->theStageHistogramFlag = false;
	thePrivateData->theStageOverviewFlag = false;
}

void oms::ImageStager::setDefaults()
{
	thePrivateData->setDefaults();
}

void oms::ImageStager::setOverviewTileSize(int width, int height)
{
   thePrivateData->setOverviewTileSize(width, height);
}

bool oms::ImageStager::stage()
{
	bool status = false;
	
	thePrivateData->setCancelFlag(false);
	
	if(thePrivateData->theStageOverviewFlag)
	{
		status = thePrivateData->buildOverviews();
		
	}
	if(thePrivateData->theStageHistogramFlag&&!thePrivateData->isCanceled())
	{
		status = thePrivateData->buildHistograms();
	}
	
	return status;	
}

bool oms::ImageStager::buildOverviews()
{
	bool status = false;
	
	if(thePrivateData->theStageOverviewFlag)
	{
		status = thePrivateData->buildOverviews();
	}
	
	return status;	
   
}

bool oms::ImageStager::buildAllOverviews()
{
	bool status = false;
	
   for ( ossim_uint32 i = 0, numEntries = thePrivateData->theHandler->getNumberOfEntries(); i < numEntries; i++ )
	{
      this->setDefaults();
      this->setEntry(i);
		status |= buildOverviews();
	}
	
	return status;	
   
}

bool oms::ImageStager::buildHistograms()
{
	bool status = false;
	
   if(thePrivateData->theStageHistogramFlag&&!thePrivateData->isCanceled())
	{
		status = thePrivateData->buildHistograms();
	}
   
	return status;	
}

bool oms::ImageStager::buildAllHistograms()
{
	bool status = false;
	
   for ( ossim_uint32 i = 0, numEntries = thePrivateData->theHandler->getNumberOfEntries(); i < numEntries; i++ )
	{
      this->setDefaults();
      this->setEntry(i);
		status |= buildHistograms();
	}
   
	return status;	
}

void oms::ImageStager::cancel()
{
	thePrivateData->cancel();
}

bool oms::ImageStager::stageAll()
{
	bool status = false;

	thePrivateData->initEntry();

	if ( thePrivateData->theHandler.valid() )
	{
		
		for ( ossim_uint32 i = 0, numEntries = thePrivateData->theHandler->getNumberOfEntries(); i < numEntries; i++ )
		{
			this->setDefaults();
			this->setEntry(i);
			status |= this->stage();
		}				 
	}
	
	return status;
}
