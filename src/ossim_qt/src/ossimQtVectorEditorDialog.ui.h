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
// $Id: ossimQtVectorEditorDialog.ui.h 5757 2003-12-12 19:50:32Z gpotts $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void ossimQtVectorEditorDialog::init()
{
    theController = new ossimQtVectorEditorDialogController(this);
}

void ossimQtVectorEditorDialog::theApplyButton_clicked()
{
    theController->apply();
}

void ossimQtVectorEditorDialog::theFeatureListbox_selectionChanged( QListBoxItem * li)
{
    theController->changeToFeature(theFeatureListbox->index(li));
}

ossimQtVectorEditorDialogController* ossimQtVectorEditorDialog::controller()
{
    return theController;
}

void ossimQtVectorEditorDialog::theCloseButton_clicked()
{
    close(true);
}

void ossimQtVectorEditorDialog::thePolygonColorPushButton_clicked()
{
  theController->polygonColor();
}


void ossimQtVectorEditorDialog::theLineColorPushButton_clicked()
{
  theController->lineColor();
}

void ossimQtVectorEditorDialog::thePointColorButton_clicked()
{
  theController->pointColor();
}


void ossimQtVectorEditorDialog::theLineEnabledCheckBox_toggled( bool)
{
    theController->lineEnabledToggled();
}


void ossimQtVectorEditorDialog::thePointEnabledCheckBox_toggled( bool )
{
    theController->pointEnabledToggled();
}


void ossimQtVectorEditorDialog::theFontEnabledCheckBox_toggled( bool )
{
    theController->fontEnabledToggled();
}


void ossimQtVectorEditorDialog::thePolygonEnabledCheckBox_clicked()
{
    theController->polygonEnabledToggled();
}


void ossimQtVectorEditorDialog::theLineThicknessInput_valueChanged( int /*value*/)
{
    theController->lineThicknessChanged();
}


void ossimQtVectorEditorDialog::thePolygonThicknessInput_valueChanged( int )
{
    theController->polygonThicknessChanged();
}


void ossimQtVectorEditorDialog::thePolygonFilledCheckBox_toggled( bool )
{
    theController->polygonFilledToggled();
}


void ossimQtVectorEditorDialog::thePointFilledCheckbox_toggled( bool )
{
    theController->pointFilledToggled();
}


void ossimQtVectorEditorDialog::theFontPointSizeSpinBox_valueChanged( int )
{
   theController->fontPointSize();
}

void ossimQtVectorEditorDialog::theFontColorPushButton_clicked()
{
    theController->fontColor();
}


void ossimQtVectorEditorDialog::theFontScaleInput_textChanged( const QString & )
{
    theController->fontScale();
}

void ossimQtVectorEditorDialog::theDisableAllButton_clicked()
{
    theController->disableAll();
}


void ossimQtVectorEditorDialog::theEnableAllButton_clicked()
{
    theController->enableAll();
}


void ossimQtVectorEditorDialog::theFontFamilyNameComboBox_activated( const QString & )
{
    theController->fontFamilyName();
}


void ossimQtVectorEditorDialog::theFontStyleNameComboBox_activated( const QString & )
{
    theController->fontStyle();
}


void ossimQtVectorEditorDialog::theFontShearInput_textChanged( const QString & )
{
    theController->fontShear();
}


void ossimQtVectorEditorDialog::theFontRotationInput_textChanged( const QString & )
{
    theController->fontRotation();
}
