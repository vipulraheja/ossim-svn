#include "ossimQtInformationDialog.h"
#include <qlayout.h>
#include <qtextedit.h>

ossimQtInformationDialog::ossimQtInformationDialog(QWidget* parent,
                                                   bool modal,
                                                   WFlags f)
   :QDialog(parent, "ossimQtInformationDialog", modal, f)
{
   theMainVBox = new QVBoxLayout(this);

   theTextEditor = new QTextEdit(this);
   theMainVBox->addWidget(theTextEditor);
}

void ossimQtInformationDialog::setText(const QString& value)
{
   theTextEditor->setText(value);
}

QTextEdit*  ossimQtInformationDialog::textEditor()
{
   return theTextEditor;
}
