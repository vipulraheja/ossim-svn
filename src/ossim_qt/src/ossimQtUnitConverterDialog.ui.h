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
// $Id: ossimQtUnitConverterDialog.ui.h 8780 2006-01-31 21:33:55Z dburken $
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void ossimQtUnitConverterDialog::init()
{
    updateFields();
}

void ossimQtUnitConverterDialog::destroy()
{
}

void ossimQtUnitConverterDialog::updateFields()
{
    theMetersField->blockSignals(true);
    theFeetField->blockSignals(true);
    theUsSurveyFeetField->blockSignals(true);
    theMilesField->blockSignals(true);
    theNauticalMilesField->blockSignals(true);
    theRadiansField->blockSignals(true);
    theDegreesField->blockSignals(true);
    theMinutesField->blockSignals(true);
    theSecondsField->blockSignals(true);
    theDmsField->blockSignals(true);
	    
    ossimDms  dms(theConversionTool.getDegrees(),false);
    theMetersField->setText(QString::number(theConversionTool.getMeters(),'g',12));
    theFeetField->setText(QString::number(theConversionTool.getFeet(),'g',12));
    theUsSurveyFeetField->setText(QString::number(theConversionTool.getUsSurveyFeet(),'g',12));
    theMilesField->setText(QString::number(theConversionTool.getMiles(),'g',12));
    theNauticalMilesField->setText(QString::number(theConversionTool.getNauticalMiles(),'g',12));
    theRadiansField->setText(QString::number(theConversionTool.getRadians(),'g',12));
    theDegreesField->setText(QString::number(theConversionTool.getDegrees(),'g',12));
    theMinutesField->setText(QString::number(theConversionTool.getMinutes(),'g',12));
    theSecondsField->setText(QString::number(theConversionTool.getSeconds(),'g',12));
    theDmsField->setText(dms.toString("ddd@mm'ss.ssss\"").c_str());
    
    theMetersField->blockSignals(false);
    theFeetField->blockSignals(false);
    theUsSurveyFeetField->blockSignals(false);
    theMilesField->blockSignals(false);
    theNauticalMilesField->blockSignals(false);
    theRadiansField->blockSignals(false);
    theDegreesField->blockSignals(false);
    theMinutesField->blockSignals(false);
    theSecondsField->blockSignals(false);
    theDmsField->blockSignals(false);
}

void ossimQtUnitConverterDialog::theCloseButton_clicked()
{
    close(true);
}

void ossimQtUnitConverterDialog::theDmsField_returnPressed()
{
    ossimDms dms(0.0,false);
    
    dms.setDegrees(theDmsField->text().ascii());
 
    theConversionTool.setDegrees(dms.getDegrees());
    
    updateFields();
}


void ossimQtUnitConverterDialog::theMetersField_returnPressed()
{
    theConversionTool.setMeters(theMetersField->text().toDouble());
    updateFields();

}


void ossimQtUnitConverterDialog::theFeetField_returnPressed()
{
    theConversionTool.setFeet(theFeetField->text().toDouble());
    updateFields();

}


void ossimQtUnitConverterDialog::theUsSurveyFeetField_returnPressed()
{
    theConversionTool.setUsSurveyFeet(theUsSurveyFeetField->text().toDouble());
    updateFields();

}

void ossimQtUnitConverterDialog::theNauticalMilesField_returnPressed()
{
    theConversionTool.setNauticalMiles(theNauticalMilesField->text().toDouble());
    updateFields();

}


void ossimQtUnitConverterDialog::theRadiansField_returnPressed()
{
    theConversionTool.setRadians(theRadiansField->text().toDouble());
    updateFields();

}


void ossimQtUnitConverterDialog::theDegreesField_returnPressed()
{
    theConversionTool.setDegrees(theDegreesField->text().toDouble());
    updateFields();

}


void ossimQtUnitConverterDialog::theMinutesField_returnPressed()
{
    theConversionTool.setMinutes(theMinutesField->text().toDouble());
    updateFields();

}


void ossimQtUnitConverterDialog::theSecondsField_returnPressed()
{
    theConversionTool.setSeconds(theSecondsField->text().toDouble());
    updateFields();

}

void ossimQtUnitConverterDialog::theMilesField_returnPressed()
{
    theConversionTool.setMiles(theMilesField->text().toDouble());
    updateFields();

}
