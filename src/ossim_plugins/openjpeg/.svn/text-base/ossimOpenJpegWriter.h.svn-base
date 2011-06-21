//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: OSSIM Open JPEG (j2k) writer.
//
//----------------------------------------------------------------------------
// $Id: ossimOpenJpegWriter.h 11652 2007-08-24 17:14:15Z dburken $
#ifndef ossimOpenJpegWriter_HEADER
#define ossimOpenJpegWriter_HEADER

#include <ossim/base/ossimRtti.h>
#include <ossim/imaging/ossimImageFileWriter.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimNBandLutDataObject.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimNBandToIndexFilter.h>
#include <ossim/base/ossimIoStream.h>

class ossimOpenJpegWriter : public ossimImageFileWriter
{
public:

   /* default constructor */
   ossimOpenJpegWriter();

   /* virtual destructor */
   virtual ~ossimOpenJpegWriter();

   /** @return "ossim_openjpeg_writer" */
   virtual ossimString getShortName() const;

   /** @return "ossim open jpeg writer" */
   virtual ossimString getLongName()  const;

   /** @return "ossimOpenJpegReader" */
   virtual ossimString getClassName()    const;
   
   /**
    * void getImageTypeList(std::vector<ossimString>& imageTypeList)const
    *
    * Appends this writer image types to list "imageTypeList".
    *
    * This writer only has one type "j2k".
    *
    * @param imageTypeList stl::vector<ossimString> list to append to.
    */
   virtual void getImageTypeList(std::vector<ossimString>& imageTypeList)const;
   
   virtual bool isOpen()const;   
   
   virtual bool open();

   virtual void close();
   
   /**
    * saves the state of the object.
    */
   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;
   
   /**
    * Method to the load (recreate) the state of an object from a keyword
    * list.  Return true if ok or false on error.
    */
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);

   /**
    * Will set the property whose name matches the argument
    * "property->getName()".
    *
    * @param property Object containing property to set.
    */
   virtual void setProperty(ossimRefPtr<ossimProperty> property);

   /**
    * @param name Name of property to return.
    * 
    * @returns A pointer to a property object which matches "name".
    */
   virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;

   /**
    * Pushes this's names onto the list of property names.
    *
    * @param propertyNames array to add this's property names to.
    */
   virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;

   bool hasImageType(const ossimString& imageType) const;


   /**
    * @brief Method to write the image to a stream.
    *
    * @return true on success, false on error.
    */
   virtual bool writeStream();

   /**
    * @brief Sets the output stream to write to.
    *
    * The stream will not be closed/deleted by this object.
    *
    * @param output The stream to write to.
    */
   virtual bool setOutputStream(std::ostream& stream);

private:

   /**
    * @brief Writes the file to disk or a stream.
    * @return true on success, false on error.
    */
   virtual bool writeFile();

   std::ostream* theOutputStream;
   bool          theOwnsStreamFlag;
   bool          theOverviewFlag;
      

   TYPE_DATA

};

#endif /* #ifndef ossimOpenJpegVoid Writer_HEADER */
