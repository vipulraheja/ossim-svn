//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// Author: Ken Melero
//         Originally written by Oscar Kramer.
//         
// Description:  This app displays a binary file in a nice
//               formatted view.  Very helpful for finding offsets of
//               binary headers.
//
//********************************************************************
// $Id: ossim-btoa.cpp 19691 2011-05-31 16:13:09Z dburken $

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimEbcdicToAscii.h>


int main(int argc, char** argv)
{
   ossimArgumentParser argumentParser(&argc, argv);
   
   bool isEbcdic = false;
   if ( argumentParser.read("-e") )
   {
      isEbcdic = true;
   }

   if ( argumentParser.read("-h") || argumentParser.read("--help") ||
        (argumentParser.argc() != 2) )
   {
      std::cout << "\nBinary to ascii usage: btoa [-e] <binary_file>\n"
                << "Options:\n" 
                << "-e Indicates text characters are ebcdic and should be"
                << "converted to ascii.\n" 
                << "-h or --help usage\n" << std::endl;
      exit(0);
   }
   
   FILE* fptr = fopen(argv[argumentParser.argc()-1], "rb");
   if (fptr == 0)
   {
      std::cout << "\nError opening file " << argv[argumentParser.argc()-1] 
                << std::endl << std::endl;
      return -1;
   }

   int           offset = 0;
   unsigned char bin_data[16];
   char          asc_data[17];
   int           hex_data[16];
   int           nbytes;
   int           i;

   ossimEbcdicToAscii* e2a = NULL;
   if ( isEbcdic )
   {
      e2a = new ossimEbcdicToAscii;
   }

   asc_data[16] = 0;
   while (!feof(fptr))
   {
      nbytes = (int)fread(bin_data, 16, 1, fptr);
      for(i=0; i<16; i++)
      {
         hex_data[i] = (int) bin_data[i];

         if (e2a) 
         {
            bin_data[i] = e2a->ebcdicToAscii(bin_data[i]);
         }
         
         if ((bin_data[i] >= 0x20) && (bin_data[i] <= 0x7F))
         {
            asc_data[i] = bin_data[i];
         }
         else
         {
            asc_data[i] = '.';
         }
      }

      printf("%06d  %02X %02X %02X %02X %02X %02X %02X %02X  "
             "%02X %02X %02X %02X %02X %02X %02X %02X  %16s\n", offset,
             hex_data[0],  hex_data[1],  hex_data[2],  hex_data[3], 
             hex_data[4],  hex_data[5],  hex_data[6],  hex_data[7], 
             hex_data[8],  hex_data[9],  hex_data[10], hex_data[11], 
             hex_data[12], hex_data[13], hex_data[14], hex_data[15],
             asc_data);

      offset += 16;
   }

   fclose (fptr);

   if (e2a)
   {
      delete e2a;
      e2a = NULL;
   }
             
   return 0;
}
