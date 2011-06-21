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
// $Id: ossimQtVceCanvasWidget.cpp 18289 2010-10-20 12:31:38Z dburken $
#include <sstream>
#include <algorithm>
#include <qapplication.h>
#include <qclipboard.h>
#include <qdragobject.h>
#include <qfiledialog.h>
#include <qrect.h>
#include <ossimQtProgressDialog.h>
#include <qmessagebox.h>
#include "ossimQtVceCanvasWidget.h"
#include "ossimQtVceImageSourceObject.h"
#include "ossimQtVceImageDisplayObject.h"
#include "ossimQtVceShapeRect.h"
#include "ossimQtVceConnectionObject.h"
#include "ossimQtVceImageHandlerObject.h"
#include "ossimQtVceCanvasContainerUtility.h"
#include "ossimQtEvent.h"
#include "ossimQtApplicationUtility.h"
#include "ossimDataManager.h"
#include "ossimQtPropertyDialog.h"
#include "ossimQtPropertyDialogController.h"
#include "ossimQWidgetFactoryRegistry.h"
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimKeywordNames.h>
#include <ossim/base/ossimProcessInterface.h>
#include <ossim/base/ossimObjectFactoryRegistry.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageChain.h>

ossimQtVceCanvasWidget::ossimQtVceCanvasWidget(QWidget* parent, 
                                               QString name)
   :QCanvasView(parent, name)
{
   theSelectionRect    = NULL;
   theLineObject       = NULL;
   theMouseButtonState = Qt::NoButton;
   setAcceptDrops(true);
   theCanvasUtility = new ossimQtVceCanvasContainerUtility(this);
   thePopupMenu = new QPopupMenu(this);
   thePopupMenu->hide();
   thePopupMenu->clear();
   thePopupMenu->insertItem("Copy", this, SLOT(copySelected()));
   thePopupMenu->insertItem("Paste", this, SLOT(paste()));
   thePopupMenu->insertItem("Cut", this, SLOT(cutSelected()));
   thePopupMenu->insertSeparator();
   thePopupMenu->insertItem("Execute", this, SLOT(executeSelected()));
}

ossimQtVceCanvasWidget::~ossimQtVceCanvasWidget ()
{
   if(theCanvasUtility)
   {
      theCanvasUtility = NULL;
   }
}

void ossimQtVceCanvasWidget::resizeContents ( int w, int h )
{
   QScrollView::resizeContents(w, h);

   canvas()->resize(w, h);
}

ossimQtVceConnectableObject* ossimQtVceCanvasWidget::getObjectWhereConnectableSlotIntersectsPoint(QCanvasItemList& itemList,
                                                                                                  const QPoint& pt)
{
   for(int idx = 0; idx < (int)itemList.size(); ++idx)
   {
      ossimQtVceShape* vceShape = ossimQtVceShape::castToVceShape(itemList[idx]);
      
      if(vceShape)
      {
         ossimQtVceConnectableObject* connectable = vceShape->castToConnectable();
         
         if(connectable)
         {
            if((connectable->hitInputConnection(pt) > -1)||
               (connectable->hitOutputConnection(pt) > -1))
            {
               return connectable;
            }
         }
      }
   }
   
   return (ossimQtVceConnectableObject*)NULL;
}

void ossimQtVceCanvasWidget::contentsMousePressEvent(QMouseEvent * e )
{
   theMouseButtonState = e->button();
   
   switch(e->button())
   {
   case Qt::LeftButton:
   {
      theLeftDownFlag = true;
      deleteSelectionRect();
      theMouseStartPt = QPoint(e->x(),
                               e->y());
      theSelectionRect = new ossimQtVceShapeRect(QRect(e->x(),
                                                       e->y(),
                                                       1,
                                                       1),
                                                 canvas());
      // make sure that the selection rect is in front of everything
      //
      theSelectionRect->setZ(2);
      
      if(!intersectsSelection())
      {
         
         unselectItems();

         // initialize mode
         //
         QCanvasItemList collisionList    = theSelectionRect->collisions(true);
         ossimQtVceConnectableObject* obj = getObjectWhereConnectableSlotIntersectsPoint(collisionList,
                                                                                         theMouseStartPt);
         if(obj)
         {
            QRect rect;
            if(obj->getConnectionSlotBoundingRect(rect,
                                                  theMouseStartPt))
            {
               delete theSelectionRect;
               theSelectionRect = NULL;
               theLineObject = new QCanvasLine(canvas());
               QPoint startPt(rect.x() + rect.width()/2,
                              rect.y() + rect.height()/2);
               theLineObject->setPoints(startPt.x(),
                                        startPt.y(),
                                        theMouseStartPt.x(),
                                        theMouseStartPt.y());
               theLineObject->setPen(QPen(QColor(0,0,0), 2, Qt::DotLine));
               theLineObject->show();
            }
         }

         if(theSelectionRect)
         {
            // now set the pen style to dashed
            //
            theSelectionRect->hide();
            theSelectionRect->setPen(QPen(QColor(0,0,0), 2, Qt::DotLine));
            theSelectionRect->show();
         }
      }
      else
      {
         deleteSelectionRect();
      }
      
      break;
   }
   case Qt::RightButton:
     {
       thePopupMenu->hide();
       QPoint pt = mapToGlobal(pos());
       thePopupMenu->popup(e->globalPos());
     }
   default:
     {
       break;
     }
   }
   
   emit canvasWidgetMousePressEvent(e);
}

void ossimQtVceCanvasWidget::contentsMouseReleaseEvent(QMouseEvent * e )
{
   theMouseButtonState = e->button();
   
   switch(e->button())
   {
   case Qt::LeftButton:
   {
      if(theSelectionRect)
      {
         QCanvasItemList collisionList = theSelectionRect->collisions(true);
         selectItems(collisionList);
         deleteSelectionRect();
      }
      else if(theLineObject)
      {
        ossimQtVceShapeRect  startRect(QRect(theLineObject->startPoint().x(),
                                             theLineObject->startPoint().y(),
                                             1,
                                             1),
                                       canvas());
        ossimQtVceShapeRect  endRect(QRect(theLineObject->endPoint().x(),
                                           theLineObject->endPoint().y(),
                                           1,
                                           1),
                                     canvas());
        
         // make sure that the selection rect is in front of everything
         //
         startRect.setZ(1);
         endRect.setZ(1);
         
         QCanvasItemList startList = startRect.collisions(true);
         QCanvasItemList endList   = endRect.collisions(true);
         QPoint startPt            = theLineObject->startPoint();
         QPoint endPt              = theLineObject->endPoint();
         
         ossimQtVceConnectableObject* startObj = getObjectWhereConnectableSlotIntersectsPoint(startList,
                                                                                              startPt);
         ossimQtVceConnectableObject* endObj   = getObjectWhereConnectableSlotIntersectsPoint(endList,
                                                                                              endPt);
         if(startObj&&endObj)
         {
            makeConnection(startObj, startPt, endObj, endPt);
         }
         delete theLineObject;
         theLineObject = NULL;
      }
      break;
   }
   default:
     {
       break;
     }
   }
   theMouseButtonState = Qt::NoButton;      
   emit canvasWidgetMouseReleaseEvent(e);
}

void ossimQtVceCanvasWidget::contentsMouseDoubleClickEvent (QMouseEvent * e )
{
   if(theSelectedItems.size() == 1)
   {
      ossimQtVceShape* vceShape = ossimQtVceShape::castToVceShape(theSelectedItems[0]);
      if(vceShape)
      {
         ossimQtVceConnectableObject* connectableObject = vceShape->castToConnectable();

         if(connectableObject)
         {
            ossimQtPropertyDialog* dialog = (ossimQtPropertyDialog*)ossimQWidgetFactoryRegistry::instance()->createEditor(connectableObject->getConnectableObject(), this);

            if (dialog)
            {
               dialog->show();
            }
         }
      }
   }
   emit canvasWidgetMouseDoubleClickEvent(e);
}

void ossimQtVceCanvasWidget::contentsMouseMoveEvent(QMouseEvent * e )
{
   if(theSelectionRect)
   {
      int x1 = e->x();
      int y1 = e->y();
      int x2 = theMouseStartPt.x();
      int y2 = theMouseStartPt.y();

      int minX = std::min(x1, x2);
      int maxX = std::max(x1, x2);
      int minY = std::min(y1, y2);
      int maxY = std::max(y1, y2);

      
      theSelectionRect->hide();
      theSelectionRect->setX(minX);
      theSelectionRect->setY(minY);
      theSelectionRect->setSize((maxX - minX)+1,
                                (maxY- minY)+1);
      theSelectionRect->show();
      
   }
   else if(theLineObject)
   {
      theLineObject->setPoints(theMouseStartPt.x(),
                               theMouseStartPt.y(),
                               e->x(),
                               e->y());
   }
   else if(theMouseButtonState == Qt::LeftButton)
   {
      moveSelectedBy(e->x() - theMouseStartPt.x(),
                     e->y() - theMouseStartPt.y());
      
      theMouseStartPt = QPoint(e->x(),
                               e->y());
   }
   emit canvasWidgetMouseMoveEvent(e);
}

void ossimQtVceCanvasWidget::getSelectedItems(std::vector<QCanvasItem*>& selectedItems)const
{
   selectedItems = theSelectedItems;
}

void ossimQtVceCanvasWidget::unselectItems()
{
   for(int idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
      theSelectedItems[idx]->setSelected(false);
   }
   
   theSelectedItems.clear();
}

bool ossimQtVceCanvasWidget::hasSelectedItems()const
{
   return (theSelectedItems.size() > 0);
}

void ossimQtVceCanvasWidget::deleteSelectionRect()
{
   if(theSelectionRect)
   {
      delete theSelectionRect;
      theSelectionRect = NULL;
   }
}

void ossimQtVceCanvasWidget::selectItems(QCanvasItemList& selectionList)
{
   if(selectionList.size())
   {
      for(int idx = 0; idx < (int)selectionList.size(); ++idx)
      {
         theSelectedItems.push_back(selectionList[idx]);
         selectionList[idx]->setSelected(true);
         emit itemSelected(selectionList[idx]);
      }
   }
}

void ossimQtVceCanvasWidget::moveSelectedBy(int dx, int dy)
{
   for(int idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
     if(theSelectedItems[idx]->rtti() != ossimQtVceShapeRttiType_CONNECTION)
       {
	 theSelectedItems[idx]->moveBy(dx, dy);
       }
   }
}

bool ossimQtVceCanvasWidget::intersectsSelection()const
{
   if(theSelectionRect)
   {
      for(int idx = 0; idx < (int)theSelectedItems.size(); ++idx)
      {
         if(theSelectionRect->collidesWith(theSelectedItems[idx]))
         {
            return true;
         }
      }
   }

   return false;
}


void ossimQtVceCanvasWidget::alignSelectedToTop()
{
   int minY = 9999999;
   int idx;
   if(theSelectedItems.size() < 2) return;
   
   for(idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
      if(theSelectedItems[idx]->y() < minY)
      {
         minY = (int)theSelectedItems[idx]->y();
      }
   }
   for(idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
      theSelectedItems[idx]->setY(minY);
   }
}

void ossimQtVceCanvasWidget::alignSelectedToBottom()
{
   int maxY = -9999999;
   int idx;
   if(theSelectedItems.size() < 2) return;
   
   for(idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
      QRect bounds = theSelectedItems[idx]->boundingRect();
      
      if(bounds.bottom() > maxY)
      {
         maxY = bounds.bottom();
      }
   }
   for(idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
      QRect bounds = theSelectedItems[idx]->boundingRect();
      theSelectedItems[idx]->moveBy(0,
                                    maxY - bounds.bottom());
   }
}

void ossimQtVceCanvasWidget::alignSelectedToLeft()
{
   int minX = 9999999;
   int idx;
   if(theSelectedItems.size() < 2) return;
   
   for(idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
      if(theSelectedItems[idx]->x() < minX)
      {
         minX = (int)theSelectedItems[idx]->x();
      }
   }
   for(idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
      theSelectedItems[idx]->setX(minX);
   }
}

void ossimQtVceCanvasWidget::alignSelectedToRight()
{
   int maxX = -9999999;
   int idx;
   if(theSelectedItems.size() < 2) return;
   
   for(idx = 0; idx < (int)theSelectedItems.size(); ++idx) 
   {
      QRect bounds = theSelectedItems[idx]->boundingRect();
      
      if(bounds.right() > maxX)
      {
         maxX = bounds.right();
      }
   }
   for(idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
      QRect bounds = theSelectedItems[idx]->boundingRect();
      theSelectedItems[idx]->moveBy(maxX - bounds.right(),
                                    0);
   }
}

void ossimQtVceCanvasWidget::selectAll()
{
   unselectItems();
   QCanvasItemList canvasItemList = canvas()->allItems();
   selectItems(canvasItemList);
}


void ossimQtVceCanvasWidget::cutSelected()
{
   if(theSelectedItems.size())
   {
      // before we delete copy to clipboard.
      // so they can re-paste if needed
      //
      copySelected();

      deleteAllAssociatedConnections(theSelectedItems);
      
      for(int idx = 0; idx < (int)theSelectedItems.size(); ++idx)
      {
	 emit itemDeleting(theSelectedItems[idx]);
	 theSelectedItems[idx]->hide();
	 delete theSelectedItems[idx];
      }
   }
   
   theSelectedItems.clear();
}

void ossimQtVceCanvasWidget::copySelected()
{
   ossimKeywordlist kwl;
   if(theSelectedItems.size())
   {
      if(theCanvasUtility->copySelectedToKeywordlist(kwl))
      {
         kwl.add(ossimKeywordNames::TYPE_KW,
                 "ossimQtVceCanvasWidget",
                 true);
         std::stringstream s;
         
         s<<kwl<<std::ends;
         QClipboard* cb = QApplication::clipboard();
         
         if(cb)
         {
            cb->setText(s.str().c_str());
         }
      }
   }
}

void ossimQtVceCanvasWidget::paste()
{
   QClipboard* cb = QApplication::clipboard();

   if(cb)
   {
      std::stringstream s(cb->text().ascii());
      ossimKeywordlist kwl;

      if(kwl.parseStream(s))
      {
         const char* type = kwl.find(ossimKeywordNames::TYPE_KW);
         if(ossimString(type) == "ossimQtVceCanvasWidget")
         {
            theCanvasUtility->copyFromKeywordlist(kwl);
         }
      }
   }
}

void ossimQtVceCanvasWidget::executeSelected()
{
   for(int idx = 0; idx < (int)theSelectedItems.size(); ++idx)
   {
     ossimQtVceShape* shape = dynamic_cast<ossimQtVceShape*>(theSelectedItems[idx]);
     
     if(shape)
     {
       ossimQtVceConnectableObject* obj = shape->castToConnectable();
       if(obj)
       {
	 ossimQtProgressDialog* pd = new ossimQtProgressDialog("");
	 ossimProcessInterface* processInterface= PTR_CAST(ossimProcessInterface,
							   obj->getConnectableObject());
	 if(processInterface)
	 {
	   ossimProcessListener* pl = PTR_CAST(ossimProcessListener, pd);
	   if (pl)
	   {
	       obj->getConnectableObject()->addListener(pl);
	   }
	   pd->setLabelText(obj->getConnectableObject()->getDescription().c_str());
	   pd->setProcessInterface(processInterface);
	   pd->show();
           pd->setAutoClose(false);
	   processInterface->execute();
	   obj->getConnectableObject()->removeListener(pl);
	   delete pd;
	   return;
	 }
       }
     }
   }
}

void ossimQtVceCanvasWidget::dragEnterEvent(QDragEnterEvent* event)
{
   event->accept(QTextDrag::canDecode(event));
}

void ossimQtVceCanvasWidget::dropEvent(QDropEvent* event)
{
   std::vector<ossimObject*> objects;
   
   QString text;
   if ( QTextDrag::decode(event, text) )
   {
      QPoint position(event->pos().x() + contentsX(),
                      event->pos().y() + contentsY());
      ossimKeywordlist kwl;
      stringstream in(text.ascii());
      bool kwlParseFlag = kwl.parseStream(in);
      const char* type = NULL;
      if(kwlParseFlag)
      {
         type = kwl.find(ossimKeywordNames::TYPE_KW);
      }
      if(ossimString(type) == "ossimDataManagerObjectList")
      {
         addAllDataManagerObjects(kwl, position);
      }
      else if(ossimString(type)=="ossimQtVceComponentView")
      {
         addAllObjects(kwl, position);
      }
      else
      {
         unselectItems();
         QString filename;
         const char* s = text.ascii();
         const char* sEnd = text.ascii()+text.length();
         int idx = 0;
         while(s < sEnd)
         {
            filename = "";
            while((*s!='\0')&&
                  (*s != '\n')&&
                  (s < sEnd)&&
                  (*s != '\r'))
            {
               filename += *s;
               ++s;
            }
            ++s;
            filename += '\0';
            if(filename != "")
            {
               filename = filename.remove("file:");
               std::vector<QCanvasItem*> newItems;
               openImageFile(filename.ascii(),
                             position,
                             newItems);
               for(idx = 0; idx < (int)newItems.size(); ++idx)
               {
                  newItems[idx]->setSelected(true);
                  theSelectedItems.push_back(newItems[idx]);
                  emit itemSelected(newItems[idx]);
               }
            }
         }
      }
   }
}

void ossimQtVceCanvasWidget::addAllDataManagerObjects(const ossimKeywordlist& kwl,
                                                      const QPoint& location,
                                                      const char* prefix)
{
   QPoint locationPoint = location;
   if((locationPoint.x() == -1)&&
      (locationPoint.y() == -1))
   {
      locationPoint.setX(0);
      locationPoint.setY(0);
   }
   ossimQtGetDataManagerEvent tempEvt;
   ossimQtApplicationUtility::sendEventToRoot(this, &tempEvt);
   if(tempEvt.getDataManager())
   {
      
      ossimString regExpression =  ossimString("^(") + ossimString(prefix)+ "object[0-9]+.)";
      std::vector<ossimString> keys =
         kwl.getSubstringKeyList( regExpression );
      int numberOfObjects = keys.size();
      int idx = 0;
      for(idx = 0; idx < numberOfObjects; ++idx)
      {
         const char* id = kwl.find(keys[idx]+"id");
         if(id)
         {
            ossimConnectableObject* obj = PTR_CAST(ossimConnectableObject,
                                                   tempEvt.getDataManager()->getObject(ossimId(ossimString(id).toInt())));
            if(addDataManagerObject(obj,
                                    locationPoint))
            {
               locationPoint.setY(locationPoint.y() + 74);
            }
         }
      }
   }
}

bool ossimQtVceCanvasWidget::addDataManagerObject(ossimConnectableObject* obj,
                                                  const QPoint& position)
{
   bool result = false;
   QPoint currentPosition = position;
   ossimImageChain* chain = PTR_CAST(ossimImageChain, obj);
   if(chain)
   {
      int numberOfObjects = chain->getNumberOfObjects(false);
      int idx = 0;
      if(numberOfObjects == 1)
      {
          addObject((ossimConnectableObject*)(*chain)[idx]->dup(),
                    currentPosition);
      }
      else
      {
         ossimConnectableObject* startObj  = (ossimConnectableObject*)(*chain)[numberOfObjects-1]->dup();
         ossimConnectableObject* endObj    = (ossimConnectableObject*)NULL;
         QCanvasItem* endObjVce   = (QCanvasItem*)NULL;
         QCanvasItem* startObjVce = addObject(startObj,
                                              currentPosition);

         for(idx = numberOfObjects-1; idx > 0; --idx)
         {
            endObj = (ossimConnectableObject*)(*chain)[idx-1]->dup();
            
            if(endObj)
            {
               endObjVce = addObject(endObj,
                                     QPoint(currentPosition.x() + 80,
                                            currentPosition.y()));
               currentPosition.setX(currentPosition.x() + 80);
               if(startObjVce&&endObjVce)
               {
                  ossimQtVceShape* shape1 = ossimQtVceShape::castToVceShape(startObjVce);
                  ossimQtVceShape* shape2 = ossimQtVceShape::castToVceShape(endObjVce);

                  if(shape1->castToConnectable()&&
                     shape2->castToConnectable())
                  {
                     makeConnection((ossimQtVceConnectableObject*)shape1,
                                    (ossimQtVceConnectableObject*)shape2);
                  }
               }
            }
            startObjVce = endObjVce;
         }
      }
      result = true;
   }
   return result;
}

void ossimQtVceCanvasWidget::addAllObjects(const ossimKeywordlist& kwl,
                                           const QPoint& location,
                                           const char* prefix)
{
   unselectItems();
   QPoint locationPoint = location;
   
   ossimString copyPrefix = prefix;
   std::vector<QCanvasItem*> newItemList;
   
   ossimString regExpression =  ossimString("^(") + copyPrefix + "object[0-9]+.)";
   vector<ossimString> keys =
      kwl.getSubstringKeyList( regExpression );
   long numberOfObjets = keys.size();//kwl.getNumberOfSubstringKeys(regExpression);

   int offset = (copyPrefix+"object").size();
   int idx = 0;
   std::vector<int> theNumberList(numberOfObjets);

   for(idx = 0; idx < (int)theNumberList.size();++idx)
   {
      ossimString numberStr(keys[idx].begin() + offset,
                            keys[idx].end());
      theNumberList[idx] = numberStr.toInt();
   }
   
   std::sort(theNumberList.begin(), theNumberList.end());
   for(idx=0;idx < (int)theNumberList.size();++idx)
   {
      ossimString newPrefix = copyPrefix;
      newPrefix += ossimString("object");
      newPrefix += ossimString::toString(theNumberList[idx]);
      newPrefix += ossimString(".");
      ossimString objType = kwl.find(newPrefix,
                                     ossimKeywordNames::TYPE_KW);
      QCanvasItem* item = NULL;
      if(objType == "ossimQtImageWindow")
      {
         item = new ossimQtVceImageDisplayObject(canvas(),
						 this);
         item->setX(locationPoint.x());
         item->setY(locationPoint.y());
         item->show();
         emit itemAdded(item);
      }
      else if(objType == "ossimImageHandler")
      {
         QStringList filenames = QFileDialog::getOpenFileNames("Images (*.adf *.ccf *.dem *.DEM *.dt1 *.dt0 *.dt2 *.hdr *.hgt *.jpg *.jpeg *.img *.doqq *.fst *.FST *.nitf *.NTF *.ntf *.ras *.sid *.tif *.tiff *.toc *.TOC);;Vectors(*.shp dht *.tab);;All Files(*)",
                                                               QString::null,
                                                               this,
                                                               "open file dialog",
                                                               "Choose a file to open");
         QStringList::Iterator it;
         for(it = filenames.begin(); it != filenames.end(); ++it)
         {
            std::vector<QCanvasItem*> newItems;
            openImageFile((*it).ascii(),
                          locationPoint,
                          newItems);
            if(newItems.size())
            {
               
//                QRect bounds = newItems[newItems.size()-1]->boundingRect();
//                locationPoint.setY(locationPoint.y() + bounds.height() + 10);

               newItemList.insert(newItemList.end(),
                                  newItems.begin(),
                                  newItems.end());
            }
         }
         // we will make sure that we don't adjust the location point any further
         //
         item = NULL;
      }
      else
      {
         ossimObject* object = ossimObjectFactoryRegistry::instance()->createObject(objType);
         
         if(object)
         {
            item = addObject(object, locationPoint);
         }
      }
      if(item)
      {
         newItemList.push_back(item);
         QRect bounds = item->boundingRect();
         
         locationPoint.setY(locationPoint.y() + bounds.height() + 10);
         emit itemAdded(item);
      }
   }
   if(newItemList.size() > 0)
   {
      for(idx = 0; idx < (int)newItemList.size(); ++idx)
      {
         newItemList[idx]->setSelected(true);
         theSelectedItems.push_back(newItemList[idx]);
         emit itemSelected(newItemList[idx]);
      }
   }
}

void ossimQtVceCanvasWidget::makeConnection(ossimQtVceConnectableObject* start,
					    ossimQtVceConnectableObject* end)
{
   if(start!=end)
   {
      ossimQtVceConnectionObject* connection = new ossimQtVceConnectionObject(canvas(),
                                                                              this);
      connection->setZ(1);
      if(connection->makeConnection(start,
                                    end))
      {
         connection->show();
      }
      else
      {
         delete connection;
         connection = NULL;
         QMessageBox::warning(this,
                              "Connection Error",
                              "Slot are not compatible, unable to make connection",
                              QMessageBox::Ok,
                              QMessageBox::NoButton);
      }
   }
}

void ossimQtVceCanvasWidget::makeConnection(ossimQtVceConnectableObject* start,
                                            const QPoint& startPt,
					    ossimQtVceConnectableObject* end,
                                            const QPoint& endPt)
{
   if(start&&end)
   {
      ossimQtVceConnectableObject* inputSlotObj  = NULL;
      ossimQtVceConnectableObject* outputSlotObj = NULL;
      if(start!=end)
      {
         int inputIdx  = start->hitInputConnection(startPt);
         int outputIdx = start->hitOutputConnection(startPt);
         if(inputIdx > -1)
         {
            inputSlotObj = start;
            outputIdx = end->hitOutputConnection(endPt);
            if(outputIdx > -1)
            {
               outputSlotObj = end;
            }
            else
            {
               QMessageBox::warning(this,
                                    "Connection Error",
                                    "Slot types are not correct, Need an output and an input slot",
                                    QMessageBox::Ok,
                                    QMessageBox::NoButton);
            }
         }
         else if(outputIdx > -1)
         {
            outputSlotObj = start;
            inputIdx = end->hitInputConnection(endPt);
            if(inputIdx > -1)
            {
               inputSlotObj = end;
            }
            else
            {
               QMessageBox::warning(this,
                                    "Connection Error",
                                    "Slot types are not correct, Need an output and an input slot",
                                    QMessageBox::Ok,
                                    QMessageBox::NoButton);
            }
         }
         else
         {
            QMessageBox::warning(this,
                                 "Connection Error",
                                 "No slot found for connection",
                                 QMessageBox::Ok,
                                 QMessageBox::NoButton);
         }

         if(inputSlotObj&&outputSlotObj)
         {

            if((!inputSlotObj->getInputConnection(inputIdx))&&
               (!outputSlotObj->getOutputConnection(outputIdx)))
            {
               ossimQtVceConnectionObject* connection = new ossimQtVceConnectionObject(canvas(),
                                                                                       this);
               connection->setZ(1);
               if(connection->makeConnection(outputSlotObj,
                                             inputSlotObj,
                                             outputIdx,
                                             inputIdx))
               {
                  connection->show();
               }
               else
               {
                  delete connection;
                  connection = NULL;
                  QMessageBox::warning(this,
                                       "Connection Error",
                                       "Slot are not compatible, unable to make connection",
                                       QMessageBox::Ok,
                                       QMessageBox::NoButton);
               }
            }
            else
            {
               QMessageBox::warning(this,
                                    "Connection Error",
                                    "Connecting to a non empty slot is currently not supported.\nPlease delete and re-connect",
                                    QMessageBox::Ok,
                                    QMessageBox::NoButton);
            }
         }
      }
   }
}

bool ossimQtVceCanvasWidget::saveState(ossimKeywordlist& kwl,
                                       const char* prefix)const
{
   kwl.add(prefix,
           ossimKeywordNames::TYPE_KW,
           "ossimQtVceCanvasWidget",
           true);
   
   theCanvasUtility->copyCanvasStateToKeywordList(kwl, prefix);
   
   return true;
}

bool ossimQtVceCanvasWidget::loadState(const ossimKeywordlist& kwl,
                                       const char* prefix)
{
   theCanvasUtility->copyFromKeywordlist(kwl, prefix);
   
   return true;
}

QCanvasItem* ossimQtVceCanvasWidget::addObject(ossimObject* obj,
                                               const QPoint& location)
{
   if(!obj) return NULL;

   ossimQtVceImageSourceObject* newItem = NULL;
   ossimConnectableObject* connectableObj = PTR_CAST(ossimConnectableObject, obj);
   if(PTR_CAST(ossimImageHandler, connectableObj))
   {
     // I might make a special image handler vce shape and use here
     // for now I'll just use the same as an image source
     //
      newItem = new ossimQtVceImageSourceObject(canvas(), this);
      newItem->setPreviewEnableFlag(true);
   }
   else
   {
      // later we will use RTTI to allocate different types of VCE component shapes
      //
      newItem = new ossimQtVceImageSourceObject(canvas(), this);
      newItem->setPreviewEnableFlag(true);
   }
   
   newItem->setConnectableObject(connectableObj);
   
   newItem->setX(location.x());
   newItem->setY(location.y());
   
   newItem->setPen( QPen(QColor(0,0,0), 1) );
   newItem->updatePreview();
   newItem->show();
   
   return newItem;
}

ossimQtVceShape* ossimQtVceCanvasWidget::createShape(const ossimString& type)
{
  ossimQtVceShape* shapeResult = (ossimQtVceShape*)NULL;

  if(type == "ossimQtVceImageSourceObject")
    {
      shapeResult = new ossimQtVceImageSourceObject(canvas(), this);
    }

  return shapeResult;
}

void ossimQtVceCanvasWidget::openImageFile(const ossimString& filename,
                                           QPoint& locationPt,
                                           std::vector<QCanvasItem*>& newItemList)
{
   ossimRefPtr<ossimImageHandler> ih = ossimImageHandlerRegistry::instance()->open(filename);
   QCanvasItem* newItem = (QCanvasItem*)NULL;
   if(ih.valid())
   {
      ih->setDescription(ih->getFilename());
      newItem = addObject(ih.get(),
                          locationPt);
      if(!newItem)
      {
         ih = 0;
      }
      else
      {
         QRect bounds = newItem->boundingRect();
         
         locationPt.setY(locationPt.y() + bounds.height() + 10);
         newItemList.push_back(newItem);
         newItem->show();
      }
   }
}

void ossimQtVceCanvasWidget::deleteAllAssociatedConnections(std::vector<QCanvasItem*>& listOfItems)
{
  std::vector<ossimQtVceConnectionObject*> associatedConnections;
  std::vector<QCanvasItem*> tempList;
  int idx = 0;
  for(idx = 0; idx < (int)listOfItems.size();++idx)
    {
      if(listOfItems[idx])
	{
	  ossimQtVceShape* shape = ossimQtVceShape::castToVceShape(listOfItems[idx]);

	  if(!shape)
	    {
	      tempList.push_back(listOfItems[idx]);
	    }
	  else if(shape->castToConnection())
	    {
	      if(std::find(associatedConnections.begin(),
			   associatedConnections.end(),
			   (QCanvasItem*)shape) == associatedConnections.end())
		{
		  associatedConnections.push_back((ossimQtVceConnectionObject*)shape);
		}
	    }
	  else if(shape->castToConnectable())
	    {
	      tempList.push_back(listOfItems[idx]);
	      ossimQtVceConnectableObject* connectable = (ossimQtVceConnectableObject*)shape;
	      int idx2 = 0;
	      for(idx2 = 0; idx2 < connectable->getNumberOfInputConnections();++idx2)
		{
		  ossimQtVceConnectionObject* connectionObject = connectable->getInputConnection(idx2);
		  if(connectionObject)
		    {
		      if(std::find(associatedConnections.begin(),
				   associatedConnections.end(),
				   (QCanvasItem*)connectionObject) == associatedConnections.end())
			{
			  associatedConnections.push_back(connectionObject);
			}
		    }
		}
	      for(idx2 = 0; idx2 < connectable->getNumberOfOutputConnections();++idx2)
		{
		  ossimQtVceConnectionObject* connectionObject = connectable->getOutputConnection(idx2);
		  if(connectionObject)
		    {
		      if(std::find(associatedConnections.begin(),
				   associatedConnections.end(),
				   (QCanvasItem*)connectionObject) == associatedConnections.end())
			{
			  associatedConnections.push_back(connectionObject);
			}
		    }
		}
	    }
	  else
	    {
	      tempList.push_back(listOfItems[idx]);
	    }
	}
    }
  listOfItems = tempList;
  for(idx = 0; idx < (int)associatedConnections.size(); ++idx)
    {
      if(associatedConnections[idx])
	{
	  associatedConnections[idx]->removeConnection();
	  emit itemDeleting(associatedConnections[idx]);
	  delete ((QCanvasItem*)associatedConnections[idx]);
	}
    }
}
