//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// OSSIM is free software; you can redistribute it and/or
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
// Author: Garrett Potts (gpotts@imagelinks.com)
//
//*************************************************************************
// $Id: ossimQtVceImageSourceObject.cpp 15766 2009-10-20 12:37:09Z gpotts $
#include <qpainter.h>
#include "ossimQtVceImageSourceObject.h"
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimScalarRemapper.h>
#include <ossim/imaging/ossimImageData.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimKeywordNames.h>

ossimQtVceImageSourceObject::ossimQtVceImageSourceObject(QCanvas* canvas,
                                                         QObject* vceParent)
: ossimQtVceConnectableObject(canvas,
                              vceParent)
{
}

ossimQtVceImageSourceObject::ossimQtVceImageSourceObject(const QRect& bounds,
                                                         QCanvas* canvas,
                                                         QObject* vceParent)
: ossimQtVceConnectableObject(canvas,
                              vceParent)
{
   setX(bounds.x());
   setY(bounds.y());
   theWidth  = bounds.width();
   theHeight = bounds.height();
}

int ossimQtVceImageSourceObject::rtti()const
{
   return ossimQtVceShapeRttiType_IMAGE_SOURCE;
}

void ossimQtVceImageSourceObject::setPreviewEnableFlag(bool flag)
{
   thePreviewEnableFlag = flag;
}

void ossimQtVceImageSourceObject::updatePreview()
{
   if(thePreviewEnableFlag&&theConnectableObject.valid())
   {
      setPreview();
   }
}

void ossimQtVceImageSourceObject::drawShape(QPainter& painter )
{
   QRect rect;
   getValidDrawingArea(rect);
   painter.drawRect(rect);
   if(thePreviewEnableFlag)
   {
      painter.drawImage((int)rect.x(),
                        (int)rect.y(),
                        theImage);
   }
}

QRect ossimQtVceImageSourceObject::boundingVceShapeRect()const
{
   int pw = (pen().width()+1)/2;
   if ( pw < 1 ) pw = 1;
   
   int ulx = (int)x() - pw;
   int uly = (int)y() - pw;
   
   QRect result( ulx, uly,
                theWidth +pen().width(),
                theHeight+pen().width());
   
   return result;
}

void ossimQtVceImageSourceObject::setPreview()
{
   ossimImageSource* inter = PTR_CAST(ossimImageSource,
                                      theConnectableObject.get());
   if(inter)
   {
      ossimIrect bounds = inter->getBoundingRect();
      int resLevel = 0;
      if(!bounds.hasNans())
      {
         int minThisWH = (theWidth > theHeight)?theHeight:theWidth;
         int levels = inter->getNumberOfDecimationLevels();
         bool found = false;
         for(int i = 0; ((i < levels)&&(!found)); ++i)
         {
            ossimIrect levelBounds = inter->getBoundingRect(i);
            if(!levelBounds.hasNans())
            {
               resLevel = i;
               int maxSize = ossim::max(levelBounds.width(), levelBounds.height());
               
               if(maxSize <= minThisWH)
               {
                  bounds = levelBounds;
                  found = true;
               }
            }
         }
      }
      ossimImageSource* startInter = inter;
      ossimRefPtr<ossimScalarRemapper> remapper = NULL;
      if(inter->getOutputScalarType() != OSSIM_UCHAR)
      {
         remapper = new ossimScalarRemapper;
         
         remapper->connectMyInputTo(theConnectableObject.get());
         startInter = remapper.get();
      }
      QRect drawingRect;
      getValidDrawingArea(drawingRect);
      
      if(theImage.isNull() ||
         (theImage.width() != drawingRect.width())||
         (theImage.height() != drawingRect.height()))
      {
         theImage.create(drawingRect.width(),
                         drawingRect.height(),
                         32);
      }
      ossimIpt midPt = bounds.midPoint();
      ossimIpt ulPt(midPt.x - drawingRect.width()/2,
                    midPt.y - drawingRect.height()/2);
      
      ossimIrect requestRect(ulPt.x ,
                             ulPt.y,
                             ulPt.x + drawingRect.width()-1,
                             ulPt.y + drawingRect.height()-1);
      
      ossimRefPtr<ossimImageData> data = startInter->getTile(requestRect,
                                                             resLevel);
      if(data.valid() && data->getBuf())
      {
         fillImage(data, &theImage);
      }
      else
      {
         theImage.fill(0);
      }
      
      if(remapper.valid())
      {
         remapper->disconnect();
         remapper = 0;
      }
   }
   else
   {
      if(!theImage.isNull())
      {
         theImage.fill(0);
      }
   }
}

void ossimQtVceImageSourceObject::fillImage(ossimRefPtr<ossimImageData>& data,
                                            QImage* tempImage)
{
   if(data.valid() && data->getBuf() && !tempImage->isNull())
   {
      ossim_uint8* buf[3];
      int numberOfBands = data->getNumberOfBands();
      int aWidth        = tempImage->size().width();
      int aHeight       = tempImage->size().height();
      int maxPixels     = aWidth*aHeight;
      int offset;
      
      if(numberOfBands >= 3)
      {
         buf[0] = static_cast<ossim_uint8*>(data->getBuf(0));
         buf[1] = static_cast<ossim_uint8*>(data->getBuf(1));
         buf[2] = static_cast<ossim_uint8*>(data->getBuf(2));
      }
      else 
      {
         buf[0] = static_cast<ossim_uint8*>(data->getBuf(0));
         buf[1] = static_cast<ossim_uint8*>(data->getBuf(0));
         buf[2] = static_cast<ossim_uint8*>(data->getBuf(0));
      }
      QRgb *bits = (QRgb*)tempImage->bits();
      if(tempImage->bits())
      {
         for(offset = 0; offset < maxPixels;++offset)
         {
            *bits = qRgb(*buf[0], *buf[1], *buf[2]);
            ++buf[0];++buf[1];++buf[2];
            ++bits;
         }
      }
      else
      {
         tempImage->fill(0);
      }
   }
   else
   {
      tempImage->fill(0);
   }
}

void ossimQtVceImageSourceObject::internalInputConnectionChanged()
{
   updatePreview();
   if(isVisible())
   {
      update();
   }
}

void ossimQtVceImageSourceObject::internalRefresh()
{
   updatePreview();
   if(isVisible())
   {
      update();
   }
}

void ossimQtVceImageSourceObject::internalProperty()
{
   updatePreview();
   if(isVisible())
   {
      update();
   }
}


bool ossimQtVceImageSourceObject::saveState(ossimKeywordlist& kwl,
                                            const char* prefix)const
{
   ossimQtVceConnectableObject::saveState(kwl, prefix);
   
   kwl.add(prefix,
           ossimKeywordNames::TYPE_KW,
           "ossimQtVceImageSourceObject",
           true);
   kwl.add(prefix,
           "preview_enabled",
           thePreviewEnableFlag,
           true);
   
   return true;
}

bool ossimQtVceImageSourceObject::loadState(const ossimKeywordlist& kwl,
                                            const char* prefix)
{
   ossimQtVceConnectableObject::loadState(kwl, prefix);
   const char* previewEnabled = kwl.find(prefix, "preview_enabled");
   
   if(previewEnabled)
   {
      thePreviewEnableFlag = ossimString(previewEnabled).toBool();
      updatePreview();
   }
   
   return true;
}
