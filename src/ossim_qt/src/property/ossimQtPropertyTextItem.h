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
// $Id: ossimQtPropertyTextItem.h 6785 2004-09-23 17:18:03Z gpotts $
#ifndef ossimQtPropertyTextItem_HEADER
#define ossimQtPropertyTextItem_HEADER
#include <qguardedptr.h>
#include <qhbox.h>
#include "ossimQtPropertyItem.h"

class ossimQtPropertyTextItem : public ossimQtPropertyItem
{
   Q_OBJECT
public:
   ossimQtPropertyTextItem(ossimQtPropertyListView *propList,
                           ossimQtPropertyItem *after,
                           ossimQtPropertyItem *parent,
                           ossimRefPtr<ossimProperty> oProp);
   virtual ~ossimQtPropertyTextItem();
   
   virtual void showEditor();
   virtual void hideEditor();

protected slots:
   void setValue();   
   void getText();
   
public slots:
   virtual void resetProperty(bool notify=true);
   
protected:
   QLineEdit *lineEditor();
   QGuardedPtr<QLineEdit> theLineEditor;
   QGuardedPtr<QHBox> theBox;
   QPushButton *thePushButton;

   bool hasMultiLines()const;
};
                                

#endif
