//*****************************************************************************
// Copyright (C) 2003 James E. Hopper & ImageLinks Inc. 
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// You should have received a copy of the GNU General Public License
// along with this software. If not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
// 1307, USA.
//
// See the GPL in the COPYING.GPL file for more details.
//
// AUTHOR: James E. Hopper (hopperj@macconnect.com)
//         Garrett Potts (gpotts@imagelinks)
//
//*****************************************************************************
#include "ossimCString.h"
#include "base/data_types/ossimString.h"
#include <vector>

#include <iostream>
#include <iterator>

ossimStringVectorH ossimCreateStringVector()
{
   return new std::vector<ossimString>();
}

ossimStringH ossimGetString(int idx,
                            ossimStringVectorH strVector)
{
   if(idx < ossimGetNumberOfStrings(strVector))
   {
      std::vector<ossimString>* tempVec = (std::vector<ossimString>*)strVector;
	   return &tempVec->at(idx);
   }
   return (ossimStringH)NULL;
}

void ossimFreeStringVector(ossimStringVectorH strVector)
{
   if(strVector)
   {
      std::vector<ossimString>* tempVec = (std::vector<ossimString>*)strVector;
//      for(int i = 0; i < (int)tempVec->size();++i)
//      {
//         ossimFreeString((*tempVec)[i]);
//      }
//      tempVec->clear();
      delete tempVec;
   }
}

int ossimGetNumberOfStrings(ossimStringVectorH strVector)
{
   if(strVector)
   {
      return (int)(((std::vector<ossimString>*)strVector)->size());
   }

   return 0;
}

ossimStringH ossimCreateString(const char *str)
{
   return (ossimStringH)(new ossimString(str));
}

void ossimFreeString(ossimStringH str)
{
   if(str)
   {
      delete ((ossimString*)str);
   }
}

const char* ossimGetChars(ossimStringH str)
{
   if(str)
   {
	   return ((ossimString*)str)->c_str();
   }

   return (const char*)NULL;
}

void ossimAppendConstCharPtrToStringVec(ossimStringVectorH strVector,
                                        const char* value)
{
   if(strVector)
   {
      ossimStringH newString = ossimCreateString(value);
      
      std::vector<ossimString>* tempVec = (std::vector<ossimString>*)strVector;

      tempVec->push_back((char*)newString);
   }
}
