//----------------------------------------------------------------------------
//
// File: ossimLibLasReaderFactory.h
// 
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: Reader factory for OSSIM libLAS plugin.
//----------------------------------------------------------------------------
// $Id: ossimLibLasReaderFactory.h 2645 2011-05-26 15:21:34Z oscar.kramer $
#ifndef ossimLibLasReaderFactory_HEADER
#define ossimLibLasReaderFactory_HEADER 1

#include <ossim/imaging/ossimImageHandlerFactoryBase.h>

class ossimString;
class ossimFilename;
class ossimKeywordlist;

/** @brief Factory for PNG image reader. */
class ossimLibLasReaderFactory : public ossimImageHandlerFactoryBase
{
public:

   /** @brief virtual destructor */
   virtual ~ossimLibLasReaderFactory();

   /**
    * @brief static method to return instance (the only one) of this class.
    * @return pointer to instance of this class.
    */
   static ossimLibLasReaderFactory* instance();

   /**
    * @brief open that takes a file name.
    * @param file The file to open.
    * @param openOverview If true image handler will attempt to open overview.
    * default = true 
    * @return pointer to image handler on success, NULL on failure.
    */
   virtual ossimImageHandler* open(const ossimFilename& fileName,
                                   bool openOverview=true) const;

   /**
    * @brief open that takes a keyword list and prefix.
    * @param kwl The keyword list.
    * @param prefix the keyword list prefix.
    * @return pointer to image handler on success, NULL on failure.
    */
   virtual ossimImageHandler* open(const ossimKeywordlist& kwl,
                                   const char* prefix=0)const;

   /**
    * @brief createObject that takes a class name (ossimLibLasReader)
    * @param typeName Should be "ossimLibLasReader".
    * @return pointer to image writer on success, NULL on failure.
    */
   virtual ossimObject* createObject(const ossimString& typeName)const;
   
   /**
    * @brief Creates and object given a keyword list and prefix.
    * @param kwl The keyword list.
    * @param prefix the keyword list prefix.
    * @return pointer to image handler on success, NULL on failure.
    */
   virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                     const char* prefix=0)const;
   
   /**
    * @brief Adds ossimLibLasWriter to the typeList.
    * @param typeList List to add to.
    */
   virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

   /**
    * @brief Method to add supported extension to the list, like "png".
    *
    * @param extensionList The list to add to.
    */
   virtual void getSupportedExtensions(
      ossimImageHandlerFactoryBase::UniqueStringList& extensionList)const;
  
protected:
   /** @brief hidden from use default constructor */
   ossimLibLasReaderFactory();

   /** @brief hidden from use copy constructor */
   ossimLibLasReaderFactory(const ossimLibLasReaderFactory&);

   /** @brief hidden from use copy constructor */
   void operator=(const ossimLibLasReaderFactory&);

   /** static instance of this class */
   static ossimLibLasReaderFactory* theInstance;

TYPE_DATA
};

#endif /* end of #ifndef ossimLibLasReaderFactory_HEADER */
