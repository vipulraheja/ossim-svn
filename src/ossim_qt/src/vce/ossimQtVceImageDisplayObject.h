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
// $Id: ossimQtVceImageDisplayObject.h 7870 2005-08-01 17:16:55Z dburken $
#ifndef ossimQtVceImageDisplayObject_HEADER
#define ossimQtVceImageDisplayObject_HEADER
#include <qpixmap.h>
#include "ossimQtVceImageSourceObject.h"
class QPixmap;
class ossimQtImageWindow;
class ossimQtVceImageDisplayObjectPrivateEventFilter;

class ossimQtVceImageDisplayObject : public ossimQtVceImageSourceObject
{
   friend class ossimQtVceImageDisplayObjectPrivateConnectable;
   friend class ossimQtVceImageDisplayObjectPrivateEventFilter;
public:
  friend class ossimQtVceImageDisplayPrivate;
   ossimQtVceImageDisplayObject(QCanvas* canvas,
				QObject* vceParent);
   virtual ~ossimQtVceImageDisplayObject();
   virtual int rtti()const;
   
   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);
   
protected:
   ossimQtImageWindow* theDisplay;
   ossimQtVceImageDisplayObjectPrivateEventFilter* theQtEventFilter;
   QPixmap              thePixmap;
   virtual void drawShape(QPainter&);
   virtual void displayClosed();

   bool connectInternalObjectsInputTo(std::vector<ossimConnectableObject*>& inputList);
};

#endif
