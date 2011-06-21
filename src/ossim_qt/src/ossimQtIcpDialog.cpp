//----------------------------------------------------------------------------
// Copyright (C) 2004 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: Image Copy interface.
//
// $Id: ossimQtIcpDialog.cpp 15766 2009-10-20 12:37:09Z gpotts $
//----------------------------------------------------------------------------

#include <exception>

#include <qgroupbox.h>
#include <qhgroupbox.h>
#include <qvbox.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qcombobox.h>

#include <ossimQtIcpDialog.h>
#include <ossimQtPropertyDialog.h>
#include <ossimQtPropertyDialogController.h>
#include <ossimQtProgressDialog.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimImageWriterFactoryRegistry.h>
#include <ossim/imaging/ossimImageFileWriter.h>
#include <ossim/imaging/ossimImageHandler.h>

ossimQtIcpDialog::ossimQtIcpDialog(QWidget* parent,
                                   ossimImageChain* image_chain)
   : QDialog(parent, "ossimQtIcpDialog", true, WDestructiveClose),
     theChain(image_chain),
     theWriter(NULL),
     theMainVBox(NULL),
     
     theHBox1(NULL),
     theSourceImageGroupBox(NULL),         
     theSourceImageLabel(NULL),
     
     theHBox2(NULL),
     theStartLineGroupBox(NULL),
     theStartLineField(NULL),
     theStopLineGroupBox(NULL),   
     theStopLineField(NULL),
     
     theHBox3(NULL),
     theStartSampleGroupBox(NULL),
     theStartSampleField(NULL),
     theStopSampleGroupBox(NULL),   
     theStopSampleField(NULL),
     
     theHBox4(NULL),
     theOutputImageGroupBox(NULL),      
     theOutputImageField(NULL),
     theOutputImageButton(NULL),
     
     theHBox5(NULL),
     theOutputImageTypeGroupBox(NULL),
     theOutputImageWriterMenu(NULL),
     theEditOutputImageWriterButton(NULL),
     
     theHBox6(NULL),
     theSaveButton(NULL),
     theCloseButton(NULL),
     theSourceImageRect(),
     theOutputImageRect()
{
   setCaption("Export Image");
   

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
   QString s = getImageFileName();
   theSourceImageLabel = new QLabel(s,
                                    theSourceImageGroupBox,
                                    "theSourceImageLabel");
   theHBox1->addWidget(theSourceImageGroupBox);
   // End of first row.

   // Second row, start line, stop line.
   theHBox2 = new QHBoxLayout(theMainVBox);
   theStartLineGroupBox = new QGroupBox(1, Qt::Horizontal, "start line", this);
   theStartLineGroupBox->setAlignment(Qt::AlignHCenter);
   theStartLineField = new QLineEdit(theStartLineGroupBox, "theStartLineField");
   theHBox2->addWidget(theStartLineGroupBox);

   // Make the stop line box.
   theStopLineGroupBox = new QGroupBox(1, Qt::Horizontal, "stop line", this);
   theStopLineGroupBox->setAlignment(Qt::AlignHCenter);
   theStopLineField = new QLineEdit(theStopLineGroupBox, "theStopLineField");
   theHBox2->addWidget(theStopLineGroupBox);
   // End of second row.

   // Third row, start sample, stop sample.
   theHBox3 = new QHBoxLayout(theMainVBox);

   // Make the start sample box.
   theStartSampleGroupBox =
      new QGroupBox(1, Qt::Horizontal, "start sample", this);
   theStartSampleGroupBox->setAlignment(Qt::AlignHCenter);
   theStartSampleField = new QLineEdit(theStartSampleGroupBox,
                                       "theStartSampleField");
   theHBox3->addWidget(theStartSampleGroupBox);

   // Make the stop sample box.
   theStopSampleGroupBox =
      new QGroupBox(1, Qt::Horizontal, "stop sample", this);
   theStopSampleGroupBox->setAlignment(Qt::AlignHCenter);
   theStopSampleField = new QLineEdit(theStopSampleGroupBox,
                                      "theStopSampleField");
   theHBox3->addWidget(theStopSampleGroupBox);

   // End of third row...

   // Fourth row, output file, file dialog button.
   theHBox4 = new QHBoxLayout(theMainVBox);
   theOutputImageGroupBox =
      new QHGroupBox("output image", this, "theOutputImageGroupBox");
   theOutputImageGroupBox->setAlignment(Qt::AlignHCenter);
   theOutputImageField = new QLineEdit(theOutputImageGroupBox,
                                       "theOutputImageField");
   theOutputImageButton = new QPushButton( theOutputImageGroupBox,
                                           "theOutputImageButton" );
   theOutputImageButton->setText( "..." );
   theOutputImageButton->setDefault(false);
   theOutputImageButton->setAutoDefault(false);
   theHBox4->addWidget(theOutputImageGroupBox);
   // End of fourth row...
   
   // Fifth row.
   theHBox5 = new QHBoxLayout(theMainVBox);
   theOutputImageTypeGroupBox =
      new QHGroupBox("output image type", this, "theOutputImageTypeGroupBox");
   theOutputImageTypeGroupBox->setAlignment(Qt::AlignHCenter);
   
   theOutputImageWriterMenu = new QComboBox(theOutputImageTypeGroupBox,
                                       "theOutputWriterBox");
   buildWriterMenu();
   theEditOutputImageWriterButton =
      new QPushButton( theOutputImageTypeGroupBox,
                       "theEditOutputImageWriterButton" );
   theEditOutputImageWriterButton->setText( "edit writer" );
   theEditOutputImageWriterButton->setDefault(false);
   theEditOutputImageWriterButton->setAutoDefault(false);
   theHBox5->addWidget(theOutputImageTypeGroupBox);

   // Sixth row.
   theHBox6 = new QHBoxLayout(theMainVBox);

   theSaveButton = new QPushButton( this, "theSaveButton" );
   theSaveButton->setText( "Save" );
   theSaveButton->setDefault(false);
   theSaveButton->setAutoDefault(false);   
   
   theCloseButton = new QPushButton( this, "theCloseButton" );
   theCloseButton->setText( "Close" );
   theCloseButton->setDefault(false);
   theCloseButton->setAutoDefault(false);   

   theHBox6->addWidget(theSaveButton);
   theHBox6->addWidget(theCloseButton);

   //---
   // Connect all the signals to slots...
   //
   // NOTE:
   // If a push button is set to "default" or "auto default" it will always
   // call that slot when return is pressed in the dialog.
   // Since this isn't what I want all defaults are set to off!
   //---
   connect( theStartLineField, SIGNAL ( returnPressed() ),
            this, SLOT ( startLinePressed() ) );
   
   connect( theStopLineField, SIGNAL ( returnPressed() ),
            this, SLOT ( stopLinePressed() ) );
   
   connect( theStartSampleField, SIGNAL ( returnPressed() ),
            this, SLOT ( startSamplePressed() ) );
   
   connect( theStopSampleField, SIGNAL ( returnPressed() ),
            this, SLOT ( stopSamplePressed() ) );

   connect( theOutputImageField, SIGNAL ( returnPressed() ),
            this, SLOT ( outputImagePressed() ) );

   connect( theOutputImageButton, SIGNAL ( clicked() ),
            this, SLOT ( outputImageClicked() ) );

   connect( theOutputImageWriterMenu, SIGNAL ( activated( const QString& ) ),
            this, SLOT ( outputImageWriterMenuActivated( const QString& ) ) );

   connect( theEditOutputImageWriterButton,
            SIGNAL ( clicked() ),
            this,
            SLOT ( editOutputImageWriterClicked() ) );

   connect( theSaveButton, SIGNAL ( clicked() ),
            this, SLOT ( saveClicked() ) );
   
   connect( theCloseButton, SIGNAL ( clicked() ),
            this, SLOT ( closeClicked() ) );

   initializeDialog();
}

ossimQtIcpDialog::~ossimQtIcpDialog()
{
   if (theWriter.valid())
   {
      theWriter->disconnect();
      theWriter = 0;
   }
}

QString ossimQtIcpDialog::getImageFileName() const
{
   QString qs;
   
   ossimImageHandler* ih = getImageHandler();
   if (ih)
   {
      qs = ih->getFilename().c_str();
   }

   return qs;
}

ossimImageHandler* ossimQtIcpDialog::getImageHandler() const
{
   ossimImageHandler* handler = NULL;
   
   if (!theChain)
   {
      return handler;
   }

   // Image handler usually at the end of chain so start there...
   const ossim_uint32 NUMBER_OF_LINKS = theChain->getNumberOfObjects(false);
   for (ossim_uint32 idx = NUMBER_OF_LINKS; idx > 0; --idx) 
   { 
      ossimConnectableObject* filter = (*theChain)[(idx-1)];
      if (filter)
      {
         if ( PTR_CAST(ossimImageHandler, filter) )
         {
            handler = PTR_CAST(ossimImageHandler, filter);
            break;
         }
      }
   }
   return handler;
}

void ossimQtIcpDialog::startLinePressed()
{
   updateStartLine();
}

void ossimQtIcpDialog::stopLinePressed()
{
   updateStopline();
}

void ossimQtIcpDialog::startSamplePressed()
{
   updateStartSample();
}

void ossimQtIcpDialog::stopSamplePressed()
{
   updateStopSample();
}

void ossimQtIcpDialog::outputImagePressed()
{
   if (!theOutputImageField)
   {
      return;
   }

   QString qs = theOutputImageField->text();

   // Make sure output filename is not the same as input.
   QString source_file = getImageFileName();
   if (source_file == qs)
   {
      QString caption = "Sorry:";
      QString text = "Output file cannot be the same as input file.";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      theOutputImageField->setText("");
      return;      
   }
   
   theOutputImageField->setText(qs);
}

void ossimQtIcpDialog::outputImageClicked()
{
   if (!theOutputImageField)
   {
      return;
   }
   
   QFileDialog* fd = new QFileDialog( this, "file dialog", TRUE );
   fd->setMode( QFileDialog::AnyFile );
   
   QString fileName;
   
   if ( fd->exec() == QDialog::Accepted )
   {
      fileName = fd->selectedFile();
   }
   delete fd;
   fd = NULL;
   
   if (fileName.isEmpty())
   {
      return;
   }
   
   // Make sure output filename is not the same as input.
   QString source_file = getImageFileName();
   if (source_file == fileName)
   {
      QString caption = "Sorry:";
      QString text = "Output file cannot be the same as input file.";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      theOutputImageField->setText("");
      return;      
   }
   
   theOutputImageField->setText(fileName);
}

void ossimQtIcpDialog::updateOutputFilenameFromWriter()
{
   if (!theOutputImageField || !theWriter)
   {
      return;
   }

   ossimFilename writersOutputFile = theWriter->getFilename();
   if (writersOutputFile.empty())
   {
      return;
   }
   
   QString fileName = writersOutputFile.c_str();
   
   if (fileName == theOutputImageField->text())
   {
      return;
   }
   
   // Make sure output filename is not the same as input.
   QString source_file = getImageFileName();
   if (source_file == fileName)
   {
      QString caption = "Sorry:";
      QString text = "Output file cannot be the same as input file.";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      theOutputImageField->setText("");
      return;      
   }
   
   theOutputImageField->setText(fileName);
}

void ossimQtIcpDialog::outputImageWriterMenuActivated(const QString& qs)
{
   if (!theOutputImageWriterMenu)
   {
      return;
   }

   // Get the writer type.
   ossimString os = qs.ascii();

   // Make the writer.
   ossimRefPtr<ossimImageFileWriter> writer =
      ossimImageWriterFactoryRegistry::instance()->createWriter(os);

   if (!writer)
   {
      return; // Should never happen...
   }

   //---
   // Set the writer to create overviews and a histogram as the default.
   // The user can override this with the  "edit writer" interface.
   //---
   writer->setWriteOverviewFlag(true);
   writer->setWriteHistogramFlag(true);   

   if (theWriter.valid())
   {
      if (writer->getClassName() != theWriter->getClassName())
      {
         theWriter->disconnect();
         theWriter = writer.get();
      }
      else // Writer the same class set the type.
      {
         theWriter->setOutputImageType(writer->getOutputImageTypeString());
         writer = 0;
      }
   }
   else
   {
      theWriter = writer.get();
   }
}

void ossimQtIcpDialog::editOutputImageWriterClicked()
{
   if (!theWriter)
   {
      return;
   }

   ossimQtPropertyDialog* dialog = new ossimQtPropertyDialog(this,
                                                             "Property editor",
                                                             true);
   dialog->controller()->setObject(theWriter.get());
   dialog->setModal(true);
   dialog->exec();

   //---
   // Since the writers have an output image property that the user could
   // have just changed, see if we need to update the line edit field.
   //---
   updateOutputFilenameFromWriter();
}

void ossimQtIcpDialog::saveClicked()
{
   if ( !theOutputImageField || !theWriter || !theChain )
   {
      return;
   }

   // Make sure the output rectangle is up to date.
   if (updateOuputRect() == false)
   {
      return;
   }
   
   // Make sure output file is not empty.
   QString output_file = theOutputImageField->text();
   if (output_file.isEmpty())
   {
      QString caption = "Sorry:";
      QString text = "You must set an output file name.";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      return;
   }

   // Check to see if file exist and prompt user for overrite.
   ossimFilename f = output_file.ascii();
   if (f.exists())
   {
      QString caption("Question:");
      QString text = "Overwrite existing file:  ";
      text += output_file;
      int answer = QMessageBox::question( this,
                                          caption,
                                          text,
                                          QMessageBox::Yes,
                                          QMessageBox::No);
      if (answer == QMessageBox::No)
      {
         theOutputImageField->setText("");
         return;
      }
   }

   // Make sure output filename is not the same as input.
   QString source_file = getImageFileName();
   if (source_file == output_file)
   {
      QString caption = "Sorry:";
      QString text = "Output file cannot be the same as input file.";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      theOutputImageField->setText("");
      return;      
   }

   // Connect it up to the source.
   theWriter->connectMyInputTo(0, theChain);

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
   qs += output_file        ;
   pd->setLabelText(qs);
   pd->show();
   
   //---
   // Process the tile...
   //---
   theWriter->open(output_file.ascii());
   theWriter->initialize();
   theWriter->setAreaOfInterest(theOutputImageRect);

   // Process the image...
   bool exceptionCaught = false;
   try
   {
      theWriter->execute();
   }
   catch(std::exception& e)
   {
      pd->close();
      QString caption = "Exception caught!\n";
      QString text = e.what();
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      exceptionCaught = true;
   }
   catch (...)
   {
      pd->close();
      QString caption = "Unknown exception caught!\n";
      QString text = "";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      exceptionCaught = true;
   }

   theWriter->close();

   if (exceptionCaught)
   {
      int status = remove(output_file.ascii()); // 0 == success, -1 failure
      
      QString caption = "Processing of file aborted!";
      QString text = "File:  ";
      text += output_file;
      if (status == 0)
      {
         text += "\nFile removed successfully...";
      }
      
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
   }
   else if (pd->wasCanceled()) // Check for cancelation.
   {
      pd->close();

      int status = remove(output_file.ascii()); // 0 == success, -1 failure
         
      QString caption = "Processing of file aborted!";
      QString text = "File:  ";
      text += output_file;
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

   // Cleanup...
   delete pd;
   pd = NULL;
}

void ossimQtIcpDialog::abortClicked()
{
   if (theWriter.valid())
   {
      theWriter->abort();
   }
}

void ossimQtIcpDialog::closeClicked()
{
   close(true);
}

void ossimQtIcpDialog::initializeDialog()
{
   if ( !theChain )
   {
      return;
   }
   
   theSourceImageRect = theChain->getBoundingRect();
   
   if (theSourceImageRect.hasNans())
   {
      return; // Should never happen...
   }
   
   theOutputImageRect = theSourceImageRect;

   setStartStopFields();  // This will set fields to theOutputImageRect.
}

void ossimQtIcpDialog::setStartStopFields()
{
   if ( !theStartLineField   || !theStopLineField ||
        !theStartSampleField || !theStopSampleField )
   {
      return;
   }
   
   QString qs; // Used throughout...
   
   qs = ossimString::toString(theOutputImageRect.ul().y).c_str();
   theStartLineField->setText(qs);

   qs = ossimString::toString(theOutputImageRect.ul().x).c_str();
   theStartSampleField->setText(qs);
   
   qs = ossimString::toString(theOutputImageRect.lr().y).c_str();
   theStopLineField->setText(qs);

   qs = ossimString::toString(theOutputImageRect.lr().x).c_str();
   theStopSampleField->setText(qs);
}

void ossimQtIcpDialog::buildWriterMenu()
{
   const QString DEFAULT_WRITER_TYPE = "tiff_tiled_band_separate";
   
   if (!theOutputImageWriterMenu)
   {
      return;
   }

   theOutputImageWriterMenu->clear();
   
   vector<ossimString> writerList;
   ossimImageWriterFactoryRegistry::instance()->getImageTypeList(writerList);

   vector<ossimString>::const_iterator i = writerList.begin();
   while (i != writerList.end())
   {
      QString qs = (*i).c_str();
      theOutputImageWriterMenu->insertItem(qs);
      ++i;
   }

   // Set the default item.
   for (int index = 0; index < theOutputImageWriterMenu->count(); ++index)
   {
      if (theOutputImageWriterMenu->text(index) == DEFAULT_WRITER_TYPE)
      {
         theOutputImageWriterMenu->setCurrentItem(index);
         break;
      }
   }

   // Initialize the writer.
   if (theWriter.valid())
   {
      theWriter->disconnect();
      theWriter = 0;
   }
   ossimString os = theOutputImageWriterMenu->currentText().ascii();
   theWriter = ossimImageWriterFactoryRegistry::instance()->createWriter(os);
   if (theWriter.valid())
   {
      //---
      // Set the writer to create overviews and a histogram as the default.
      // The user can override this with the  "edit writer" interface.
      //---
      theWriter->setWriteOverviewFlag(true);
      theWriter->setWriteHistogramFlag(true);
   }
}

bool ossimQtIcpDialog::updateOuputRect()
{
   if (updateStartLine() == false)
   {
      return false;
   }
   if (updateStopline() == false)
   {
      return false;
   }
   if (updateStartSample() == false)
   {
      return false;
   }
   if (updateStopSample() == false)
   {
      return false;
   }

   return true;
}

bool ossimQtIcpDialog::updateStartLine()
{
   if (!theStartLineField)
   {
      return false;
   }
   
   QString     qs   = theStartLineField->text();
   ossimString os   = qs.ascii();
   ossim_int32 line = os.toInt32();
   
   if (line < theSourceImageRect.ul().y)
   {
      QString caption = "Range Error:";
      QString text =
         "Start line cannot be less than the start of the image!\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );

      setStartStopFields();  // This will reset fields to theOutputImageRect.
      return false;
   }
   if (line >= theOutputImageRect.lr().y)
   {
      QString caption = "Range Error:";
      QString text =
         "Start line must be less than the stop line!\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      setStartStopFields();  // This will reset fields to theOutputImageRect.
      return false;
   }

   theOutputImageRect.set_uly(line);

   return true;
}

bool ossimQtIcpDialog::updateStopline()
{
   if (!theStopLineField)
   {
      return false;
   }
   
   QString     qs   = theStopLineField->text();
   ossimString os   = qs.ascii();
   ossim_int32 line = os.toInt32();
   
   if (line > theSourceImageRect.lr().y)
   {
      QString caption = "Range Error:";
      QString text =
         "Stop line cannot be greater than the end of the image!\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      
      setStartStopFields();  // This will reset fields to theOutputImageRect.
      return false;
   }
   if (line <= theOutputImageRect.ul().y)
   {
      QString caption = "Range Error:";
      QString text =
         "Stop line must be greater than the start line!\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      setStartStopFields();  // This will reset fields to theOutputImageRect.
      return false;
   }

   theOutputImageRect.set_lry(line);

   return true;
}

bool ossimQtIcpDialog::updateStartSample()
{
   if (!theStartSampleField)
   {
      return false;
   }
   
   QString     qs     = theStartSampleField->text();
   ossimString os     = qs.ascii();
   ossim_int32 sample = os.toInt32();
   
   if (sample < theSourceImageRect.ul().x)
   {
      QString caption = "Range Error:";
      QString text =
         "Start sample cannot be less than the start of the image!\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );

      setStartStopFields();  // This will reset fields to theOutputImageRect.
      return false;
   }
   if (sample >= theOutputImageRect.lr().x)
   {
      QString caption = "Range Error:";
      QString text =
         "Start sample must be less than the stop sample!\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      setStartStopFields(); // This will reset fields to theOutputImageRect. 
      return false;
   }

   theOutputImageRect.set_ulx(sample);

   return true;
}

bool ossimQtIcpDialog::updateStopSample()
{
   if (!theStopSampleField)
   {
      return false;
   }

   QString     qs     = theStopSampleField->text();
   ossimString os     = qs.ascii();
   ossim_int32 sample = os.toInt32();
   
   if (sample > theSourceImageRect.lr().x)
   {
      QString caption = "Range Error:";
      QString text =
         "Stop sample cannot be greater than the end of the image!\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      
      setStartStopFields();  // This will reset fields to theOutputImageRect.
      return false;
   }
   if (sample <= theOutputImageRect.ul().x)
   {
      QString caption = "Range Error:";
      QString text =
         "Stop sample must be greater than the start sample!\n";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      setStartStopFields();  // This will reset fields to theOutputImageRect.
      return false;
   }

   theOutputImageRect.set_lrx(sample);

   return true;
}

ossimQtIcpDialog::ossimQtIcpDialog(const ossimQtIcpDialog& /* obj */ )
   : QDialog(),
     theChain(NULL)
{
}

const ossimQtIcpDialog& ossimQtIcpDialog::operator=(const ossimQtIcpDialog& /* rhs */ )
{
   return *this;
}
