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
// $Id: ossimQtVceImageSourceObject.h 7234 2005-02-11 15:10:32Z dburken $
#ifndef ossimQtVceImageSourceObject_HEADER
#define ossimQtVceImageSourceObject_HEADER
#include <qimage.h>
#include "ossimQtVceConnectableObject.h"
#include "ossimQtVceShapeRtti.h"

class ossimImageData;
class ossimQtVceImageSourceObject : public ossimQtVceConnectableObject
{
public:
   friend class ossimQtVceImageSourceObjectPrivateListener;
   ossimQtVceImageSourceObject(QCanvas* canvas,
			       QObject* vceParent);
   ossimQtVceImageSourceObject(const QRect& bounds,
                               QCanvas* canvas,
			       QObject* vceParent);
   virtual int rtti()const;
   virtual void setPreviewEnableFlag(bool flag);
   virtual void updatePreview();
   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);
   
  //  virtual void setConnectableObject(ossimConnectableObject* connectable);
protected:
  QImage theImage;
  bool  thePreviewEnableFlag;
  //  ossimQtVceImageSourceObjectPrivateListener* thePrivateListener;

  virtual void fillImage(ossimRefPtr<ossimImageData>& data, QImage* tempImage);
  virtual void setPreview();
  virtual QRect boundingVceShapeRect()const;
  
  virtual void drawShape(QPainter&);

  virtual void internalInputConnectionChanged();
  virtual void internalRefresh();
  virtual void internalProperty();

};

#endif
