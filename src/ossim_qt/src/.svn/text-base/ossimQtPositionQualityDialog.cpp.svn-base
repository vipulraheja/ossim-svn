//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description:
//
// Tabbed dialog box for the position quality evaluator.  Contains two widgets
// or tabs, the "Quality Evaluator" and the "Report Generator".
//
// $Id$
//----------------------------------------------------------------------------

// Define for proprietary inserts. Uncomment only if you have them.
// #define HAS_PQE_INSERTS

#include <sstream>
#include <ctime>

#include <qfiledialog.h>
#include <qgroupbox.h>
#include <qvgroupbox.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qlayout.h>
#include <qhbox.h>
#include <qvbox.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qtextedit.h>

#include <ossimQtPositionQualityDialog.h>
#include <ossimQtImageWindowController.h>
#include <ossimQtScrollingImageWidget.h>
#include <ossimQtDisplayUtility.h>
#include <ossimQtEvent.h>
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimDms.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimGeoidManager.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/base/ossimPreferences.h>
#include <ossim/base/ossimTrace.h>
#include <ossim/base/ossimXmlAttribute.h>
#include <ossim/base/ossimXmlNode.h>
#include <ossim/base/ossimXmlDocument.h>
#include <ossim/elevation/ossimElevManager.h>
#include <ossim/imaging/ossimGeoAnnotationSource.h>
#include <ossim/imaging/ossimGeoAnnotationEllipseObject.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageRenderer.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimImageViewTransform.h>
#include <ossim/projection/ossimImageViewProjectionTransform.h>
#include <ossim/projection/ossimRpcModel.h>
#include <ossim/projection/ossimSensorModel.h>
#include <ossim/projection/ossimSensorModelTuple.h>
#include <ossim/projection/ossimPositionQualityEvaluator.h>

#ifdef HAS_PQE_INSERTS
#  include <insertion-code/pqeInsert3.h>
#endif

static ossimTrace traceDebug(
   ossimString("ossimQtPositionQualityDialog:debug"));

//---
// Must match ossimPositionQualityEvaluator enumeration as it will be used as
// index to this array. Last cell must be '0' for qt combo box.
//---
static const char* PROBABILITY_LEVEL[] =
{ "ONE SIGMA", "P50", "P90", "P95", 0 };

static const int DEFAULT_PROBABILITY_ITEM_INDEX = 3; // "P95"

static const ossimString LAT_FORMAT = "dd@ mm' ss.ssss\" C";
static const ossimString LON_FORMAT = "ddd@ mm' ss.ssss\" C";

//---
// This is the name used in the "Elevation Accuracy" pulldown if no
// "pqe_elev" keywords are found in the ossim preferences file.
//---
static const ossimString ELEV_SOURCE_IGNORE_NAME = "n/a";


static const QString ANNOTATED_CHIP_OPTION = "Annotated Chip";
static const QString ORP_OPTION            = "OSSIM Report (ORP)";

ossimPqeAccSrc::ossimPqeAccSrc()
   : theName(),
     theCe90(0.0),
     theLe90(0.0)
{}

std::ostream& operator<<(std::ostream& out, const ossimPqeAccSrc& obj)
{
   out << "ossimPqeAccSrc"
       << "\ntheName: " << obj.theName
       << "\ntheCe90: " << obj.theCe90
       << "\ntheLe90: " << obj.theLe90
       << std::endl;
   return out;
}



ossimQtPositionQualityDialog::ossimQtPositionQualityDialog(QWidget* parent)
   :
   QTabDialog(parent),
   // theOkButton(0),
   theQualityEvaluatorWidget(0),
   
   thePqeEnabledCheckBox(0),
   theGraphicsEnabledCheckBox(0),
   
   theSemiMajorAxisLineEdit(0),
   theSemiMinorAxisLineEdit(0),
   theAzimuthLineEdit(0),
   
   theCircularErrorLineEdit(0),
   theLinearErrorLineEdit(0),
   
   theLatitudeLineEdit(0),
   theLongitudeLineEdit(0),
   theHeightAboveEllipsoidLineEdit(0),
   theHeightAboveMslLineEdit(0),

   theElevSourceLineEdit(0),
   
   theProbabilityLevelComboBox(0),
   theBackdropAccuracyComboBox(0),
   theElevationAccuracyComboBox(0),
   
   theReportGeneratorWidget(0),
   thePointIdLineEdit(0),
   theAnnotationNoteTextEdit(0),
   theReportFormatComboBox(0),
   theSaveButton(0),
   
   theWidget(0),
   theWidgetLayer(0),
   theController(0),
   
   theGroundPt(),
   theImagePt(),
   theCovMat(3, 3),
   theHeightAboveEllipsoid(0.0),
   theHeightAboveMsl(0.0),
   theSemiMinorAxis(0.0),
   theSemiMajorAxis(0.0),
   theAzimuth(0.0),
   theCe90(0.0),
   theLe90(0.0),
   thePqeEnabledFlag(true),
   theGraphicsEnabledFlag(true),
          
   theEllipse(0),
   theAnnotator(0),
          
   theBackdropSources(),
   theElevationSources(),

   theRpcPqeInputs()
{
   //---
   // Set the nan as an indication to the save routine that the user has NOT
   // dropped a point yet.
   //---
   theAzimuth = ossim::nan();
   
   // Set to have destructive close.
   setWFlags(getWFlags()|Qt::WDestructiveClose);
   
   // Set the main caption.
   setCaption("Position Quality Evaluator");

   // Create the "Quality Evaluator" widget.
   theQualityEvaluatorWidget =
      new QVBox(this, QString("Quality Evaluator"));

   // Add the tab to this tab dialog.
   addTab(theQualityEvaluatorWidget,  QString("Quality Evaluator"));

   // Create the "Report Generator" widget.
   theReportGeneratorWidget  =
      new QVBox(this, QString("Report Generator"));

   // Add the tab to this tab dialog.
   addTab(theReportGeneratorWidget, QString("Report Generator"));

   // Build the quality evaluator widget internals.
   buildQualityEvaluatorWidget();

   // Build the report generator widget internals.
   buildReportGeneratorWidget();
}


void ossimQtPositionQualityDialog::buildQualityEvaluatorWidget()
{
   // Row 1:
   QHBox* hBoxRow1 = new QHBox(theQualityEvaluatorWidget);

   // QVGroupBox* gb1 = new QVGroupBox(QString("Point ID"), hBoxRow1);
   // theQePointIdLineEdit = new QLineEdit(gb1);
   
   // QVGroupBox* gb2 = new QVGroupBox(hBoxRow1);
   thePqeEnabledCheckBox = new QCheckBox(hBoxRow1);
   thePqeEnabledCheckBox->setText(QString("PQE Mouse Entry Enabled"));
   thePqeEnabledCheckBox->setChecked(thePqeEnabledFlag);
      
   theGraphicsEnabledCheckBox = new QCheckBox(hBoxRow1);
   theGraphicsEnabledCheckBox->setText(QString("Graphics Overlay Enabled"));
   theGraphicsEnabledCheckBox->setChecked(theGraphicsEnabledFlag);
   
   // Row 2:

   // Main box row 2
   QHBox* hBoxRow2 = new QHBox(theQualityEvaluatorWidget);

   // box for row 2 column 1 (r2c1)
   QVGroupBox* r2c1 = new QVGroupBox(hBoxRow2);

   // position box row 2 column 1 row 1 (r2c1r1)
   QVGroupBox* r2c1r1 = new QVGroupBox(QString("Position"), r2c1);

   // elev source box row 2 column 1 row 2 (r2c1r2
   QVGroupBox* r2c1r2 = new QVGroupBox(QString("Model elevation source"),
                                       r2c1);

   // box for row 2 column 2 (r2c2)
   QVGroupBox* r2c2 = new QVGroupBox(hBoxRow2);

   // error ellipse box (r2c2r1)
   QVGroupBox* r2c2r1 = new QVGroupBox(QString("Error Ellipse"), r2c2);

   // accuracy box (r2c2r2)
   QVGroupBox* r2c2r2 = new QVGroupBox(QString("Accuracy"), r2c2);

   // latitude
   QHBox* r2c1r1r1 = new QHBox(r2c1r1);
   QLabel* lab1 = new QLabel("Lat:", r2c1r1r1);
   if (lab1)
   {
      theLatitudeLineEdit = new QLineEdit(r2c1r1r1);
      theLatitudeLineEdit->setReadOnly(false);
   }
   
   // longitude
   QHBox* r2c1r1r2 = new QHBox(r2c1r1);
   QLabel* lab2 = new QLabel("Lon:", r2c1r1r2);
   if (lab2)
   {
      theLongitudeLineEdit = new QLineEdit(r2c1r1r2);
   }
   
   // height above ellipsoid
   QHBox* r2c1r1r3 = new QHBox(r2c1r1);
   QLabel* lab3 = new QLabel("Hgt:", r2c1r1r3);
   if (lab3)
   {
      theHeightAboveEllipsoidLineEdit = new QLineEdit(r2c1r1r3);
   }

   // height above msl
   QHBox* r2c1r1r4 = new QHBox(r2c1r1);
   QLabel* lab4 = new QLabel("MSL:", r2c1r1r4);
   if (lab4)
   {
      theHeightAboveMslLineEdit = new QLineEdit(r2c1r1r4);
   }

   // model elevation source
   // QLabel* lab4 = new QLabel("MSL:", r2c1r1r4);

   theElevSourceLineEdit = new QLineEdit(r2c1r2);
   theElevSourceLineEdit->setReadOnly(false);

   // Semi-Major Axis:
   QHBox* r2c1r1r5 = new QHBox(r2c2r1);
   QLabel* lab6 = new QLabel("Semi-Major Axis:", r2c1r1r5);
   if (lab6)
   {
      theSemiMajorAxisLineEdit= new QLineEdit(r2c1r1r5);
   }

   // Semi-Minor Axis:
   QHBox* hbox7 = new QHBox(r2c2r1);
   QLabel* lab7 = new QLabel("Semi-Minor Axis:", hbox7);
   if (lab7)
   {
      theSemiMinorAxisLineEdit= new QLineEdit(hbox7);
   }

   // Azimuth:
   QHBox* hbox8 = new QHBox(r2c2r1);
   QLabel* lab8 = new QLabel("Azimuth:", hbox8);
   if (lab8)
   {
      theAzimuthLineEdit= new QLineEdit(hbox8);
   }

   // Circular Error:
   QHBox* hbox9 = new QHBox(r2c2r2);
   QLabel* lab9 = new QLabel("Circular Error:", hbox9);
   if (lab9)
   {
      theCircularErrorLineEdit= new QLineEdit(hbox9);
   }

   // Linear Error:
   QHBox* hbox10 = new QHBox(r2c2r2);
   QLabel* lab10 = new QLabel("Linear Error:", hbox10);
   if (lab10)
   {
      theLinearErrorLineEdit= new QLineEdit(hbox10);
   }

    // Row 3.
   QHBox* hBoxRow3 = new QHBox(theQualityEvaluatorWidget);
   QVGroupBox* gb7 = new QVGroupBox(QString("Probability Level"),  hBoxRow3);
   QVGroupBox* gb8 = new QVGroupBox(QString("Backdrop Accuracy"),  hBoxRow3);
   QVGroupBox* gb9 = new QVGroupBox(QString("Elevation Accuracy"),
                                    hBoxRow3);

   theProbabilityLevelComboBox  = new QComboBox(FALSE, gb7);
   theBackdropAccuracyComboBox  = new QComboBox(FALSE, gb8);
   theElevationAccuracyComboBox = new QComboBox(FALSE, gb9);
   theProbabilityLevelComboBox->insertStrList(PROBABILITY_LEVEL);

   // Set "P95" as the default.
   theProbabilityLevelComboBox->setCurrentItem(DEFAULT_PROBABILITY_ITEM_INDEX);
   
   buildBackdropPulldown();
   buildElevAccPulldown();

   // Connect signals with slots.
   connect(thePqeEnabledCheckBox, SIGNAL( toggled(bool) ),
           this, SLOT( pqeEnabledToggled(bool) ) );

   connect(theGraphicsEnabledCheckBox, SIGNAL( toggled(bool) ),
           this, SLOT( graphicsEnabledToggled(bool) ) );

   connect(theLatitudeLineEdit, SIGNAL( returnPressed() ),
           this, SLOT( lineEditReturnPressed() ) );
   

   connect(theProbabilityLevelComboBox, SIGNAL( activated(int) ),
           this, SLOT( recalc(int) ) );
   connect(theBackdropAccuracyComboBox, SIGNAL( activated(int) ),
           this, SLOT( recalc(int) ) );
   connect(theElevationAccuracyComboBox, SIGNAL( activated(int) ),
           this, SLOT( recalc(int) ) );
}

void ossimQtPositionQualityDialog::buildReportGeneratorWidget()
{
   // Row 1:
   QHBox* hBoxRow1 = new QHBox(theReportGeneratorWidget);
   QVGroupBox* gb1 = new QVGroupBox(QString("Point ID"),  hBoxRow1);
   QVGroupBox* gb2 = new QVGroupBox(QString("Annotation Notes"),  hBoxRow1);
   thePointIdLineEdit = new QLineEdit(gb1);
   theAnnotationNoteTextEdit = new QTextEdit(gb2);
   
   // Row 2:
   QHBox* hBoxRow2 = new QHBox(theReportGeneratorWidget);
   QVGroupBox* gb3 = new QVGroupBox(QString("Report Format"),    hBoxRow2);
   theReportFormatComboBox  = new QComboBox(FALSE, gb3);
   theReportFormatComboBox->insertItem(ANNOTATED_CHIP_OPTION);
   theReportFormatComboBox->insertItem(ORP_OPTION);

#ifdef HAS_PQE_INSERTS
#  include <insertion-code/pqeInsert1.h>
#endif

   theSaveButton = new QPushButton("Save", hBoxRow2);
   
   connect(theSaveButton, SIGNAL( clicked() ),
           this, SLOT( saveButtonClicked() ) );
}

ossimQtPositionQualityDialog::~ossimQtPositionQualityDialog()
{
   if (theAnnotator.get())
   {
      removeAnnotatorFromChain();
   }
   
   // ossimNotify(ossimNotifyLevel_DEBUG)
   // << "ossimQtPositionQualityDialog::~ossimQtPositionQualityDialog entered..." << std::endl;
}

void ossimQtPositionQualityDialog::setImageWidget(
   ossimQtScrollingImageWidget* widget)
{
   theWidget      = widget;
   theWidgetLayer = 0; // tmp...

   connect(theWidget,
           SIGNAL(scrollingImageWidgetMouseEvent(ossimQtMouseEvent*)),
           this,
           SLOT(trackScrollingImageWidget(ossimQtMouseEvent*)));
}

void ossimQtPositionQualityDialog::setController(
   ossimQtImageWindowController* controller)
{
   theController = controller;
}

void ossimQtPositionQualityDialog::trackScrollingImageWidget(ossimQtMouseEvent* event)
{
   if (thePqeEnabledFlag == false)
   {
      event->getEvent()->ignore();
      return;
   }
   
   // Activate on left press only...
   if ( ( event->getButton() == Qt::LeftButton) &&
        ( event->getQtEventType() == QEvent::MouseButtonPress ) )
   {
      // Get the mouse point.
      ossimDpt viewPt = event->getShiftPoint();

      //---
      // Convert the view point to image space for the
      // ossimSensorModelTuple::intersect method.
      //---
      ossimImageViewTransform* view = getImageViewTransform();
      if (view)
      {
         // Use the view to convert to image point.
         view->viewToImage(viewPt, theImagePt);
      }

      //---
      // Convert the view point to world space.  This will be the center
      // point of the ellipse.
      //---
      ossimProjection* proj = getViewProjection();
      if (proj)
      {
         proj->lineSampleToWorld(viewPt, theGroundPt);
         initializeDialog();
      }

   } // End of mouse event check.
}

void ossimQtPositionQualityDialog::recalc(int /* item */ )
{
   initAccuracyStrings();
}

void ossimQtPositionQualityDialog::pqeEnabledToggled(bool flag)
{
   thePqeEnabledFlag = flag;
   // do something here...

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << " pqeEnabledToggled DEBUG:"
         << "\nflag: " << (flag?"true":"false")
         << std::endl;
   }

}

void ossimQtPositionQualityDialog::graphicsEnabledToggled(bool flag)
{
   theGraphicsEnabledFlag = flag;
   if (theAnnotator.get())
   {
      theAnnotator->setEnableFlag(flag);
      refresh();
   }

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "graphicsEnabledToggled  DEBUG:"
         << "\nflag: " << (flag?"true":"false")
         << std::endl;
   }
}

void ossimQtPositionQualityDialog::lineEditReturnPressed()
{
}

void ossimQtPositionQualityDialog::saveButtonClicked()
{
   if (!theReportFormatComboBox)
   {
      return;
   }

   //---
   // Verify the user has dropped a point.  At construction of this dialog
   // "theAzimuth" is set to nan for this purpose.  If a point has been dropped
   // it should NOT be nan.
   //---
   if (ossim::isnan(theAzimuth))
   {
      QString caption = "Notice:";
      QString text = "No point has been dropped yet.  Nothing to save!";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      return;
   }

   QString qs = theReportFormatComboBox->currentText();
   if (qs == ANNOTATED_CHIP_OPTION)
   {
      if (theController)
      {
         // Turn off mouse capture.
         thePqeEnabledCheckBox->setChecked(false);
         
         theController->igenExport();
      }
   }
   else if (qs == ORP_OPTION)
   {
      QFileDialog* fd = new QFileDialog( 0, "file dialog", TRUE );
      fd->setMode( QFileDialog::AnyFile );
      QString types ("Any files (*.xml *.XML)");
      fd->setFilter(types);
      QString fileName;
      if ( fd->exec() == QDialog::Accepted )
      {
         fileName = fd->selectedFile();
         bool concatenateFlag = false;
         if ( QFile::exists( fileName ) )
         {
            int answer = QMessageBox::question(
               this,
               tr("Concatenate File?"),
               tr("File exists: %1\n"
                  "Do you want to concatenate your point to it?\n"
                  "Choose Yes to concatenate or No to overwrite.")
               .arg( fileName ),
               QMessageBox::Yes, QMessageBox::No, QMessageBox::NoButton);
            if (answer == QMessageBox::Yes)
            {
               concatenateFlag = true;
            }
         }

         ossimFilename f = fileName.ascii();
         if ( f != getImageName(false))
         {
            if (saveToFile(f, concatenateFlag) == true)
            {
               ossimNotify(ossimNotifyLevel_NOTICE)
                  << "Wrote file: " << f << endl;
            }
         }
         else
         {
            QString caption = "Cannot save warning:";
            QString text = "Report file and image file are the same!";
            QMessageBox::information( this,
                                      caption,
                                      text,
                                      QMessageBox::Ok );
         }
      }
      delete fd;
      fd = 0;
   }
#ifdef HAS_PQE_INSERTS
#  include <insertion-code/pqeInsert2.h>
#endif   
}

void ossimQtPositionQualityDialog::initializeDialog()
{
   initPositionStrings();
   
   // Check elevation:
   if (checkElevForPoint(theGroundPt))
   {
      initAccuracyStrings();
   }
}

void ossimQtPositionQualityDialog::initPositionStrings()
{
   setLatString();
   setLonString();
   setHgtAboveEllipsoidString();
   setHgtAboveMslString();
   setElevSourceString();
}

void ossimQtPositionQualityDialog::initAccuracyStrings()
{
   static const char MODULE[] =
      "ossimQtPositionQualityDialog::initAccuracyStrings";

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << " entered..." << std::endl;
   }
   
   ossimSensorModel* model = getSensorModel();
   if (model)
   {
      if (traceDebug())
      {
         ossimNotify(ossimNotifyLevel_DEBUG)
            << "Model name: " << model->getClassName() << std::endl;
      }
      
      // Load the models into the tuple
      ossimSensorModelTuple smTuple;
      smTuple.addImage(model);
      
      //---
      // Set the surface accuracy.  User choice of from source data or from
      // preference settings.
      //---
      ossim_float64 elevCE90 = 0.0;
      ossim_float64 elevLE90 = 0.0;
      getCeLe(elevCE90, elevLE90);
      
      if ( elevCE90 && elevLE90 )
      {
         if (traceDebug())
         {
            ossimNotify(ossimNotifyLevel_DEBUG)
               << MODULE
               << "\nSetting intersection surface accuracy: "
               << "ce=" << elevCE90 << " le=" << elevLE90
               << std::endl;
         }
         smTuple.setIntersectionSurfaceAccuracy(elevCE90, elevLE90);
      }
      else
      {
         if (traceDebug())
         {
            ossimNotify(ossimNotifyLevel_DEBUG)
               << MODULE
               << " No surface accuracy used in solution!"
               << std::endl;
         }
      }

      ossimEcefPoint intECF;
      ossimSensorModelTuple::IntersectStatus status =
         smTuple.intersect(0, theImagePt, intECF, theCovMat);
      if (status != ossimSensorModelTuple::ERROR_PROP_FAIL)
      {
         if (isRpcModel())
         {
            // Capture the rpc inputs to pqe.
            smTuple.getRpcPqeInputs(theRpcPqeInputs);
         }
         
         // Instantiate a quality evaluator.
         ossimPositionQualityEvaluator qev(intECF, theCovMat);
         
         // Set theCovMat to ENU for output if necessary
         qev.getCovMatrix(theCovMat);

         // Index 0 is none.
         if ( theBackdropAccuracyComboBox->currentItem() != 0 )
         {
            // Add backdrop contributions.
            int bdSourceIdx = theBackdropAccuracyComboBox->currentItem();
            ossim_float64 bdCE90 = theBackdropSources[bdSourceIdx].theCe90;
            ossim_float64 bdLE90 = theBackdropSources[bdSourceIdx].theLe90;
            qev.addContributingCE_LE(bdCE90, bdLE90);

            if (traceDebug())
            {
               ossimNotify(ossimNotifyLevel_DEBUG)
                  << theBackdropSources[bdSourceIdx]
                  << std::endl;
            }
         }

         //---
         // Accuracy results processing
         //---

         pqeProbLev_t pLev = static_cast<pqeProbLev_t>(
            theProbabilityLevelComboBox->currentItem());

         if (traceDebug())
         {
            ossimNotify(ossimNotifyLevel_DEBUG)
               << "DEBUG:"
               << "\nProbability level:  " << PROBABILITY_LEVEL[pLev]
               << std::endl;
         }
         
         theCe90 = 0.0;
         theLe90 = 0.0;
         
         // Get the accuracy estimate.
         bool epOK = qev.computeCE_LE(pLev, theCe90, theLe90);

         if (epOK)
         {
            // Get the error ellipse.
            pqeErrorEllipse ell;
            if (qev.extractErrorEllipse(pLev, ell))
            {
               theSemiMinorAxis = ell.theSemiMinorAxis;
               theSemiMajorAxis = ell.theSemiMajorAxis;               
               theAzimuth       = ell.theAzimAngle*DEG_PER_RAD;

               ossimString os;

               os = ossimString::toString(theSemiMajorAxis, 2);
               os += " m";
               theSemiMajorAxisLineEdit->setText(os.c_str());

               os = ossimString::toString(theSemiMinorAxis, 2);
               os += " m";
               theSemiMinorAxisLineEdit->setText(os.c_str());

               os = ossimString::toString(theAzimuth, 2);
               os += " deg";
               theAzimuthLineEdit->setText(os.c_str());

               os = ossimString::toString(theCe90, 2);
               os += " m";
               theCircularErrorLineEdit->setText(os.c_str());

               os = ossimString::toString(theLe90, 2);
               os += " m";
               theLinearErrorLineEdit->setText(os.c_str());

               // Update the ellipse graphic.
               updateEllipse();
            }
            else
            {
               QString caption = "ERROR:";
               QString text = "Error returned from ossimPositionQualityEvaluator::extractErrorEllipse method.";
               QMessageBox::information( this,
                                         caption,
                                         text,
                                         QMessageBox::Ok );
            }
            
         } // if (epOK)
         
      } // if (status != ossimSensorModelTuple::ERROR_PROP_FAIL)
   }
   else
   {
      QString caption = "Sensor model required:";
      QString text = "Cannot derive position quality from this data.";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
   }

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << MODULE << " exited..." << std::endl;
   }
}

void ossimQtPositionQualityDialog::setLatString()
{
   ossimDms dms(theGroundPt.latd(), true);
   theLatitudeLineEdit->setText( dms.toString(LAT_FORMAT).c_str() );
}

void ossimQtPositionQualityDialog::setLonString()
{
   ossimDms dms(theGroundPt.lond(), false);
   theLongitudeLineEdit->setText( dms.toString(LON_FORMAT).c_str() );
}

void ossimQtPositionQualityDialog::setHgtAboveEllipsoidString()
{
   theHeightAboveEllipsoid =
      ossimElevManager::instance()->getHeightAboveEllipsoid(theGroundPt);
   
   if ( ossim::isnan(theHeightAboveEllipsoid) )
   {
      theHeightAboveEllipsoidLineEdit->setText("nan");
   }
   else
   {
      ossimString os = ossimString::toString(theHeightAboveEllipsoid, 2);
      os += " m";
      theHeightAboveEllipsoidLineEdit->setText(os.c_str());
   }
}

void ossimQtPositionQualityDialog::setHgtAboveMslString()
{
   theHeightAboveMsl =
      ossimElevManager::instance()->getHeightAboveMSL(theGroundPt);

   if ( ossim::isnan(theHeightAboveMsl) )
   {
      theHeightAboveMslLineEdit->setText("nan");
   }
   else
   {
      ossimString os = ossimString::toString(theHeightAboveMsl, 2);
      os += " m";
      theHeightAboveMslLineEdit->setText(os.c_str());
   }
}

void ossimQtPositionQualityDialog::setElevSourceString()
{
#if 0
   ossimFilename f = ossimElevManager::instance()->
      getCellFilenameForPoint(theGroundPt);
   theElevSourceLineEdit->setText(f.c_str());
#endif
}

void ossimQtPositionQualityDialog::buildBackdropPulldown()
{
   if (!theBackdropAccuracyComboBox)
   {
      return;
   }

   //---
   // Keyword example "name,ce90,le90":
   // pqe_backdrop1: JOG-A,25,25
   //---

   // Start with clean list.
   theBackdropSources.clear();
   
   // Put "None" as the first item.
   ossimPqeAccSrc src;
   src.theName = "None";
   src.theCe90 = 1.0;
   src.theLe90 = 1.0;
   theBackdropSources.push_back(src);

   // Add sources from ossim preferences.
   ossimString keyBase = "pqe_backdrop";
   buildSourceList(keyBase, theBackdropSources);

   std::vector<ossimPqeAccSrc>::const_iterator i = theBackdropSources.begin();
   while (i != theBackdropSources.end())
   {
      // Insert into pulldown.
      theBackdropAccuracyComboBox->insertItem((*i).theName.c_str());
      ++i;
   }
}

void ossimQtPositionQualityDialog::buildElevAccPulldown()
{
   if (!theElevationAccuracyComboBox)
   {
      return;
   }

   //---
   // Keyword example "name,ce90,le90":
   // pqe_backdrop1: JOG-A,25,25
   //---

   // Start with a clean list.
   theElevationSources.clear();

   ossimPqeAccSrc src;
   src.theName = "source";
   theElevationSources.push_back(src);
   
   // Add sources from ossim preferences.
   ossimString keyBase = "pqe_elev";
   buildSourceList(keyBase, theElevationSources);

   // If no sources were in the preferences put one in with an n/a.
   if (theElevationSources.size() == 1)
   {
      ossimPqeAccSrc src;
      src.theName = ELEV_SOURCE_IGNORE_NAME;
      theElevationSources.push_back(src);
   }

   std::vector<ossimPqeAccSrc>::const_iterator i = theElevationSources.begin();
   while (i != theElevationSources.end())
   {
      // Insert into pulldown.
      theElevationAccuracyComboBox->insertItem((*i).theName.c_str());
      ++i;
   }
}

void ossimQtPositionQualityDialog::buildSourceList(
   const ossimString& keyBase, std::vector<ossimPqeAccSrc> & result)
{
   const ossimKeywordlist KWL = ossimPreferences::instance()->preferencesKWL();

   ossim_uint32 numberOfSources = KWL.numberOf(keyBase.c_str());
   ossim_uint32 found = 0;
   ossim_uint32 idx = 0;
   const ossim_uint32 MAX = numberOfSources + 10;
   while (found <  numberOfSources)
   {
      ossimString key = keyBase;
      key += ossimString::toString(idx);
      const char* lookup = KWL.find(key);
      if (lookup)
      {
         ossimString lookupString = lookup;
         
         // split on commas name,ce90,le90
         std::vector<ossimString> value;
         lookupString.split(value, ossimString(","));
         
         if (value.size() == 3)
         {
            ossimPqeAccSrc src;
            src.theName = value[0];
            src.theCe90 = value[1].toFloat64();
            src.theLe90 = value[2].toFloat64();
            
            // Store it.
            result.push_back(src);
            
            ++found;
         }
      }
      ++idx;

      // Since our while loop can skip numbers add sanity check.
      if ( idx > MAX) 
      {
         break;
      }
   }
}

void ossimQtPositionQualityDialog::updateLatitudeField()
{
   if (theLatitudeLineEdit)
   {
      QString     qs     = theLatitudeLineEdit->text();
      ossimString os     = qs.ascii();
      theGroundPt.latd( getDegrees(os, true) );
      setLatString();
   }
}

ossimImageChain* ossimQtPositionQualityDialog::getChain() const
{
   ossimImageChain* ic = 0;
   if (theWidget)
   {
      ossimConnectableObject* obj = theWidget->getInput(theWidgetLayer);
      if (obj)
      {
         ic = PTR_CAST(ossimImageChain, obj);
      }
      else
      {
         ossimNotify(ossimNotifyLevel_FATAL)
            << "FATAL ossimQtPositionQualityDialog::getChain: "
            << "getInput failed!" << std::endl;
      }
   }
   return ic;
}

ossimImageHandler* ossimQtPositionQualityDialog::getImageHandler() const
{
   ossimImageHandler* handler = 0;
   ossimImageChain* ic = getChain();
   if (ic)
   {
      // Image handler usually at the end of chain so start there...
      const ossim_uint32 NUMBER_OF_LINKS = ic->getNumberOfObjects(false);
      for (ossim_uint32 idx = NUMBER_OF_LINKS; idx > 0; --idx) 
      { 
         ossimConnectableObject* filter = (*ic)[(idx-1)];
         if (filter)
         {
            if ( PTR_CAST(ossimImageHandler, filter) )
            {
               handler = PTR_CAST(ossimImageHandler, filter);
               break;
            }
         }
      }
   }
   return handler;
}

ossimImageViewTransform* ossimQtPositionQualityDialog::getImageViewTransform() const
{
   ossimImageViewTransform* trans = 0;

   ossimImageChain* ic = getChain();
   if (ic)
   {
      ossimImageRenderer* obj = (ossimImageRenderer*)ic->findObjectOfType("ossimImageRenderer", ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT);
      if(obj)
      {
         trans = obj->getImageViewTransform();
      }
   }
   return trans;
}

ossimProjection* ossimQtPositionQualityDialog::getImageProjection() const
{
   ossimProjection* proj = 0;
   
   ossimImageViewTransform* trans = getImageViewTransform();
   if (trans)
   {
      ossimImageViewProjectionTransform* ivpt
         = PTR_CAST(ossimImageViewProjectionTransform, trans);
      if(ivpt)
      {
         ossimImageGeometry* geom = ivpt->getImageGeometry();
         proj = geom?geom->getProjection():0;
      }
   }
   
   return proj;
}

ossimProjection* ossimQtPositionQualityDialog::getViewProjection() const
{
   ossimProjection* proj = 0;
   
   ossimImageViewTransform* trans = getImageViewTransform();
   if (trans)
   {
      ossimImageViewProjectionTransform* ivpt
         = PTR_CAST(ossimImageViewProjectionTransform, trans);
      if(ivpt)
      {
         ossimImageGeometry* geom = ivpt->getImageGeometry();
         proj =  geom?geom->getProjection():0;
      }
   }
   
   return proj;
}

ossimSensorModel* ossimQtPositionQualityDialog::getSensorModel() const
{
   ossimSensorModel* model = 0;
   
   ossimProjection* proj = getImageProjection();
   if (proj)
   {
      model = PTR_CAST(ossimSensorModel, proj);
   }
   
   return model;
}

ossimGeoAnnotationEllipseObject* ossimQtPositionQualityDialog::getEllipse() const
{
   ossimGeoAnnotationEllipseObject* ellipse = 0;
   
   ossimImageChain* ic = getChain();
   if (ic)
   {
      ellipse = (ossimGeoAnnotationEllipseObject*)ic->
         findObjectOfType("ossimGeoAnnotationEllipseObject",
                          ossimConnectableObject::CONNECTABLE_DIRECTION_INPUT);
   }
   
   return ellipse;
}

void ossimQtPositionQualityDialog::addAnnotatorToChain()
{
   if (!theAnnotator)
   {
      theAnnotator = new ossimGeoAnnotationSource();
      ossimProjection* proj = getViewProjection();
      if (proj)
      {
         theAnnotator->setImageGeometry(new ossimImageGeometry(0, proj));
      }

      ossimImageChain* ic = getChain();
      if (ic)
      {
         ossimConnectableObject* obj = PTR_CAST(ossimConnectableObject,
                                                theAnnotator.get());
         if (obj)
         {
            //---
            // This is the most right object in the chain with the image
            // handler being the left most object.
            //---
            ic->addFirst(obj);
         }
      }

      // enable/disable
      theAnnotator->setEnableFlag(theGraphicsEnabledFlag);
   }
}

void ossimQtPositionQualityDialog::removeAnnotatorFromChain()
{
   if (theAnnotator.get())
   {
      ossimImageChain* ic = getChain();
      if (ic)
      {
         ossimConnectableObject* obj =
            PTR_CAST(ossimConnectableObject, theAnnotator.get());
         if (obj)
         {
            ic->removeChild(obj);
            if (theWidget)
            {
               refresh();
            }
         }
      }
   }
}

void ossimQtPositionQualityDialog::updateEllipse()
{
   if (!theAnnotator) // First time through.
   {
      addAnnotatorToChain();
   }

   if (!theEllipse) // First time through.
   {
      theEllipse = new ossimGeoAnnotationEllipseObject();

      // Setup the options, fill, thickness, axes and color.
      setEllipseOptions();

      // Parent to theAnnotator.  The annotator handles memory.
      theAnnotator->addObject(theEllipse);
   }

   theEllipse->setCenter(theGroundPt);
   theEllipse->setEllipseWidthHeightUnitType(OSSIM_METERS);

   // We use "Width" for "Minor" and "Height" for "Major".
   theEllipse->setWidthHeight(ossimDpt(theSemiMinorAxis,theSemiMajorAxis));
   theEllipse->setAzimuth(theAzimuth);
   ossimProjection* proj = getViewProjection();
   ossimRefPtr<ossimImageGeometry> geom = new ossimImageGeometry(0, proj);
   if (proj)
   {
      theAnnotator->transformObjects(geom.get());
   }
   
   refresh();
}

double ossimQtPositionQualityDialog::getDegrees(const ossimString& s,
                                                bool lat_flag) const
{
   ossimDms dms(0.0, lat_flag);
   dms.setDegrees(s.c_str());
   return dms.getDegrees();
}

void ossimQtPositionQualityDialog::refresh()
{
   ossimImageChain* ic = getChain();
   if (ic)
   {
      ossimQtDisplayUtility::flushAllOutputs(ic);
   }
}

void ossimQtPositionQualityDialog::setEllipseOptions()
{
   if (!theEllipse)
   {
      return;
   }

   // Default color to white.
   ossim_uint8 r = 255;
   ossim_uint8 g = 255;
   ossim_uint8 b = 255;
   
   // Look for pen color in preferences.
   const char* lookup = ossimPreferences::instance()->
      findPreference("pqe_normalized_rgb_ellipse_color");
   
   if (lookup)
   {
      ossim_float64 rNorm;
      ossim_float64 gNorm;
      ossim_float64 bNorm;

      std::istringstream in(lookup);
      in >> rNorm >> gNorm >> bNorm;
      
      if ( (rNorm >= 0.0) && (rNorm <=1.0) )
      {
         r = static_cast<ossim_uint8>(rNorm * 255.0 + 0.5);
      }
      if ( (gNorm >= 0.0) && (gNorm <=1.0) )
      {
         g = static_cast<ossim_uint8>(gNorm * 255.0 + 0.5);
      }
      if ( (bNorm >= 0.0) && (bNorm <=1.0) )
      {
         b = static_cast<ossim_uint8>(bNorm * 255.0 + 0.5);
      }
   }
   
   theEllipse->setFillFlag(false);
   theEllipse->setThickness(1);
   theEllipse->setDrawAxesFlag(true);
   theEllipse->setColor(r, g, b);
}

bool ossimQtPositionQualityDialog::checkElevForPoint(const ossimGpt& gpt)
{
   //---
   // At a minimum, users should have a geoid grid with the offset from
   // the ellipsiod.  Consider this an error and return false if a nan is
   // picked up.
   //---
   ossim_float64 d = ossimGeoidManager::instance()->offsetFromEllipsoid(gpt);
   if ( ossim::isnan(d) )
   {
      QString caption = "Elevation ERROR:";
      QString text = "\
Check for elevation coverage.\n\
Minimum of geoid grid coverage required!";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
      return false;
   }

   //---
   // Send warning to user if no height above msl.
   // Return true though as the image could be over the ocean.
   //---
   d = ossimElevManager::instance()->getHeightAboveMSL(gpt);
   if ( ossim::isnan(d) )
   {
      QString caption = "Elevation WARNING:";
      QString text = "\
No height above mean sea level found!\n\
Over ocean perhaps?";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
   }   

   return true;
}

void ossimQtPositionQualityDialog::getCeLe(ossim_float64& ce,
                                           ossim_float64& le)
{
   int elevSourceIdx = theElevationAccuracyComboBox->currentItem();

   if ( theElevationSources[elevSourceIdx].theName == "source")
   {
      getSourceCeLe(ce, le);
   }
   else
   {
      getDemoCeLe(ce, le);
   }
}

void ossimQtPositionQualityDialog::getSourceCeLe(ossim_float64& ce,
                                                 ossim_float64& le)
{
   // Get the circular error.
   ce = ossimElevManager::instance()->getAccuracyCE90(theGroundPt);

   // Get the linear error.
   le = ossimElevManager::instance()->getAccuracyLE90(theGroundPt);

   if (!ce | !le)
   {
      QString caption = "WARNING:";
      QString text = "Elevation source does not have accuracy info.";
      text += "\nNo surface accuracy used in solution!";
      QMessageBox::information( this,
                                caption,
                                text,
                                QMessageBox::Ok );
   }

   if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimQtPositionQualityDialog::getSourceCeLe"
         << "\nSurface accuracy derived from source elevation: "
         << "\nce=" << ce << " le=" << le
         << std::endl;
   }
}

void ossimQtPositionQualityDialog::getDemoCeLe(ossim_float64& ce,
                                               ossim_float64& le) const
{
   int elevSourceIdx = theElevationAccuracyComboBox->currentItem();

   // Get the circular error.
   ce = theElevationSources[elevSourceIdx].theCe90;

   // Get the linear error.
   le = theElevationSources[elevSourceIdx].theLe90;

      if (traceDebug())
   {
      ossimNotify(ossimNotifyLevel_DEBUG)
         << "ossimQtPositionQualityDialog::getDemoCeLe"
         << "\nSurface accuracy derived from ossim preferences demo settings:"
         << "\nce=" << ce << " le=" << le
         << std::endl;
   }
}

ossimString ossimQtPositionQualityDialog::getImageName(
   bool baseNameOnlyFlag) const
{
   ossimString result;
   ossimImageHandler* handler = getImageHandler();
   if (handler)
   {
      if (baseNameOnlyFlag)
      {
         result = handler->getFilename().file();
      }
      else
      {
         result = handler->getFilename();
      }
   }
   return result;
}

ossimString ossimQtPositionQualityDialog::getUncertaintyType() const
{
   if (isRpcModel())
   {
      return ossimString("rpc");
   }
   return ossimString("cov");
}

bool ossimQtPositionQualityDialog::isRpcModel() const
{
   ossimSensorModel* sensor = getSensorModel();
   if (sensor)
   {
      ossimRpcModel* rpc = PTR_CAST(ossimRpcModel, sensor);
      if (rpc)
      {
         return true;
      }
   }
   return false;
}

bool ossimQtPositionQualityDialog::saveToFile(const ossimFilename& f,
                                              bool concatenateFlag) const
{
   const ossimString ROOT_TAG        = "PqeReport";
   const ossimString UPDATE_TIME_TAG = "pqeUpdateTime";
   const ossimString IMAGE_TAG       = "image";
   const ossimString PQE_POINT_TAG   = "pqePoint";
   const ossimString GML_POINT_TAG   = "gml:Point";

   ossimXmlDocument doc;
   ossimRefPtr<ossimXmlNode> rootNode   = 0;
   ossimRefPtr<ossimXmlNode> timeNode   = 0;
   ossimRefPtr<ossimXmlNode> imageNode  = 0;
   ossimRefPtr<ossimXmlNode> pqeNode    = 0;
   ossimRefPtr<ossimXmlNode> tmpNode    = 0;
   ossimRefPtr<ossimXmlNode> tmpSubNode = 0;
   
   ossimString tag;
   ossimString attribute;
   ossimString value;
   ossimString text;
   ossim_uint32 idIndex = 1;
   ossimString imageName = getImageName(true);

   if (f.exists() && concatenateFlag)
   {
      if (doc.openFile(f) == false)
      {
         ossimNotify(ossimNotifyLevel_WARN)
            << "ossimQtPositionQualityDialog::saveToFile WARNING\n"
            << "Could not open:  " << f.c_str() << std::endl;
         return false;
      }

      rootNode = doc.getRoot();
      if (rootNode->getTag() != ROOT_TAG)
      {
         ossimNotify(ossimNotifyLevel_WARN)
            << "ossimQtPositionQualityDialog::saveToFile WARNING\n"
            << "Root tag from xml document not " << ROOT_TAG << std::endl;
         return false;
      }

      // To hold nodes found.
      std::vector<ossimRefPtr<ossimXmlNode> > xmlNodes;

      // For path:
      ossimString xpath;

      // For iterations.
      std::vector<ossimRefPtr<ossimXmlNode> >::const_iterator i;
      
      // Get an array of nodes matching <image>.
      xpath = "/" + ROOT_TAG + "/" + IMAGE_TAG;
      doc.findNodes(xpath, xmlNodes);

      // Find the <image> node that matches our file name if one exists.
      i = xmlNodes.begin();
      attribute = "filename";
      while (i != xmlNodes.end())
      {
         (*i)->getAttributeValue(value, attribute);
         if (value == imageName)
         {
            imageNode = (*i);
            break;
         }
         ++i;
      }

      // Find the <pqeUpdateTime> update time tag.
      xpath = "/" + ROOT_TAG + "/" + UPDATE_TIME_TAG;
      xmlNodes.clear();
      doc.findNodes(xpath, xmlNodes);
      if (xmlNodes.size())
      {
         timeNode = xmlNodes[0].get();
      }

      // Find the last id index
      xpath = "/" + ROOT_TAG + "/" + IMAGE_TAG + "/" + PQE_POINT_TAG + "/"
         + GML_POINT_TAG;
      xmlNodes.clear();
      doc.findNodes(xpath, xmlNodes);
      idIndex = xmlNodes.size() + 1;
   }

   // The root node can be set or not set so check and make if needed.
   if ( !rootNode.get() )
   {
      rootNode = new ossimXmlNode();
      rootNode->setTag(ROOT_TAG);

      attribute = "xmlns";
      value = "urn:pqe";
      rootNode->addAttribute(attribute, value);

      attribute = "xmlns:igm";
      value = "http://www.opengis.net/igm/0.0";
      rootNode->addAttribute(attribute, value);
      
      attribute = "xmlns:gml";
      value = "http://www.opengis.net/gml";
      rootNode->addAttribute(attribute, value);

      attribute = "xmlns:xsi";
      value = "http://www.w3.org/2001/XMLSchema-instance";
      rootNode->addAttribute(attribute, value);

      attribute = "xsi:schemaLocation";
      value = "urn:pqe pqeReport.xsd";
      rootNode->addAttribute(attribute, value);
      
      attribute = "id";
      value = "Example PQE Report";
      rootNode->addAttribute(attribute, value);

      // Parent to document.
      doc.initRoot(rootNode);

      tmpNode = new ossimXmlNode();
      tag = "pqeOriginatingSystem";
      tmpNode->setTag(tag);
      text = "OSSIM ImageLinker PQE";
      tmpNode->setText(text);
      rootNode->addChildNode(tmpNode);
   }

   // The time node can be set or not set so check and make if needed.
   if ( !timeNode.get() )
   {
      timeNode = new ossimXmlNode();
      tag = "pqeUpdateTime";
      timeNode->setTag(tag);
      rootNode->addChildNode(timeNode);
   }

   // Set the time in the format of: yyyy-mm-ddThh:mm:ss
   char s[20];
   s[19] = '\0';
   time_t t;
   time(&t);
   tm* lt = localtime(&t);
   strftime(s, 20, "%FT%T", lt);
   text = s;
   timeNode->setText(text);
   
   // The image node can be set or not set so check and make if needed.
   if ( !imageNode.get() )
   {
      imageNode = new ossimXmlNode();
      imageNode->setTag(IMAGE_TAG);
      attribute = "filename";
      imageNode->addAttribute(attribute, imageName);

      // Parent to root.
      rootNode->addChildNode(imageNode);  
   }

   if (isRpcModel())
   {
      addRpcPoint(imageNode.get(), idIndex);
   }
   else
   {
      addCovPoint(imageNode.get(), idIndex);
   }

   return doc.write(f);
}

void ossimQtPositionQualityDialog::addRpcPoint(ossimXmlNode* parent,
                                               ossim_uint32 idIndex) const
{
   ossimRefPtr<ossimXmlNode> pqeNode  = 0;
   ossimRefPtr<ossimXmlNode> node     = 0;
   ossimRefPtr<ossimXmlNode> subNode  = 0;
   ossimRefPtr<ossimXmlNode> subNode2 = 0;
   ossimString value;

   // Node for this point.
   pqeNode = new ossimXmlNode();
   pqeNode->setTag(ossimString("pqePoint"));
   value = "Using geometrically-specified uncertainty input;";
   pqeNode->addAttribute(ossimString("remark"), value);
   parent->addChildNode(pqeNode);

   addImagePosition(pqeNode.get());

   addGroundPosition(pqeNode.get(), idIndex);

   node = new ossimXmlNode();
   node->setTag(ossimString("InputUncertainty"));
   node->addAttribute(ossimString("type"),
                      ossimString("losSurfaceIntersection"));
   pqeNode->addChildNode(node);

   subNode = new ossimXmlNode();
   subNode->setTag(ossimString("losBiasError"));
   subNode->addAttribute(ossimString("uom"), ossimString("m"));
   subNode->setText(ossimString::toString(theRpcPqeInputs.theRpcBiasError, 2));
   node->addChildNode(subNode);
   
   subNode = new ossimXmlNode();
   subNode->setTag(ossimString("losRandError"));
   subNode->addAttribute(ossimString("uom"), ossimString("m"));
   subNode->setText(ossimString::toString(theRpcPqeInputs.theRpcRandError, 2));
   node->addChildNode(subNode);

   subNode = new ossimXmlNode();
   subNode->setTag(ossimString("losElevationAngle"));
   subNode->addAttribute(ossimString("uom"), ossimString("degrees"));
   subNode->setText(ossimString::toString(theRpcPqeInputs.theRpcElevationAngle,
                                          2));
   node->addChildNode(subNode);

   subNode = new ossimXmlNode();
   subNode->addAttribute(ossimString("uom"), ossimString("degrees"));
   subNode->setTag(ossimString("losAzimuthAngle"));
   subNode->setText(ossimString::toString(theRpcPqeInputs.theRpcAzimuthAngle,
                                          2));
   node->addChildNode(subNode);

   subNode = new ossimXmlNode();
   subNode->setTag(ossimString("surfaceCharacter"));
   node->addChildNode(subNode);

   value = ossimString::toString(theRpcPqeInputs.theSurfaceNormalVector[0],5);
   value += " ";
   value += ossimString::toString(theRpcPqeInputs.theSurfaceNormalVector[1],5);
   value += " ";
   value += ossimString::toString(theRpcPqeInputs.theSurfaceNormalVector[2],5);
   subNode->addChildNode(ossimString("gml:vector"), value);

   addMatrix(subNode.get(), theRpcPqeInputs.theSurfaceCovMatrix);

   addEvaluation(pqeNode.get());
}

void ossimQtPositionQualityDialog::addCovPoint(ossimXmlNode* parent,
                                               ossim_uint32 idIndex) const
{
   ossimRefPtr<ossimXmlNode> pqeNode = 0;
   ossimRefPtr<ossimXmlNode> node    = 0;
   ossimRefPtr<ossimXmlNode> subNode = 0;
   ossimString value;

   // Node for this point.
   pqeNode = new ossimXmlNode();
   pqeNode->setTag(ossimString("pqePoint"));
   value = "Using covariance matrix uncertainty input;";
   pqeNode->addAttribute(ossimString("remark"), value);
   parent->addChildNode(pqeNode);
   
   addImagePosition(pqeNode.get());

   addGroundPosition(pqeNode.get(), idIndex);

   node = new ossimXmlNode();
   node->setTag(ossimString("InputUncertainty"));
   node->addAttribute(ossimString("type"),
                      ossimString("covarianceMatrix"));
   pqeNode->addChildNode(node);

   addMatrix(node.get(), theCovMat);

   addEvaluation(pqeNode.get());
}

void ossimQtPositionQualityDialog::addImagePosition(ossimXmlNode* parent) const
{
   // image point
   ossimRefPtr<ossimXmlNode> node = new ossimXmlNode();
   node->setTag(ossimString("imagePosition"));
   node->addChildNode(ossimString("samp"),
                      ossimString::toString(theImagePt.x, 1));
   node->addChildNode(ossimString("line"),
                      ossimString::toString(theImagePt.y, 1));
   parent->addChildNode(node);
}

void ossimQtPositionQualityDialog::addGroundPosition(
   ossimXmlNode* parent, ossim_uint32 idIndex) const
{
   ossimString value;
   
   ossimRefPtr<ossimXmlNode> node = new ossimXmlNode();
   node->setTag(ossimString("gml:Point"));
   node->addAttribute(ossimString("srsName"),
                      ossimString("urn:ogc:def:crs:EPSG::4979"));

   value = "p";
   value += ossimString::toString(idIndex);
   node->addAttribute(ossimString("gml:id"), value);
   parent->addChildNode(node);
   
   value = ossimString::toString(theGroundPt.latd());
   value += " ";
   value += ossimString::toString(theGroundPt.lond());
   value += " ";
   value += ossimString::toString(theGroundPt.height(), 2);
   node->addChildNode(ossimString("gml:pos"), value);
}

void ossimQtPositionQualityDialog::addEvaluation(ossimXmlNode* parent) const
{
   ossimRefPtr<ossimXmlNode> node     = 0;
   ossimRefPtr<ossimXmlNode> subNode  = 0;
   ossimRefPtr<ossimXmlNode> subNode2 = 0;
   ossimString value;
   
   node = new ossimXmlNode();
   node->setTag(ossimString("OriginatingEvaluation"));
   parent->addChildNode(node);
   
   subNode = new ossimXmlNode();
   subNode->setTag(ossimString("ErrorEllipse"));
   node->addChildNode(subNode);
   
   subNode2 = new ossimXmlNode();
   subNode2->setTag(ossimString("semiMajorAxis"));
   subNode2->addAttribute(ossimString("uom"), ossimString("m"));
   subNode2->setText(ossimString::toString(theSemiMajorAxis, 2));
   subNode->addChildNode(subNode2);
   
   subNode2 = new ossimXmlNode();
   subNode2->setTag(ossimString("semiMinorAxis"));
   subNode2->addAttribute(ossimString("uom"), ossimString("m"));
   subNode2->setText(ossimString::toString(theSemiMinorAxis, 2));
   subNode->addChildNode(subNode2);
   
   subNode2 = new ossimXmlNode();
   subNode2->setTag(ossimString("azimuth"));
   subNode2->addAttribute(ossimString("uom"), ossimString("degrees"));
   subNode2->setText(ossimString::toString(theAzimuth, 2));
   subNode->addChildNode(subNode2);
   
   subNode->addChildNode(ossimString("pLevel"),
                         ossimString::toString(getProbabilityLevel()));

   subNode = new ossimXmlNode();
   subNode->setTag(ossimString("CE"));
   subNode->addAttribute(ossimString("uom"), ossimString("m"));
   subNode->setText(ossimString::toString(theCe90, 2));
   node->addChildNode(subNode);

   subNode = new ossimXmlNode();
   subNode->setTag(ossimString("LE"));
   subNode->addAttribute(ossimString("uom"), ossimString("m"));
   subNode->setText(ossimString::toString(theLe90, 2));
   node->addChildNode(subNode);

   addMatrix(node.get(), theCovMat);
}

void ossimQtPositionQualityDialog::addMatrix(
   ossimXmlNode* parent, const NEWMAT::Matrix& matrix) const
{
   ossimRefPtr<ossimXmlNode> node = new ossimXmlNode();
   node->setTag(ossimString("igm:CompleteMatrix"));
   parent->addChildNode(node);

   node->addChildNode(ossimString("igm:valueUnit"), ossimString("m m m"));

   // Upper triangular covariance matrix.
   ossimString value;

   value += ossimString::toString(matrix[0][0], 6);
   value+= " ";
   value += ossimString::toString(matrix[0][1], 6);
   value+= " ";
   value += ossimString::toString(matrix[0][2], 6);
   value+= " ";
   value += ossimString::toString(matrix[1][1], 6);
   value+= " ";
   value += ossimString::toString(matrix[1][2], 6);
   value+= " ";
   value += ossimString::toString(matrix[2][2], 6);
   
   node->addChildNode(ossimString("igm:valuesList"), value);
}

ossim_int32 ossimQtPositionQualityDialog::getProbabilityLevel() const
{
   ossim_int32 result = 0;
   
  pqeProbLev_t pLev = static_cast<pqeProbLev_t>(
     theProbabilityLevelComboBox->currentItem());
  switch(pLev)
  {
     case ONE_SIGMA:
        result = 68;
        break;
     case P50:
        result = 50;
        break;
     case P90:
        result = 90;
        break;
     case P95:
        result = 95;
        break;
     default:
        result = 0;
  };
  return result;
}

      
// Hidden (private) copy constructor.
ossimQtPositionQualityDialog::ossimQtPositionQualityDialog(
   const ossimQtPositionQualityDialog& /* obj */ )
   : QTabDialog()
{
}

// Hidden (privat) assignment operator.
const ossimQtPositionQualityDialog& ossimQtPositionQualityDialog::operator=(
   const ossimQtPositionQualityDialog& /* rhs */ )
{
   return *this;
}
