// $Id$


#include <string>

#include <omarFileObject.h>

omarFileObject::omarFileObject()
   :
   omar2__FileObject()
{
   filename  = new std::string();
   id        = 0;
   mainFile  = new bool;
   *mainFile = false;
   soap      = 0;
}

omarFileObject::~omarFileObject()
{
   if (filename)
   {
      delete filename;
      filename = 0;
   }
   if (id)
   {
      delete id;
      id = 0;
   }
   if (mainFile)
   {
      delete mainFile;
      mainFile = 0;
   }

   // "soap" deleted elsewhere...
}

void omarFileObject::setFilename(const std::string& arg)
{
   *filename = arg;
}

std::string omarFileObject::getFilename() const
{
   return *filename;
}

void omarFileObject::setId(LONG64 arg)
{
   *id = arg; 
}

void omarFileObject::setMainFileFlag(bool arg)
{
   *mainFile = arg;
}

bool omarFileObject::getMainFileFlag() const
{
   return *mainFile;
}

