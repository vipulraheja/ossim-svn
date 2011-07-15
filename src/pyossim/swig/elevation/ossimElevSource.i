/*-----------------------------------------------------------------------------
 * Filename        : ossimElevSource.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevSource
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimSource.h>
#include <ossim/base/ossimGrect.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimGeoid.h>
#include <ossim/elevation/ossimElevSource.h>
%}

/* Handling operators */
%rename(__set__) ossimElevSource::operator=;

/* Wrapping class ossimElevSource */
class ossimElevSource : public ossimSource
{
        public:
                virtual const ossimElevSource& operator = (const ossimElevSource& src);
                virtual double getHeightAboveMSL(const ossimGpt&) = 0;
                virtual double getHeightAboveEllipsoid(const ossimGpt&);

                bool intersectRay(const ossimEcefRay& ray, ossimGpt& gpt);

                virtual double getMinHeightAboveMSL() const;
                virtual double getMaxHeightAboveMSL() const;

                double getNullHeightValue() const;
                double getSeaLevelValue()   const;

                virtual bool pointHasCoverage(const ossimGpt&) const = 0;

                virtual double getMeanSpacingMeters() const = 0;

                virtual double getAccuracyLE90(const ossimGpt& gpt) const = 0;
                virtual double getAccuracyCE90(const ossimGpt& gpt) const = 0;


                virtual const ossimGrect& getBoundingGndRect() const;

                virtual bool canConnectMyInputTo(ossim_int32 inputIndex,
                                const ossimConnectableObject* object)const;

                virtual void initialize();
                //   virtual ossimFilename getFilename() const;

                //   virtual bool open();
                //   virtual void close();

                virtual bool getComputeStatisticsFlag() const;
                virtual void setComputeStatisticsFlag(bool flag);


        protected:
                virtual ~ossimElevSource();
                /**
                 * Constructors/Destructors:
                 */
                ossimElevSource();
                ossimElevSource(const ossimElevSource& src);

                /**
                 * Data members:
                 */
                double     theMinHeightAboveMSL;
                double     theMaxHeightAboveMSL;
                double     theNullHeightValue;
                double     theSeaLevelValue;
                ossimGrect theGroundRect;

                //> Controls statistics gathering.  Defaulted to true.
                bool       theComputeStatsFlag;


        private:
                /* Ignoring Macro 
                   TYPE_DATA */
};
