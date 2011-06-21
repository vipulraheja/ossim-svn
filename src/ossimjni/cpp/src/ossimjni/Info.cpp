//-----------------------------------------------------------------------------
// File:  Info.cpp
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Class definition for Info.
//
//-----------------------------------------------------------------------------
// $Id: Info.cpp 19750 2011-06-13 15:04:07Z dburken $

#include <ossimjni/Info.h>
#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/util/ossimInfo.h>

ossimjni::Info::Info() :
   m_info(new ossimInfo)
{
}
      
ossimjni::Info::~Info()
{
   if (m_info)
   {
      delete m_info;
      m_info = 0;
   }
}

bool ossimjni::Info::initialize(int argc, char* argv[])
{
   ossimArgumentParser ap(&argc, argv);
   return m_info->initialize(ap);
}

void ossimjni::Info::execute()
{
   m_info->execute();
}

std::map<std::string, std::string> ossimjni::Info::getImageInfo(const std::string& file,
                                                                bool dumpFlag,
                                                                bool dnoFlag,
                                                                bool imageGeomFlag,
                                                                bool imageInfoFlag,
                                                                bool metaDataFlag,
                                                                bool paletteFlag) const
{
   ossimFilename imageFile(file);
   ossimKeywordlist kwl;
   m_info->getImageInfo(imageFile,
                        dumpFlag,
                        dnoFlag,
                        imageGeomFlag,
                        imageInfoFlag,
                        metaDataFlag,
                        paletteFlag,
                        kwl);
   return kwl.getMap();
}
