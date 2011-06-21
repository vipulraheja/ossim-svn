//*******************************************************************
// Copyright (C) 2000 ImageLinks Inc. 
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtVceCanvasWidget.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtVceCanvasWidget_HEADER
#define ossimQtVceCanvasWidget_HEADER
#include <vector>
#include <qcanvas.h>
#include <qpoint.h>
#include <qevent.h>
#include <qwidgetplugin.h>
#include <qpopupmenu.h>
#include <ossim/base/ossimKeywordlist.h>

class ossimObject;
class ossimQtVceConnectableObject;
class ossimQtVceConnectionObject;
class ossimQtVceShapeRect;
class ossimQtVceShape;
class ossimConnectableObject;
class ossimQtVceCanvasContainerUtility;

class ossimQtVceCanvasWidget : public QCanvasView
{
   Q_OBJECT
public:
   friend class ossimQtVceCanvasContainerUtility;
   ossimQtVceCanvasWidget(QWidget* parent, 
                          QString name);
   virtual ~ossimQtVceCanvasWidget ();
   
   virtual void resizeContents ( int w, int h );
   void getSelectedItems(std::vector<QCanvasItem*>& selectedItems)const;
   bool hasSelectedItems()const;
   
   void makeConnection(ossimQtVceConnectableObject* start,
                       ossimQtVceConnectableObject* end);
   void makeConnection(ossimQtVceConnectableObject* start,
                       const QPoint& pt,
                       ossimQtVceConnectableObject* end,
                       const QPoint& endPt);
   
   bool saveState(ossimKeywordlist& kwl,
                  const char* prefix=0)const;
   bool loadState(const ossimKeywordlist& kwl,
                  const char* prefix=0);
   
protected:
   bool theLeftDownFlag;
   std::vector<QCanvasItem*> theSelectedItems;
   mutable ossimQtVceShapeRect*  theSelectionRect;
   mutable QCanvasLine*          theLineObject;
   ButtonState               theMouseButtonState;
   QPoint                    theMouseStartPt;
   ossimQtVceCanvasContainerUtility* theCanvasUtility;
   QPopupMenu*                       thePopupMenu;
   
   ossimQtVceConnectableObject* getObjectWhereConnectableSlotIntersectsPoint(QCanvasItemList& itemList,
                                                                             const QPoint& pt);
   
   virtual void contentsMousePressEvent ( QMouseEvent * e );
   virtual void contentsMouseReleaseEvent ( QMouseEvent * e );
   virtual void contentsMouseDoubleClickEvent ( QMouseEvent * e );
   virtual void contentsMouseMoveEvent ( QMouseEvent * e );
   
   void deleteSelectionRect();
   void selectItems(QCanvasItemList& itemList);
   bool intersectsSelection()const;

   virtual void dragEnterEvent(QDragEnterEvent* event);
   virtual void dropEvent(QDropEvent* event);

   void addAllDataManagerObjects(const ossimKeywordlist& kwl,
                                 const QPoint& location = QPoint(-1, -1),
                                 const char* prefix = NULL);
   
   void addAllObjects(const ossimKeywordlist& kwl,
                      const QPoint& location = QPoint(-1, -1),
                      const char* prefix = NULL);
   void openImageFile(const ossimString& filename,
                      QPoint& locationPt,
                      std::vector<QCanvasItem*>& newItems);
   QCanvasItem* addObject(ossimObject* obj,
                          const QPoint& location);

//     void copyFromKeywordlist(const ossimKeywordlist& kwl,
//                              const char* prefix=0);

  /*
   * This method is only temporary and will be moved
   * to a factory implementation.
   *
   */
  ossimQtVceShape* createShape(const ossimString& type);
public slots:
   void alignSelectedToTop();
   void alignSelectedToBottom();
   void alignSelectedToLeft();
   void alignSelectedToRight();

   void selectAll();
   void cutSelected();
   void copySelected();
   void paste();
   void executeSelected();

   void moveSelectedBy(int dx, int dy);
   void unselectItems();
   
   void deleteAllAssociatedConnections(std::vector<QCanvasItem*>& listOfItems);
   bool addDataManagerObject(ossimConnectableObject* obj,
                             const QPoint& position);
   
signals:
   void canvasWidgetMousePressEvent(QMouseEvent* evt);
   void canvasWidgetMouseReleaseEvent(QMouseEvent* evt);
   void canvasWidgetMouseDoubleClickEvent(QMouseEvent* evt);
   void canvasWidgetMouseMoveEvent(QMouseEvent* evt);
   void itemAdded(QCanvasItem* item);
   void itemSelected(QCanvasItem*);
   void itemDeleting(QCanvasItem*);
};

#endif
