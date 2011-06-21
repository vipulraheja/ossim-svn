//----------------------------------------------------------------------------
// Copyright (C) 2004 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: Single image window.
//
// $Id: ossimQtSingleImageWindow.h 18517 2010-12-07 21:02:39Z dburken $
//----------------------------------------------------------------------------
#ifndef ossimQtSingleImageWindow_HEADER 
#define ossimQtSingleImageWindow_HEADER

#include <vector>
#include <qmainwindow.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConnectableDisplayListener.h>
#include <ossim/imaging/ossimImageGeometry.h>

class ossimQtScrollingImageWidget;
class ossimImageChain;
class ossimImageCombiner;
class ossimImageHandler;
class ossimImageGeometry;
class ossimQtMouseEvent;
class QComboBox;
class QPopupMenu;
class ossimRLevelFilter;

/**
 * This window is designed to be used as a simple viewer, exporter.
 * The basic image chain has no renderer and works in image space only.
 */
class ossimQtSingleImageWindow : public QMainWindow,
                                 public ossimConnectableObject,
                                 public ossimConnectableDisplayListener
{
   Q_OBJECT
public:

   ossimQtSingleImageWindow(QWidget* parent=0,
                            const char* name=0,
                            WFlags f=0);
   virtual ~ossimQtSingleImageWindow();

   /** Override virtual method from ossimDisplayEventListener. */
   virtual void displayListEvent(ossimDisplayListEvent&);

   /** Override virtual method from ossimDisplayEventListener. */
   virtual void displayRefreshEvent(ossimDisplayRefreshEvent&);

   /** Concrete implementation of pure virtual from ossimConnectableObject. */
   virtual bool canConnectMyInputTo(ossim_int32 /*myInputIndex*/,
                                    const ossimConnectableObject* object)const;

   /**
    * Method to listen to "theChain" for adds of objects so we can,
    * for instance, rebuild the reduced res menu if one is added.
    */
   virtual void addObjectEvent(ossimContainerEvent& event);

   /**
    * Method to listen to "theChain" for adds of objects so we can,
    * for instance, rebuild the reduced res menu if one is removed.
    */
   virtual void removeObjectEvent(ossimContainerEvent& event);
 
public slots:
   void trackImageWidget(ossimQtMouseEvent* evt);

protected:
   virtual void customEvent(QCustomEvent* event);
   
private slots:
   
   /** Calls theImageWidget->refresh() */
   void refreshDisplay();

   /**
    * Changes resolution level if an rlevel filter is in the chain.
    * Does nothing if no rlevel filter is present.
    */
   void changeResolutionLevel(int level);
   
   void openImage();
   
   void overlayShapeFile();
   void clearShapeFiles();
   
   void closeImage();
   void editImageChain();
   void exportImage();
   void closeWindow();
   void about();

private:
   // Hide from use.
   ossimQtSingleImageWindow(const ossimQtSingleImageWindow& obj);

   // Hide from use.
   const ossimQtSingleImageWindow& operator=(const ossimQtSingleImageWindow& rhs);

   void displayImage(const ossimFilename& file);
   void createImageChain(ossimImageHandler* ih);
   void getAllowedFilterList(std::vector<ossimString>&) const;
   void buildOverViews(ossimImageHandler* ih);

   void overlayShapeFile(const ossimFilename& file);
   void combineShapeFile(ossimImageHandler* ih);
   

   /**
    * Builds the resolution level menu.
    */
   void buildResolutionLevelMenu();
   
   /**
    * Checks "theImageChain" for an ossimRLevelFilter and returns a pointer
    * to it.
    * 
    * @return A pointer to the ossimRLevelFilter if there is one; else, NULL.
    */
   ossimRLevelFilter* getRLevelFilter();

   ossim_uint32 getCurrentRLevel() ;

   /**
    * Checks "theImageChain" for an ossimImageHandler and returns a pointer
    * to it.
    * 
    * @return A pointer to the ossimImageHandler if there is one; else, NULL.
    */
   ossimImageHandler* getImageHandler() ;

   /** Initializes theModel. */
   void createImageModel();

   void transformShapesToImage();

   void clearShapeChains();

   void setupButtons();
   
   ossimQtScrollingImageWidget*                m_imageWidget;
   ossimRefPtr<ossimImageChain>                m_imageChain;
   std::vector<ossimRefPtr<ossimImageChain> >  m_shapeChains;
   ossimFilename                               m_lastOpenedDirectory;
   QPopupMenu*                                 m_fileMenu;
   QPopupMenu*                                 m_resolutionLevelMenu;
   ossimRefPtr<ossimImageCombiner>             m_combiner;
   ossimRefPtr<ossimImageGeometry>             m_geom;
   ossim_int32                                 m_overLayerShapeFileId;
   ossim_int32                                 m_clearShapeFilesId;
   
TYPE_DATA   
};
#endif /* #ifndef ossimQtSingleImageWindow_HEADER */
