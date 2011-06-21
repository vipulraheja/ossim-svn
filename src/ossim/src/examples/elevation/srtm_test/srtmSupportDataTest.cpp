//----------------------------------------------------------------------------
// Copyright (C) 2005 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: Test application / example code for srtm support data class.
// and using it.
//
// $Id: srtmSupportDataTest.cpp 7328 2005-03-13 21:54:09Z dburken $
//----------------------------------------------------------------------------

#include <iostream>
using namespace std;

#include <init/ossimInit.h>
#include <support_data/srtm/ossimSrtmSupportData.h>
#include <base/data_types/ossimKeywordlist.h>

int main(int argc, char *argv[])
{
   ossimInit::instance()->initialize(argc, argv);

   if (argc != 2)
   {
      cout << "usage:  " << argv[0] << " srtm_file" << endl;
      return 0;
   }

   ossimSrtmSupportData sd;
   if (sd.setFilename(ossimFilename(argv[1]), true))
   {
      cout << sd << endl;

      ossimKeywordlist kwl;
      sd.getImageGeometry(kwl);
      cout << "geometry file:\n" << kwl << endl;
   }
   else
   {
      cout << "Could not open:  " << argv[1] << endl;
   }
   
   return 0;
}
