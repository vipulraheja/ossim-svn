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
// $Id: ossimQtSwipeScrollingImageWidget.cpp 15766 2009-10-20 12:37:09Z gpotts $
#include <qpainter.h>
#include <qpixmap.h>
#include <qimage.h>
#include "ossimQtSwipeScrollingImageWidget.h"
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimScalarRemapper.h>
#include <ossim/imaging/ossimCacheTileSource.h>
#include <ossim/imaging/ossimImageSourceSequencer.h>
#include "ossimQtEvent.h"


ossimQtSwipeScrollingImageWidget::ossimQtSwipeScrollingImageWidget(QWidget* parent,
                                                                   QString  name)
   :ossimQtScrollingImageWidget(parent, name),
    theSwipeType(ossimQtSwipeType_NONE)
{
   connect(this, SIGNAL(scrollingImageWidgetMouseEvent(ossimQtMouseEvent*)),
           this, SLOT(swipeWidgetMouseEvent(ossimQtMouseEvent*)));
   theBottomLayerRgbChain = new ossimImageChain;
   theBottomLayerRgbChain->addChild(new ossimScalarRemapper);
   theBottomLayerBackingStore.setTileSize(theTileSize);
   theLastRadius = -1;
   theLastMousePosition.makeNan();
}

ossimQtSwipeScrollingImageWidget::~ossimQtSwipeScrollingImageWidget ()
{
   theBottomLayerRgbChain->disconnect();
   
   theBottomLayerRgbChain = 0;
    theTopLayer.reset();
    theBottomLayer.reset();
}


void ossimQtSwipeScrollingImageWidget::setSwipeType(ossimQtSwipeType type)
{
   theSwipeType  = type;
   theLastRadius = -1;
   theLastMousePosition.makeNan();
}

void ossimQtSwipeScrollingImageWidget::setInputInformation()
{
   theBottomLayerRgbChain->disconnect();
   
   theBottomLayerBackingStore.flush();
   theBottomLayerRgbChain->connectMyInputTo(0, getInput(1));
   theBottomLayerRgbChain->initialize();
   ossimQtScrollingImageWidget::setInputInformation();
   theLastRadius = -1;
   theLastMousePosition.makeNan();
}

void ossimQtSwipeScrollingImageWidget::setInputInformation(const ossimIpt& pt)
{
   theBottomLayerRgbChain->disconnect();
   theBottomLayerBackingStore.flush();
   theTopLayer.reset();
   theBottomLayer.reset();
   theBottomLayerRgbChain->connectMyInputTo(0, getInput(1));
   theBottomLayerRgbChain->initialize();
   ossimQtScrollingImageWidget::setInputInformation(pt);
   theLastRadius = -1;
   theLastMousePosition.makeNan();
}

void ossimQtSwipeScrollingImageWidget::flushCache(bool repaintFlag)
{
   theBottomLayerBackingStore.flush();
   theTopLayer.reset();
   theBottomLayer.reset();
   ossimQtScrollingImageWidget::flushCache(repaintFlag);
   theLastRadius = -1;
   theLastMousePosition.makeNan();
}

void ossimQtSwipeScrollingImageWidget::refresh(const ossimIpt& pt,
                                               bool repaintFlag)
{
   theBottomLayerBackingStore.flush();
   theTopLayer.reset();
   theBottomLayer.reset();
   theLastRadius = -1;
   theLastMousePosition.makeNan();
   
   ossimQtScrollingImageWidget::refresh(pt, repaintFlag); 
}

void ossimQtSwipeScrollingImageWidget::refresh(bool repaintFlag)
{
   theBottomLayerBackingStore.flush();
   theTopLayer.reset();
   theBottomLayer.reset();
   theLastRadius = -1;
   theLastMousePosition.makeNan();
   
   ossimQtScrollingImageWidget::refresh(repaintFlag); 
}


void ossimQtSwipeScrollingImageWidget::convertRequest(const ossimIrect& reqRect)
{
   if((theBottomLayerRgbChain->getInput())&&
      (theSwipeType != ossimQtSwipeType_NONE))
   {
      ossimRefPtr<ossimImageData> data = theBottomLayerRgbChain->getTile(reqRect);
      
      QImage tempImage(theTileSize.x,
		       theTileSize.y,
		       32);
      if(data.valid() && data->getBuf())
        {
	  fillImage(data, &tempImage);
        }
        tempImage.setOffset(QPoint(theShiftToZeroZero.x + reqRect.ul().x,
                                   theShiftToZeroZero.y + reqRect.ul().y));
	
        theBottomLayerBackingStore.addTile(tempImage);
   }
   if(!theTopLayer.isNull())
    {
       theTopLayer.reset();
       theBottomLayer.reset();
    }
    ossimQtScrollingImageWidget::convertRequest(reqRect);
}

void ossimQtSwipeScrollingImageWidget::drawContents(QPainter* p, int clipx, int clipy, int clipw, int cliph)
{
   theTopLayer.reset();
   theBottomLayer.reset();
   theLastRadius = -1;
   theLastMousePosition.makeNan();
   ossimQtScrollingImageWidget::drawContents(p,
                                             clipx,
                                             clipy,
                                             clipw,
                                             cliph);
}


void ossimQtSwipeScrollingImageWidget::fillLayerBuffers()
{
   ossimIrect vRect = getViewportRect();
   vRect.stretchToTileBoundary(theTileSize);
//   ossimIrect shiftedVRect = vRect - theShiftToZeroZero;
   
   theTopLayer.create(vRect.width(), vRect.height(), 32);
   theBottomLayer.create(vRect.width(), vRect.height(), 32);
   QPixmap tempBuffer(theTopLayer);
   
   QPainter p(&tempBuffer);
   int x,y, w, h;
   w = vRect.width();
   h = vRect.height();
   for(y =0; y <= h; y+=theTileSize.y)
   {
      for(x=0; x < w;x+=theTileSize.x)
      {
         ossimIpt origin = ossimIpt(x,y)+vRect.ul();
         
	 theBackingStoreCache.getTile(origin, theImageBuffer);
	 p.drawImage(x, y, theImageBuffer);
      }
   }
   theTopLayer = tempBuffer.convertToImage();
   for(y =0; y <= h; y+=theTileSize.y)
   {
      for(x=0; x < w;x+=theTileSize.x)
      {
         ossimIpt origin = ossimIpt(x,y)+vRect.ul();
         
	 theBottomLayerBackingStore.getTile(origin, theImageBuffer);
	 p.drawImage(x, y, theImageBuffer);
      }
   }
   theBottomLayer = tempBuffer.convertToImage();
}


void ossimQtSwipeScrollingImageWidget::eraseCursor(QPainter* p)
{
   if(!getInput(0)||!getInput(1))
   {
      ossimQtScrollingImageWidget::eraseCursor(p);
      return;
   }
   
   if( theCursorDrawnFlag && (!theLastMousePosition.hasNans()) )
   {
      QImage& topCacheImage       = theBackingStoreCache.getCache();
      QImage& bottomCacheImage    = theBottomLayerBackingStore.getCache();
      ossimIrect topCacheRect     = theBackingStoreCache.getCacheRect();
      ossimIrect bottomCacheRect  = theBottomLayerBackingStore.getCacheRect();
      
      ossimIpt mousePosition = theCursorLocation;
      ossimIpt swipePosition = theLastMousePosition + theShiftToZeroZero;
      ossimIrect viewportRect = getViewportRect();
      ossimIpt ul = viewportRect.ul();
      ossimIpt lr = viewportRect.lr();
      
      // erase horizontal line
      
      switch(theSwipeType)
      {
         case ossimQtSwipeType_HORIZONTAL:
         {
            // erase vertical line
            if(mousePosition.x < swipePosition.x)
            {
               p->drawImage(mousePosition.x - ul.x,
                            0,
                            topCacheImage,
                            mousePosition.x     - topCacheRect.ul().x,
                            viewportRect.ul().y - topCacheRect.ul().y,
                            1,
                            viewportRect.height());
            }
            else
            {
               p->drawImage(mousePosition.x - ul.x,
                            0,
                            bottomCacheImage,
                            mousePosition.x     - bottomCacheRect.ul().x,
                            viewportRect.ul().y - bottomCacheRect.ul().y,
                            1,
                            viewportRect.height());
            }
            
            // erase horizontal
            
            if((mousePosition.y >= ul.y)&&
               (mousePosition.y <= lr.y))
            {
               p->drawImage(0,
                            mousePosition.y-ul.y,
                            topCacheImage,
                            ul.x - topCacheRect.ul().x,
                            mousePosition.y - topCacheRect.ul().y,
                            swipePosition.x - ul.x,
                            (int)1);
               
               p->drawImage(swipePosition.x - ul.x,
                            mousePosition.y - ul.y,
                            bottomCacheImage,
                            swipePosition.x - bottomCacheRect.ul().x,
                            mousePosition.y - bottomCacheRect.ul().y,
                            (int)swipePosition.x - (int)lr.x,
                            (int)1);
            }
            
            break;
         }
         case ossimQtSwipeType_VERTICAL:
         {
            // erase vertical line
            if((mousePosition.x >= ul.x)&&
               (mousePosition.x <= lr.x))
            {
               
               p->drawImage(mousePosition.x-ul.x,
                            0,
                            topCacheImage,
                            mousePosition.x - topCacheRect.ul().x,
                            viewportRect.ul().y - topCacheRect.ul().y,
                            (int)1,
                            swipePosition.y - ul.y);
               
               p->drawImage(mousePosition.x - ul.x,
                            swipePosition.y - ul.y,
                            bottomCacheImage,
                            mousePosition.x - bottomCacheRect.ul().x,
                            swipePosition.y - bottomCacheRect.ul().y,
                            (int)1,
                            (int)swipePosition.y - (int)lr.y);
            }
            
            // erase horizontal
            if(mousePosition.y < swipePosition.y)
            {
               // use top layer to erase mouse  
               p->drawImage(0,
                            mousePosition.y-ul.y,
                            topCacheImage,
                            ul.x - topCacheRect.ul().x,
                            mousePosition.y - topCacheRect.ul().y,
                            (int)viewportRect.width(),
                            (int)1);
            }
            else
            {
               // use bottom layer to erase
               p->drawImage(0,
                            mousePosition.y-ul.y,
                            bottomCacheImage,
                            ul.x - bottomCacheRect.ul().x,
                            mousePosition.y - bottomCacheRect.ul().y,
                            (int)viewportRect.width(),
                            (int)1);
               
            }
            break;
         }

         default:
            break;

      } // End of "switch(theSwipeType)"
      
      theCursorDrawnFlag = false;
   }
}


void ossimQtSwipeScrollingImageWidget::swipeWidgetMouseEvent(ossimQtMouseEvent* evt)
{
   if((theSwipeType == ossimQtSwipeType_NONE)||
      (!getInput(1)))
   {
      return;
   }
      
   if(isProcessingTiles())
   {
      if(!theTopLayer.isNull())
      {
         theTopLayer.reset();
         theBottomLayer.reset();
      }
      return;
   }
   else if(theTopLayer.isNull())
   {
      fillLayerBuffers();
   }

   switch(theSwipeType)
   {
   case ossimQtSwipeType_HORIZONTAL:
   {
      performHorizontalSwipe(evt);
      break;
   }
   case ossimQtSwipeType_VERTICAL:
   {
      performVerticalSwipe(evt);
      break;
   }
   case ossimQtSwipeType_BOX:
   {
      performBoxSwipe(evt);
      break;
   }
   case ossimQtSwipeType_CIRCLE:
   {
      performCircleSwipe(evt);
      break;
   }
   default:
   {
      break;
   }
   }
}

void ossimQtSwipeScrollingImageWidget::performHorizontalSwipe(ossimQtMouseEvent* evt)
{
   ossimIrect vRect = getAbsoluteViewportRect();
   ossimIpt       mousePoint = evt->getShiftPoint();

   ossimIrect viewportRect = vRect;
   vRect.stretchToTileBoundary(theTileSize);
   int leftWidth = mousePoint.x - vRect.ul().x;
   if(leftWidth < 0) leftWidth = 0;
   if(leftWidth > (int)vRect.width()) leftWidth = vRect.width();
   int rightWidth = vRect.width() - leftWidth;
   
   ossimIpt image1Offset( vRect.ul().x - viewportRect.ul().x,
                          vRect.ul().y - viewportRect.ul().y);
   QPainter p(viewport());

   if(theLastMousePosition.hasNans())
   {
   
      p.drawImage(image1Offset.x, image1Offset.y,
                  theTopLayer,
                  0, 0, leftWidth);
      
      p.drawImage(image1Offset.x+leftWidth, image1Offset.y,
                  theBottomLayer,
                  leftWidth, 0, rightWidth);
   }
   else
   {
      int dirtyWidth = abs(theLastMousePosition.x - mousePoint.x);
      // need to add the bottom layer
      if(theLastMousePosition.x > mousePoint.x)
      {
         p.drawImage(image1Offset.x+leftWidth, image1Offset.y,
                     theBottomLayer,
                     leftWidth, 0, dirtyWidth);
      }
      else // need to add the top layer
      {
         p.drawImage(image1Offset.x+leftWidth-dirtyWidth, image1Offset.y,
                     theTopLayer,
                     leftWidth-dirtyWidth, 0, dirtyWidth);
      }
   }
   theLastMousePosition = mousePoint;
}

void ossimQtSwipeScrollingImageWidget::performVerticalSwipe(ossimQtMouseEvent* evt)
{
   ossimIrect vRect = getAbsoluteViewportRect();
   ossimIpt       mousePoint = evt->getShiftPoint();

   ossimIrect viewportRect = vRect;
   vRect.stretchToTileBoundary(theTileSize);
   int topHeight = mousePoint.y - vRect.ul().y;
   if(topHeight < 0) topHeight = 0;
   if(topHeight > (int)vRect.height()) topHeight = vRect.height();
   int bottomHeight = vRect.height() - topHeight;
   
   ossimIpt image1Offset( vRect.ul().x - viewportRect.ul().x,
                          vRect.ul().y - viewportRect.ul().y);
   QPainter p(viewport());

   if(theLastMousePosition.hasNans())
   {
      
      p.drawImage(image1Offset.x, image1Offset.y,
                  theTopLayer,
                  0, 0, -1, topHeight);
      
      p.drawImage(image1Offset.x, image1Offset.y+topHeight,
                  theBottomLayer,
                  0, topHeight, -1, bottomHeight);
   }
   else
   {
      int dirtyHeight = abs(theLastMousePosition.y - mousePoint.y);
      // need to add the bottom layer
      if(theLastMousePosition.y > mousePoint.y)
      {
         p.drawImage(image1Offset.x, image1Offset.y+topHeight,
                     theBottomLayer,
                     0, topHeight, -1, dirtyHeight);
      }
      else // need to add the top layer
      {
         p.drawImage(image1Offset.x, image1Offset.y+topHeight-dirtyHeight,
                     theTopLayer,
                     0, topHeight-dirtyHeight, -1, dirtyHeight);
      }
   }
   theLastMousePosition = mousePoint;
}

void ossimQtSwipeScrollingImageWidget::performBoxSwipe(ossimQtMouseEvent* evt)
{
   ossimIrect vRect = getAbsoluteViewportRect();
   ossimIpt       mousePoint = evt->getShiftPoint();

   ossimIrect viewportRect = vRect;
   vRect.stretchToTileBoundary(theTileSize);
   
   ossimIpt midPoint = viewportRect.midPoint();
   ossimIpt delta = midPoint - mousePoint;
   
   int radius = (int)ossim::max(abs(delta.x), abs(delta.y));
   radius = 2*radius;
   ossimIpt visibleUl = midPoint - ossimIpt(radius>>1,
                                            radius>>1);
   ossimIrect visibleBottomLayerRect(visibleUl.x,
                                     visibleUl.y,
                                     visibleUl.x+radius,
                                     visibleUl.y+radius);


   ossimIpt image1Offset( vRect.ul().x - viewportRect.ul().x,
                          vRect.ul().y - viewportRect.ul().y);
   
   int leftWidth    = visibleBottomLayerRect.ul().x - vRect.ul().x;
   int topHeight    = visibleBottomLayerRect.ul().y - vRect.ul().y;
   
   if(leftWidth < 0) leftWidth = 0;
   if(topHeight < 0) topHeight = 0;

   QPainter p(viewport());
   
   if(theLastRadius == -1)
   {
      p.drawImage(image1Offset.x, image1Offset.y,
                  theTopLayer,
                  0, 0);
   }
   else
   {
      if(theLastRadius > radius)
      {
         int deltaRadius = theLastRadius - radius;
         p.drawImage(image1Offset.x+leftWidth-deltaRadius, image1Offset.y+topHeight-deltaRadius,
                     theTopLayer,
                     leftWidth-deltaRadius, topHeight-deltaRadius, radius+2*deltaRadius, radius+2*deltaRadius);
      }
   }
   p.drawImage(image1Offset.x+leftWidth, image1Offset.y+topHeight,
               theBottomLayer,
               leftWidth, topHeight, radius, radius);
   
   theLastRadius = radius;
}

void ossimQtSwipeScrollingImageWidget::performCircleSwipe(ossimQtMouseEvent* /*evt*/)
{
}

void ossimQtSwipeScrollingImageWidget::disconnectInputEvent(ossimConnectionEvent& event)
{
   ossimQtScrollingImageWidget::disconnectInputEvent(event);
   theRgbChain->disconnect();
}

void ossimQtSwipeScrollingImageWidget::viewportMoving(int x, int y)
{
  ossimQtScrollingImageWidget::viewportMoving(x, y);

  QSize framesize = viewport()->frameSize();

  theBottomLayerBackingStore.setRect(ossimIrect(x, 
						y, 
						x + framesize.width()-1, 
						y + framesize.height()-1));
}

void ossimQtSwipeScrollingImageWidget::viewportResizeEvent(QResizeEvent* event)
{

  int newW = event->size().width();
  int newH = event->size().height();
  if(newW < 1)
    {
      newW = 1;
    }
  if(newH < 1)
    {
      newH = 1;
    }
  
  ossimIrect cacheRect = theBottomLayerBackingStore.getCacheRect();

  theBottomLayerBackingStore.setRect(ossimIrect(cacheRect.ul().x,
						cacheRect.ul().y,
						cacheRect.ul().x + newW - 1,
						cacheRect.ul().y + newH - 1));

  ossimQtScrollingImageWidget::viewportResizeEvent(event);
}
