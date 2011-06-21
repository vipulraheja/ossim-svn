/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


void ossimQtQuadProjectionDialog::savePushButtonClicked()
{
   if (theController)
   {
      theController->save();
   }   
}

void ossimQtQuadProjectionDialog::setImageWidget(ossimQtScrollingImageWidget* widget, ossim_uint32 layer )
{
   if (theController)
   {
      theController->setImageWidget(widget, layer);
   }
}

void ossimQtQuadProjectionDialog::resetPushButtonClicked()
{
   if (theController)
   {
      theController->reset();
   }
}

void ossimQtQuadProjectionDialog::closePushButtonClicked()
{
   close(true);
}

void ossimQtQuadProjectionDialog::init()
{
   theController = new ossimQtQuadProjectionController(this);
}

void ossimQtQuadProjectionDialog::destroy()
{
   if (theController)
   {
      delete theController;
      theController = NULL;
   }
}

void ossimQtQuadProjectionDialog::deleteRowPushButtonClicked()
{
   if (theController)
   {
      theController->deleteRow();
   }
}

void ossimQtQuadProjectionDialog::addRowPushButtonClicked()
{

   if (theController)
   {
      theController->addRow();
   }  
}


void ossimQtQuadProjectionDialog::cellValueChanged( int row, int col )
{
   if (theController)
   {
      theController->cellValueChanged(row, col);
   }  
}


void ossimQtQuadProjectionDialog::roamingEnabledRadioButtonToggled( bool flag )
{
   if (theController)
   {
      theController->enableRoaming(flag);
   }
}

