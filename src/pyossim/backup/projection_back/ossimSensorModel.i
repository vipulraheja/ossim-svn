/*-----------------------------------------------------------------------------
 * Filename        : ossimSensorModel.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimSensorModel
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimBilinearProjection.h>
#include <ossim/projection/ossimOptimizableProjection.h>
#include <ossim/base/ossimEcefRay.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimPolygon.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/base/ossimCommon.h> /* for ossim::nan() */
#include <ossim/elevation/ossimElevSource.h>
#include <ossim/base/ossimAdjustableParameterInterface.h>
#include <ossim/matrix/newmat.h>
#include <ossim/matrix/newmatap.h>
#include <ossim/base/ossimException.h>
#include <ossim/projection/ossimSensorModel.h>

%}        

/* Handling operators */
%rename(__cmp__) ossimSensorModel::operator==;
%rename(ossimSensorModel_print) print;

/* Wrappnig class ossimSensorModel */    
class ossimSensorModel : public ossimProjection,
        public ossimOptimizableProjection,
        public ossimAdjustableParameterInterface
{
        public:

                enum CovMatStatus
                {
                        COV_INVALID = 0,
                        COV_PARTIAL = 1,
                        COV_FULL    = 2
                };

                enum DeriveMode
                {
                        OBS_INIT =-99,
                        EVALUATE =-98,
                        P_WRT_X = -1,
                        P_WRT_Y = -2,
                        P_WRT_Z = -3
                };

                /*!
                 * CONSTRUCTORS:
                 */
                ossimSensorModel();
                ossimSensorModel(const ossimSensorModel& copy_this);
                ossimSensorModel(const ossimKeywordlist& geom_kwl);

                virtual ossimObject* getBaseObject();
                virtual const ossimObject* getBaseObject()const;

                /*!
                 * ACCESS METHODS:
                 */
                virtual ossimGpt origin()            const {return theRefGndPt; }
                virtual ossimDpt getMetersPerPixel() const {return ossimDpt(fabs(theGSD.x),
                                fabs(theGSD.y));}

                virtual const double& getNominalPosError() const { return theNominalPosError; }
                virtual const double& getRelativePosError() const { return theRelPosError; }
                virtual void setNominalPosError(const double& ce90) { theNominalPosError = ce90; }
                virtual void setRelativePosError(const double& ce90) { theRelPosError = ce90; }

                virtual void  lineSampleToWorld(const ossimDpt& image_point,
                                ossimGpt&       world_point) const;
                virtual void  worldToLineSample(const ossimGpt& world_point,
                                ossimDpt&       image_point) const;

                virtual void lineSampleHeightToWorld(const ossimDpt& lineSampPt,
                                const double&   heightAboveMSL,
                                ossimGpt&       worldPt) const = 0;
                virtual void imagingRay(const ossimDpt& image_point,
                                ossimEcefRay&   image_ray) const;

                /*!
                 * METHOD: print()
                 * Fulfills base-class pure virtual. Dumps contents of object to ostream.
                 */
                virtual std::ostream& print(std::ostream& out) const;

                void setRefImgPt(const ossimDpt& pt);
                void setRefGndPt(const ossimGpt& pt);

                void setImageRect(const ossimDrect& imageRect);
                void setGroundRect(const ossimGpt& ul,
                                const ossimGpt& ur,
                                const ossimGpt& lr,
                                const ossimGpt& ll);
                
                ossimDpt imageSize() const { return theImageSize; }
                void setImageSize(const ossimDpt& size){theImageSize = size;}
                
                virtual void adjustableParametersChanged()
                {
                        updateModel();
                }
               
                /*!
                 * VIRTUAL METHOD: updateModel()
                 * Following a change to the adjustable parameter set, this virtual
                 * is called to permit instances to compute derived quantities after
                 * parameter change.
                 */
                virtual void updateModel() {}

                /*!
                 * METHODS:  saveState, loadState
                 * Fulfills ossimObject base-class pure virtuals. Loads and saves geometry
                 * KWL files.
                 */
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0) const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                /*!
                 * METHOD: insideImage(image_point)
                 * Returns true if the image_point lies inside the image rectangle.
                 */
                virtual bool insideImage(const ossimDpt& p) const
                {
                        /*          return( (p.u>=(0.0-FLT_EPSILON)) && */
                        /*                  (p.u<=(double)(theImageSize.u-(1-FLT_EPSILON))) && */
                        /*                  (p.v>=(0.0-FLT_EPSILON)) && */
                        /*                  (p.v<=(double)(theImageSize.v-(1-FLT_EPSILON))) ); */
                        // if its close to the edge we will consider it inside the image
                        //
                        return theImageClipRect.pointWithin(p, 2.0);
                }

                /*!
                 * STATIC METHOD: writeGeomTemplate(ostream)
                 * Writes a template of keywords processed by loadState and saveState to
                 * output stream.
                 */
                static void writeGeomTemplate(ostream& os);

                /*!
                 * OPERATORS: 
                 */
                virtual bool operator==(const ossimProjection& proj) const; //inline below

                //! Access methods:
                const ossimString&   getImageID()               const { return theImageID; }
                const ossimDrect&    getImageClipRect()         const { return theImageClipRect; }

                /*!
                 * optimizableProjection implementation
                 */
                virtual ossim_uint32 degreesOfFreedom()const;
                inline virtual bool needsInitialState()const {return true;}
                virtual double optimizeFit(const ossimTieGptSet& tieSet,
                                double* targetVariance=0);

                /*!
                 * METHOD: getForwardDeriv()
                 * gives forward() partial derivative regarding parameter parmIdx (>=0)
                 * default implementation is centered finite difference
                 * -should be reimplemented with formal derivative in child class
                 */
                virtual ossimDpt getForwardDeriv(int parmIdx, const ossimGpt& gpos, double hdelta=1e-11);

                /*!
                 * METHOD: getInverseDeriv()
                 * gives inverse() partial derivative regarding parameter parmIdx (>=0)
                 * default implementation is centered finite difference
                 * -should be reimplemented with formal derivative in child class
                 */
                virtual ossimGpt getInverseDeriv(int parmIdx, const ossimDpt& ipos, double hdelta=1e-11);

                /*!
                 * METHOD: getObsCovMat()
                 * gives 2X2 covariance matrix of observations
                 */
                virtual ossimSensorModel::CovMatStatus getObsCovMat(
                                const ossimDpt& ipos, NEWMAT::SymmetricMatrix& Cov);

                /**
                 * @brief Implementation of pure virtual
                 * ossimProjection::isAffectedByElevation method.
                 * @return true.
                 */
                virtual bool isAffectedByElevation() const { return true; }

                /**
                 * This method computes the ground sample distance(gsd) and sets class
                 * attributes theGSD and theMeanGSD by doing a lineSampleHeightToWorld on
                 * four points and calculating the distance from them.
                 *
                 * @return Nothing but throws ossimException on error.
                 */
                void computeGsd();

        protected:
                virtual ~ossimSensorModel();


                /*!
                 * METHOD: extrapolate()
                 * Extrapolates solutions for points outside of the image. The second
                 * version accepts a height value -- if left at the default, the elevation
                 * will be looked up via theElevation object.
                 */
                virtual ossimDpt extrapolate (const ossimGpt& gp) const;
                virtual ossimGpt extrapolate (const ossimDpt& ip,
                                const double& height=ossim::nan()) const;

                /*!
                 * METHOD: buildNormalEquation
                 * builds linearized system  (LMS equivalent)
                 * A*dp = projResidue
                 * 
                 * A: symetric matrix = tJ*J
                 * dp: system parameter shift that we want to estimate
                 * projResidue = tJ * residue
                 *
                 * t: transposition operator
                 * J = jacobian of transform relative to parameters p, transform can be forward() or inverse()
                 * jacobian is obtained via finite differences
                 * residue can be image (2D) or ground residue(3D)
                 *
                 * TODO: use image/ground points covariance matrices
                 */
                void buildNormalEquation(const ossimTieGptSet& tieSet,
                                NEWMAT::SymmetricMatrix& A,
                                NEWMAT::ColumnVector& residue,
                                NEWMAT::ColumnVector& projResidue,
                                double pstep_scale);

                /*!
                 * METHOD: getResidue()
                 * returns ground opr image residue
                 */
                NEWMAT::ColumnVector getResidue(const ossimTieGptSet& tieSet);

                NEWMAT::ColumnVector solveLeastSquares(NEWMAT::SymmetricMatrix& A,  NEWMAT::ColumnVector& r)const;

                /*!
                 * stable invert stolen from ossimRpcSolver
                 */
                NEWMAT::Matrix invert(const NEWMAT::Matrix& m)const;

                ossimIpt       theImageSize;       // pixels

                /*!
                 * Support sub-image of larger full image by maintaining offset to UL corner
                 */
                ossimDpt       theSubImageOffset;  // pixels

                ossimString    theImageID;
                ossimString    theSensorID;
                ossimDpt       theGSD;             // meters
                ossim_float64  theMeanGSD;         // meters
                ossimGpt       theRefGndPt;        // should be image center
                ossimDpt       theRefImgPt;        // should be image center
                ossimPolygon   theBoundGndPolygon;
                ossimDrect     theImageClipRect;
                ossim_float64  theRelPosError; 	// meters, relative to other models in the set
                ossim_float64  theNominalPosError; // meters

                /** Partials for current point */
                ossimDpt theParWRTx;
                ossimDpt theParWRTy;
                ossimDpt theParWRTz;

                /** Observations & residuals for current point */
                ossimDpt theObs;
                ossimDpt theResid;

                /**
                 * Used as an initial guess for iterative solutions and a guess for points outside the support
                 * bounds.
                 */ 
                ossimRefPtr<ossimProjection> theSeedFunction;

                mutable bool theExtrapolateImageFlag;
                mutable bool theExtrapolateGroundFlag;

                /* Ignoring Macro
                TYPE_DATA */
};
