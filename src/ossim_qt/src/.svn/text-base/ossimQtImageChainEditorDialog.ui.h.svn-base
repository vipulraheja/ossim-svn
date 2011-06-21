/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void ossimQtImageChainEditorDialog::setImageWidget(ossimQtScrollingImageWidget* widget)
{
   if (theController)
   {
      theController->setImageWidget(widget);
   }
}

void ossimQtImageChainEditorDialog::setAvailableFilterList( const std::vector<ossimString> & list )
{
   if (theController)
   {
      theController->setAvailableFilterList(list);
   }   
}

void ossimQtImageChainEditorDialog::init()
{
   theController = new ossimQtImageChainEditorController(this);
}

void ossimQtImageChainEditorDialog::destroy()
{
   if (theController)
   {
      delete theController;
      theController = NULL;
   }
}

void ossimQtImageChainEditorDialog::closePushButton_clicked()
{
   close(true);
}

void ossimQtImageChainEditorDialog::insertBeforeButton_clicked()
{
   if (theController)
   {
      theController->insertBeforeButtonClicked();
   }
}

void ossimQtImageChainEditorDialog::insertAfterPushButton_clicked()
{
   if (theController)
   {
      theController->insertAfterPushButtonClicked();
   }
}

void ossimQtImageChainEditorDialog::layerComboBox_activated( int /* layer */ )
{
   if (theController)
   {
      theController->layerComboBoxActivated();
   }
}

void ossimQtImageChainEditorDialog::editPropertiesPushButton_clicked()
{
   if (theController)
   {
      theController->editPropertiesPushButtonClicked();
   }
}

void ossimQtImageChainEditorDialog::deletePushButton_clicked()
{
   if (theController)
   {
      theController->deletePushButtonClicked();
   }   
}
