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
#ifndef ossimCObject_HEADER
#define ossimCObject_HEADER
#include "ossimCString.h"
#include "ossimCRtti.h"
#include "base/common/ossimConstants.h"

typedef void* ossimObjectH;
typedef void* ossimKeywordlistH;

#ifdef __cplusplus
extern "C"
{
#endif

    ossimObjectH ossimCreateObject();
    void ossimFreeObject(ossimObjectH obj);
    ossimObjectH dupC(ossimObjectH obj);
   
    ossimStringH getShortNameC(ossimObjectH obj);
    ossimStringH getLongNameC(ossimObjectH obj);
    ossimStringH getDescriptionC(ossimObjectH obj);
    ossimStringH getClassNameC(ossimObjectH obj);

   /*!
    * Will return the type of this class in an RTTI format.
    */
    RTTItypeidH getType(ossimObjectH obj);
    bool canCastTo(ossimObjectH fromObj, 
                  ossimObjectH toObj);   
    bool canCastToRtti(ossimObjectH fromObj,
                   const RTTItypeidH id);

   /*!
    * Will use RTTI to search the derived classes to see if it derives from
    * the passed in type.  If so then this object can be casted to the
    * passed in class name.
    */
   bool canCastToClassName(ossimObjectH fromObj,
                  ossimStringH parentClassName);

   /*!
    * Method to save the state of the object to a keyword list.
    * Return true if ok or false on error.
    */
   bool saveState(ossimObjectH obj,
                  ossimKeywordlistH kwl,
                  const char* prefix); // = 0

   /*!
    * Method to the load (recreate) the state of the object from a keyword
    * list.  Return true if ok or false on error.
    */
   bool loadState(ossimObjectH obj,
                  ossimKeywordlistH kwl,
                  const char* prefix); // =0

#ifdef __cplusplus
}
#endif 

#endif
