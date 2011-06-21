// $Id$

#include <string>
#include <vector>

#include <omarArrayOfFileObject.h>
#include <omarFileObject.h>

omarArrayOfFileObject::omarArrayOfFileObject()
   : omar2__ArrayOfFileObject()
{
   soap       = 0;
}

omarArrayOfFileObject::~omarArrayOfFileObject()
{
   cleanList();

   // "soap" deleted elsewhere...
}

void omarArrayOfFileObject::setFileList(const std::vector<ossimFilename> & list)
{
   if (list.size() == 0)
   {
      return;
   }

   // This will clear out omar2__ArrayOfFileObject::FileObject.
   cleanList();

   // iterator at start of list.
   std::vector<ossimFilename>::const_iterator i = list.begin();

   //---
   // We will assume the first file is the "mainFile" probably the image
   // itself.
   //---
   omarFileObject* file = new omarFileObject();
   file->setFilename( (*i).c_str() ); // store the filename
   file->setMainFileFlag(true);       // 1st file is main file
   FileObject.push_back(file);        // add to array
   ++i;                               // go to next file

   while ( i != list.end() )
   {
      file = new omarFileObject();
      file->setFilename( (*i).c_str() ); // store the filename
      FileObject.push_back(file);        // add to array
      ++i;                               // go to next file
   }
}

void omarArrayOfFileObject::getFileList(std::vector<ossimFilename>& list) const
{
   list.clear();

   std::vector<omar2__FileObject* >::const_iterator i = FileObject.begin();
   while ( i != FileObject.end() )
   {
      ossimFilename f =
         static_cast<omarFileObject*>((*i))->getFilename().c_str();
      list.push_back( f );
      ++i;
   }
}

void omarArrayOfFileObject::cleanList()
{
   std::vector<omar2__FileObject* >::iterator i = FileObject.begin();
   while ( i != FileObject.end() )
   {
      delete (*i);
      (*i) = 0;
      ++i;
   }
   FileObject.clear();
}
