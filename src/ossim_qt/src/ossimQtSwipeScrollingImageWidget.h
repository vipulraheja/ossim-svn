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
// $Id: ossimQtSwipeScrollingImageWidget.h 15766 2009-10-20 12:37:09Z gpotts $
#ifndef ossimQtSwipeScrollingImageWidget_HEADER
#define ossimQtSwipeScrollingImageWidget_HEADER
#include "ossimQtScrollingImageWidget.h"
class ossimQtMouseEvent;

class ossimQtSwipeScrollingImageWidget : public ossimQtScrollingImageWidget
{
   Q_OBJECT
   Q_ENUMS(ossimQtSwipeType)
   Q_PROPERTY( ossimQtSwipeType swipeType READ swipeType WRITE setSwipeType )
public:
   enum ossimQtSwipeType
      {
         ossimQtSwipeType_NONE = 0,
         ossimQtSwipeType_HORIZONTAL,
         ossimQtSwipeType_VERTICAL,
         ossimQtSwipeType_BOX,
         ossimQtSwipeType_CIRCLE
      };
   
   ossimQtSwipeScrollingImageWidget(QWidget* parent,
                                    QString  name);
   virtual ~ossimQtSwipeScrollingImageWidget();
   ossimQtSwipeType swipeType()const
      {
         return theSwipeType;
      }
   void setSwipeType(ossimQtSwipeType type);
   virtual void refresh(const ossimIpt& pt, bool repaintFlag=true);
   virtual void refresh(bool repaintFlag=true);
   virtual void flushCache(bool repaintFlag);
   virtual void disconnectInputEvent(ossimConnectionEvent& event);
  virtual void viewportResizeEvent(QResizeEvent* event);

protected:
   ossimQtSwipeType    theSwipeType;
   ossimRefPtr<ossimImageChain>    theBottomLayerRgbChain;
   QImage              theTopLayer;
   QImage              theBottomLayer;
   ossimQtStaticTileImageCache theBottomLayerBackingStore;
   ossimIpt            theLastMousePosition;
   int                 theLastRadius;
   virtual void setInputInformation();
   virtual void setInputInformation(const ossimIpt& pt);
   virtual void convertRequest(const ossimIrect& reqRect);
   virtual void fillLayerBuffers();
   virtual void drawContents(QPainter* p, int clipx, int clipy, int clipw, int cliph);

   virtual void eraseCursor(QPainter* p);

   
   virtual void performHorizontalSwipe(ossimQtMouseEvent* evt);
   virtual void performVerticalSwipe(ossimQtMouseEvent* evt);
   virtual void performBoxSwipe(ossimQtMouseEvent* evt);
   virtual void performCircleSwipe(ossimQtMouseEvent* evt);

protected slots:
   virtual void viewportMoving(int x, int y);
  
public slots:
   void swipeWidgetMouseEvent(ossimQtMouseEvent* evt);

};

#endif
