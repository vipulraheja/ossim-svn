//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Test code for ossimElevManger.
//
// $Id: ossim-elevation-manager-test.cpp 19751 2011-06-13 15:13:07Z dburken $
//----------------------------------------------------------------------------
#include <iostream>
using namespace std;

#include <ossim/init/ossimInit.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/elevation/ossimElevManager.h>

int main(int argc, char *argv[])
{
   ossimInit::instance()->initialize(argc, argv);

   if (argc != 2)
   {
      cout << "usage: " << argv[0] << " <elevationDirectoryToOpen>" << endl;
      return 0;
   }
   
   ossimFilename dir = argv[1];

   cout << "dir: " << dir << endl;
   
   if (ossimElevManager::instance()->loadElevationPath(dir))
   {
      cout << "ossimElevManager::openDirectory worked for: " << dir << endl;
   }
   else
   {
      cout << "ossimElevManager::openDirectory failed for: " << dir << endl;
   }
   return 0;
}
