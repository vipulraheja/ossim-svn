/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
void ossimQtPreferencesDialog::init()
{
    theController = new ossimQtPreferencesDialogController(this);
}

void ossimQtPreferencesDialog::destroy()
{
    if(theController)
    {
	delete theController;
	theController = 0;
    }
}

ossimQtPreferencesDialogController* ossimQtPreferencesDialog::controller()
{
    return theController;
}


void ossimQtPreferencesDialog::theAddPluginButton_clicked()
{
    if(theController)
    {
	theController->addPlugin();
    }
}

void ossimQtPreferencesDialog::theRemovePluginButton_clicked()
{
    if(theController)
    {
	theController->removePlugin();
    }
}


void ossimQtPreferencesDialog::theCloseButton_clicked()
{
    reject();
}


void ossimQtPreferencesDialog::thePluginList_currentChanged( QListBoxItem *  item)
{
    if(theController)
    {
	theController->currentPluginSelectionChanged(item);
    }
}


void ossimQtPreferencesDialog::theSelectAllPluginButton_clicked()
{
    if(theController)
    {
	theController->selectAllPlugin();
    }
}


void ossimQtPreferencesDialog::theReloadPluginButton_clicked()
{
    if(theController)
    {
	theController->reloadPlugin();
    }

}
