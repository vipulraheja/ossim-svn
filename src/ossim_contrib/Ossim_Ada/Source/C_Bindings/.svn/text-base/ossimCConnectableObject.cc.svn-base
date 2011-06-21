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
#include "ossimCConnectableObject.h"
#include "base/common/ossimConnectableObject.h"

ossimConnectableObjectH castObjectToConnectableObject(ossimObjectH obj)
{
   return (ossimConnectableObjectH)PTR_CAST(ossimConnectableObject,
                                            (ossimObject*)obj);
}

void ossimConnectObjects(ossimObjectH leftObject,
                         ossimObjectH rightObject)
{
   ossimConnectableObject* connectable1 = PTR_CAST(ossimConnectableObject,
                                                   (ossimObject*)leftObject);
   
   ossimConnectableObject* connectable2 = PTR_CAST(ossimConnectableObject,
                                                   (ossimObject*)rightObject);
   if(connectable1&&connectable2)
   {
      connectable1->connectMyInputTo(connectable2);
   }
}

void ossimConnectObject(ossimObjectH leftObject,
                        ossimObjectH rightObject,
                        int idxRightObjectSlot)
{
   ossimConnectableObject* connectable1 = PTR_CAST(ossimConnectableObject,
                                                   (ossimObject*)leftObject);
   
   ossimConnectableObject* connectable2 = PTR_CAST(ossimConnectableObject,
                                                   (ossimObject*)rightObject);
   if(connectable1&&connectable2)
   {
      connectable1->connectMyInputTo(idxRightObjectSlot, connectable2);
   }
}

ossim_int32 connectMyInputTo(ossimObjectH outObject,
                    ossimConnectableObjectH inputObject,
                    bool makeOutputConnection,
                    bool createEventFlag)
{
    ossimConnectableObject* connectable1 = PTR_CAST(ossimConnectableObject,
                                    (ossimObject*)outObject);
    ossimConnectableObject* connectable2 = PTR_CAST(ossimConnectableObject,
                                                   (ossimObject*)inputObject);

    return connectable1->connectMyInputTo(connectable2,
                makeOutputConnection, createEventFlag);
}

ossim_int32 connectMyInputToIndex(ossimObjectH outObject,
                                ossim_int32 inputIndex,
                                ossimConnectableObjectH inputObject,
                                bool makeOutputConnection,
                                bool createEventFlag)
{
    ossimConnectableObject* connectable1 = PTR_CAST(ossimConnectableObject,
                                    (ossimObject*)outObject);
    ossimConnectableObject* connectable2 = PTR_CAST(ossimConnectableObject,
                                                   (ossimObject*)inputObject);

    return connectable1->connectMyInputTo(inputIndex, connectable2,
                makeOutputConnection, createEventFlag);
}

