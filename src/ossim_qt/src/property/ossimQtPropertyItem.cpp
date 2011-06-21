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
// $Id: ossimQtPropertyItem.cpp 9114 2006-06-14 17:42:07Z gpotts $
#include <qapplication.h>
#include <qpushbutton.h>
#include <qheader.h>
#include <qhbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qpainter.h>
#include <qstyle.h>
#include <qvariant.h>
#include "ossimQtPropertyItem.h"
#include "ossimQtPropertyListView.h"
#include <ossim/base/ossimProperty.h>
#include <ossim/base/ossimPropertyInterface.h>

const int ossimQtPropertyItem::INDENTATION_AMOUNT = 20;

ossimQtPropertyItem::ossimQtPropertyItem(ossimQtPropertyListView *propList,
                                         ossimQtPropertyItem *after,
                                         ossimQtPropertyItem *parent,
                                         ossimRefPtr<ossimProperty> oProp)
   :QListViewItem( propList, after ),
    theListView( propList ),
    theParent( parent ),
    theProperty(oProp),
    theResetProperty(0),
    theMaker(0)
{
   theResetButton = NULL;
   theOpenFlag = false;
   setSelectable( false );
   setText( 0, theProperty->getName().c_str());
   setText(1, "");      
   theChangedFlag = false;
   if(oProp.valid())
   {
      theResetProperty = (ossimProperty*)oProp->dup();
   }
}

ossimQtPropertyItem::~ossimQtPropertyItem()
{
   theProperty = 0;
   theResetProperty = 0;
   theMaker = 0;
   if(theResetButton)
   {
      delete theResetButton;
      theResetButton = 0;
   }
}

ossimRefPtr<ossimProperty> ossimQtPropertyItem::getOssimProperty()
{
   return theProperty;
}

const ossimRefPtr<ossimProperty> ossimQtPropertyItem::getOssimProperty()const
{
   return theProperty;
}


void ossimQtPropertyItem::notifyValueChange()
{
   setChanged( true );
   if ( hasSubItems() )
   {
      initChildren();
   }
}

int ossimQtPropertyItem::getIndentation()const
{
   if(!propertyParent())
   {
      return INDENTATION_AMOUNT;
   }

   return INDENTATION_AMOUNT + propertyParent()->getIndentation();
}


ossimQtPropertyListView* ossimQtPropertyItem::getListView()
{
   return theListView;
}

bool ossimQtPropertyItem::isOpen() const
{
   return theOpenFlag;
}

void ossimQtPropertyItem::setOpen(bool b )
{
   if(theOpenFlag == b)
   {
      return;
   }
   theOpenFlag = b;
   if ( !theOpenFlag )
   {
      int idx = 0;
      for(idx = 0; idx < childCount();++idx)
      {
         child(idx)->setOpen(theOpenFlag);
      }
      theChildren.setAutoDelete( TRUE );
      theChildren.clear();
      theChildren.setAutoDelete( FALSE );
      qApp->processEvents();
      theListView->updateEditorSize();
      return;
   }
    createChildren();
    initChildren();
    qApp->processEvents();
    theListView->updateEditorSize();
}

ossimQtPropertyItem *ossimQtPropertyItem::propertyParent() const
{
   return theParent;
}

bool ossimQtPropertyItem::hasSubItems() const
{
   return false;
}

void ossimQtPropertyItem::showEditor()
{
    createResetButton();
    theResetButton->show();
    placeEditor(0);
}

void ossimQtPropertyItem::hideEditor()
{
    createResetButton();
//    theResetButton->parentWidget()->hide();
    theResetButton->hide();
}

void ossimQtPropertyItem::setChanged(bool b)
{
   theChangedFlag = b;

   if(getOssimProperty().valid())
   {
      getOssimProperty()->setModifiedFlag(theChangedFlag);
   }
   if ( propertyParent() )
   {
      propertyParent()->childValueChanged(this);
   }
   else
   {
      theListView->valueChanged( this );
   }
   repaint();
   updateResetButtonState();
}

bool ossimQtPropertyItem::isChanged() const
{
   return theChangedFlag;
}

void ossimQtPropertyItem::placeEditor( QWidget *w )
{
   createResetButton();
   QRect r = theListView->itemRect( this );
   if ( !r.size().isValid() ) {
      theListView->ensureItemVisible( this );
#if defined(Q_WS_WIN)
      theListView->repaintContents( FALSE );
#endif
      r = theListView->itemRect( this );
   }
   r.setX(theListView->header()->sectionPos( 1 ));
   r.setWidth(theListView->header()->sectionSize( 1 ) - 1);
   r.setWidth(r.width() - theResetButton->width() - 2);
   r = QRect( theListView->viewportToContents(r.topLeft() ), r.size());
   if(w)
   {
      w->resize(r.size());
      theListView->moveChild( w, r.x(), r.y() );
   }
//   theResetButton->setGeometry(r.x() + r.width(), r.y(), theResetButton->sizeHint().width(), r.height());
   theResetButton->resize( theResetButton->sizeHint().width() + 10, r.height() );
   theListView->moveChild(theResetButton, r.x() + r.width(), r.y());
   theResetButton->setFixedHeight( r.height() );
}

void ossimQtPropertyItem::createResetButton()
{
   if ( theResetButton )
   {
//      theResetButton->parentWidget()->lower();
      theResetButton->lower();
      return;
   }
//   QHBox *hbox = new QHBox( theListView->viewport() );
//   hbox->setFrameStyle(QFrame::StyledPanel);
//   hbox->setFrameStyle( QFrame::StyledPanel | QFrame::Sunken );
//    hbox->setLineWidth( 1 );
//    hbox->setMargin(0);
//    hbox->setSpacing(1);
//   theResetButton = new QPushButton( hbox);
   theResetButton = new QPushButton( theListView->viewport());
   theResetButton->setPixmap( QPixmap::fromMimeSource( "resetproperty" ) );
   theResetButton->setFixedWidth( theResetButton->sizeHint().width() );
//   hbox->layout()->setAlignment( Qt::AlignRight );
//   theListView->addChild( hbox );
//   hbox->hide();
   theResetButton->hide();
   QObject::connect( theResetButton, SIGNAL( clicked() ),
                     theListView, SLOT( resetProperty() ) );
   QToolTip::add(theResetButton, "Reset the property to its default value");
   QWhatsThis::add(theResetButton, "Click this button to reset the property to its default value");
           
   updateResetButtonState();
}

void ossimQtPropertyItem::updateResetButtonState()
{
   if ( !theResetButton )
   {
      return;
   }

   theResetButton->setEnabled( isChanged() );
}

void ossimQtPropertyItem::addChild( ossimQtPropertyItem *i )
{
    theChildren.append( i );
}

int ossimQtPropertyItem::childCount() const
{
   return theChildren.count();
}

ossimQtPropertyItem *ossimQtPropertyItem::child( int i )
{
   if((i < childCount())&&
      (i >= 0))
   {
      return theChildren.at(i);
   }
   
   return 0;
}

ossimQtPropertyItem* ossimQtPropertyItem::getRootItem()
{
   ossimQtPropertyItem* result = this;

   while(result->propertyParent())
   {
      result = result->propertyParent();
   }
   
   return result;
}


void ossimQtPropertyItem::paintCell( QPainter *p, const QColorGroup &cg,
                                     int column, int width, int align )
{
   QColorGroup g( cg );
   g.setColor( QColorGroup::Base, backgroundColor() );
   g.setColor( QColorGroup::Foreground, Qt::black );
   g.setColor( QColorGroup::Text, Qt::black );
   int indent = 0;
   if ( column == 0 )
   {
      indent = getIndentation();
//      indent = 20 + ((propertyParent())?20:0);
      p->fillRect( 0, 0, width, height(), backgroundColor() );
      p->save();
      p->translate( indent, 0 );
   }
   
   if ( isChanged() && column == 0 )
   {
      p->save();
      QFont f = p->font();
      f.setBold( TRUE );
      p->setFont( f );
   }

   if(!hasCustomContents() || column != 1 )
   {
      QListViewItem::paintCell( p, g, column, width - indent, align  );
   }
   else
   {
      p->fillRect( 0, 0, width, height(), backgroundColor() );
      drawCustomContents( p, QRect( 0, 0, width, height() ) );
   }
   if ( isChanged() && column == 0 )
   {
      p->restore();
   }
   if ( column == 0 )
   {
      p->restore();
   }
   if ( hasSubItems() && column == 0 )
   {
      // let's paint the plus or minus sign
      //
      indent = getIndentation();
      p->save();
      p->translate( indent-INDENTATION_AMOUNT, 0 );
      p->setPen( cg.foreground() );
      p->setBrush( cg.base() );
      p->drawRect( 5, height() / 2 - 4, 9, 9 );
      p->drawLine( 7, height() / 2, 11, height() / 2 );
      if ( !isOpen() )
      {
         p->drawLine( 9, height() / 2 - 2, 9, height() / 2 + 2 );
      }
      p->restore();
   }
   p->save();
   p->setPen( QPen( cg.dark(), 1 ) );
   p->drawLine( 0, height() - 1, width, height() - 1 );
   p->drawLine( width - 1, 0, width - 1, height() );
   p->restore();
   
   if ( theListView->currentItem() == this && column == 0 &&
        !theListView->hasFocus() && !theListView->viewport()->hasFocus() )
   {
      paintFocus( p, cg, QRect( 0, 0, width, height() ) );
   }
   
}

void ossimQtPropertyItem::paintBranches( QPainter * p, const QColorGroup & cg,
                                         int w, int y, int h )
{
   QColorGroup g( cg );
   g.setColor( QColorGroup::Base, backgroundColor() );
   QListViewItem::paintBranches( p, g, w, y, h );
}

void ossimQtPropertyItem::paintFocus( QPainter *p, const QColorGroup &cg, const QRect &r )
{
   p->save();
   QApplication::style().drawPrimitive(QStyle::PE_Panel, p, r, cg,
                                       QStyle::Style_Sunken, QStyleOption(1,1) );
   p->restore();
}

bool ossimQtPropertyItem::hasCustomContents() const
{
   return false;
}
 
void ossimQtPropertyItem::drawCustomContents( QPainter* /* p */,
                                              const QRect& /* r */ )
{
}

void ossimQtPropertyItem::updateBackgroundColor()
{
   
   if ( itemAbove() && this != theListView->firstChild() )
   {
      if ( ( ( ossimQtPropertyItem*)itemAbove() )->theBackgroundColor == theListView->getBackgroundColor1())
      {
         theBackgroundColor = theListView->getBackgroundColor2();
      }
      else
      {
         theBackgroundColor =  theListView->getBackgroundColor1();
      }
   }
   else
   {
      theBackgroundColor = theListView->getBackgroundColor1();
   }
   if ( theListView->firstChild() == this )
   {
      theBackgroundColor = theListView->getBackgroundColor1();
   }
}

QColor ossimQtPropertyItem::backgroundColor()
{
   updateBackgroundColor();
   
   if ((QListViewItem*)this == theListView->currentItem())
   {
      return theListView->getSelectedBackgroundColor();
   }
   
   return theBackgroundColor;
}

void ossimQtPropertyItem::childValueChanged( ossimQtPropertyItem * )
{
   
   bool modified = false;
   int idx;
   for(idx= 0; idx < childCount(); ++idx)
   {
      if(child(idx)->isChanged())
      {
         modified = true;
      }
   }
   theChangedFlag = modified;
   if(getOssimProperty().valid())
   {
      getOssimProperty()->setModifiedFlag(theChangedFlag);
   }
   repaint();
   updateResetButtonState();
   
   if(propertyParent())
   {
      propertyParent()->childValueChanged(this);
   }
   else
   {
      theListView->valueChanged(this);
   }
}

void ossimQtPropertyItem::notifyResetStateChanged()
{
#if 0
   int idx = 0;

   bool modified = false;
   for(idx= 0; idx < childCount(); ++idx)
   {
      if(child(idx)->isChanged())
      {
         modified = true;
      }
   }
   if(getOssimProperty().valid())
   {
      getOssimProperty()->setModifiedFlag(modified);
   }
   if(theChangedFlag != modified)
   {
      theChangedFlag = modified;
      repaint();
      updateResetButtonState();
      if(propertyParent())
      {
         propertyParent()->notifyResetStateChanged();
      }
      else  // we are at the root so let the list view know that this object
      {
         theListView->valueChanged( this );
      }
   }
#endif
}

void ossimQtPropertyItem::createChildren()
{
   
}

void ossimQtPropertyItem::initChildren()
{
}

void ossimQtPropertyItem::setText( int col, const QString &t )
{
   QString txt( t );
   if ( col == 1 )
   {
      txt = txt.replace( "\n", " " );
   }
   
   QListViewItem::setText( col, txt );
}

void ossimQtPropertyItem::setup()
{
   widthChanged();
   setHeight(20);
}

void ossimQtPropertyItem::setValue(const QVariant& v)
{
   if(getOssimProperty().valid())
   {
     getOssimProperty()->setValue(v.toString().ascii());
   }
}

QVariant ossimQtPropertyItem::value()const
{
   QString result;
   
   if(getOssimProperty().valid())
   {
      result = getOssimProperty()->valueToString().c_str();
   }
   
   return result;
}

void ossimQtPropertyItem::toggle()
{
}

void ossimQtPropertyItem::resetProperty(bool notify)
{
   *theProperty = *theResetProperty;

   if(notify)
   {
      setChanged(false);
   }
   else
   {
      theChangedFlag = false;
      if(getOssimProperty().valid())
      {
         getOssimProperty()->setModifiedFlag(theChangedFlag);
      }
      repaint();
      updateResetButtonState();
   }
}

void ossimQtPropertyItem::setMaker(ossimPropertyInterface* maker)
{
   theMaker = maker;

   // Not sure about children yet...
   
   // int idx = 0;
   // for(idx = 0; idx < childCount(); ++idx)
   // {
   //    child(idx)->setMaker(maker);
   // }
}

void ossimQtPropertyItem::updateGUI()
{
#if 0
   cout << "ossimQtPropertyItem::updateGUI entered..."
        << "\nDerived classes should implement!"
        << "\nossimQtPropertyItem::updateGUI exited..." << endl;
#endif
}
