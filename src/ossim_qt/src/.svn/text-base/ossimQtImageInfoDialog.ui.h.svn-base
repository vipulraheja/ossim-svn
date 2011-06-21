/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void ossimQtImageInfoDialog::setImageWidget(ossimQtScrollingImageWidget* widget)
{
   if (theController)
   {
      theController->setImageWidget(widget);
   }
}

void ossimQtImageInfoDialog::init()
{
   theController = new ossimQtImageInfoController(this);
}

void ossimQtImageInfoDialog::destroy()
{
   if (theController)
   {
      delete theController;
      theController = NULL;
   }
}

void ossimQtImageInfoDialog::closeButtonClicked()
{
   close(true);
}

void ossimQtImageInfoDialog::helpButtonClicked()
{
}

void ossimQtImageInfoDialog::scanForMinMaxButtonClicked()
{
   if (theController)
   {
      theController->scanForMinMax();
   }
}

void ossimQtImageInfoDialog::scanForValidVerticesButtonClicked()
{
   if (theController)
   {
      theController->scanForValidVertices();
   }
}

void ossimQtImageInfoDialog::layerComboBoxActivated( int /* layer */)
{
   if (theController)
   {
      theController->layerComboBoxActivated();	
   }
}

void ossimQtImageInfoDialog::bandSpinBoxValueChanged( int /* band */ )
{
   if (theController)
   {
      theController->initializeMinMaxNulls();
   }
}

void ossimQtImageInfoDialog::projectionComboBoxActivated( const QString & )
{
   if (theController)
   {
      theController->projectionComboBoxActivated();
   }
}

void ossimQtImageInfoDialog::datumComboBoxActivated( const QString & )
{
}

void ossimQtImageInfoDialog::pixelTypeComboBoxActivated( const QString & )
{
}

void ossimQtImageInfoDialog::zoneComboBoxActivated( const QString & )
{
   if (theController)
   {
      theController->zoneComboBoxActivated();
   }
}

void ossimQtImageInfoDialog::hemisphereComboBoxActivated( const QString & )
{
}

void ossimQtImageInfoDialog::originLatitudeLineEditReturnPressed()
{
   if (theController)
   {
      theController->originLineEditActivated();
   }
}

void ossimQtImageInfoDialog::centralMeridianLineEditReturnPressed()
{
   if (theController)
   {
      theController->centralMeridianLineEditActivated();
   }
}

void ossimQtImageInfoDialog::tiePointX_LineEditReturnPressed()
{
   if (theController)
   {
      theController->tiePointX_activated();
   }
}

void ossimQtImageInfoDialog::tiePointY_LineEditReturnPressed()
{
   if (theController)
   {
      theController->tiePointY_activated();
   }
}

void ossimQtImageInfoDialog::parallelOneLineEditReturnPressed()
{
   if (theController)
   {
      theController->parallelOneLineEditActivated();
   }
}

void ossimQtImageInfoDialog::parallelTwoLineEditReturnPressed()
{
   if (theController)
   {
      theController->parallelTwoLineEditActivated();
   }
}

void ossimQtImageInfoDialog::resetProjectionPushButtonClicked()
{
   if (theController)
   {
      theController->resetProjection();
   }
}


void ossimQtImageInfoDialog::saveProjectionPushButtonClicked()
{
   if (theController)
   {
      theController->saveProjection();
   }
}

void ossimQtImageInfoDialog::customDialogHasClosed()
{
   if (theController)
   {
      theController->customDialogHasClosed();
   }
}


void ossimQtImageInfoDialog::imageInfoTabWidgetSelected( const QString& qs )
{
   if (theController)
   {
      theController->tabChanged(qs);
   }
}
