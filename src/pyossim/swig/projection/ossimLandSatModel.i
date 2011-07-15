/*-----------------------------------------------------------------------------
 * Filename        : ossimLandSatModel.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimLandSatModel
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimSensorModel.h>
#include <ossim/projection/ossimLandSatModel.h>
#include <ossim/projection/ossimMapProjection.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimEcefRay.h>
#include <ossim/base/ossimEcefPoint.h>
#include <ossim/base/ossimMatrix3x3.h>
#include <iostream>

%}

/* Handling operators */
%rename(ossimLandSatModel_print) print;

/* Wrapping class ossimLandSatModel */
class ossimLandSatModel : public ossimSensorModel
{
        public:
                /*!
                 * CONSTRUCTORS:
                 */
                ossimLandSatModel();
                ossimLandSatModel(const ossimFfL7& head);
                ossimLandSatModel(const ossimFilename& init_file);
                ossimLandSatModel(const ossimKeywordlist& geom_kwl);
                ossimLandSatModel(const ossimLandSatModel& rhs);
                virtual ossimObject* dup()const;

                enum ProjectionType
                {
                        UNKNOWN_PROJECTION = 0,
                        UTM_MAP,
                        UTM_ORBIT,
                        SOM_MAP,
                        SOM_ORBIT
                };

                enum AdjustParamIndex
                {
                        INTRACK_OFFSET = 0,
                        CRTRACK_OFFSET,
                        LINE_GSD_CORR,
                        SAMP_GSD_CORR,
                        ROLL_OFFSET,
                        YAW_OFFSET,
                        YAW_RATE,
                        MAP_ROTATION,
                        NUM_ADJUSTABLE_PARAMS // not an index
                };


                /*!
                 * Extends base-class implementation. Dumps contents of object to ostream.
                 */
                virtual std::ostream& print(std::ostream& out) const;

                /*!
                 * Fulfills ossimObject base-class pure virtuals. Loads and saves geometry
                 * KWL files. Returns true if successful.
                 */
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0) const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                static void writeGeomTemplate(ostream& os);

                virtual void lineSampleHeightToWorld(const ossimDpt& image_point,
                                const double&   heightEllipsoid,
                                ossimGpt&       worldPoint) const;

                virtual void imagingRay(const ossimDpt& image_point,
                                ossimEcefRay&   image_ray) const;

                virtual void updateModel();

                inline virtual bool useForward()const {return false;} //!image to ground faster
                virtual bool setupOptimizer(const ossimString& init_file); //!uses file path to init model

        protected:

                virtual ~ossimLandSatModel();
                
                void initFromHeader(const ossimFfL7& head);

                virtual void initAdjustableParameters();
                void initMapProjection();

                /***
                // Image constant parameters:
                ***/
                double           theIllumAzimuth;  
                double           theIllumElevation;
                double           theOrbitAltitude;
                double           theOrbitInclination;
                int              theMapZone;
                ossimDpt         theMapOffset;
                int              theWrsPathNumber;
                int              theWrsRowNumber;    
                double           theMeridianalAngle;   
                double           thePositionError;

                ProjectionType       theProjectionType;
                ossimRefPtr<ossimMapProjection>  theMapProjection;

                double           theMapAzimAngle; 
                double           theMapAzimCos;    
                double           theMapAzimSin;
                double           theMap2IcRotAngle;
                double           theMap2IcRotCos;
                double           theMap2IcRotSin;

                /***
                // Adjustable parameters:
                ***/
                double           theIntrackOffset;
                double           theCrtrackOffset;
                double           theLineGsdCorr;   
                double           theSampGsdCorr;   
                double           theRollOffset;
                double           theYawOffset; 
                double           theYawRate; 
                double           theMapRotation; 

                /***
                // Quantities derived from the adjustable parameters:
                ***/
                NEWMAT::Matrix   theRollRotMat;

                /* Ignoring Macro
                TYPE_DATA */
};
