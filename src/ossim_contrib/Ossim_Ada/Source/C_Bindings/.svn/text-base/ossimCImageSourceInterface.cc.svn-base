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
#include "ossimCImageSourceInterface.h"
#include "ossimCIRect.h"
#include "base/common/ossimRtti.h"
#include "base/common/ossimObject.h"
#include "imaging/ossimImageSourceInterface.h"


ossimImageSourceInterfaceH ossimCastObjectToImageSourceInterface(ossimObjectH obj)
{
   ossimObject* tempObj = (ossimObject*)obj;
   return PTR_CAST(ossimImageSourceInterface,
                   tempObj);
   
}

ossimIrectH getNewBoundingRect(ossimImageSourceInterfaceH inter,
                               unsigned long int resLevel)
{
   if(inter)
   {
      ossimIrect rect = ((ossimImageSourceInterface*)inter)->getBoundingRect(resLevel);

      return ossimCreateIrectFromIrect((ossimIrectH)(&rect));
   }
   return (ossimIrectH)NULL;
}


ossimImageDataH ossimGetTile(ossimImageSourceInterfaceH inter,
                             ossimIrectH rect,
                             unsigned long int resLevel)
{
   ossimImageSourceInterface* tempInterface = (ossimImageSourceInterface*)inter;

   if(tempInterface)
   {
      return (ossimImageDataH)tempInterface->getTile(*((ossimIrect*)rect),
                                                     resLevel);
   }
   return (ossimImageDataH)NULL;
}
