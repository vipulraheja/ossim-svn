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
// $Id: ossimQtPropertyColorItem.h 6785 2004-09-23 17:18:03Z gpotts $
#ifndef ossimQtPropertyColorItem_HEADER
#define ossimQtPropertyColorItem_HEADER
#include <qguardedptr.h>
#include <qhbox.h>
#include <qpushbutton.h>
#include "ossimQtPropertyItem.h"

class ossimQtPropertyColorItem : public ossimQtPropertyItem
{
   Q_OBJECT
public:
   ossimQtPropertyColorItem(ossimQtPropertyListView *propList,
                            ossimQtPropertyItem *after,
                            ossimQtPropertyItem *parent,
                            ossimRefPtr<ossimProperty> oProp);
   virtual ~ossimQtPropertyColorItem();
   
   virtual void createChildren();
   virtual void initChildren();
   virtual void showEditor();
   virtual void hideEditor();
   virtual bool hasSubItems() const;
   virtual void childValueChanged( ossimQtPropertyItem *child );
   virtual bool hasCustomContents() const;
   virtual void drawCustomContents( QPainter *p, const QRect &r );
   virtual void resetProperty(bool notify=true);

protected slots:
   void getColor();

protected:
   QGuardedPtr<QHBox>       theBox;
   QGuardedPtr<QFrame>      theColorPreview;
   QGuardedPtr<QPushButton> theButton;
};

#endif
