//----------------------------------------------------------------------------
//
// License:   See LICENSE.txt file in the top level directory.
//
// Author:  David Burken
//
// Description:  Dialog for building image histograms.
//
// $Id: ossimQtHistogramBuilderDialog.cpp 15766 2009-10-20 12:37:09Z gpotts $
//----------------------------------------------------------------------------

#include <qgroupbox.h>
#include <qhgroupbox.h>
#include <qvbox.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qmessagebox.h>

#include <ossimQtHistogramBuilderDialog.h>
#include <ossimQtPropertyDialog.h>
#include <ossimQtPropertyDialogController.h>
#include <ossimQtProgressDialog.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimHistogramWriter.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageHistogramSource.h>

ossimQtHistogramBuilderDialog::ossimQtHistogramBuilderDialog(
   QWidget* parent,
   ossimImageHandler* imageHandler)
   :
      QDialog(parent,
              "ossimQtHistogramBuilderDialog",
              true),
      theImageHandler(imageHandler),
      theWriter(NULL),
      theMainVBox(NULL),
     
      theHBox1(NULL),
      theSourceImageGroupBox(NULL),         
      theSourceImageLabel(NULL),
      
      theHBox2(NULL),
      theSpacer1(NULL), 
      theBuildButton(NULL),
      theCloseButton(NULL)
{
   setCaption("Build Histograms");

   if (!theImageHandler)
   {
      close();
   }
   
   // Main vertical box.
   theMainVBox = new QVBoxLayout(this);

   // First row, display source image file name.
   theHBox1 = new QHBoxLayout(theMainVBox);
   
   theSourceImageGroupBox = new QGroupBox(1,
                                          Qt::Horizontal,
                                          "source image",
                                          this,
                                          "theSourceImageGroupBox");
   theSourceImageGroupBox->setAlignment(Qt::AlignHCenter);
   QString qs = theImageHandler->getFilename().c_str();
   theSourceImageLabel = new QLabel(qs,
                                    theSourceImageGroupBox,
                                    "theSourceImageLabel");
   theHBox1->addWidget(theSourceImageGroupBox);
   // End of first row.

   // Second row.
   theHBox2 = new QHBoxLayout(theMainVBox);

   // theSpacer1 = new QSpacerItem(-1, -1);
   
   theBuildButton = new QPushButton( this, "theBuildButton" );
   theBuildButton->setText( "build" );
   theBuildButton->setDefault(false);
   theBuildButton->setAutoDefault(false);   
   
   theCloseButton = new QPushButton( this, "theCloseButton" );
   theCloseButton->setText( "Close" );
   theCloseButton->setDefault(false);
   theCloseButton->setAutoDefault(false);   

   // theHBox2->addWidget(theSpacer1);
   theHBox2->addWidget(theBuildButton);
   theHBox2->addWidget(theCloseButton);

   //---
   // Connect all the signals to slots...
   //
   // NOTE:
   // If a push button is set to "default" or "auto default" it will always
   // call that slot when return is pressed in the dialog.
   // Since this isn't what I want all defaults are set to off!
   //---
   connect( theBuildButton, SIGNAL ( clicked() ),
            this, SLOT ( buildClicked() ) );
   
   connect( theCloseButton, SIGNAL ( clicked() ),
            this, SLOT ( closeClicked() ) );
}

ossimQtHistogramBuilderDialog::~ossimQtHistogramBuilderDialog()
{
   theWriter = NULL;
}

void ossimQtHistogramBuilderDialog::buildClicked()
{
   if ( !theImageHandler )
   {
      return;
   }

   if(theWriter.valid())
   {
      theWriter->disconnect();
      theWriter = 0;
   }
   // Set up the histogram source.
   ossimRefPtr<ossimImageHistogramSource> histoSource =
      new ossimImageHistogramSource;
   histoSource->setMaxNumberOfRLevels(1);
   histoSource->connectMyInputTo(0, theImageHandler.get());
   histoSource->enableSource();

   // Set up the histogram writer.
   theWriter = new ossimHistogramWriter;
   theWriter->connectMyInputTo(0, histoSource.get());
   ossimFilename histoFile =
      theImageHandler->getFilenameWithThisExtension(ossimString(".his"));
   theWriter->setFilename(histoFile);

   // Make a progress dialog.
   ossimQtProgressDialog* pd = new ossimQtProgressDialog("");
   pd->setMinimumDuration(250); // Update 4 times a second.

   //---
   // Connect the progress dialog's signal "canceled()" up to our slot
   // "saveCanceled()" so that we can tell the writer to abort.
   //---
   connect( pd, SIGNAL(canceled()), this, SLOT(abortClicked()) );
   
   theWriter->addListener(pd); // Progress dialog listens to writer...

   // Set up the progress dialog...
   QString qs = "Processing file ";
   qs += histoFile.c_str();
   pd->setLabelText(qs);
   pd->show();
   
   // Process the tile...
   theWriter->execute();

   // Check for cancelation.
   if (pd->wasCanceled())
   {
      pd->close();

      int status = remove(histoFile.c_str()); // 0 == success, -1 failure
         
      QString caption = "Processing of file aborted!";
      QString text = "File:  ";
      text += histoFile.c_str();
      if (status == 0)
      {
         text += "\nFile removed successfully...";
      }

      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
   }

   theWriter->removeListener(pd);
   theWriter->disconnect();
   theWriter = 0;
   // Cleanup...
   delete pd;
   pd = NULL;

   close();
   
}

void ossimQtHistogramBuilderDialog::abortClicked()
{
   if (theWriter.valid())
   {
      theWriter->abort();

      // Remove the file if present.
      if (theImageHandler.valid())
      {
         ossimFilename histoFile =
            theImageHandler->getFilenameWithThisExtension(ossimString(".his"));
         if (histoFile.exists())
         {
            histoFile.remove();
         }
      }
   }
}

void ossimQtHistogramBuilderDialog::closeClicked()
{
   close();
}

ossimQtHistogramBuilderDialog::ossimQtHistogramBuilderDialog(
   const ossimQtHistogramBuilderDialog& /* obj */ )
   : QDialog()
{
}

const ossimQtHistogramBuilderDialog& ossimQtHistogramBuilderDialog::operator=(
   const ossimQtHistogramBuilderDialog& /* rhs */ )
{
   return *this;
}
