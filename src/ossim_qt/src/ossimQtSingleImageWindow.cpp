//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Single image window.
//
// $Id: ossimQtSingleImageWindow.cpp 19688 2011-05-31 14:55:39Z dburken $
//----------------------------------------------------------------------------

#include <iostream>
#include <sstream>
#include <iomanip>

#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbutton.h>
#include <ossim/vpfutil/set.h>
#include <qmainwindow.h>
#include <qcombobox.h>
#include <ossimQtSingleImageWindow.h>
#include <ossimQtIcpDialog.h>
#include <ossimQtIviewAboutDialog.h>
#include <ossimQtOverviewBuilderDialog.h>
#include <ossimQtProgressDialog.h>
#include <ossimQtScrollingImageWidget.h>
#include <ossimQtImageChainEditorDialog.h>
#include <ossimQtImageWindowControllerEventFilter.h>
#include <ossimQtEditorWidgetManager.h>
#include <ossimQtEvent.h>
#include <ossimQtDisplayUtility.h>
#include <ossim/base/ossimContainerEvent.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/imaging/ossimJpegYCbCrToRgbSource.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimImageGeometry.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageCombiner.h>
#include <ossim/imaging/ossimImageMosaic.h>
#include <ossim/imaging/ossimTiffOverviewBuilder.h>
#include <ossim/imaging/ossimBandSelector.h>
#include <ossim/imaging/ossimBrightnessContrastSource.h>
#include <ossim/imaging/ossimCacheTileSource.h>
#include <ossim/imaging/ossimHistogramRemapper.h>
#include <ossim/imaging/ossimHsiRemapper.h>
#include <ossim/imaging/ossimRLevelFilter.h>
#include <ossim/imaging/ossimWatermarkFilter.h>
#include <ossim/imaging/ossimTiffTileSource.h>

static const int DEFAULT_WIDTH  = 512;
static const int DEFAULT_HEIGHT = 512;

RTTI_DEF2(ossimQtSingleImageWindow,
          "ossimQtSingleImageWindow",
          ossimConnectableObject,
          ossimConnectableDisplayListener);

ossimQtSingleImageWindow::ossimQtSingleImageWindow(QWidget* parent,
                                                   const char* name,
                                                   WFlags f)
   : QMainWindow(parent, name, f),
     ossimConnectableObject(),
     ossimConnectableDisplayListener(),
     m_imageWidget(0),
     m_imageChain(0),
     m_shapeChains(),
     m_lastOpenedDirectory(),
     m_fileMenu(0),
     m_resolutionLevelMenu(0),
     m_combiner(0),
     m_geom(0),
     m_overLayerShapeFileId(-1),
     m_clearShapeFilesId(-1)
{
   ossimReferenced::ref();
   setCaption("iview");
   
   QSize size(DEFAULT_WIDTH, DEFAULT_HEIGHT);
   setBaseSize(size);
   
   // Create the image widget parenting it to this.
   m_imageWidget = new ossimQtScrollingImageWidget(this, "image_widget");

   // This will clear out any initial garbage in the widget.
   m_imageWidget->refresh();

   // Disable random caching scheme.
   m_imageWidget->setRandomPriorityQueueEnabledFlag(false);
   
   // Set the the width and height of the window.
   m_imageWidget->resizeContents(DEFAULT_WIDTH, DEFAULT_HEIGHT);

   // Make the image widget the centralized widget.
   setCentralWidget(m_imageWidget);

   // Make the "File" pull down menu.
   m_fileMenu = new QPopupMenu( this );
   menuBar()->insertItem( "&File", m_fileMenu );

   m_fileMenu->insertItem( "&Open Image", this,
                            SLOT(openImage()), CTRL+Key_O );
   
   m_fileMenu->insertItem( "&Close Image", this,
                            SLOT(closeImage()), CTRL+Key_C );

   m_overLayerShapeFileId =
      m_fileMenu->insertItem( "&Overlay shape file",
                               this, SLOT(overlayShapeFile()) );
   m_clearShapeFilesId =
      m_fileMenu->insertItem( "&Clear shape files",
                               this, SLOT(clearShapeFiles()) );

   m_fileMenu->insertItem( "&Export",  this,
                            SLOT(exportImage()), CTRL+Key_E );
   
   m_fileMenu->insertItem( "&Quit",  this,
                            SLOT(closeWindow()), CTRL+Key_Q );

   // Make the "Edit" pull down menu.
   QPopupMenu* edit = new QPopupMenu( this );
   menuBar()->insertItem( "&Edit", edit );
   edit->insertItem( "Image Chain",  this, SLOT(editImageChain()));

   // Make the "Utilities" pull down menu.
   QPopupMenu* utilities = new QPopupMenu( this );
   menuBar()->insertItem( "&Utilities", utilities );
   utilities->insertItem( "Refresh",  this, SLOT(refreshDisplay()));

   // Make the "Resolution_Level" pull down menu.
   m_resolutionLevelMenu = new QPopupMenu( this );
   menuBar()->insertItem( "&Resolution_Level",  m_resolutionLevelMenu);
   m_resolutionLevelMenu->insertItem( QString("0"), 0, 0 );

   // Connect the activated signal to the changeResolutionLevel slot.
   connect( m_resolutionLevelMenu, SIGNAL ( activated(int) ),
            this, SLOT ( changeResolutionLevel(int) ) );

   // Make the "Help" pull down menu.
   QPopupMenu* help = new QPopupMenu( this );
   menuBar()->insertItem( "&Help", help );
   help->insertItem( "&About",  this, SLOT(about()), CTRL+Key_A );

   // Connect up the slot to capture mouse events.
   connect(m_imageWidget,
           SIGNAL(scrollingImageWidgetMouseEvent(ossimQtMouseEvent*)),
           this,
           SLOT(trackImageWidget(ossimQtMouseEvent*)));

   // Add us in as a listener for display events like refresh. 
   addListener((ossimConnectableDisplayListener*)this);
   
   //---
   // Connect this display up to "m_imageWidget" so that event propagation
   // comes up the chain to us.
   //---
   connectMyInputTo(m_imageWidget);

   // Send a dummy message to make the status bar show.
   statusBar()->message( QString(" ") );

   // Set up conditional buttons.
   setupButtons();
}

ossimQtSingleImageWindow::~ossimQtSingleImageWindow()
{
   if (m_imageChain.valid())
   {
      m_imageChain->disconnect();
      m_imageChain = 0;
   }

   clearShapeChains();

   if (m_geom.valid())
   {
      m_geom = 0;
   }
   
   ossimConnectableObject::disconnect();
   ossimReferenced::unref_nodelete();
}

void ossimQtSingleImageWindow::addObjectEvent(ossimContainerEvent& event)
{
   ossimObject* addedObject = event.getAssociatedObject();
   if (addedObject)
   {
      if ( PTR_CAST(ossimRLevelFilter, addedObject) ||
           PTR_CAST(ossimTiffTileSource, addedObject) )
      {
         buildResolutionLevelMenu();
      }
   }
}

void ossimQtSingleImageWindow::removeObjectEvent(ossimContainerEvent& event)
{
   ossimObject* removedObject = event.getAssociatedObject();
   
   if (removedObject)
   {
      ossimRLevelFilter* rf = PTR_CAST(ossimRLevelFilter, removedObject);
      if (rf)
      {
         if (m_resolutionLevelMenu)
         {
            m_resolutionLevelMenu->clear();
            m_resolutionLevelMenu->insertItem( QString("0"), 0, 0 );
         }
      }
   }
}

void ossimQtSingleImageWindow::refreshDisplay()
{
   if (m_imageWidget)
   {
      m_imageWidget->refresh();
   }
}

void ossimQtSingleImageWindow::changeResolutionLevel(int level)
{
   ossimRLevelFilter* rf = getRLevelFilter();
   if (rf)
   {
      ossim_uint32 new_level = static_cast<ossim_uint32>(level);
      ossim_uint32 current_level = rf->getCurrentRLevel();
      if (new_level != current_level)
      {

         rf->setCurrentRLevel(new_level);
         
         if (new_level == 0)
         {
            rf->disableSource();
         }
         else
         {
            rf->enableSource();
         }

         if (m_shapeChains.size() && m_geom.valid())
         {
            transformShapesToImage();
         }

         // Force the window to repaint.
         ossimQtDisplayUtility::flushAllOutputs(rf, true);
      }
   }
}

void ossimQtSingleImageWindow::openImage()
{
   QFileDialog* fd = new QFileDialog( this, "file dialog", TRUE );
   fd->setMode( QFileDialog::ExistingFile );

   if (!m_lastOpenedDirectory.empty())
   {
      if (m_lastOpenedDirectory.exists())
      {
         QString qs = m_lastOpenedDirectory.c_str();
         fd->setDir(qs);
      }
   }
   
   ossimFilename fileName;
  
   if ( fd->exec() == QDialog::Accepted )
   {
      fileName = fd->selectedFile().ascii();
      m_lastOpenedDirectory = fileName.path();
   }

   delete fd;
   fd = 0;
   
   if (fileName.empty())
   {
      return;
   }
   
   displayImage(fileName);
}

void ossimQtSingleImageWindow::overlayShapeFile()
{
   if (m_imageChain.valid())
   {
      QFileDialog* fd = new QFileDialog( this, "file dialog", TRUE );
      fd->setMode( QFileDialog::ExistingFile );
      
      if (!m_lastOpenedDirectory.empty())
      {
         if (m_lastOpenedDirectory.exists())
         {
            QString qs = m_lastOpenedDirectory.c_str();
            fd->setDir(qs);
         }
      }
      
      ossimFilename fileName;
      
      if ( fd->exec() == QDialog::Accepted )
      {
         fileName = fd->selectedFile().ascii();
         m_lastOpenedDirectory = fileName.path();
      }
      
      delete fd;
      fd = 0;
   
      if (fileName)
      {
         overlayShapeFile(fileName);
      }
   }
   else
   {
      QString caption = "Sorry:";
      QString text = "You must open an image first\n";
      text += " you can overlay a shape file.\n";
      text += "  Use \"File->Open Image\"\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
   }
}


void ossimQtSingleImageWindow::overlayShapeFile(const ossimFilename& file)
{
   ossimRefPtr<ossimImageHandler> ih = ossimImageHandlerRegistry::instance()->open(file);
   if (ih.valid())
   {
      if (ih->canCastTo("ossimOgrGdalTileSource"))
      {
         combineShapeFile(ih.get());
      }
      else
      {
         ih = 0;
         
         QString caption = "Sorry:";
         QString text = " Must be a shape file!";
         QMessageBox::information( this,
                                   caption,
                                   text,
                                   QMessageBox::Ok );
            
      }
   }
   else
   {
      QString caption = "Sorry:";
      QString text = "Could not find the image handler for file:\n";
      text += file.c_str();
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
   }
}

void ossimQtSingleImageWindow::combineShapeFile(ossimImageHandler* ih)
{
   // Must have a model to reproject shape file to image.
   if (ih && m_geom.valid())
   {
      // Shape file reader is an ossimViewInterface.
      ossimViewInterface* itrf = PTR_CAST(ossimViewInterface, ih);
      if (itrf)
      {
         // Make sure the model has current rrds for transform.
         m_geom->setTargetRrds(getCurrentRLevel());

         // Transform this shape file to image space.
         itrf->setView(m_geom.get()); 
      
         ossimRefPtr<ossimImageChain> chain = new ossimImageChain();

         // Add the image handler. Last is far left of chain.
         chain->addLast(ih);
      
         // Add a cache at the end of the chain.
         // ossimCacheTileSource* cache = new ossimCacheTileSource();
         
         // First is far right of chain so we have: shape_reader->cache->
         // chain->addFirst(cache);

         // Always call initialize.
         chain->initialize();

         // Add it to the array of chains.
         m_shapeChains.push_back(chain.get());

         if ( !m_combiner )
         {
            // First time through...
            m_combiner = new ossimImageMosaic();
         }
         else
         {
            // Wipe input connections so we can reorder with shapes on top.
            m_combiner->disconnectAllInputs();
         }
         
         // Always put shape files on top.
         const std::vector<ossimImageChain*>::size_type COUNT =
            m_shapeChains.size();
         for (std::vector<ossimImageChain*>::size_type i = 0; i < COUNT; ++i)
         {
            m_combiner->connectMyInputTo(m_shapeChains[i].get());
         }

         // Connect the base image.
         m_combiner->connectMyInputTo(m_imageChain.get());

         // Always call initialize.
         m_combiner->initialize();

         // Setup conditional buttons.
         setupButtons();
         
         // Give it to the widget.
         m_imageWidget->disconnectAllInputs();
         m_imageWidget->connectMyInputTo(m_combiner.get());
         m_imageWidget->refresh();
         
      } // End:  if (itrf)
      
   } // End: if (ih && m_geom)
}

void ossimQtSingleImageWindow::closeImage()
{
   // Disconnect widget.
   if (m_imageWidget)
   {
      m_imageWidget->disconnectAllInputs();
      QString caption = "iview";
      setCaption(caption);
   }

   // Close any shape stuff.
   clearShapeChains();

   m_geom = 0;
   
   // Close the image chain.
   m_imageChain = 0;

   // Clear the rrds method.
   if (m_resolutionLevelMenu)
   {
      m_resolutionLevelMenu->clear();
   }

   // Set up any conditional buttons.
   setupButtons();

   // Refresh.
   if (m_imageWidget)
   {
      m_imageWidget->refresh();
   }
}

void ossimQtSingleImageWindow::exportImage()
{
   if (!m_imageChain)
   {
      QString caption = "Sorry:";
      QString text = "You must open an image first.";
      text += "  Use \"File->Open Image\"\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      return;
   }
   
   ossimString name = "ossimQtIcpDialog";

   // First see if we already have a dialog open for this.
   QWidget* w = ossimQtEditorWidgetManager::instance()->getFromList(name,
                                                                    this);
   if (w)
   {
      w->raise();
      return;
   }

   w = new ossimQtIcpDialog(this, m_imageChain.get());

   // Add to the list so we don't make a duplicate dialog.
   ossimQtEditorWidgetManager::instance()->addToList(w, this);

   w->show();
}

void ossimQtSingleImageWindow::closeWindow()
{
   close(true);
}

void ossimQtSingleImageWindow::displayImage(const ossimFilename& file)
{
   ossimRefPtr<ossimImageHandler> ih = ossimImageHandlerRegistry::instance()->open(file);
   if (!ih)
   {
      QString caption = "Sorry:";
      QString text = "Could not find the image handler for file:\n";
      text += file.c_str();
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      return;
   }

   if (ih->getNumberOfDecimationLevels() == 1)
   {
      QString caption("Question:");
      QString text = "Would you like to build reduced resolution data sets?\n";
      text += "Note:\n";
      text += "This can take some time depending on the size of your image.";
      text += "\nAlternatively use the command line application:  \"img2rr\"";

      int answer = QMessageBox::question( this,
                                          caption,
                                          text,
                                          QMessageBox::Yes,
                                          QMessageBox::No);
      if (answer == QMessageBox::Yes)
      {
         //---
         // We need to listen for the open overview signal to rebuild the
         // m_resolutionLevelMenu.
         //---
         ih->addListener(this);
         buildOverViews(ih.get());
      }
   }

   createImageChain(ih.get());

   createImageModel();

   // Build the resolution level menu.
   buildResolutionLevelMenu();

   // Set conditional buttons on or off.
   setupButtons();

   // Give it to the widget.
   m_imageWidget->connectMyInputTo(m_imageChain.get());
   m_imageWidget->refresh();

   connectMyInputTo(m_imageChain.get());
   QString caption = "iview : ";
   caption += file.file().c_str();
   setCaption(caption);
}

void ossimQtSingleImageWindow::createImageChain(ossimImageHandler* ih)
{
   if (!ih)
   {
      return;
   }
   
   statusBar()->message( QString(" ") );

   if(m_imageChain.valid())
   {
      m_imageChain->disconnect();
      m_imageChain = 0;
   }
   m_imageChain = new ossimImageChain;

   // We need to listen to the chain.
   m_imageChain->addListener(this);

   // Add the image handler.
   if (m_imageChain->addLast(ih) == false)
   {
      m_imageChain = 0;
      return;
   }

   if (ih->getNumberOfOutputBands() > 1)
   {
      // Add a band selector.
      ossimBandSelector* bs = new ossimBandSelector();
      m_imageChain->addFirst(bs);
   }

   if (ih->getNumberOfDecimationLevels())
   {
      ossimRLevelFilter* rf = new ossimRLevelFilter();
      
      // Start with this filter disabled since we're coming up in r0.
      rf->disableSource();

      //---
      // Always override the geometry so that reduced resolution cuts come
      // out with correct scale.
      //---
      rf->setOverrideGeometryFlag(true);

      m_imageChain->addFirst(rf);
   }

   // Add a cache at the end of the chain.
   ossimCacheTileSource* cache = new ossimCacheTileSource();
   m_imageChain->addFirst(cache);

   m_imageChain->initialize();
}

void ossimQtSingleImageWindow::trackImageWidget(ossimQtMouseEvent* event)
{
   if (!event)
   {
      return;
   }
   
   if (!m_imageChain)
   {
      event->getEvent()->ignore();
      return;
   }

   switch(event->getQtEventType())
   {
      case QEvent::MouseButtonPress:
      case QEvent::MouseMove:
      {
         //---
         // We want to track only left clicks or left down and drag.
         //---
         if( (event->getState()  == Qt::LeftButton) ||
             (event->getButton() == Qt::LeftButton) )
         {
            ossimIpt pt = event->getShiftPoint();
            std::ostringstream os;
            os << setiosflags(ios::right)
               << "line:"    << setw(9) << pt.y
               << "    sample:" << setw(9) << pt.x
               << "    pixel value";
            
            ossim_uint8 r;
            ossim_uint8 g;
            ossim_uint8 b;
            m_imageWidget->getRgb(pt, r, g, b);
            
            const ossim_uint32 BANDS =
               m_imageChain->getNumberOfOutputBands();
            switch (BANDS)
            {
               case 1:
                  os << ":" << setw(6) << int(r);
                  break;
               case 2:
                  os << "s:" << setw(6) << int(r) << setw(6) << int(g);
                  break;
               default:
                  os << "s:" << setw(6) << int(r) << setw(6) << int(g)
                     << setw(6) << int(b);
                  break;
            }
            
            QString qs = os.str().c_str();
            statusBar()->message(qs);
         }
         else
         {
            event->getEvent()->ignore();
         }
         break;
      }
      
      default:
      {
         event->getEvent()->ignore();
         break;
      }
   }
}


void ossimQtSingleImageWindow::editImageChain()
{
   if (!m_imageChain)
   {
      QString caption = "Sorry:";
      QString text = "You must open an image first.";
      text += "  Use \"File->Open Image\"\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      return;
   }

   ossimString name = "ossimQtImageChainEditorDialog";

   // First see if we already have a dialog open for this.
   QWidget* w = ossimQtEditorWidgetManager::instance()->getFromList(name,
                                                                    this);
   if (w)
   {
      w->raise();
      return;
   }
      
   ossimQtImageChainEditorDialog* chainEditor
      = new ossimQtImageChainEditorDialog(this,
                                          name.c_str(),
                                          false,
                                          WDestructiveClose);
   chainEditor->setImageWidget(m_imageWidget);
   vector<ossimString> list;
   getAllowedFilterList(list);
   chainEditor->setAvailableFilterList(list);

   // Add to the list so we don't make a duplicate dialog.
   ossimQtEditorWidgetManager::instance()->addToList(chainEditor, this);

   chainEditor->show();
}

void ossimQtSingleImageWindow::about()
{
   ossimString name = "ossimQtIviewAboutDialog";

   // First see if we already have a dialog open for this.
   QWidget* w = ossimQtEditorWidgetManager::instance()->getFromList(name);
   if (w)
   {
      w->raise();
      return;
   }
   
   w = new ossimQtIviewAboutDialog(this);

   // Add to the list so we don't make a duplicate dialog.
   ossimQtEditorWidgetManager::instance()->addToList(w);

   w->show();
}

void ossimQtSingleImageWindow::getAllowedFilterList(vector<ossimString>& list) const
{
   list.push_back(ossimString("ossimBandSelector"));
   list.push_back(ossimString("ossimBrightnessContrastSource"));   
   list.push_back(ossimString("ossimCastTileSourceFilter"));
   list.push_back(ossimString("ossimJpegYCbCrToRgbSource"));
   list.push_back(ossimString("ossimHistogramRemapper"));   
   list.push_back(ossimString("ossimHsiRemapper"));
   list.push_back(ossimString("ossimMeanMedianFilter"));
   list.push_back(ossimString("ossimNBandToIndexFilter"));
   list.push_back(ossimString("ossimPixelFlipper"));
   list.push_back(ossimString("ossimRgbToGreyFilter"));
   list.push_back(ossimString("ossimRLevelFilter"));
   list.push_back(ossimString("ossimScalarRemapper"));
   list.push_back(ossimString("ossimWatermarkFilter"));
}

void ossimQtSingleImageWindow::customEvent(QCustomEvent* event)
{
   if (!m_imageChain) // No image open...
   {
      return;
   }
   
   switch(event->type())
   {
      case OSSIM_QT_EVENT_REFRESH_DISPLAY_ID:
      {
         m_imageWidget->refresh(false);
         break;
      }
      case OSSIM_QT_EVENT_FLUSH_DISPLAY_ID:
      {
         m_imageWidget->refresh(true);
         break;
      }
      default:
      {
         break;
      }
   }
}

void ossimQtSingleImageWindow::displayListEvent(ossimDisplayListEvent& event)
{
   event.addDisplay(this);
}

void ossimQtSingleImageWindow::displayRefreshEvent(ossimDisplayRefreshEvent& /* event */)
{
   m_imageWidget->refresh(false);
}

bool ossimQtSingleImageWindow::canConnectMyInputTo(ossim_int32 /*myInputIndex*/,
                                    const ossimConnectableObject* /* object */)const
{
   return true;
}

void ossimQtSingleImageWindow::buildOverViews(ossimImageHandler* ih)
{
   if (!ih)
   {
      QString caption = "Sorry:";
      QString text = "You must open an image first.";
      text += "  Use \"File->Open Image\"\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      return;
   }

   ossimQtOverviewBuilderDialog* builder =
      new ossimQtOverviewBuilderDialog(this, ih);
   builder->buildClicked();
   delete builder;
}

void ossimQtSingleImageWindow::buildResolutionLevelMenu()
{
   if (!m_resolutionLevelMenu) return;
   
   ossim_uint32 count = m_resolutionLevelMenu->count();
   ossim_uint32 numberOfReducedResSets = 1;
   
   ossimRLevelFilter* rf = getRLevelFilter();
   if (rf)
   {
      numberOfReducedResSets = rf->getNumberOfDecimationLevels();
   }

   if (count != numberOfReducedResSets)
   {
      m_resolutionLevelMenu->clear();
      for (ossim_uint32 i = 0; i < numberOfReducedResSets; ++i)
      {
         int id = static_cast<int>(i);
         QString qs = ossimString::toString(i).c_str();
         m_resolutionLevelMenu->insertItem( qs, id, id );
      }
   }
}

ossimRLevelFilter* ossimQtSingleImageWindow::getRLevelFilter()   
{
   ossimRLevelFilter* rf = 0;
   if (m_imageChain.valid())
   {
      ossimConnectableObject* obj =
         m_imageChain->findFirstObjectOfType("ossimRLevelFilter");
      if (obj)
      {
         rf = PTR_CAST(ossimRLevelFilter, obj);
      }
   }
   return rf;
}

ossim_uint32 ossimQtSingleImageWindow::getCurrentRLevel() 
{
   ossim_uint32 result = 0;
   ossimRLevelFilter* rf = getRLevelFilter();
   if (rf)
   {
      result = rf->getCurrentRLevel();
   }
   return result;
}

ossimImageHandler* ossimQtSingleImageWindow::getImageHandler() 
{
   ossimImageHandler* ih = 0;
   if (m_imageChain.valid())
   {
      //Last object is the most left in the chain.
      ossimObject* obj = m_imageChain->getLastObject();
      if (obj)
      {
         ih = PTR_CAST(ossimImageHandler, obj);
      }
   }
   return ih;
}

void ossimQtSingleImageWindow::createImageModel()
{
   m_geom = 0;
   
   ossimImageHandler* ih = getImageHandler();
   if (ih)
   {
      m_geom = ih->getImageGeometry();
      if (m_geom->getProjection() == 0) // no geometry
      {
         m_geom = 0;
      }
   }
}

void ossimQtSingleImageWindow::transformShapesToImage()
{
   if ( m_shapeChains.size() && m_geom.valid() )
   {
      const std::vector<ossimImageChain*>::size_type COUNT =
         m_shapeChains.size();
      for (std::vector<ossimImageChain*>::size_type i = 0; i < COUNT; ++i)
      {
         ossimObject* obj = m_shapeChains[i]->getLastObject();
         ossimViewInterface* itrf = PTR_CAST(ossimViewInterface, obj);
         if (itrf)
         {
            m_geom->setTargetRrds(getCurrentRLevel());
            
            itrf->setView(m_geom.get()); 
         }
      }
   }
}

// public slot
void ossimQtSingleImageWindow::clearShapeFiles()
{
   // An "Are you sure popup maybe??? (drb)

   // call private method.
   clearShapeChains();

   setupButtons();

   // Reconnect widget to chain.
   if ( m_imageWidget && m_imageChain.valid() )
   {
      m_imageWidget->connectMyInputTo(m_imageChain.get());
      m_imageWidget->refresh();
   }
   
}

void ossimQtSingleImageWindow::clearShapeChains()

{
   if (m_imageWidget)
   {
      m_imageWidget->disconnectAllInputs();
      m_imageWidget->disconnectAllOutputs();
   }
   if (m_combiner.valid())
   {
      m_combiner->disconnect();
      m_combiner = 0;
   }
   if (m_shapeChains.size())
   {
      const std::vector<ossimImageChain*>::size_type COUNT =
         m_shapeChains.size();
      for (std::vector<ossimImageChain*>::size_type i = 0; i < COUNT; ++i)
      {
         m_shapeChains[i]->disconnect();
         m_shapeChains[i] = 0;
      }
      m_shapeChains.clear();
   } 
}

void ossimQtSingleImageWindow::setupButtons()
{
   if (m_fileMenu)
   {
      if ( m_overLayerShapeFileId != -1 )
      {
         bool enable = false;
         if (m_geom.valid())
         {
            enable = true;
         }
         m_fileMenu->setItemEnabled(m_overLayerShapeFileId, enable);
      }
      if ( m_clearShapeFilesId != -1 )
      {
         bool enable = false;
         if ( m_shapeChains.size() )
         {
            enable = true;
         }
         m_fileMenu->setItemEnabled(m_clearShapeFilesId, enable);
      }
   }      
}

// Hidden from use...
ossimQtSingleImageWindow::ossimQtSingleImageWindow(
   const ossimQtSingleImageWindow& /* obj */)
   : QMainWindow(),
     ossimConnectableObject(),
     ossimConnectableDisplayListener()
{
   ossimReferenced::ref();
}

// Hidden from use...
const ossimQtSingleImageWindow& ossimQtSingleImageWindow::operator=(
   const ossimQtSingleImageWindow& /* rhs */)
{
   return *this;
}

   
