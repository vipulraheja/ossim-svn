//*******************************************************************
//
// License:  See top level LICENSE.txt file.
// 
// Author:  Garrett Potts (gpotts@imagelinks.com)
//
// Description:
//
//*******************************************************************
//  $Id: directorytest.cpp 9966 2006-11-29 02:01:07Z gpotts $
#include <iostream>
#include "base/data_types/ossimDirectoryTree.h"

int main()
{
   // create a directory object
   ossimDirectoryTree dirTree;

   // open a directory
   dirTree.open(".");

   ossimFilename tempFile;

   // initialize the enumeration over the current directory
   // using the default directory flags.  It will return true
   // if it was able to open the file and will return false it if was
   // not able to open the file.
   if(dirTree.getFirst(tempFile))
   {
      do
      {
         std::cout << tempFile << std::endl;
      }while(dirTree.getNext(tempFile));
   }
}
