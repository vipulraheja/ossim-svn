//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: "main" application for staging data into the omar database.
//
//----------------------------------------------------------------------------

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

#include <ossim/base/ossimConstants.h>
#include <ossim/init/ossimInit.h>
#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimApplicationUsage.h>
#include <ossim/base/ossimDirectory.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimTrace.h>

#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>

#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>

#include <soapStagerWebServiceHttpBindingProxy.h>
#include <StagerWebServiceHttpBinding.nsmap>
#include <omarStagerUtil.h>

static ossimTrace traceDebug("omarstager:main");

int main(int argc, char **argv)
{
   std::string tempString;
   ossimArgumentParser::ossimParameter stringParam(tempString);
   ossimArgumentParser argumentParser(&argc, argv);
   ossimInit::instance()->addOptions(argumentParser);
   ossimInit::instance()->initialize(argumentParser);

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "omarstager:main DEBUG:"
         << "\n"
         << std::endl;
   }

   argumentParser.getApplicationUsage()->setApplicationName(argumentParser.getApplicationName());

   argumentParser.getApplicationUsage()->setDescription(argumentParser.getApplicationName()+" stager for omar");
   
   argumentParser.getApplicationUsage()->setCommandLineUsage(argumentParser.getApplicationName()+" <files>");
   
   argumentParser.getApplicationUsage()->addCommandLineOption("-h or --help","Display this information");
   
   if(argumentParser.read("-h") || argumentParser.read("--help"))
   {
      argumentParser.getApplicationUsage()->write(std::cout);
      exit(0);
   }
   
   if(argumentParser.argc() < 2)
   {
      argumentParser.getApplicationUsage()->write(std::cout);
      exit(1);
   }

   
   omarStagerUtil stager;

   for (int i=1 ; i < argumentParser.argc(); ++i)
   {
      ossimFilename f = argumentParser.argv()[i];
      
      std::cout << "argumentParser.argv()[" << i << "]: " << f << std::endl;

      if (f.isDir())
      {
         stager.stageDir(f);
      }
      else
      {
         stager.stageFile(f);
      }
   }
   return 0;
}
