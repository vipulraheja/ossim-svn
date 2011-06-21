//*******************************************************************
// Copyright (C) 2004 Intelligence Data Systems, Inc.  All rights reserved.
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
// Author:  David Burken
// 
// Description:
//
// Controller for quad projection dialog box.
//
//*************************************************************************
// $Id: ossimQtQuadProjectionController.h 9114 2006-06-14 17:42:07Z gpotts $
#ifndef ossimQtQuadProjectionController_HEADER
#define ossimQtQuadProjectionController_HEADER 

#include <qobject.h>
#include <ossim/base/ossimConstants.h>

class ossimQtQuadProjectionDialog;
class ossimQtScrollingImageWidget;
class ossimQtImageInfoController;
class ossimDatum;
class ossimDpt;
class ossimGpt;
class ossimImageChain;
class ossimImageHandler;
class ossimQtMouseEvent;
class ossimKeywordlist;
class ossimString;
class ossimImageViewTransform;
class ossimProjection;


class ossimQtQuadProjectionController : public QObject
{
Q_OBJECT
      
public:

   enum Column
   {
      LINE_COLUMN      = 0,
      SAMPLE_COLUMN    = 1,
      LATITUDE_COLUMN  = 2,
      LONGITUDE_COLUMN = 3,
      HEIGHT_COLUMN    = 4
   };
   
   ossimQtQuadProjectionController(ossimQtQuadProjectionDialog* dialog);
   virtual ~ossimQtQuadProjectionController();

   void setImageWidget(ossimQtScrollingImageWidget* widget,
                       ossim_uint32 widget_layer);

   void reset();
   void save();
   void deleteRow() const;
   void addRow() const;
   void cellValueChanged(int row, int col) const;

   /**
    * If true mouse events will be ignored.
    */
   void enableRoaming(bool flag);
      
private:
   ossimQtQuadProjectionController( const ossimQtQuadProjectionController&);
   ossimQtQuadProjectionController& operator=( const ossimQtQuadProjectionController&);

   void initializeDialog() const;
   void buildTable() const;
   void buildDatumMenu() const;
   void clearDialog() const;
   bool updateDialogFromImageHandler() const;
   
   void setDatumMenu(const ossimKeywordlist& kwl) const;
   void setDatumMenu(const ossimString& code) const;
   void setTableRow(int row, const ossimGpt& gp, const ossimDpt& dp) const;
   void setTableRow(int row, const ossimGpt& gp) const;
   void setTableRow(int row, const ossimDpt& dp) const;

   void sendEmptyColumnMessage(int row,
                               ossimQtQuadProjectionController::Column col) const;
   
   const ossimDatum*        getDatum()              const;
   ossimImageHandler*       getImageHandler()       const;
   ossimImageChain*         getChain()              const;
   ossimImageViewTransform* getImageViewTransform() const;
   ossimProjection*         getImageProjection()    const;

   double getDegrees(const ossimString& s, bool lat_flag) const;
   
   ossimQtQuadProjectionDialog* theDialog;
   ossimQtScrollingImageWidget* theWidget;
   ossim_uint32                 theWidgetLayer;
   bool                         theRoamingFlag;

public slots:

   /**
    * Slot to hook up to the widget's scrollingImageWidgetMouseEvent.
    */
   virtual void trackScrollingImageWidget(ossimQtMouseEvent* evt);
};

#endif /* #ifndef ossimQtQuadProjectionController_HEADER */
