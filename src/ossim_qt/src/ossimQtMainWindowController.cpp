//*******************************************************************
// License:  See top level LICENSE.txt file.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtMainWindowController.cpp 19706 2011-06-01 18:48:00Z dburken $
#include <algorithm>
#include <sstream>
#include <qfiledialog.h>
#include <qevent.h>
#include <qdragobject.h>
#include <qvbox.h>
#include <qapplication.h>
#include <qaction.h>
#include <qmessagebox.h>

#include <ossimQtMainWindowController.h>

#include <ossimQtDataManagerListBox.h>
#include <ossimQtDisplayUtility.h>
#include <ossimQtEditorWidgetManager.h>
#include <ossimQtImagelinkerAboutDialog.h>
#include <ossimQtLayerChooser.h>
#include <ossimQtMainWindow.h>
#include <ossimQtMainWindowWorkspace.h>
#include <ossimQtElevationManagerDialog.h>
#include <ossimQtUnitConverterDialog.h>
#include <ossimQtDatumConverterDialog.h>
#include <ossimQtGeometryBuilderDialog.h>
#include <ossimQtImageWindow.h>
#include <ossimQtImageWindowController.h>
#include <ossimQtVceWindow.h>
#include <ossimQtVceWindowController.h>
#include <ossimQtVceComponentDialog.h>
#include <ossimQtUnitConverterDialog.h>
#include <ossimQtDataManagerDialog.h>
#include <ossimDataManager.h>
#include <ossimQtEvent.h>
#include <ossimQtProject.h>
#include <ossimQtOverviewBuilderDialog.h>


#include <ossim/base/ossimGeoidManager.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimKeywordNames.h>
#include <ossim/base/ossimObjectFactoryRegistry.h>
#include <ossim/elevation/ossimElevManager.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimImageRenderer.h>
#include <ossimQtPreferencesDialogController.h>
#include <ossimQtPreferencesDialog.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimNotifyContext.h>
#include <ossim/imaging/ossimImageGeometry.h>
#include <ossim/projection/ossimEquDistCylProjection.h>
#include <ossim/projection/ossimImageViewProjectionTransform.h>

static ossimTrace traceDebug("ossimQtMainWindowController:debug");

ossimQtMainWindowController::ossimQtMainWindowController(ossimQtMainWindow* mainWindow)
:theMainWindow(mainWindow),
theCurrentProject(0),
theElevManagerDialog(0),
theUnitConverterDialog(0),
theDatumConverterDialog(0),
theGeometryBuilderDialog(0),
theLayerManager(0),
theVceComponentDialog(0)
{
   QVBox* vb = new QVBox( theMainWindow );
   vb->setFrameStyle( QFrame::StyledPanel | QFrame::Sunken );
   theMainWindow->setCentralWidget( vb );
   theProjectList.push_back(new ossimQtProject(vb));
   theCurrentProject = theProjectList[0];
   theCurrentProject->show();
   theMainWindow->setCaption(theCurrentProject->getFilename().c_str());
   initializeMenus();
   theMainWindow->setIcon(QPixmap::fromMimeSource("ImageLinkerSplash"));
}

// ___________ display manipulation implementation ______

ossimQtMainWindowController::~ossimQtMainWindowController()
{
   for(int idx = 0; idx < (int)theProjectList.size(); ++idx)
   {
      delete theProjectList[idx];
   }
   theProjectList.clear();
   
   theMainWindow = 0;
}

bool ossimQtMainWindowController::destroyController()
{
   // We need to later add 
   // checks for quitting here
   // and user feedback for saving
   //
   for(int idx = 0; idx < (int)theProjectList.size(); ++idx)
   {
      delete theProjectList[idx];
   }
   
   theProjectList.clear();
   
   theMainWindow = 0;
   
   return true;
}

void ossimQtMainWindowController::initializeMenus()
{
   
}

void ossimQtMainWindowController::preferences()
{
   ossimQtPreferencesDialog dialog(theMainWindow);
   dialog.setModal(true);
   dialog.exec();
   
   initializeMenus();
}

void ossimQtMainWindowController::vceNewChain()
{
   ossimQtVceWindow* vce = new ossimQtVceWindow(theCurrentProject->getWorkspace(), 0, 
                                                WDestructiveClose);
   
   // need to later connect up some signals so to interface to the main data manager for
   // completion of chain designs
   //
   // For now we will just show the chain display
   //
   
   vce->show();
}

void ossimQtMainWindowController::cascadeDisplays()
{
   theCurrentProject->getWorkspace()->cascade();
}

void ossimQtMainWindowController::tileDisplays()
{
   theCurrentProject->getWorkspace()->tile();
}


void ossimQtMainWindowController::minimizeAllDisplays()
{
   theCurrentProject->getWorkspace()->minimizeAll();
}

void ossimQtMainWindowController::restoreAllDisplays()
{  
   theCurrentProject->getWorkspace()->restoreAll();
}

void ossimQtMainWindowController::refreshAllDisplays()
{
   theCurrentProject->getWorkspace()->refreshAll();
}

void ossimQtMainWindowController::closeAllDisplays()
{
   theCurrentProject->getWorkspace()->closeAll();
}

void ossimQtMainWindowController::maximizeActiveDisplay()
{
   if(theCurrentProject->getWorkspace()->activeWindow())
   {
      theCurrentProject->getWorkspace()->activeWindow()->showMaximized();
   }
}

void ossimQtMainWindowController::vceComponentDialog()
{
   if(!theVceComponentDialog)
   {
      theVceComponentDialog =
      new ossimQtVceComponentDialog(theMainWindow,
                                    "Visual Chain Editor Components",
                                    false,
                                    WDestructiveClose);
      connect(theVceComponentDialog,
              SIGNAL(destroyed()),
              this, SLOT(vceComponentDialogDestroyed()));
   }
   theVceComponentDialog->show();
}

// ________ the utilities implementation _____
void ossimQtMainWindowController::openElevationManager()
{
   if(!theElevManagerDialog)
   {
      theElevManagerDialog = new ossimQtElevationManagerDialog(theMainWindow, "Elevation Manager", 
                                                               false, 
                                                               WStyle_Customize | WStyle_NormalBorder | 
                                                               WStyle_Title | WStyle_SysMenu|WDestructiveClose);
      connect(theElevManagerDialog, SIGNAL(destroyed()), this, SLOT(elevationManagerDestroyed()));
   }
   theElevManagerDialog->show();
}



void ossimQtMainWindowController::openUnitConverter()
{
   if(!theUnitConverterDialog)
   {
      theUnitConverterDialog = new ossimQtUnitConverterDialog(theMainWindow, "Unit converter", 
                                                              false, 
                                                              WStyle_Customize | WStyle_NormalBorder | 
                                                              WStyle_Title | WStyle_SysMenu|WDestructiveClose);
      connect(theUnitConverterDialog, SIGNAL(destroyed()), this, SLOT(unitConverterDestroyed()));
      
   }
   theUnitConverterDialog->show();
}

void ossimQtMainWindowController::openDatumConverter()
{
   if(!theDatumConverterDialog)
   {
      theDatumConverterDialog = new ossimQtDatumConverterDialog(theMainWindow, 
                                                                "Datum converter", 
                                                                false, 
                                                                WStyle_Customize | WStyle_NormalBorder | 
                                                                WStyle_Title | WStyle_SysMenu|WDestructiveClose);
      connect(theDatumConverterDialog, SIGNAL(destroyed()), this, SLOT(datumConverterDestroyed()));
   }
   theDatumConverterDialog->show();
}

void ossimQtMainWindowController::openGeometryBuilder()
{
   if(!theGeometryBuilderDialog)
   {
      theGeometryBuilderDialog = new ossimQtGeometryBuilderDialog(theMainWindow, 
                                                                  "eometry Builder", 
                                                                  false, 
                                                                  (WFlags)(WStyle_Customize | WStyle_NormalBorder | 
                                                                           WStyle_Title | WStyle_SysMenu|WDestructiveClose));
      connect(theGeometryBuilderDialog, SIGNAL(destroyed()), this, SLOT(geometryBuilderDialogDestroyed()));
      theGeometryBuilderDialog->show();
   }
   else
   {
      theGeometryBuilderDialog->show();
      theGeometryBuilderDialog->raise();
   }
}

void ossimQtMainWindowController::vceComponentDialogDestroyed()
{
   theVceComponentDialog = 0;
}

void ossimQtMainWindowController::elevationManagerDestroyed()
{
   theElevManagerDialog=0;
}

void ossimQtMainWindowController::unitConverterDestroyed()
{
   theUnitConverterDialog=0;
}

void ossimQtMainWindowController::datumConverterDestroyed()
{
   theDatumConverterDialog=0;
}

void ossimQtMainWindowController::geometryBuilderDialogDestroyed()
{
   theGeometryBuilderDialog = 0;
}

void ossimQtMainWindowController::histogramMatch()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to Match");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyHistogramMatch(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeHistogramMatchSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::colorNormalizedFusion()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   
   layerChooser->setCaption("Choose Layers to Fuse Using Color Normalized Fusion");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyColorNormalizedFusion(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeFusionSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::localCorrelationFusion()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   
   layerChooser->setCaption("Choose Layers to Fuse Using Local Correlation Fusion");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyLocalCorrelationFusion(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeFusionSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}
void ossimQtMainWindowController::SFIMFusion()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   
   layerChooser->setCaption("Choose Layers to Fuse Using Local Correlation Fusion");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applySFIMFusion(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeFusionSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}


void ossimQtMainWindowController::applyHistogramMatch(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   ossimConnectableObject* result = theCurrentProject->getDataManager()->createStandardHistogramMatch(selectedObjects,
                                                                                                      0,
                                                                                                      "ossimFeatherMosaic");
   if(result)
   {
      emit closeHistogramMatchSelector();
      
      displayLayer(result, false);
   }
}


void ossimQtMainWindowController::applyColorNormalizedFusion(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyFusionCombiner(ossimString("ossimColorNormalizedFusion"),
                       selectedObjects);
}

void ossimQtMainWindowController::applyLocalCorrelationFusion(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyFusionCombiner(ossimString("ossimLocalCorrelationFusion"),
                       selectedObjects);
}

void ossimQtMainWindowController::applySFIMFusion(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyFusionCombiner(ossimString("ossimSFIMFusion"),
                       selectedObjects);
}

void ossimQtMainWindowController::applyFusionCombiner(const ossimString& className,
                                                      ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   if(selectedObjects.size() != 2)
   {
      
   }
   else
   {
      ossimString errorMessage = "";
      bool layersOk = false;
      
      ossimImageSource* layer1 = PTR_CAST(ossimImageSource, selectedObjects[0].get());
      ossimImageSource* layer2 = PTR_CAST(ossimImageSource, selectedObjects[1].get());
      
      if(layer1&&layer2)
      {
         int bands1 = layer1->getNumberOfOutputBands();
         int bands2 = layer2->getNumberOfOutputBands();
         
         if((bands1 >= 3)&&(bands2==1))
         {
            layersOk = true;
         }
         if(!layersOk)
         {
            if(bands1 == 1)
            {
               std::swap(layer1, layer2);
               std::swap(bands1, bands2);
               std::swap(selectedObjects[0], selectedObjects[1]);
            }
            if((bands1 >= 3)&&(bands2 == 1))
            {
               layersOk = true;
            }
            else
            {
               errorMessage = "Need to have one 3 or greater band layer and one single band layer";
            }
         }
         if(layersOk)
         {
            emit closeFusionSelector();
            ossimConnectableObject* resultObj = theCurrentProject->getDataManager()->createStandardFusionChain(className, selectedObjects);
            if(resultObj)
            {
               displayLayer(resultObj, false);
            }
            else
            {
               errorMessage = "Unable to create fusion " + className;
            }
         }
      }
      else
      {
         errorMessage = "All selected layers were not found in the data manager";
      }
      
      if(errorMessage != "")
      {
         QMessageBox message("Fusion Error", errorMessage.c_str(), QMessageBox::Warning, QMessageBox::Ok,
                             QMessageBox::NoButton,  QMessageBox::NoButton, theMainWindow);
         message.exec();
      }
   }
}

void ossimQtMainWindowController::simpleCombiner()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   
   layerChooser->setCaption("Choose Layers to Mosaic");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applySimpleCombiner(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::blendCombiner()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to Blend");
   
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyBlendCombiner(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::bandMergeCombiner()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   
   layerChooser->setCaption("Choose Layers to Merge Bands");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyBandMergeCombiner(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::featherCombiner()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to Feather");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyFeatherCombiner(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::orthoCombiner()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to Feather");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyOrthoCombiner(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::maxCombiner()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to do a Max combine");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyMaxCombiner(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::closestToCenterCombiner()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to do a closest to center combine");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyClosestToCenterCombiner(ossimConnectableObject::ConnectableObjectList>&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}
void ossimQtMainWindowController::twoColorViewCombiner()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to do a Two color view");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyTwoColorViewCombiner(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::combinerFactory()
{
   
}

void ossimQtMainWindowController::hillShade()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to Hill Shade");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyHillShade(ossimConnectableObject::ConnectableObjectLists&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::elevationNormals()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layers to Apply Normal Calculations");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyElevationNormals(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeNormalSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::topographicCorrection()
{
   ossimQtLayerChooser* layerChooser = new ossimQtLayerChooser(theMainWindow, 
                                                               "",
                                                               true,
                                                               WDestructiveClose);
   layerChooser->setCaption("Choose Layer to Correct and Normal Layer");
   connect(layerChooser, SIGNAL(applySelected(ossimConnectableObject::ConnectableObjectList&)),
           this, SLOT(applyTopographicCorrection(ossimConnectableObject::ConnectableObjectList&)));
   connect(this, SIGNAL(closeCombinerSelector()), layerChooser, SLOT(close()));
   
   layerChooser->show();
}

void ossimQtMainWindowController::applySimpleCombiner(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyCombiner("ossimImageMosaic",
                 selectedObjects);
}

void ossimQtMainWindowController::applyBandMergeCombiner(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyCombiner("ossimBandMergeSource",
                 selectedObjects);
}

void ossimQtMainWindowController::applyFeatherCombiner(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyCombiner("ossimFeatherMosaic",
                 selectedObjects);
}

void ossimQtMainWindowController::applyOrthoCombiner(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyCombiner("ossimOrthoImageMosaic",
                 selectedObjects);
}

void ossimQtMainWindowController::applyBlendCombiner(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyCombiner("ossimBlendMosaic",
                 selectedObjects);
}

void ossimQtMainWindowController::applyMaxCombiner(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyCombiner("ossimMaxMosaic",
                 selectedObjects);
}

void ossimQtMainWindowController::applyClosestToCenterCombiner(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyCombiner("ossimClosestToCenterCombiner",
                 selectedObjects);
   
}

void ossimQtMainWindowController::applyTwoColorViewCombiner(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   applyCombiner("ossimTwoColorView",
                 selectedObjects);
}

void ossimQtMainWindowController::applyCombiner(
                                                const ossimString& className,
                                                ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   if(selectedObjects.size()  < 1)
   {
      return;
   }
   emit closeCombinerSelector();
   
   //---
   // Check 
   //---
   
   ossimConnectableObject* resultObj = (ossimConnectableObject*)0;
   if(className == "ossimOrthoImageMosaic")
   {
      resultObj = theCurrentProject->getDataManager()->createStandardOrthoMosaic(selectedObjects);
   }
   else
   {
      resultObj = theCurrentProject->getDataManager()->createStandardMosaic(selectedObjects, className);
   }
   if(resultObj)
   {
      displayLayer(resultObj, false);
   }
}

void ossimQtMainWindowController::applyTopographicCorrection(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   if(selectedObjects.size() == 2)
   {
      ossimConnectableObject* planeNormals = 0;
      int idx = 0;
      
      planeNormals = selectedObjects[0]->findObjectOfType("ossimImageToPlaneNormalFilter",
                                                          ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT,
                                                          true);
      if(!planeNormals)
      {
         planeNormals = selectedObjects[1]->findObjectOfType("ossimImageToPlaneNormalFilter",
                                                             ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT,
                                                             true);
         idx = 1;
      }
      
      if(!planeNormals)
      {
         QMessageBox message("Topographic Correction Error", "Need elevation normals", QMessageBox::Warning, QMessageBox::Ok,
                             QMessageBox::NoButton,  QMessageBox::NoButton, theMainWindow);
         message.exec();
      }
      else
      {
         if(idx == 0)
         {
            std::swap(selectedObjects[0], selectedObjects[1]);
         }
      }
      applyCombiner("ossimTopographicCorrectionFilter",
                    selectedObjects);
   }
   else
   {
      QMessageBox message("Topographic Correction Error", "Need 2 layers for input, correction layer and elevation normals layer", QMessageBox::Warning, QMessageBox::Ok,
                          QMessageBox::NoButton,  QMessageBox::NoButton, theMainWindow);
      message.exec();
   }
}

void ossimQtMainWindowController::applyHillShade(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   if(selectedObjects.size() > 0)
   {
      ossimConnectableObject* planeNormals = 0;
      int idx = 0;
      
      planeNormals = selectedObjects[0]->findObjectOfType("ossimImageToPlaneNormalFilter",
                                                          ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT,
                                                          true);
      if(!planeNormals&&(selectedObjects.size() > 1))
      {
         planeNormals = selectedObjects[1]->findObjectOfType("ossimImageToPlaneNormalFilter",
                                                             ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT,
                                                             true);
         idx = 1;
      }
      
      if(!planeNormals)
      {
         QMessageBox message("Topographic Correction Error", "Need elevation normals", QMessageBox::Warning, QMessageBox::Ok,
                             QMessageBox::NoButton,  QMessageBox::NoButton, theMainWindow);
         message.exec();
      }
      else
      {
         if(idx != 0)
         {
            std::swap(selectedObjects[0], selectedObjects[1]);
         }
      }
      applyCombiner("ossimBumpShadeTileSource", selectedObjects);
   }
}


void ossimQtMainWindowController::applyElevationNormals(ossimConnectableObject::ConnectableObjectList& selectedObjects)
{
   if(selectedObjects.size() > 0)
   {
      std::map<QObject*,QObject*> displayList;
      ossimConnectableObject* obj = 0;
      emit closeNormalSelector();
      for(int idx = 0; idx < (int)selectedObjects.size(); ++idx)
      {
         if(selectedObjects[idx].valid())
         {
            obj = selectedObjects[idx]->findObjectOfType("ossimImageToPlaneNormalFilter",
                                                         ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT,
                                                         true);
            if(!obj)
            {
               ossimConnectableObject* parentObj = PTR_CAST(ossimConnectableObject,
                                                            selectedObjects[idx].get());
               ossimConnectableObject* resultingChain = theCurrentProject->getDataManager()->insertObject("ossimImageToPlaneNormalFilter",
                                                                                                          parentObj->getId());
               if(resultingChain)
               {
                  ossimPropertyEvent evt(resultingChain);
                  resultingChain->fireEvent(evt);
                  resultingChain->propagateEventToOutputs(evt);
                  ossimQtDisplayUtility::findAllDisplays(displayList,
                                                         resultingChain);
               }
            }
         }
      }
      ossimQtDisplayUtility::flushAllDisplays(displayList);
   }
}
// ___________basic layer loading implementation___________

void ossimQtMainWindowController::openImageFile(const char* filename)
{
   if(traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
      << "Trying to open image file = " << filename << std::endl;
   }
   
   if(filename)
   {
      ossimConnectableObject::ConnectableObjectList  result = theCurrentProject->getDataManager()->createStandardProjectionChain(filename);
      
      ossim_uint32 size = result.size();
      
      if (size == 0)
      {
         QString caption = "Sorry:";
         QString text = "Could not find the image handler for file:\n";
         text += filename;
         QMessageBox::information( theMainWindow,
                                  caption,
                                  text,
                                  QMessageBox::Ok );
         return;
      }
      
      bool someNotDisplayedFlag = false;
      for(ossim_uint32 idx = 0; idx < size; ++idx)
      {
         checkForImageGeometry(result[idx].get());
         checkElevation(result[idx].get());
         checkForOverviews(result[idx].get());
         if(!result[idx]->findObjectOfType("ossimWorldWindHandler",
                                           ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT,
                                           true))
         {
            displayLayer(result[idx].get(), true);
         }
         else
         {
            someNotDisplayedFlag = true;
         }
      }
      if(someNotDisplayedFlag)
      {
         QMessageBox::information( theMainWindow,
                                  "Some layers not displayed",
                                  "Remote data loaders detected, Open layer manager to display these layers manually",
                                  QMessageBox::Ok );
      }
   }
}

void ossimQtMainWindowController::checkForImageGeometry(ossimConnectableObject* obj) const
{
   if (!obj) return;
   
   ossimImageChain* chain = PTR_CAST(ossimImageChain, obj);
   
   if (!chain) return;
   
   ossimRefPtr<ossimImageGeometry> geom = chain->getImageGeometry();
   
   if(geom.valid()&&geom->getProjection())
   {
      return;
   }
   
   // If we get here we have an image chain with no geomtry info.
   QString caption("Question:");
   QString text = "Your image has no input projection.\n";
   text += "Would you like to create a default projection to work with?";
   int answer = QMessageBox::question( theMainWindow,
                                      caption,
                                      text,
                                      QMessageBox::Yes,
                                      QMessageBox::No);
   if (answer == QMessageBox::Yes)
   {
      ossimImageSource* last = chain->getLastSource();
      ossimImageHandler* ih = PTR_CAST(ossimImageHandler, last);
      if (ih)
      {
         ossimEquDistCylProjection* proj = new ossimEquDistCylProjection;
         proj->setMetersPerPixel(ossimDpt(1.0, 1.0));
         ossimImageGeometry* geom = new ossimImageGeometry(0, proj);
         // Set the image handler to a default projection.
         ih->setImageGeometry(geom);
         chain->initialize();
      }
      else
      {
         caption = "Sorry:";
         text = "Could not find the image handler.\n";
         QMessageBox::information( theMainWindow,
                                  caption,
                                  text,
                                  QMessageBox::Ok );
      }
   }
   else
   {
      caption = "OK:";
      text = "You will not be able to zoom in and out.\n";
      text += "Even if you have overviews...";
      QMessageBox::information( theMainWindow,
                               caption,
                               text,
                               QMessageBox::Ok );
   }
}

void ossimQtMainWindowController::checkElevation(
                                                 ossimConnectableObject* obj) const
{
   if (!obj)
   {
      return;
   }
   
   ossimImageRenderer* renderer =
   (ossimImageRenderer*)obj->findObjectOfType(
                                              "ossimImageRenderer",
                                              ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT);
   if(renderer)
   {
      ossimImageViewProjectionTransform* trans =
      PTR_CAST(ossimImageViewProjectionTransform,
               renderer->getImageViewTransform());
      if(trans)
      {
         ossimRefPtr<ossimImageGeometry> geom = trans->getImageGeometry();
         if (geom.valid())
         {
            if (geom->isAffectedByElevation())
            {
               // Get the ground point of the corner.
               ossimDpt dpt(0.0, 0.0);
               ossimGpt gpt;
               geom->localToWorld(dpt, gpt);
               
               //---
               // Only need to test Ellipsoidal height now for te elevation databases
               // handle the shifts if it's a valid MSL height
               //---
               ossim_float64 d = ossimElevManager::instance()->
               getHeightAboveEllipsoid(gpt);
               
               if (ossim::isnan(d) == false) // Has good msl post, check geoid.
               {
                  d = ossimGeoidManager::instance()->offsetFromEllipsoid(gpt);
                  
                  if (ossim::isnan(d) == false) // Has good geoid post.
                  {
                     return;
                  }
               }
               
               // Issue warning to user opening image.
               QString caption = "WARNING!";
               QString text = "\
               Your input image projection is affected by elevation;\n \
               however, we could not get the height for this image.\n\
               This can significantly reduce the accuracy! You should\n\
               check the elevation set up in your ossim preferences,\n\
               or perhaps you need to download the appropriate\n\
               elevation cell(s). Run command line application\n\
               \"ossim_height\" to test.\n\
               e.g. \"ossim_height ";
               text += ossimString::toString(gpt.lat, 5).c_str();
               text += " ";
               text += ossimString::toString(gpt.lon, 5).c_str();
               text += "\"\n\
               There should be no \"nan\" (not a number) values in the\n\
               resulting output.";
               QMessageBox::information( theMainWindow,
                                        caption,
                                        text,
                                        QMessageBox::Ok ); 
            }
         }
      }
   }
}

void ossimQtMainWindowController::checkForOverviews(ossimConnectableObject* obj)
const
{
   if (!obj) return;
   
   ossimImageChain* chain = PTR_CAST(ossimImageChain, obj);
   
   if (!chain) return;
   
   // Get the image handler.
   ossimImageSource* last = chain->getLastSource();
   ossimImageHandler* ih = PTR_CAST(ossimImageHandler, last);
   if (ih)
   {
      if (ih->getNumberOfDecimationLevels() == 1)
      {
         QString caption("Question:");
         QString text = "Would you like to build reduced resolution data sets?\n";
         text += "Note:\n";
         text += "This can take some time depending on the size of your image.";
         text += "\nAlternatively use the command line application:  \"img2rr\"";
         
         int answer = QMessageBox::question( theMainWindow,
                                            caption,
                                            text,
                                            QMessageBox::Yes,
                                            QMessageBox::No);
         if (answer == QMessageBox::Yes)
         {
            buildOverViews(ih);
         }
      }
   }
}

void ossimQtMainWindowController::buildOverViews(ossimImageHandler* ih) const
{
   if (!ih)
   {
      QString caption = "Sorry:";
      QString text = "You must open an image first.";
      text += "  Use \"File->Open Image\"\n";
      QMessageBox::information( theMainWindow,
                               caption,
                               text,
                               QMessageBox::Ok );
      return;
   }
   
   ossimQtOverviewBuilderDialog* builder =
   new ossimQtOverviewBuilderDialog(theMainWindow, ih);
   builder->buildClicked();
   delete builder;
}

void ossimQtMainWindowController::displayAboutDialog()
{
   ossimString name = "ossimQtImagelinkerAboutDialog";
   
   // First see if we already have a dialog open for this.
   QWidget* w = ossimQtEditorWidgetManager::instance()->getFromList(name);
   if (w)
   {
      w->raise();
      return;
   }
   
   w = new ossimQtImagelinkerAboutDialog(theMainWindow);
   
   // Add to the list so we don't make a duplicate dialog.
   ossimQtEditorWidgetManager::instance()->addToList(w);
   
   w->show();
   
#if 0
   imageInfo->show();
   QString caption = "About ImageLinker";
   QString text    = "\nVersion 1.5";
   text += "\nRelease 5";
   QMessageBox::about(theMainWindow,
                      caption,
                      text);
#endif
}

void ossimQtMainWindowController::openImageFileLayer()
{
   ossimImageHandlerFactoryBase::UniqueStringList stringList;
   
   ossimImageHandlerRegistry::instance()->getSupportedExtensions(stringList);
   
   ossim_uint32 idx = 0;
   QString extString = "Images(";
   for(idx = 0; idx < stringList.size(); ++idx)
   {
      extString += ("*."+stringList[idx]).c_str();
      if((idx+1) != stringList.size())
      {
         extString += " ";
      }
   }
   extString += ");;Vectors(*shp );;All Files(*)";
   
   QStringList filenames = QFileDialog::getOpenFileNames(extString,//"All Files(*);;Images (*.adf *.ccf *.dem *.DEM *.dt1 *.dt0 *.dt2 *.hdr *.hgt *.jpg *.jpeg *.img *.doqq *.fst *.FST *.nitf *.NTF *.ntf *.ras *.sid *.tif *.tiff *.toc *.TOC *.png *.jp2);;Vectors(*.shp dht *.tab)",
                                                         QString::null,
                                                         theMainWindow,
                                                         "open file dialog",
                                                         "Choose a file to open");
   QStringList::Iterator it;
   for(it = filenames.begin(); it != filenames.end(); ++it)
   {
      openImageFile((*it).ascii());
   }
}

void ossimQtMainWindowController::displayLayer(ossimConnectableObject* obj, bool fitToWindowFlag)
{
   if(obj)
   {
      ossimQtImageWindow* iw = new ossimQtImageWindow(theCurrentProject->getWorkspace(), 0, 
                                                      WDestructiveClose);
      
      iw->addInputSource(obj);
      iw->show();
      if(fitToWindowFlag)
      {
         iw->controller()->fitToWindow();
      }
   }
}

void ossimQtMainWindowController::displayLayer(ossim_int32 id, bool fitToWindowFlag)
{
   ossimConnectableObject* obj = theCurrentProject->getDataManager()->getObject(ossimId(id));
   if(obj)
   {
      displayLayer(obj, fitToWindowFlag);
   }
}

void ossimQtMainWindowController::displayLayerManager()
{
   if(!theLayerManager)
   {
      theLayerManager = new ossimQtDataManagerDialog(theMainWindow,
                                                     "Layer manager", 
                                                     false, 
                                                     WStyle_Customize | WStyle_NormalBorder | 
                                                     WStyle_Title | WStyle_SysMenu|WDestructiveClose);
      
      connect(theLayerManager, SIGNAL(destroyed()), this, SLOT(layerManagerDestroyed()));
   }
   
   theLayerManager->show();
}

void ossimQtMainWindowController::layerManagerDestroyed()
{
   theLayerManager=0;
}


// drag and drop events
//
bool ossimQtMainWindowController::acceptsDragEvent(QDragEnterEvent* event)
{
   return QTextDrag::canDecode(event);
}

void ossimQtMainWindowController::dropEvent(QDropEvent* event)
{
   QString result;
   QString filename;
   ossimKeywordlist kwl;
   
   if(QTextDrag::decode(event, result))
   {
      ossimString tempString = result.ascii();
      stringstream kwlStream(tempString.c_str());
      bool kwlFlag = false;
      tempString = tempString.substitute("%5c",
                                         "\\",
                                         true);
      tempString = tempString.substitute("%20",
                                         " ",
                                         true);
      result = tempString.c_str();
      if(kwl.parseStream(kwlStream))
      {
         const char* type = kwl.find(ossimKeywordNames::TYPE_KW);
         if(type)
         {
            if(ossimString(type) == "ossimDataManagerObjectList")
            {
               ossimString regExpression =  ossimString("^(") + "object[0-9]+.)";
               std::vector<ossimString> keys =
               kwl.getSubstringKeyList( regExpression );
               int numberOfObjects = keys.size();
               int idx = 0;
               for(idx = 0; idx < numberOfObjects; ++idx)
               {
                  const char* id = kwl.find(keys[idx]+"id");
                  if(id)
                  {
                     displayLayer(ossimString(id).toInt(), false);
                  }
               }
            }
            kwlFlag = true;
         }
      }
      if(!kwlFlag) // check to see if they were image names drag from somewhere else
      {
         
         const char* s = result.ascii();
         const char* sEnd = result.ascii()+result.length();
         
         while(s < sEnd)
         {
            filename = "";
            while((*s!='\0')&&
                  (*s != '\n')&&
                  (s < sEnd)&&
                  (*s != '\r'))
            {
               filename += *s;
               ++s;
            }
            ++s;
            filename += '\0';
            if(filename != "")
            {
               filename = filename.remove("file:");
               filename = filename.replace("///", "/", false);
               ossimFilename tempFile = filename.ascii();
               if(tempFile.exists())
               {
                  if(tempFile.ext().downcase() == "prj")
                  {
                     openProject(tempFile);
                  }
                  else
                  {
                     openImageFile(filename);
                  }
               }
            }
         }
      }
   }
}


void ossimQtMainWindowController::openProject()
{
   if(theCurrentProject)
   {
      QString filename = QFileDialog::getOpenFileName(QString::null, "Ossim Project (*.prj)");
      if(filename != QString::null)
      {
         openProject(ossimFilename(filename.ascii()));
      }
      else
      {
         ossimString des = theCurrentProject->getDescription();
         if(des = "")
         {
            des = theCurrentProject->getFilename();
         }
         theMainWindow->setCaption(des.c_str());
      }
   }
}

void ossimQtMainWindowController::openProject(const ossimFilename& projectFile)
{
   theCurrentProject->close();
   theCurrentProject->open(projectFile);
   ossimString des = theCurrentProject->getDescription();
   
   if(des = "")
   {
      des = theCurrentProject->getFilename();
   }
   theMainWindow->setCaption(des.c_str());
}

void ossimQtMainWindowController::saveProject()
{
   if(theCurrentProject)
   {
      if(theCurrentProject->getFilename().contains("unnamed"))
      {
         QString filename = QFileDialog::getSaveFileName(QString::null, "Ossim Project (*.prj)");
         if(filename != QString::null)
         {
            theCurrentProject->setFilename(filename.ascii());
            theCurrentProject->save();
         }
      }
      else
      {
         theCurrentProject->save();
      }
      ossimString des = theCurrentProject->getDescription();
      
      if(des == "")
      {
         des = theCurrentProject->getFilename();
      }
      theMainWindow->setCaption(des.c_str());
   }  
}

void ossimQtMainWindowController::saveAsProject()
{
   if(theCurrentProject)
   {
      QString filename = QFileDialog::getSaveFileName(QString::null, "Ossim Project (*.prj)");
      if(filename != QString::null)
      {
         theCurrentProject->setFilename(filename.ascii());
         theCurrentProject->save();
      }
      ossimString des = theCurrentProject->getDescription();
      
      if(des == "")
      {
         des = theCurrentProject->getFilename();
      }
      theMainWindow->setCaption(des.c_str());
   }  
}

void ossimQtMainWindowController::newProject()
{
   closeProject();
   if(theCurrentProject)
   {
      theCurrentProject->setDirtyFlag(true);
   }
}

void ossimQtMainWindowController::closeProject()
{
   if(theCurrentProject)
   {
      if(theCurrentProject->isDirty())
      {            
         switch(QMessageBox::question(theMainWindow,
                                      QString("Save Project -- Ossim"),
                                      QString("Current Project has been Modified.\nDo you want to save it?"),
                                      QString("&Yes"),
                                      QString("&No")))
         {
            case 0:
               saveProject();
               break;
               
            case 1:
               break;
         }
      }
      
      theCurrentProject->close();
      ossimString des = theCurrentProject->getDescription();
      
      if(des == "")
      {
         des = theCurrentProject->getFilename();
      }
      theMainWindow->setCaption(des.c_str());
   }
}

void ossimQtMainWindowController::exitProject()
{
   if(theCurrentProject)
   {
      if(theCurrentProject->isDirty())
      {
         switch(QMessageBox::question(theMainWindow,
                                      QString("Save Project -- Ossim"),
                                      QString("Current Project has been Modified.\nDo you want to save it?"),
                                      QString("&Yes"),
                                      QString("&No")))
         {
            case 0:
               saveProject();
               break;
               
            case 1:
               break;
         }
      }
      theCurrentProject->close();
   }
   // later we need to set the current to the next project
   // for now since we only have one we will force an exit;
   theMainWindow->close(true);
}


void ossimQtMainWindowController::customEvent(QCustomEvent* evt)
{
   switch(evt->type())
   {
      case OSSIM_QT_EVENT_REFRESH_DISPLAY_ID:
      {
         break;
      }
      case OSSIM_QT_EVENT_DISPLAY_LIST_ID:
      {
         break;
      }
      case OSSIM_QT_EVENT_DISPLAY_GEO_VIEW_ID:
      {
         ossimQtCustomEvent* event = (ossimQtCustomEvent*)evt;
         event->setPropagating();
         theCurrentProject->getWorkspace()->sendEventToAll(event);
         
         break;
      }
      case OSSIM_QT_EVENT_RESAMPLER_ID:
      {
         ossimQtCustomEvent* event = (ossimQtCustomEvent*)evt;
         event->setPropagating();
         theCurrentProject->getWorkspace()->sendEventToAll(event);
         
         break;
      }
      case OSSIM_QT_EVENT_TRACK_POSITION_ID:
      {
         ossimQtCustomEvent* event = (ossimQtCustomEvent*)evt;
         event->setPropagating();
         theCurrentProject->getWorkspace()->sendEventToAll(event);
         
         break;
      }
      case OSSIM_QT_EVENT_DISPLAY_CHAIN_ID:
      {
         ossimQtDisplayChainEvent* tempEvt = (ossimQtDisplayChainEvent*)evt;
         displayLayer(tempEvt->getId());
         
         break;
      }
      case OSSIM_QT_EVENT_GET_DATA_MANAGER:
      {
         ossimQtGetDataManagerEvent* tempEvt = (ossimQtGetDataManagerEvent*)evt;
         tempEvt->setDataManager(theCurrentProject->getDataManager());
         
         break;
      }
      case OSSIM_QT_EVENT_GET_PROJECT:
      {
         ossimQtGetProjectEvent* tempEvt = (ossimQtGetProjectEvent*)evt;
         tempEvt->setProject(theCurrentProject);
         
         break;
      }
      case OSSIM_QT_EVENT_QUERY_OBJECT_ALLOCATED:
      {
         ossimQtQueryObjectAllocationEvent* tempEvent = (ossimQtQueryObjectAllocationEvent*)evt;
         ossim_uint32 idx = 0;
         
         for(idx = 0; idx < theProjectList.size(); ++idx)
         {
            if(theProjectList[idx]->getDataManager())
            {
               std::vector<ossimString> classNameList;
               tempEvent->getQueryList(classNameList);
               
               if(theProjectList[idx]->getDataManager()->hasObjectsOfType(classNameList))
               {
                  tempEvent->setObjectsAllocatedFlag();
               }
            }
         }
         theCurrentProject->getWorkspace()->sendEventToAll(tempEvent);
         
         break;
      }
      case OSSIM_QT_EVENT_ADD_IMAGE_FILE:
      {
         ossimQtAddImageFileEvent* tempEvent = (ossimQtAddImageFileEvent*)evt;
         if(tempEvent)
         {
            if(tempEvent->getFilename().exists())
            {
               openImageFile(tempEvent->getFilename());
            }
         }
         break;
      }
      default:
      {
         break;
      }
   }
}
