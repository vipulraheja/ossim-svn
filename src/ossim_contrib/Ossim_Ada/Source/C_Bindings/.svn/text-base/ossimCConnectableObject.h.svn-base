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
#ifndef ossimCConnectableObject_HEADER
#define ossimCConnectableObject_HEADER
#include "ossimCObject.h"

typedef void* ossimConnectableObjectH;
#ifdef __cplusplus
extern "C"
{
#endif

   ossimConnectableObjectH castObjectToConnectableObject(ossimObjectH obj);

   void ossimConnectObjects(ossimObjectH leftObject, ossimObjectH rightObject);
   void ossimConnectObject(ossimObjectH leftObject,
                           ossimObjectH rightObject,
                           int idxRightObjectSlot);

   /*!
    * Will try to connect this objects input to the passed in object.
    * It will return a valid index >= 0 if successful.  Will use the
    * getMyInputIndexToConnectTo method to implement the connection
    */
   ossim_int32 connectMyInputTo(ossimObjectH outObject,
                    ossimConnectableObjectH inputObject,
                    bool makeOutputConnection,
                    bool createEventFlag);

   /*!
    * Will connect the specified input to the passed in object
    */
    ossim_int32 connectMyInputToIndex(ossimObjectH outObject,
                                 ossim_int32 inputIndex,
                                 ossimConnectableObjectH inputObject,
                                 bool makeOutputConnection,
                                 bool createEventFlag);

#ifdef __cplusplus
}
#endif
#endif
