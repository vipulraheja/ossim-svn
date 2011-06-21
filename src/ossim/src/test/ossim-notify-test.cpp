//----------------------------------------------------------------------------
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// ossimNotify functions test.
// 
//----------------------------------------------------------------------------
// $Id: ossim-notify-test.cpp 19751 2011-06-13 15:13:07Z dburken $

#include <iostream>
using namespace std;

#include <ossim/init/ossimInit.h>
#include <ossim/base/ossimNotify.h>

int main(int argc, char *argv[])
{
   ossimInit::instance()->initialize(argc, argv);

   ossimFilename logFile;
   ossimGetLogFilename(logFile);

   cout << "log file after ossimInit::instance()->initialize: "
        << logFile << endl;

   if (logFile.size() == 0)
   {
      logFile = "/tmp/ossim-log.txt";
      ossimSetLogFilename(logFile);
   }

   ossimGetLogFilename(logFile);

   cout << "set logFile end of test: " << logFile
        << endl;
   
   return 0;
}
