//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: Factory for OSSIM Open JPEG writer.
//----------------------------------------------------------------------------
// $Id: ossimOpenJpegWriterFactory.h 10121 2006-12-14 22:38:33Z dburken $

#ifndef ossimOpenJpegWriterFactory_HEADER
#define ossimOpenJpegWriterFactory_HEADER
#include <ossim/imaging/ossimImageWriterFactoryBase.h>

class ossimImageFileWriter;
class ossimKeywordlist;
class ossimImageWriterFactory;

/** @brief Factory for PNG image writer. */
class ossimOpenJpegWriterFactory: public ossimImageWriterFactoryBase
{   
public:

   /** @brief virtual destructor */
   virtual ~ossimOpenJpegWriterFactory();

   /**
    * @brief static method to return instance (the only one) of this class.
    * @return pointer to instance of this class.
    */
   static ossimOpenJpegWriterFactory* instance();

   /**
    * @brief Creates a writer from extension like "png".
    * @param fileExtension "png"
    */
   virtual ossimImageFileWriter *createWriterFromExtension(
      const ossimString& fileExtension)const;

   /**
    * @brief Create that takes a keyword list and prefix.
    * @param kwl The keyword list.
    * @param prefix the keyword list prefix.
    * @return pointer to image handler on success, NULL on failure.
    */
   virtual ossimImageFileWriter* createWriter(const ossimKeywordlist& kwl,
                                              const char *prefix=0)const;

   /**
    * @brief createWriter that takes a class name (ossimOpenJpegWriter)
    * @param kwl The keyword list.
    * @param prefix the keyword list prefix.
    * @return pointer to image writer on success, NULL on failure.
    */
   virtual ossimImageFileWriter* createWriter(const ossimString& typeName)const;

   /**
    * @brief Creates and object given a keyword list.
    * @param kwl The keyword list.
    * @param prefix the keyword list prefix.
    * @return pointer to image writer on success, NULL on failure.
    */
   virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                     const char *prefix=0)const;

   /**
    * @brief createObject that takes a class name (ossimOpenJpegWriter)
    * @param typeName Should be "ossimOpenJpegReader".
    * @return pointer to image writer on success, NULL on failure.
    */
   virtual ossimObject* createObject(const ossimString& typeName)const;


   /**
    * @brief Adds "png" to list.
    * @param extList List to add to.
    */
   virtual void getExtensions(std::vector<ossimString>& extList)const;

   /**
    * @brief Adds "ossimOpenJpegWriter" to list.
    * @param typeList List to add to.
    */
   virtual void getTypeNameList(std::vector<ossimString>& typeList)const;
   
   /**
    * @brief Adds "ossim_png" to writer list.
    * @param imageTypeList List to append to.
    */
   virtual void getImageTypeList(std::vector<ossimString>& imageTypeList)const;
   
protected:
   /** @brief hidden from use default constructor */
   ossimOpenJpegWriterFactory();

   /** @brief hidden from use copy constructor */
   ossimOpenJpegWriterFactory(const ossimOpenJpegWriterFactory&);

   /** @brief hidden from use copy constructor */
   void operator=(const ossimOpenJpegWriterFactory&);

   /** static instance of this class */
   static ossimOpenJpegWriterFactory* theInstance;

TYPE_DATA
};

#endif /* end of #ifndef ossimOpenJpegWriterFactory_HEADER */
