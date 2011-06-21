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
#include "ossimCObject.h"
#include "base/common/ossimObject.h"
class ossimKeywordlist;

    ossimObjectH ossimCreateObject()
    {
        ossimObject* obj = new ossimObject();
        return obj;
    }

    void ossimFreeObject(ossimObjectH obj)
    {
        if(obj)
        {
            delete ((ossimObject*)obj);
        }
    }

    ossimObjectH dupC(ossimObjectH obj)
    {
       ossimObject* object = (ossimObject*)obj;
       return object->dup(); 
    }
   
    ossimStringH getShortNameC(ossimObjectH obj)
    {
        ossimObject* object = (ossimObject*)obj;
        ossimString* shortName = new ossimString(object->getShortName());
        return (ossimStringH)shortName;
    }
    
    ossimStringH getLongNameC(ossimObjectH obj)
    {
	ossimObject* object = (ossimObject*)obj;
        ossimString* longName = new ossimString(object->getLongName());
        return (ossimStringH)longName;
    }
    
    ossimStringH getDescriptionC(ossimObjectH obj)
    {
        ossimObject* object = (ossimObject*)obj;
        ossimString* desc = new ossimString(object->getDescription());
        return (ossimStringH)desc;
    }
    
    ossimStringH getClassNameC(ossimObjectH obj)
    {
        ossimObject* object = (ossimObject*)obj;
        ossimString* className = new ossimString(object->getClassName());
	return (ossimStringH)className;
   }

   /*!
    * Will return the type of this class in an RTTI format.
    */
    RTTItypeidH getType(ossimObjectH obj)
    {
         ossimObject* object = (ossimObject*)obj;
         RTTItypeid* typeId = new RTTItypeid(object->getType());
         return (RTTItypeidH)typeId;
   }
    
    bool canCastTo(ossimObjectH fromObj, 
                  ossimObjectH toObj)
    {
        ossimObject* object = (ossimObject*)fromObj;
        return object->canCastTo((ossimObject*)toObj);
    }
    
    bool canCastToRtti(ossimObjectH fromObj,
                   const RTTItypeidH id)
    {
        ossimObject* object = (ossimObject*)fromObj;
        RTTItypeid* Ident = (RTTItypeid*)id;
        return object->canCastTo(*Ident);
   }

   /*!
    * Will use RTTI to search the derived classes to see if it derives from
    * the passed in type.  If so then this object can be casted to the
    * passed in class name.
    */
   bool canCastToClassName(ossimObjectH fromObj,
                  ossimStringH parentClassName)
    {
         ossimObject* object = (ossimObject*)fromObj;
         ossimString* ClassName = (ossimString*)parentClassName;
         return object->canCastTo(*ClassName);
   }

   /*!
    * Method to save the state of the object to a keyword list.
    * Return true if ok or false on error.
    */
   bool saveState(ossimObjectH obj,
                  ossimKeywordlistH kwl,
                  const char* prefix) // = 0
    {
        ossimObject* object = (ossimObject*)obj;
        ossimKeywordlist* key = (ossimKeywordlist*)kwl;
        return object->saveState(*key, prefix);
    }

   /*!
    * Method to the load (recreate) the state of the object from a keyword
    * list.  Return true if ok or false on error.
    */
   bool loadState(ossimObjectH obj,
                  ossimKeywordlistH kwl,
                  const char* prefix) // =0
    {
        ossimObject* object = (ossimObject*)obj;
        ossimKeywordlist* key = (ossimKeywordlist*)kwl;
        return object->loadState(*key, prefix);
    }

