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
// $Id: ossimQtVceComponentDialogController.h 8909 2006-03-21 15:13:30Z gpotts $
#ifndef ossimQtVceComponentDialogController_HEADER
#define ossimQtVceComponentDialogController_HEADER
#include <qobject.h>

class ossimQtVceComponentDialog;
class ossimQtVceComponentDialogController : public QObject
{
   Q_OBJECT
public:
   ossimQtVceComponentDialogController(ossimQtVceComponentDialog* widget);
   virtual ~ossimQtVceComponentDialogController();
        
protected:
   ossimQtVceComponentDialog* theWindow;

   void loadViews();
   void loadDisplay();
   void loadImageHandler();
};

#endif
