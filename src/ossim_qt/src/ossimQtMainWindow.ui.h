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
// $Id: ossimQtMainWindow.ui.h 13326 2008-07-28 16:01:50Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
void ossimQtMainWindow::dragEnterEvent(QDragEnterEvent* event)
{
  event->accept(theController->acceptsDragEvent(event));
}

void ossimQtMainWindow::dropEvent(QDropEvent* event)
{
  theController->dropEvent(event);
}

void ossimQtMainWindow::destroy()
{
    if(theController)
    {
	delete theController;
	theController=NULL;
    }
}

void ossimQtMainWindow::init()
{
    theController = new ossimQtMainWindowController(this);
}

ossimQtMainWindowController* ossimQtMainWindow::getController()
{
  return theController;
}

void ossimQtMainWindow::windowCascade_activated()
{
  theController->cascadeDisplays();
}


void ossimQtMainWindow::windowTile_activated()
{
  theController->tileDisplays();
}


void ossimQtMainWindow::windowMinimizeAll_activated()
{
  theController->minimizeAllDisplays();
}


void ossimQtMainWindow::windowCloseAll_activated()
{
  theController->closeAllDisplays();
}


void ossimQtMainWindow::ActionwindowMaximize_activated()
{
  theController->maximizeActiveDisplay();
}


void ossimQtMainWindow::projectExitAction_activated()
{
    theController->exitProject();
}


void ossimQtMainWindow::projectOpenAction_activated()
{
    theController->openProject();
}


void ossimQtMainWindow::projectSaveAction_activated()
{
    theController->saveProject();
}


void ossimQtMainWindow::projectSaveAsAction_activated()
{
    theController->saveAsProject();
}

void ossimQtMainWindow::projectNewAction_activated()
{
    theController->newProject();
}

void ossimQtMainWindow::projectCloseAction_activated()
{
    theController->closeProject();
}

void ossimQtMainWindow::utilitiesElevationManagerAction_activated()
{
  theController->openElevationManager();
}


void ossimQtMainWindow::utilitiesUnitConverterAction_activated()
{
  theController->openUnitConverter();
}


void ossimQtMainWindow::utilitiesDatumConverterAction_activated()
{
  theController->openDatumConverter();
}


void ossimQtMainWindow::layerImportFileAction_activated()
{

}


void ossimQtMainWindow::layerCombineLayersAction_activated()
{

}


void ossimQtMainWindow::layerOpenFileAction_activated()
{
  theController->openImageFileLayer();
}


void ossimQtMainWindow::displayLayerAction_activated()
{
}

void ossimQtMainWindow::customEvent(QCustomEvent* evt)
{
   QApplication::sendEvent(theController, evt);
}


void ossimQtMainWindow::windowRestoreAllAction_activated()
{
    theController->restoreAllDisplays();
}


void ossimQtMainWindow::windowRefreshAllAction_activated()
{
    theController->refreshAllDisplays();
}


void ossimQtMainWindow::ossimQtMainWindow_usesTextLabelChanged( bool )
{

}


void ossimQtMainWindow::layerManager_activated()
{
    theController->displayLayerManager();
}



void ossimQtMainWindow::layerFusionColorNormalizedAction_activated()
{
    theController->colorNormalizedFusion();
}

void ossimQtMainWindow::layerFusionLocal_CorrelationAction_activated()
{
   if(theController)
   {
      theController->localCorrelationFusion();
   }
}

void ossimQtMainWindow::layerCombineBandMergeAction_activated()
{
    theController->bandMergeCombiner();
}


void ossimQtMainWindow::layerCombineBlendAction_activated()
{
    theController->blendCombiner();
}


void ossimQtMainWindow::layerCombineFeatherAction_activated()
{
    theController->featherCombiner();
}


void ossimQtMainWindow::layerCombineMosaicAction_activated()
{
    theController->simpleCombiner();
}

void ossimQtMainWindow::layerCombineOrthoAction_activated()
{
    theController->orthoCombiner();
}

void ossimQtMainWindow::layerElevationHillShadeAction_activated()
{
    theController->hillShade();
}


void ossimQtMainWindow::layerElevationNormalsAction_activated()
{
    theController->elevationNormals();
}


void ossimQtMainWindow::layerCorrectionTopographicAction_activated()
{
    theController->topographicCorrection();
}


void ossimQtMainWindow::layerHistogramMatchAction_activated()
{
    theController->histogramMatch();
}


void ossimQtMainWindow::vceNewChainAction_activated()
{
    theController->vceNewChain();
}


void ossimQtMainWindow::vceComponentDialogAction_activated()
{
   theController->vceComponentDialog();
}


void ossimQtMainWindow::projectPreferencesAction_activated()
{
    if(theController)
    {
	theController->preferences();
    }
}


void ossimQtMainWindow::helpAboutActionActivated()
{
    if (theController)
    {
	theController->displayAboutDialog();
    }
}


void ossimQtMainWindow::layerCombinerMaxActionActivated()
{
    if(theController)
    {
	theController->maxCombiner();
    }
}


void ossimQtMainWindow::layerCombinerFactoryActionActivated()
{
    if(theController)
    {
	theController->combinerFactory();
    }
}


void ossimQtMainWindow::layerCombinerClosestPtAction_activated()
{
   if(theController)
   {
      theController->closestToCenterCombiner();
   }
   
}
void ossimQtMainWindow::layerCombinerTwoColorViewAction_activated()
{
   if(theController)
   {
      theController->twoColorViewCombiner();
   }
   
}


void ossimQtMainWindow::layerFusionLocalCorrelationAction_activated()
{
    if(theController)
    {
	theController->localCorrelationFusion();
    }
}


void ossimQtMainWindow::layerFusionSFIMAction_activated()
{
    if(theController)
    {
	theController->SFIMFusion();
    }
}


void ossimQtMainWindow::utilitiesGeometry_BuilderAction_activated()
{
    if(theController)
    {
	theController->openGeometryBuilder();
    }
}
