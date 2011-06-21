//*******************************************************************
// Copyright (C) 2003 ImageLinks Inc. 
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
// 
// Description:
// Main interface between the elevation manager and the elevation manager
// dialog box.
//
//*************************************************************************
// $Id: ossimQtElevationManagerController.h 9114 2006-06-14 17:42:07Z gpotts $

#ifndef ossimQtElevationManagerController_HEADER
#define ossimQtElevationManagerController_HEADER

#include <vector>
using namespace std;

#include <ossimQtDatumConverterDialog.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimElevationManagerEventListener.h>
#include <ossim/base/ossimElevationManagerEvent.h>

// Forward class declarations.
class ossimElevManager;
class ossimQtElevationManagerDialog;
class QStringList;

class ossimQtElevationManagerController : public ossimElevationManagerEventListener
{
public:

   enum
   {
      ADD_BUTTON,
      ADD_DIRECTORY_BUTTON,
      REMOVE_BUTTON,
      REMOVE_ALL_BUTTON,
      UP_BUTTON,
      DOWN_BUTTON,
      TOP_BUTTON,
      BOTTOM_BUTTON,
      CLOSE_BUTTON,
      ENABLE_BUTTON,
      AUTO_LOAD_ENABLE_BUTTON,
      AUTO_SORT_ENABLE_BUTTON,
      MOSAIC_BUTTON
   };

   ossimQtElevationManagerController(ossimQtElevationManagerDialog* dialog);
   virtual ~ossimQtElevationManagerController();

   virtual void processEvent(ossimElevationManagerEvent&) const;

   void onAdd(const QStringList& cells) const;
   void onAddDirectory(const QString& directory) const;
   void onRemove(const QStringList& cells) const;
   void onRemoveAll() const;
   void onUp(const QStringList& cells) const;
   void onDown(const QStringList& cells) const;
   void onTop(const QStringList& cells) const;
   void onBottom(const QStringList& cells) const;
   void onEnable(bool flag) const;
   void onAutoLoadEnable(bool flag) const;
   void onAutoSortEnable(bool flag) const;
   void onClose(const QStringList& cells) const;
   void onMosaic(const QStringList& cells) const;

   static ossimFilename getLatestOpenCellPath();

private:
   void update() const;
   void updateListBox() const;
   void updateEnableBox() const;
   void updateAutoLoadEnableBox() const;
   void updateAutoSortEnableBox() const;

   // Disallow copy  constructor, assignment operator.
   ossimQtElevationManagerController( const ossimQtElevationManagerController&);
   ossimQtElevationManagerController& operator=( const ossimQtElevationManagerController&);
   
   ossimQtElevationManagerDialog* theDialog;
   ossimElevManager*              theMgr;

   // Static data member to capture the last directory.
   static ossimFilename theLatestOpenCellPath;
};

#endif
