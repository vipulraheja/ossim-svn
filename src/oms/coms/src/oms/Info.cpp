//----------------------------------------------------------------------------
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Singleton class for queries about things like writer strings
// that should stay the same throughout the session.
//
// $Id: Info.cpp 11646 2007-08-23 21:04:16Z dburken $
//----------------------------------------------------------------------------

// #include <cstddef>
#include <oms/Info.h>
#include <ossim/base/ossimString.h>
#include <ossim/imaging/ossimImageWriterFactoryRegistry.h>


oms::Info* oms::Info::theInstance = 0;


oms::Info::~Info()
{
   theWriterList.clear();
}

oms::Info* oms::Info::instance()
{
   if (!theInstance)
   {
      theInstance = new oms::Info;
   }
   return theInstance;
}

void oms::Info::getWriterList(std::vector<std::string>& list) const
{
   list = theWriterList;
}

void oms::Info::initializeWriterList()
{
   std::vector<ossimString> outputType;
   
   ossimImageWriterFactoryRegistry::instance()->getImageTypeList(outputType);

   std::vector<ossimString>::const_iterator i = outputType.begin();
   while (i != outputType.end())
   {
      std::string s = (*i).c_str();
      theWriterList.push_back(s);
      ++i;
   }
}

oms::Info::Info()
   : theWriterList()
{
   initializeWriterList();
}

oms::Info::Info(const oms::Info& /* obj */)
{
}

const oms::Info& oms::Info::operator=(const oms::Info& /* obj */)
{
   return *this;
}

