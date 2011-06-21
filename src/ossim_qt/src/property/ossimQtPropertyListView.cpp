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
// $Id: ossimQtPropertyListView.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include <qheader.h>
#include "ossimQtPropertyListView.h"
#include <ossim/base/ossimPropertyInterface.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimProperty.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimRefreshEvent.h>
#include "ossimQtDisplayUtility.h"
#include "ossimQtPropertyFactory.h"
#include "ossimQtPropertyItem.h"

ossimQtPropertyListView::ossimQtPropertyListView(QWidget* parent,
                                                 const char* name,
                                                 WFlags flags)
   :QListView(parent, name, flags),
    theBackgroundColor1( 250, 248, 235),
    theBackgroundColor2( 255, 255, 255 ),
    theSelectedBackgroundColor(230, 230, 230)
{
   theAutoApplyFlag = false;
   
   header()->setMovingEnabled( FALSE );
   header()->setStretchEnabled( TRUE );
   setResizePolicy( QScrollView::Manual );
   viewport()->setAcceptDrops( TRUE );
   viewport()->installEventFilter( this );
   
   addColumn("Property");
   addColumn("Value");
   connect( header(), SIGNAL( sizeChange( int, int, int ) ),
            this, SLOT( updateEditorSize() ) );
   connect( this, SIGNAL( doubleClicked( QListViewItem * ) ),
            this, SLOT( toggleOpen( QListViewItem * ) ) );
   connect( this, SIGNAL( pressed( QListViewItem *, const QPoint &, int ) ),
            this, SLOT( itemPressed( QListViewItem *, const QPoint &, int ) ) );
   setSorting( -1 );
   setColumnWidthMode( 1, Manual );
   header()->installEventFilter( this );
}

void ossimQtPropertyListView::setObject(ossimObject* obj)
{
   theObject = obj;
   transferToWindow();
}

void ossimQtPropertyListView::transferToWindow()
{
   QString className = "";
   ossimPropertyInterface* propertyInterface = PTR_CAST(ossimPropertyInterface, theObject);
   clear();

   if(theObject)
   {
      className = theObject->getClassName().c_str();
   }
   
   if(propertyInterface)
   {
      std::vector<ossimRefPtr<ossimProperty> > propertyList;
      int idx = 0;
      
      propertyInterface->getPropertyList(propertyList);

      ossimQtPropertyItem* previous = 0;
      for(idx = 0; idx < (int)propertyList.size(); ++idx)
      {
         ossimQtPropertyItem* tempItem = ossimQtPropertyFactory::instance()->
            createProperty(this,
                           previous,
                           0,
                           propertyList[idx]);
         if(tempItem)
         {
            //---
            // Set the maker of the ossimProperty held by the
            // ossimQtPropertyItem so that it can update its ossimProperty
            // after a state change.
            //---
            tempItem->setMaker(propertyInterface);

            previous = tempItem;
         }
      }
      updateEditorSize();
   }
}

void ossimQtPropertyListView::transferFromWindow()
{
}

void ossimQtPropertyListView::setCurrentItem(QListViewItem* i)
{
    if ( !i )
	return;

    if ( currentItem() )
    {
       ( (ossimQtPropertyItem*)currentItem() )->hideEditor();
    }
    QListView::setCurrentItem( i );
    ((ossimQtPropertyItem*)currentItem())->showEditor();
}

void ossimQtPropertyListView::setAutoApplyFlag(bool flag)
{
   theAutoApplyFlag = flag;
}

bool ossimQtPropertyListView::getAutoApplyFlag()const
{
   return theAutoApplyFlag;
}

const QColor& ossimQtPropertyListView::getBackgroundColor1()const
{
   return theBackgroundColor1;
}

const QColor& ossimQtPropertyListView::getBackgroundColor2()const
{
   return theBackgroundColor2;
}

const QColor& ossimQtPropertyListView::getSelectedBackgroundColor()const
{
   return theSelectedBackgroundColor;
}

void ossimQtPropertyListView::resizeEvent( QResizeEvent *e )
{
   QListView::resizeEvent( e );
   if ( currentItem() )
   {
      ( ( ossimQtPropertyItem* )currentItem() )->showEditor();
   }
   
}


void ossimQtPropertyListView::updateEditorSize()
{
   if ( currentItem() )
   {
      ( ( ossimQtPropertyItem* )currentItem() )->showEditor();
   }
}

void ossimQtPropertyListView::resetProperty()
{
   if ( currentItem() )
   {
      ( ( ossimQtPropertyItem* )currentItem() )->resetProperty();

      ossimQtPropertyItem* rootItem = ( ( ossimQtPropertyItem* )currentItem() )->getRootItem();
      
      if(rootItem&&rootItem->getOssimProperty().valid()&&theAutoApplyFlag)
      {
         setProperty(rootItem->getOssimProperty());
      }
   }
}

void ossimQtPropertyListView::resetAllProperties()
{
   
}

void ossimQtPropertyListView::applyProperty()
{
   if(currentItem())
   {
      if( ((ossimQtPropertyItem* )currentItem())->isChanged())
      {
         setProperty(((ossimQtPropertyItem* )currentItem())->getOssimProperty());
      }
   }
}

void ossimQtPropertyListView::applyAllProperties()
{
   
}

void ossimQtPropertyListView::valueChanged( ossimQtPropertyItem *i )
{
   ossimQtPropertyItem* rootItem = i->getRootItem();
   
   if(rootItem->getOssimProperty().valid()&&theAutoApplyFlag)
   {
      setProperty(rootItem->getOssimProperty());
   }
}

void ossimQtPropertyListView::setProperty(ossimRefPtr<ossimProperty> prop)
{
   if(!prop) return;
   
   ossimPropertyInterface* propertyInterface = PTR_CAST(ossimPropertyInterface, theObject);
   if(propertyInterface)
   {
      ossimConnectableObject* connectable = PTR_CAST(ossimConnectableObject,
                                                     theObject);
      propertyInterface->setProperty(prop);
      if(prop->isChangeTypeSpecified())
      {
         if(connectable)
         {
            ossimRefreshEvent evt(connectable);
            connectable->fireEvent(evt);
            
            // check spatial change first since this causes
            // more to be refreshed.
            //
            if(prop->isFullRefresh())
            {
               ossimQtDisplayUtility::refreshAllOutputs(connectable);
            }
            else
            {
               ossimQtDisplayUtility::flushAllOutputs(connectable);
            }
         }
      }
      refreshGUI();
   }
}

void ossimQtPropertyListView::itemPressed( QListViewItem *i, const QPoint &p, int c )
{
   if ( !i )
   {
      return;
   }
   ossimQtPropertyItem *pi = (ossimQtPropertyItem*)i;
   if ( !pi->hasSubItems() )
   {
      return;
   }

   int identationRight = pi->getIndentation();
   int identationLeft  = identationRight - ossimQtPropertyItem::INDENTATION_AMOUNT;

   int mapped = viewport()->mapFromGlobal( p ).x();
   if( c == 0 &&
       ((mapped < identationRight)&&(mapped >  identationLeft)))
   {
      toggleOpen( i );
   }
}

void ossimQtPropertyListView::toggleOpen( QListViewItem *i )
{
   if ( !i )
   {
      return;
   }
   ossimQtPropertyItem *pi = (ossimQtPropertyItem*)i;
   if ( pi->hasSubItems() )
   {
      pi->setOpen( !pi->isOpen() );
   }
   else
   {
      pi->toggle();
   }
}

void ossimQtPropertyListView::refreshGUI()
{
   QListViewItemIterator it( this );
   while ( it.current() )
   {
      ((ossimQtPropertyItem* )it.current())->updateGUI();
      ++it;
   }
}
