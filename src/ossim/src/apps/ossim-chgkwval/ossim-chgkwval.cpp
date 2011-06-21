//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  See top level LICENSE.txt file.
//
// Author: Ken Melero
// 
// Description: Changes the value of a keyword within a keyword list to
//              value passed in by user.
//
//********************************************************************
// $Id: chgkwval.cpp 13083 2008-06-25 19:45:41Z dburken $

#include <iostream>
#include <ossim/base/ossimKeywordlist.h>

int main(int argc, char* argv[])
{
   if (argc != 4)
   {
      std::cout
         << "Usage: chgkwval <keywordlist_file> <keyword> <value>\n"
         << "Changes the keyword value within the keyword list to "
         << "value specified.\n"
         << "Example:   chgval band1.spec area.size \"pixels 7689 8031\"\n"
         << "Changes the keyword value of area.size to pixels 7689 8031\n\n"
         << "Note 1:  Use no colon \":\" after the keyword.\n"
         << "Note 2:  If the keyword is present in the keyword list it will\n"
         << "         be overwritten.\n"
         << "Note 3:  If the keyword is not in the keyword list it will"
         << " be added.\n"
         << "Note 4:  Enclose value in double quotes if it is more than one"
         << " string.\n"
         << std::endl;
      return 0;
   }
   
   ossimKeywordlist kwl(argv[1]);
   
   if (kwl.getErrorStatus() != ossimErrorCodes::OSSIM_OK)
   {
      std::cerr << "Error opening keyword list:  " << argv[1] << std::endl;
      return 1;
   }
   
   // Change the value of keyword in the keyword list.
   kwl.add(argv[2], argv[3], true);
   
   std::cout << "Changing " << argv[2] << " value in " << argv[1] << " to:  "
             << argv[3] << std::endl;
   
   kwl.write(argv[1]);
   
   return 0;
}
