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
#include "ossimCKeywordlist.h"
#include "base/data_types/ossimKeywordlist.h"

ossimKeywordlistH ossimCreateKeywordlist()
{
   return (ossimKeywordlistH) (new ossimKeywordlist());
}

ossimKeywordlistH ossimCreateKeywordlistNewDelimeter(char delimeter)
{
   return (ossimKeywordlistH) (new ossimKeywordlist(delimeter));
}

void ossimFreeKeywordlist(ossimKeywordlistH kwl)
{
	if(kwl)
		delete ((ossimKeywordlist*)kwl);	
}

void ossimAddKeywordAndPrefixString(ossimKeywordlistH kwl,
                                    const char* prefix,
                                    const char* key,
                                    const char* value,
                                    bool replace)
{
   if(kwl)
   {
      ((ossimKeywordlist*)kwl)->add(prefix, key, value, replace);
   }
}

void ossimAddKeywordString(ossimKeywordlistH kwl,
                          const char* key,
                          const char* value,
                          bool replace)
{
   if(kwl)
   {
      ((ossimKeywordlist*)kwl)->add(key, value, replace);
   }
}

bool loadKeywordlistFromFile(ossimKeywordlistH kwl,
                             const char* filename)
{
   return ((ossimKeywordlist*)kwl)->addFile(filename);
}
