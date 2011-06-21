// $Id$

#ifndef omarArrayOfFileObject_HEADER
#define omarArrayOfFileObject_HEADER

#include <soapStagerWebServiceHttpBindingProxy.h>
#include <ossim/base/ossimFilename.h>

class omarArrayOfFileObject : public omar2__ArrayOfFileObject
{
public:

   /** @brief default constructor */
   omarArrayOfFileObject();

   /** @brief destructor */
   virtual ~omarArrayOfFileObject();

   /**
    * @brief Sets omar2__ArrayOfFileObject::FileObject which is a
    * std::vector<omar2__FileObject* >
    *
    * @param list list of files.
    *
    * @note it is assumed that the first file in the "list" is the main
    * file(usually an image).  All other files are associated with the
    * main file.
    */
   void setFileList(const std::vector<ossimFilename> & list);

   /**
    * @brief Returns the list of files.
    * @param list This list to initialize.
    */
   void getFileList(std::vector<ossimFilename>& list) const;

private:
   /**
    * @brief Private convenience method to clear
    * omar2__ArrayOfFileObject::FileObject.
    */
   void cleanList();
};

#endif /* #ifndef ossimArrayOfFileObject_HEADER */
