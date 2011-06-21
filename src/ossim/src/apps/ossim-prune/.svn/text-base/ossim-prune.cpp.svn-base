//*******************************************************************
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Lucas
//
//*******************************************************************
//  $Id: prune.cpp 10698 2007-04-12 13:59:43Z gpotts $


#include <iostream>
#include <stdlib.h>
using namespace std;

#include <ossim/ossimConfig.h>


#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimErrorCodes.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/init/ossimInit.h>

static ossimTrace traceDebug("prune:main");

static void usage();

int main(int argc, char* argv[])
{
   ossimInit::instance()->initialize(argc, argv);
   
   // One required arg:  input file
   if (argc != 2)
   {
      usage();
      exit(0);
   }

   const char* input_file = argv[1];

   // Get an image handler for the input file.
   ossimRefPtr<ossimImageHandler> ih
      = ossimImageHandlerRegistry::instance()->open(ossimFilename(input_file));

   if (!ih)
   {
      cout << "ERROR: Unsupported image file: " << input_file
           << "\nExiting application." << endl;
      exit(0);
   }

   // Initialize the 
   if (ih->getErrorStatus() == ossimErrorCodes::OSSIM_ERROR)
   {
      cerr << "ERROR: Unable to read image file: " << input_file
           << "\nExiting application." << endl; 
      exit(1);
   }

   ih->initialize();

   int lines   = ih->getNumberOfLines(0);
   int samples = ih->getNumberOfSamples(0);
   int tileHeight = ih->getTileHeight();
   int tileWidth = ih->getTileWidth();
   int tilesInLineDir = lines / tileHeight;
   int tilesInSampDir = samples / tileWidth;

   if(lines % tileHeight) ++tilesInLineDir;

   if(samples % tileWidth) ++tilesInSampDir;

   for(int i=0; i<tilesInLineDir; i++)
   {
      for(int j=0; j<tilesInSampDir; j++)
      {
         ossimIpt origin(j*tileWidth,i*tileHeight);
         ossimRefPtr<ossimImageData> id=ih->getTile(origin);
         if( id.valid() && (id->getDataObjectStatus() != OSSIM_EMPTY) )
         {
            cout << "RESULT: Image file has data: " << input_file << endl;
            exit(0);
         }
      }
   }

   
   ossimFilename f = input_file;

   ossimFilename f2 = f.fileNoExtension();
   f2 += ".readme.txt";
   
   f+= ".null";
   
   ossimFilename f3 = f.fileNoExtension();
   f3 += ".readme.txt.null";

   ossimString command="mv ";
   command+= input_file;
   command+= " ";
   command+= f;
   
   cout << "Executing " << command << endl;

   system(command.c_str());

   command="mv ";
   command+= f2;
   command+= " ";
   command+= f3;
   
   cout << "Executing " << command << endl;

   system(command.c_str());
   
   exit(0);
}
   
void usage()
{
   cout << "prune: Displays if image is null or not.\n"
        << "Usage:\n"
        << "ossim-prune <image_file>"
        << "\n";
   return;
}
