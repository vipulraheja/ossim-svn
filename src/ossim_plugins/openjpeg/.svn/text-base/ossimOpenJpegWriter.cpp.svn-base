//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: OSSIM Open JPEG writer.
//
//----------------------------------------------------------------------------
// $Id: ossimOpenJpegWriter.cpp 11652 2007-08-24 17:14:15Z dburken $

#include <ctime>

#include "ossimOpenJpegWriter.h"
#include <ossim/base/ossimKeywordNames.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimEndian.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimIoStream.h>
#include <ossim/base/ossimScalarTypeLut.h>
#include <ossim/base/ossimStringProperty.h>
#include <ossim/base/ossimNumericProperty.h>
#include <ossim/projection/ossimMapProjection.h>
#include <ossim/imaging/ossimImageData.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimScalarRemapper.h>

RTTI_DEF1(ossimOpenJpegWriter,
	  "ossimOpenJpegWriter",
	  ossimImageFileWriter)

//---
// For trace debugging (to enable at runtime do:
// your_app -T "ossimOpenJpegWriter:debug" your_app_args
//---
static ossimTrace traceDebug("ossimOpenJpegWriter:debug");

//---
// For the "ident" program which will find all exanded $Id: ossimOpenJpegWriter.cpp 11652 2007-08-24 17:14:15Z dburken $ macros and print
// them.
//---
#if OSSIM_ID_ENABLED
static const char OSSIM_ID[] = "$Id: ossimOpenJpegWriter.cpp 11652 2007-08-24 17:14:15Z dburken $";
#endif

ossimOpenJpegWriter::ossimOpenJpegWriter()
   : ossimImageFileWriter(),
     theOutputStream(0),
     theOwnsStreamFlag(false)
{
   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimOpenJpegWriter::ossimOpenJpegWriter entered" << std::endl;
#if OSSIM_ID_ENABLED
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "OSSIM_ID:  "
         << OSSIM_ID
         << std::endl;
#endif
   }

   // Since there is no internal geometry set the flag to write out one.
   setWriteExternalGeometryFlag(true);

   theOutputImageType = "ossim_openjpeg_writer";
}

ossimOpenJpegWriter::~ossimOpenJpegWriter()
{
   // This will flush stream and delete it if we own it.
   close();
}

ossimString ossimOpenJpegWriter::getShortName() const
{
   return ossimString("ossim_openjpeg_writer");
}

ossimString ossimOpenJpegWriter::getLongName() const
{
   return ossimString("ossim open jpeg writer");
}

ossimString ossimOpenJpegWriter::getClassName() const
{
   return ossimString("ossimOpenJpegWriter");
}

bool ossimOpenJpegWriter::writeFile()
{
   if( !theInputConnection || (getErrorStatus() != ossimErrorCodes::OSSIM_OK) )
   {
      return false;
   }

   //---
   // Make sure we can open the file.  Note only the master process is used for
   // writing...
   //---
   if(theInputConnection->isMaster())
   {
      if (!isOpen())
      {
         open();
      }
   }

   return writeStream();
}

bool ossimOpenJpegWriter::writeStream()
{
   static const char MODULE[] = "ossimOpenJpegWriter::write";
   
   if (!theInputConnection) // Must have a sequencer...
   {
      if (traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << MODULE << " DEBUG:\ntheInputConnection is NULL!" << endl;
      }
      return false;
   }
   
   //---
   // Make sure we have a stream.  Note only the master process is used for
   // writing...
   //---
   if(theInputConnection->isMaster())
   {
      if (!theOutputStream)         
      {
         ossimNotify(ossimNotifyLevel_WARN)
            << MODULE << " ERROR:"
            << "\nNULL output stream!"
            << "\nReturning from method." << std::endl;

         return false;
      }
   }
   
   // make sure we have a region of interest
   if(theAreaOfInterest.hasNans())
   {
      theInputConnection->initialize();
      theAreaOfInterest = theInputConnection->getAreaOfInterest();
   }
   else
   {
      theInputConnection->setAreaOfInterest(theAreaOfInterest);
   }

   if(theAreaOfInterest.hasNans()) // Must have an area of interest...
   {
      if (traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << MODULE << " ERROR:  Area of interest has nans!"
            << "Area of interest:  "
            << theAreaOfInterest
            << "\nReturning..." << endl;
      }

      return false;
   }

   // Get the number of bands.  Must be one or three for this writer.
   ossim_int32 bands = theInputConnection->getNumberOfOutputBands();
   if (bands != 1 && bands != 3)
   {
      ossimNotify(ossimNotifyLevel_WARN)
         << MODULE << " Range Error:"
         << "\nInvalid number of input bands!  Must be one or three."
         << "\nInput bands = " << bands
         << "\nReturning from method." << endl;
      
      return false;
   }

   return false;
}

bool ossimOpenJpegWriter::saveState(ossimKeywordlist& kwl,
                                const char* prefix)const
{
   return ossimImageFileWriter::saveState(kwl, prefix);
}

bool ossimOpenJpegWriter::loadState(const ossimKeywordlist& kwl,
                                const char* prefix)
{
   const char* value;
   
   value = kwl.find(prefix, ossimKeywordNames::OVERVIEW_FILE_KW);
   if(value)
   {
      theOverviewFlag = ossimString(value).toBool();
   }
   
   theOutputImageType = "j2k";
   
   return ossimImageFileWriter::loadState(kwl, prefix);
}

bool ossimOpenJpegWriter::isOpen() const
{
   if (theOutputStream)
   {
     return true;
   }
   return false;
}

bool ossimOpenJpegWriter::open()
{
   close();

   // Check for empty filenames.
   if (theFilename.empty())
   {
      return false;
   }

   return false;
}

void ossimOpenJpegWriter::close()
{
   if (theOutputStream)      
   {
      theOutputStream->flush();

      if (theOwnsStreamFlag)
      {
         delete theOutputStream;
         theOutputStream = 0;
         theOwnsStreamFlag = false;
      }
   }
}

void ossimOpenJpegWriter::getImageTypeList(std::vector<ossimString>& imageTypeList)const
{
   imageTypeList.push_back(ossimString("ossim_openjpeg"));
}

bool ossimOpenJpegWriter::hasImageType(const ossimString& imageType) const
{
   return false;
}

void ossimOpenJpegWriter::setProperty(ossimRefPtr<ossimProperty> property)
{
   if (!property)
   {
      return;
   }

}

ossimRefPtr<ossimProperty> ossimOpenJpegWriter::getProperty(const ossimString& name)const
{
   return ossimImageFileWriter::getProperty(name);
}

void ossimOpenJpegWriter::getPropertyNames(std::vector<ossimString>& propertyNames)const
{
   ossimImageFileWriter::getPropertyNames(propertyNames);
}

bool ossimOpenJpegWriter::setOutputStream(std::ostream& stream)
{
   if (theOwnsStreamFlag && theOutputStream)
   {
      delete theOutputStream;
   }
   theOutputStream = &stream;
   theOwnsStreamFlag = false;
   return true;
}
