/*-----------------------------------------------------------------------------
 * Filename        : ossimSensorModelTuple.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimSensorModelTuple
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimSensorModel.h>
#include <ossim/projection/ossimSensorModelTuple.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/elevation/ossimHgtRef.h>
#include <ossim/matrix/newmat.h>

%}

/* Handling operators */
%rename(ossimSensorModelTuple_print) print;

typedef vector<ossimDpt> DptSet_t;

/**
 * Container class to hold computed rpc model inputs to the
 * ossimPositionQualityEvaluator constructor.  These are stored for retrieval
 * purposes only and will only be initialized if the underlying sensor model
 * is an rpc.
 */
class ossimRpcPqeInputs
{
        public:
                ossimRpcPqeInputs();
                ~ossimRpcPqeInputs();
                ossim_float64       theRpcElevationAngle; // decimal degrees
                ossim_float64       theRpcAzimuthAngle;   // decimal degrees
                ossim_float64       theRpcBiasError;
                ossim_float64       theRpcRandError;
                ossimColumnVector3d theSurfaceNormalVector;
                NEWMAT::Matrix      theSurfaceCovMatrix;
};

class ossimSensorModelTuple
{
        public:

                enum DeriveMode
                {
                        OBS_INIT =-99,
                        EVALUATE =-98,
                        P_WRT_X = -1,
                        P_WRT_Y = -2,
                        P_WRT_Z = -3
                };

                enum IntersectStatus
                {
                        OP_SUCCESS      = 0,
                        ERROR_PROP_FAIL = 1,
                        OP_FAIL         = 2
                };

                /** @brief default constructor */
                ossimSensorModelTuple();

                /** @brief virtual destructor */
                ~ossimSensorModelTuple();

                /**
                 * @brief Method to add an image to the tuple.
                 */
                void addImage(ossimSensorModel* image);

                /**
                 * @brief print method.
                 */
                std::ostream& print(std::ostream& out) const;

                ossimSensorModelTuple::IntersectStatus intersect(
                                const DptSet_t         obs,
                                ossimEcefPoint&  pt,
                                NEWMAT::Matrix&  covMat) const;

                ossimSensorModelTuple::IntersectStatus intersect(
                                const ossim_int32&     img,
                                const ossimDpt&        obs,
                                ossimEcefPoint&  pt,
                                NEWMAT::Matrix&  covMat);

                ossimSensorModelTuple::IntersectStatus intersect(
                                const ossim_int32&     img,
                                const ossimDpt&        obs,
                                const ossim_float64&   heightAboveEllipsoid,
                                ossimEcefPoint&  pt,
                                NEWMAT::Matrix&  covMat);

                bool setIntersectionSurfaceAccuracy(const ossim_float64& surfCE90,
                                const ossim_float64& surfLE90);

                /** @param obj Object to initialize with rpc pqe inputs. */
                void getRpcPqeInputs(ossimRpcPqeInputs& obj) const;

        private:
                std::vector<ossimSensorModel*> theImages;

                ossim_int32    theNumImages;

                ossim_float64  theSurfCE90;
                ossim_float64  theSurfLE90;
                bool           theSurfAccSet;
                bool           theSurfAccRepresentsNoDEM;

                /**
                 * Rpc model only, container to capture pqe inputs for report purposes only.
                 */
                ossimRpcPqeInputs theRpcPqeInputs;

                bool computeSingleInterCov(const ossim_int32& img,
                                const ossimDpt&    obs,
                                const ossimGpt&    ptG,
                                HeightRefType_t    cRefType,
                                NEWMAT::Matrix&    covMat);


                bool getGroundObsEqComponents(const ossim_int32 img,
                                const ossim_int32 iter,
                                const ossimDpt& obs,
                                const ossimGpt& ptEst,
                                ossimDpt& resid,
                                NEWMAT::Matrix& B,
                                NEWMAT::SymmetricMatrix& W) const;

                NEWMAT::Matrix invert(const NEWMAT::Matrix& m) const;

};
