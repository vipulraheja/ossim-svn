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
// $Id: ossimQtPreferencesDialogController.h 5936 2004-01-16 20:53:56Z gpotts $
#ifndef ossimQtPreferencesDialogController_HEADER
#define ossimQtPreferencesDialogController_HEADER
#include <qobject.h>
class QListBoxItem;
class ossimQtPreferencesDialog;

class ossimQtPreferencesDialogController : public QObject
{
   Q_OBJECT

public:
   ossimQtPreferencesDialogController(ossimQtPreferencesDialog* dialog);

   virtual ~ossimQtPreferencesDialogController();
   
public slots:
   virtual void close();
   virtual void addPlugin();
   virtual void removePlugin();
   virtual void reloadPlugin();
   virtual void selectAllPlugin();
   virtual void currentPluginSelectionChanged(QListBoxItem* item);

protected:
   ossimQtPreferencesDialog* theDialog;

   void transferToDialog();

   void transferPluginToDialog();
};

#endif
