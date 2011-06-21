/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
void ossimQtDataManagerDialog::setDataManager(ossimDataManager* dataManager)
{
    theDataManagerListBox->setDataManager(dataManager);
}


void ossimQtDataManagerDialog::theCloseButton_clicked()
{
    close(true);
}


void ossimQtDataManagerDialog::theDisplayButton_clicked()
{
   ossimConnectableObject::ConnectableObjectList objList = theDataManagerListBox->getSelectedObjects();

  for(int i = 0; i < (int)objList.size(); ++i)
    {
      ossimQtDisplayChainEvent* evt = new ossimQtDisplayChainEvent(objList[i]->getId().getId());
      ossimQtApplicationUtility::postEventToRoot(this, evt);
    }
}
