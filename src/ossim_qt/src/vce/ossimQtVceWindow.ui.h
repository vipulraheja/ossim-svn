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
// $Id: ossimQtVceWindow.ui.h 5757 2003-12-12 19:50:32Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
void ossimQtVceWindow::init()
{
    theController = new ossimQtVceWindowController(this);
}

void ossimQtVceWindow::customEvent(QCustomEvent* event)
{
    QApplication::sendEvent(theController, event);
}

void ossimQtVceWindow::closeEvent(QCloseEvent* event)
{
   if(theController)
   {
      theController->closeEvent(event);
   }
}

ossimQtVceWindowController* ossimQtVceWindow::controller()
{
    return theController;
}

void ossimQtVceWindow::fileNew()
{

}


void ossimQtVceWindow::fileOpen()
{

}


void ossimQtVceWindow::fileSave()
{

}


void ossimQtVceWindow::fileSaveAs()
{

}


void ossimQtVceWindow::filePrint()
{

}


void ossimQtVceWindow::fileExit()
{

}


void ossimQtVceWindow::editUndo()
{

}


void ossimQtVceWindow::editRedo()
{

}


void ossimQtVceWindow::editCut()
{
   theController->cutSelectedObjects();
}


void ossimQtVceWindow::editCopy()
{
    theController->copySelectedObjects();
}


void ossimQtVceWindow::editPaste()
{
    theController->paste();
}


void ossimQtVceWindow::editFind()
{

}

void ossimQtVceWindow::theCutTool_clicked()
{
   theController->cutSelectedObjects();
}

void ossimQtVceWindow::theCopyTool_clicked()
{
    theController->copySelectedObjects();
}

void ossimQtVceWindow::thePasteTool_clicked()
{
    theController->paste();
}

void ossimQtVceWindow::theAlignLeftTool_clicked()
{
    theController->alignLeft();
}


void ossimQtVceWindow::theAlignRightTool_clicked()
{
   theController->alignRight();
}


void ossimQtVceWindow::theAlignTopTool_clicked()
{
   theController->alignTop();
}


void ossimQtVceWindow::theAlignBottomTool_clicked()
{
   theController->alignBottom();
}

void ossimQtVceWindow::editSelectAllAction_activated()
{
    theController->selectAll();
}
