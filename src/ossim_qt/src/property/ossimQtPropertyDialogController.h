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
// $Id: ossimQtPropertyDialogController.h 7870 2005-08-01 17:16:55Z dburken $
#ifndef ossimQtPropertyDialogController_HEADER
#define ossimQtPropertyDialogController_HEADER
#include <qobject.h>
class ossimQtPropertyDialog;
class ossimObject;
class ossimQtPropertyDialogControllerPrivateListener;

class ossimQtPropertyDialogController : public QObject
{
   Q_OBJECT
public:
   friend class ossimQtPropertyDialogControllerPrivateListener;
   
   ossimQtPropertyDialogController(ossimQtPropertyDialog* dialog);
   virtual ~ossimQtPropertyDialogController();

   virtual void setObject(ossimObject* obj);
   
protected:
   ossimQtPropertyDialog* theDialog;
   ossimObject*           theObject;
   ossimQtPropertyDialogControllerPrivateListener* thePrivateListener;
public slots:
   virtual void closeButton();
   virtual void resetButton();
   virtual void applyButton();
   virtual void autoApplyToggledButton(bool value);
};

#endif
