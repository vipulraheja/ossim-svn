/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
void ossimQtGeometryBuilderDialog::init()
{
    theController = new ossimQtGeometryBuilderDialogController(this);
}

void ossimQtGeometryBuilderDialog::destroy()
{
    if(theController)
    {
	delete theController;
	theController = 0;
    }
}


void ossimQtGeometryBuilderDialog::theGdalWktConvertButton_clicked()
{
    if(theController)
    {
	theController->convertFromWkt();
    }
}

void ossimQtGeometryBuilderDialog::theCancelButton_clicked()
{
    close(true);
}


void ossimQtGeometryBuilderDialog::theOssimSaveGeomButton_clicked()
{
    if(theController)
    {
	theController->saveOssimGeometry();
    }
}


void ossimQtGeometryBuilderDialog::theGdalWktLoadFromFileButton_clicked()
{
    if(theController)
    {
	theController->loadWktStringFromFile();
    }
}


ossimQtGeometryBuilderDialogController* ossimQtGeometryBuilderDialog::controller()
{
    return theController;
}

void ossimQtGeometryBuilderDialog::theOssimProjectionList_activated( const QString & )
{
    if(theController)
    {
	theController->generateDefaultOssimGeometry(theOssimProjectionList->currentText().ascii());
    }

}
