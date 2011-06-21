//*******************************************************************
//
// License:  See top level LICENSE.txt file.
// 
// Author: Garrett Potts (gpotts@imagelinks.com)
// Description: Does a table dump on any vpf table.
//
//********************************************************************
// $Id: dump_table.cpp 9966 2006-11-29 02:01:07Z gpotts $
#include <vec/vpf/ossimVpfTable.h>
#include <base/common/ossimErrorCodes.h>

void displayUsage()
{
   cout << "usage:\ndump_table <full path to table>" << endl;
}

int main(int argc, char *argv[])
{
   if(argc == 2)
   {
      ossimVpfTable table;
   
      if(table.openTable(argv[1]) == ossimErrorCodes::OSSIM_OK)
      {
         cout << table << endl;
      }
   }
   else
   {
      displayUsage();
   }
}
