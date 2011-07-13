/*-----------------------------------------------------------------------------
 * Filename        : ossimMapProjection.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimMapProjection
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimMapProjection.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimKeyword.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimEllipsoid.h>
#include <ossim/base/ossimDatum.h>
#include <ossim/base/ossimDrect.h>
#include <iostream>

#include <ossim/base/ossimMatrix4x4.h>

%}

/* Handling ossimHistogramRemapper assignment operator */
%rename(__cmp__) ossimMapProjection::operator==;

/* Handling the reserved function print */
%rename(ossimMapProjection_print) ossimMapProjection::print;


/* Wrapping the class ossimMapProjection */
class ossimMapProjection : public ossimProjection
{
        public:
                ossimMapProjection(const ossimEllipsoid& ellipsoid = ossimEllipsoid(),
                                const ossimGpt& origin=ossimGpt());
                ossimMapProjection(const ossimMapProjection& src);

                virtual ossimGpt origin()const;
                virtual ossimDpt forward(const ossimGpt &worldPoint) const = 0;
                virtual ossimGpt inverse(const ossimDpt &projectedPoint)const = 0;

                virtual ossimDpt worldToLineSample(const ossimGpt &worldPoint)const;
                virtual void     worldToLineSample(const ossimGpt &worldPoint,
                                ossimDpt&       lineSample)const;

                virtual ossimGpt lineSampleToWorld(const ossimDpt &projectedPoint)const;
                virtual void     lineSampleToWorld(const ossimDpt &projectedPoint,
                                ossimGpt& gpt)const;

                virtual void lineSampleHeightToWorld(const ossimDpt& lineSampPt,
                                const double&   heightAboveEllipsoid,
                                ossimGpt&       worldPt) const;
                virtual void lineSampleToEastingNorthing(const ossimDpt& liineSample,
                                ossimDpt& eastingNorthing)const;

                virtual void eastingNorthingToLineSample(const ossimDpt& eastingNorthing,
                                ossimDpt&       lineSample)const;
                virtual void eastingNorthingToWorld(const ossimDpt& eastingNorthing,
                                ossimGpt&       worldPt)const;


                virtual double getFalseEasting() const;
                virtual double getFalseNorthing() const;

                virtual double getStandardParallel1() const;
                virtual double getStandardParallel2() const;

                virtual void update();

                virtual void setPcsCode(ossim_uint32 pcsCode);
                virtual void setGcsCode(ossim_uint32 pcsCode);

                virtual ossim_uint32 getPcsCode()const;
                virtual ossim_uint32 getGcsCode()const;

                virtual ossimString getProjectionName() const;

                virtual double getA() const;
                virtual double getB() const;
                virtual double getF() const;

                virtual ossimDpt getMetersPerPixel() const;

                virtual const ossimDpt& getDecimalDegreesPerPixel() const;

                virtual const ossimDpt&   getUlEastingNorthing() const;
                virtual const ossimGpt&   getUlGpt() const;
                virtual const ossimDatum* getDatum() const;
                const ossimEllipsoid&     getEllipsoid() const { return theEllipsoid; }
                const ossimGpt& getOrigin() const;
                virtual bool isGeographic()const;

                virtual void applyScale(const ossimDpt& scale, bool recenterTiePoint);

                virtual void setEllipsoid(const ossimEllipsoid& ellipsoid);
                virtual void setAB(double a, double b);
                virtual void setDatum(const ossimDatum* datum);
                virtual void setOrigin(const ossimGpt& origin);

                virtual void setMetersPerPixel(const ossimDpt& gsd);
                virtual void setDecimalDegreesPerPixel(const ossimDpt& gsd);
                virtual void setUlTiePoints(const ossimGpt& gpt);
                virtual void setUlTiePoints(const ossimDpt& eastingNorthing);
                virtual void setUlEastingNorthing(const  ossimDpt& ulEastingNorthing);
                virtual void setUlGpt(const  ossimGpt& ulGpt);
                virtual void assign( const  ossimProjection &aProjection);

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0) const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                virtual std::ostream& print(std::ostream& out) const;

                virtual bool operator==(const ossimProjection& projection) const;

                virtual void computeDegreesPerPixel(const ossimGpt& ground,
                                const ossimDpt& metersPerPixel,
                                double &deltaLat,
                                double &deltaLon);
                virtual void computeMetersPerPixel(const ossimGpt& center,
                                double deltaDegreesPerPixelLat,
                                double deltaDegreesPerPixelLon,
                                ossimDpt &metersPerPixel);
                virtual void computeMetersPerPixel(double deltaDegreesPerPixelLat,
                                double deltaDegreesPerPixelLon,
                                ossimDpt &metersPerPixel);

                void setMatrix(double rotation,
                                const ossimDpt& scale,
                                const ossimDpt& translation);
                void setMatrixScale(const ossimDpt& scale);
                void setMatrixRotation(double rotation);
                void setMatrixTranslation(const ossimDpt& translation);

                void snapTiePointTo(ossim_float64 multiple, ossimUnitType unitType);
                void snapTiePointToOrigin();

                void setElevationLookupFlag(bool flag);
                bool getElevationLookupFlag()const;
                ossimUnitType getModelTransformUnitType()const
                {
                        return theModelTransformUnitType;
                }
                void setModelTransformUnitType(ossimUnitType unit)
                {
                        theModelTransformUnitType = unit;
                }
                bool hasModelTransform()const
                {
                        return (theModelTransformUnitType != OSSIM_UNIT_UNKNOWN);
                }

                virtual bool isAffectedByElevation() const { return false; }

                void setProjectionUnits(ossimUnitType units) { theProjectionUnits = units; }
                ossimUnitType getProjectionUnits() const { return theProjectionUnits; }

        protected:

                virtual ~ossimMapProjection();

                void updateFromTransform();

                ossimEllipsoid   theEllipsoid;
                ossimGpt         theOrigin;

                const ossimDatum* theDatum;

                ossimDpt          theMetersPerPixel;
                ossimDpt          theDegreesPerPixel;
                ossimGpt          theUlGpt;
                ossimDpt          theUlEastingNorthing;
                ossimDpt          theFalseEastingNorthing;

                mutable ossim_uint32      thePcsCode;
                mutable ossim_uint32      theGcsCode;

                bool              theElevationLookupFlag;

                ossimMatrix4x4 theModelTransform;               // goes from image to model
                ossimMatrix4x4 theInverseModelTransform;        //goes from model back to image

                ossimUnitType theModelTransformUnitType;
                ossimUnitType theProjectionUnits;
                
                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
