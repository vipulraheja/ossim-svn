//----------------------------------------------------------------------------
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Singleton class for queries about things like writer strings
// that should stay the same throughout the session.
//
// $Id: Init.cpp 13480 2008-08-22 14:42:42Z gpotts $
//----------------------------------------------------------------------------

#include <iostream>

#include <oms/Init.h>
#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimEnvironmentUtility.h>
#include <ossim/init/ossimInit.h>
#include <ossim/base/ossimNotify.h>


oms::Init* oms::Init::theInstance = 0;

oms::Init::~Init()
{
}

oms::Init* oms::Init::instance()
{
   if (!theInstance)
   {
      theInstance = new oms::Init;
   }
   return theInstance;
}

void oms::Init::initialize(int argc, char* argv[])
{
   if(!theInitCalledFlag)
   {
      theInitCalledFlag = true;
      for (int i=0; i<argc; ++i)
      {
         // std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
      }
      //ossimSetLogFilename(ossimFilename("/tmp/oms.log"));
      
      ossimArgumentParser argumentParser(&argc, argv);
      ossimInit::instance()->addOptions(argumentParser);
      ossimInit::instance()->initialize(argumentParser);
   }
}

void oms::Init::initialize()
{
   if(!theInitCalledFlag)
   {
      theInitCalledFlag = true;
      ossimInit::instance()->initialize();
   }
}

oms::Init::Init()
:theInitCalledFlag(false)
{
}

oms::Init::Init(const oms::Init& /* obj */)
:theInitCalledFlag(false)
{
}

const oms::Init& oms::Init::operator=(const oms::Init& /* obj */)
{
   return *this;
}

