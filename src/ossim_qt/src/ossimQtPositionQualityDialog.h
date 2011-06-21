//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description:
//
// This dialog box is the interface between an image in imagelinker and the
// ossimPositionQualityEvaluator.  The image must have a sensor model that
// provides some type of error stats to work.
//
// $Id$
//----------------------------------------------------------------------------
#ifndef ossimQtPositionQualityDialog_HEADER
#define ossimQtPositionQualityDialog_HEADER

#include <iosfwd>

#include <qtabdialog.h>

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/matrix/newmat.h>

#include <ossim/projection/ossimSensorModelTuple.h> /* for ossimRpcPqeInputs */


// Forward class declarations.
class QGroupBox;
class QVGroupBox;
class QVBox;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QPushButton;
class QTextEdit;

class ossimImageChain;
class ossimImageHandler;
class ossimImageViewTransform;
class ossimProjection;
class ossimQtScrollingImageWidget;
class ossimQtMouseEvent;
class ossimGpt;
class ossimSensorModel;
class ossimGeoAnnotationEllipseObject;
class ossimGeoAnnotationSource;
class ossimQtImageWindowController;

/**
 * Container class PQE accuracy source for "Backdrop Acc" and "Elev Acc"
 * pulldowns.
 */
class ossimPqeAccSrc
{
public:
   /** default constuctor */
   ossimPqeAccSrc();
   
   ossimString   theName;
   ossim_float64 theCe90;
   ossim_float64 theLe90;

   friend std::ostream& operator<<(std::ostream& out,
                                   const ossimPqeAccSrc& obj);
};

class ossimQtPositionQualityDialog : public QTabDialog
{
   Q_OBJECT

public:

   /** public constructor */
   ossimQtPositionQualityDialog(QWidget* parent);

   /** virtual destructor */
   virtual ~ossimQtPositionQualityDialog();

   void setImageWidget(ossimQtScrollingImageWidget* widget);

   /** Sets pointer to the image window controller for igen call. */
   void setController(ossimQtImageWindowController* controller);


public slots:

   /** Slot to hook up to the widget's scrollingImageWidgetMouseEvent. */
   virtual void trackScrollingImageWidget(ossimQtMouseEvent* evt);

   /**
    * Slot for activated signal from "Probability Level", "Backdrop Acc" or
    * "Elev Acc" combo boxes.  This in turn calls initAccuracyStrings().
    */
   void recalc(int item);

   void pqeEnabledToggled(bool flag);

   void graphicsEnabledToggled(bool flag);

   void lineEditReturnPressed();

   void saveButtonClicked();

private:

   ossimImageChain*         getChain()              const;
   ossimImageHandler*       getImageHandler()       const;
   ossimImageViewTransform* getImageViewTransform() const;
   ossimProjection*         getImageProjection()    const;
   ossimProjection*         getViewProjection()     const;
   ossimSensorModel*        getSensorModel()        const;
   
   ossimGeoAnnotationEllipseObject* getEllipse() const;
   void addAnnotatorToChain();
   void removeAnnotatorFromChain();
   void updateEllipse();

   void initializeDialog();
   void initPositionStrings();
   void initAccuracyStrings();
   void setLatString();
   void setLonString();
   void setHgtAboveMslString();
   void setHgtAboveEllipsoidString();
   void setElevSourceString();

   void buildQualityEvaluatorWidget();
   void buildReportGeneratorWidget();
   void buildBackdropPulldown();
   void buildElevAccPulldown();

   /**
    * @brief Builds an array of ossimPqeAccSrc's from keyBase and ossim
    * preferences.
    *
    * @param keyBase Key to search preferences for e.g.: "pqe_backdrop"
    * 
    * @param result vector to initialize.
    */
   void buildSourceList(const ossimString& keyBase,
                        std::vector<ossimPqeAccSrc> & result);

   void updateLatitudeField();

   ossim_float64  getDegrees(const ossimString& s, bool lat_flag) const;

   void refresh();

   /**
    * @brief Sets the ellipse options, fill, thickness, axes, and color.
    * Default color is white.
    * 
    * @note Color can be set in preferences using key word (example for green):
    * pqe_normalized_rgb_ellipse_color: 0.004 1.0 0.004
    */
   void setEllipseOptions();

   /**
    * @brief Checks for nan geiod or msl offsets.
    * @return true if no nans, false if not.
    *
    * This is not const because of QT messsage call is not const...
    */
   bool checkElevForPoint(const ossimGpt& gpt);

   /**
    * @brief Gets CE/LE from either source or ossim preferences(demo).
    */
   void getCeLe(ossim_float64& ce, ossim_float64& le);

   /**
    * @brief Gets CE/LE for theGroundPt from the elevation manager.
    * @param ce Argument to initialize with circular error.
    * @param le Argument to initialize with linear error.
    */
   void getSourceCeLe(ossim_float64& ce, ossim_float64& le);

   /**
    * @brief Gets CE/LE from selection on theElevationAccuracyComboBox.
    * @param ce Argument to initialize with circular error.
    * @param le Argument to initialize with linear error.
    */
   void getDemoCeLe(ossim_float64& ce, ossim_float64& le) const;

   /**
    * @brief Gets the image name.
    * 
    * @param baseNameOnlyFlag  If true returns only the basename so if file is
    * /data1/image_formats/nitf/iran/iran-10DEC05QB02.ntf
    * this will return iran-10DEC05QB02.ntf
    * 
    * @return The image file.  Either full path or basename.
    */
   ossimString getImageName(bool baseNameOnlyFlag) const;

   /**
    * @return The uncertaintly type as a string.  This will either be "rpc"
    * or "cov".
    */
   ossimString getUncertaintyType() const;

   /** @return true if senor model is of rpc type. */
   bool isRpcModel() const;
   
   /**
    * @brief Saves the last dropped point to a file.  If file exists and
    * the concatenateFlag is true the point will be added to the file; else
    * it will be overwritten.
    *
    * @param f File to write to.
    *
    * @param concatenateFlag If true and f exist we will concatenate to f.
    *
    * @return True on successful write of file, false on error.  Error can
    * be on open of existing or write of new file.
    */
   bool saveToFile(const ossimFilename& f, bool concatenateFlag) const;

   void addRpcPoint(ossimXmlNode* parent, ossim_uint32 idIndex) const;
   void addCovPoint(ossimXmlNode* parent, ossim_uint32 idIndex) const;
   void addImagePosition(ossimXmlNode* parent) const;
   void addGroundPosition(ossimXmlNode* parent, ossim_uint32 idIndex) const;
   void addEvaluation(ossimXmlNode* parent) const;
   void addMatrix(ossimXmlNode* parent,
                  const NEWMAT::Matrix& matrix) const;
   ossim_int32 getProbabilityLevel() const;
   

   /** Hide from use copy constructor. */
   ossimQtPositionQualityDialog(const ossimQtPositionQualityDialog& obj);

   /** Hide from use assignment operator. */
   const ossimQtPositionQualityDialog& operator=(const ossimQtPositionQualityDialog& rhs);

   /** OK button */
   // QPushButton* theOkButton;

   /** "Quality Evaluator" widget parented to this dialog. */
   QVBox* theQualityEvaluatorWidget;

   // QLineEdit* theQePointIdLineEdit;

   QCheckBox* thePqeEnabledCheckBox;
   QCheckBox* theGraphicsEnabledCheckBox;
   
   QLineEdit* theSemiMajorAxisLineEdit;
   QLineEdit* theSemiMinorAxisLineEdit;
   QLineEdit* theAzimuthLineEdit;

   QLineEdit* theCircularErrorLineEdit;
   QLineEdit* theLinearErrorLineEdit;
      
   QLineEdit* theLatitudeLineEdit;
   QLineEdit* theLongitudeLineEdit;
   QLineEdit* theHeightAboveEllipsoidLineEdit;
   QLineEdit* theHeightAboveMslLineEdit;
   
   QLineEdit* theElevSourceLineEdit;
   
   // QLineEdit* theUtmZoneLineEdit;
   // QPushButton* thePositionToButton;
   
   QComboBox* theProbabilityLevelComboBox;
   QComboBox* theBackdropAccuracyComboBox;
   QComboBox* theElevationAccuracyComboBox;
   
   /** "Report Generator" widget parented to this dialog. */
   QVBox*       theReportGeneratorWidget;
   QLineEdit*   thePointIdLineEdit;
   QTextEdit*   theAnnotationNoteTextEdit;
   QComboBox*   theReportFormatComboBox;
   QPushButton* theSaveButton;

   ossimQtScrollingImageWidget*  theWidget;
   ossim_uint32                  theWidgetLayer;
   ossimQtImageWindowController* theController;

   ossimGpt       theGroundPt;
   ossimDpt       theImagePt; // line sample of point in image space.
   NEWMAT::Matrix theCovMat;  // 3 x 3
   ossim_float64  theHeightAboveEllipsoid;
   ossim_float64  theHeightAboveMsl;
   ossim_float64  theSemiMinorAxis;     // meters
   ossim_float64  theSemiMajorAxis;     // meters
   ossim_float64  theAzimuth;           // degrees
   ossim_float64  theCe90;              // meters
   ossim_float64  theLe90;              // meters
   bool           thePqeEnabledFlag;
   bool           theGraphicsEnabledFlag;

   ossimGeoAnnotationEllipseObject*      theEllipse;
   ossimRefPtr<ossimGeoAnnotationSource> theAnnotator;
   
   std::vector<ossimPqeAccSrc> theBackdropSources;
   std::vector<ossimPqeAccSrc> theElevationSources;

   ossimRpcPqeInputs theRpcPqeInputs;
};

#endif /* End of "#ifndef ossimQtPositionQualityDialog_HEADER" */
