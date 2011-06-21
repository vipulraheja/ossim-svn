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
#ifndef ossimCKeywordlist_HEADER
#define ossimCKeywordlist_HEADER
#include "ossimCCommon.h"

typedef void* ossimKeywordlistH;

#ifdef __cplusplus
extern "C"
{
#endif
   ossimKeywordlistH ossimCreateKeywordlist();
   ossimKeywordlistH ossimCreateKeywordlistNewDelimeter(char delimeter);
   void ossimFreeKeywordlist(ossimKeywordlistH kwl);

   void ossimAddKeywordAndPrefixString(ossimKeywordlistH kwl,
                                  const char* prefix,
                                  const char* key,
                                  const char* value,
                                  bool replace);
   
   void ossimAddKeywordString(ossimKeywordlistH kwl,
                        const char* key,
                        const char* value,
                        bool replace);

   bool loadKeywordlistFromFile(ossimKeywordlistH kwl,
                                const char* filename);
#ifdef __cplusplus
}
#endif

#endif
