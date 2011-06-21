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
// $Id: ossimQtImageWindow.ui.h 14337 2009-04-17 11:43:07Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
void ossimQtImageWindow::init()
{
    theController = new ossimQtImageWindowController(this);
}

void ossimQtImageWindow::destroy()
{
    if(theController)
    {
	delete theController;
	theController = NULL;
    }
}

void ossimQtImageWindow::enterEvent(QEvent* evt)
{
    if(theController)
    {
	theController->enterEvent(evt);	
    }
}

void ossimQtImageWindow::leaveEvent(QEvent* evt)
{
    if(theController)
    {
	theController->leaveEvent(evt);
    }
}

void ossimQtImageWindow::addInputSource(ossimConnectableObject* obj)
{
   if(theController)
   {
      theController->addInput(obj);
   }
}

ossimQtSwipeScrollingImageWidget* ossimQtImageWindow::getImageWidget()
{
    return theImageWidget;
}

void ossimQtImageWindow::editImageGeometryAction_activated()
{
   if(theController)
   {
      theController->imageGeometry();
   }
}


void ossimQtImageWindow::editRedoAction_activated()
{

}


void ossimQtImageWindow::editUndoAction_activated()
{

}


void ossimQtImageWindow::editViewToolAction_activated()
{
   if(theController)
   {
      theController->viewTool();
   }
}


void ossimQtImageWindow::enhancementsBandSelectorAction_activated()
{
   if(theController)
   {
      theController->bandSelector();
   }
}

void ossimQtImageWindow::enhancementsBrightnessContrastAction_activated()
{
   if(theController)
   {
      theController->brightnessContrast();
   }
}

void ossimQtImageWindow::enhancementsHistogramOperationsAction_activated()
{
   if(theController)
   {
      theController->histogramOperation();
   }
}

void ossimQtImageWindow::enhancementsHsiAction_activated()
{
   if(theController)
   {
      theController->hsiAdjustments();
   }
}


void ossimQtImageWindow::fileExitAction_activated()
{
   if(theController)
   {
      theController->fileExit();
   }
}

void ossimQtImageWindow::fileSaveTiePointsAction_activated()
{
   if(theController)
   {
      theController->fileSaveTiePoints();
   }
}

void ossimQtImageWindow::fileSaveAsAction_activated()
{
   if(theController)
   {
      theController->igenExport();
   }
}


ossimQtImageWindowController* ossimQtImageWindow::controller()
{
    return theController;
}

void ossimQtImageWindow::customEvent(QCustomEvent* event)
{
    QApplication::sendEvent(theController, event);
}

void ossimQtImageWindow::closeEvent(QCloseEvent* event)
{
   if(theController)
   {
      theController->closeEvent(event);
   }
}

void ossimQtImageWindow::resamplerActionGroup_selected( QAction * action)
{
   if(theController)
   {
      theController->setResampler(action->menuText());
   }
}

void ossimQtImageWindow::thePropagateButton_clicked()
{
   if(theController)
   {
      theController->propagateView();
   }
}


void ossimQtImageWindow::theFullResButton_clicked()
{
   if(theController)
   {
      theController->fullRes();
   }
}


void ossimQtImageWindow::theFitToWindowButton_clicked()
{
   if(theController)
   {
      theController->fitToWindow();
   }
}


void ossimQtImageWindow::thePanToTool_toggled( bool value)
{
   if(theController)
   {
      theController->panToToolButtonToggled(value);
   }
}

void ossimQtImageWindow::theZoomToolButton_toggled( bool value)
{
   if(theController)
   {
      theController->zoomToolButtonToggled(value);
   }
}



void ossimQtImageWindow::resamplerPropagateAction_activated()
{
   if(theController)
   {
      theController->propagateResampler();
   }
}


void ossimQtImageWindow::swipeAddLayerAction_activated()
{
   if(theController)
   {
      theController->swipeAddLayer();
   }
}


void ossimQtImageWindow::swipeRemoveLayerAction_activated()
{
   if(theController)
   {
      theController->swipeRemoveLayer();
   }
}


void ossimQtImageWindow::swipeBoxAction_activated()
{
   if(theController)
   {
      theController->swipeBox();
   }
}


void ossimQtImageWindow::swipeCircleAction_activated()
{
   if(theController)
   {
      theController->swipeCircle();
   }
}


void ossimQtImageWindow::swipeVerticalAction_activated()
{
   if(theController)
   {
      theController->swipeVertical();
   }
}


void ossimQtImageWindow::swipeHorizontalAction_activated()
{
   if(theController)
   {
      theController->swipeHorizontal();
   }
}


void ossimQtImageWindow::editImageChainAction_activated()
{
   if(theController)
   {
      theController->editImageChain();
   }
}

void ossimQtImageWindow::editImageInfoAction_activated()
{
   if(theController)
   {
      theController->editImageInfo();
   }
}

void ossimQtImageWindow::editLayersAction_activated()
{
   if(theController)
   {
      theController->editLayers();
   }
}


void ossimQtImageWindow::editParameterAdjustmentAction_activated()
{
   if(theController)
   {
      theController->geometryAdjustment();
   }
}


void ossimQtImageWindow::editVectorSourceAction_activated()
{
   if(theController)
   {
      theController->vectorSource();
   }
}


void ossimQtImageWindow::enhancementsFusionAction_activated()
{
   if(theController)
   {
      theController->fusion();
   }

}


void ossimQtImageWindow::theResamplerSelection_activated( const QString & value)
{
    if(theController)
    {
	theController->setResampler(value);
    }
}


void ossimQtImageWindow::editPositionInformationActionActivated()
{
    if(theController)
    {
	theController->showPositionInformation();
    }
}

void ossimQtImageWindow::editPositionQualityActionActivated()
{
    if(theController)
    {
	theController->showPositionQuality();
    }
}


void ossimQtImageWindow::refreshButtonClicked()
{
    if(theController)
    {
	theController->refreshWindow();
    }
}


void ossimQtImageWindow::enhancementTopographicCorrection_activated()
{
   if(theController)
   {
      theController->topographicCorrection();
   }

}
