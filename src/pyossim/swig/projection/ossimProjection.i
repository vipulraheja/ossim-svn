/*-----------------------------------------------------------------------------
Filename        : ossimProjection.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimProjection which is the 
                  Base class for all projections (2D-to-3D transform).
-----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimErrorStatusInterface.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimGeoPolygon.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimProperty.h>
#include <ossim/base/ossimPropertyInterface.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimSource.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimRefPtr.h>

#include <ossim/projection/ossimProjection.h>

#include <vector>
#include <string>
%}


class ossimProjection : public ossimObject
{
        public:
                ossimProjection();

                virtual ~ossimProjection() {};

                virtual ossimObject *dup() const=0;

                virtual ossimGpt origin() const=0;

                virtual ossimGpt forward(const ossimGpt &wp) const;
                virtual ossimGpt backward(const ossimDpt &pp) const;

                virtual void worldToLineSample(const ossimGpt& worldPoint,
                                ossimDpt& lineSampPt) const=0;

                virtual void lineSampleToWorld(const ossimDpt& lineSampPt,
                                ossimGpt& worldPt) const=0;

                virtual void lineSampleHeightToWorld(const ossimDpt& lineSampPt,
                                const double&   heightAboveEllipsoid,
                                ossimGpt&       worldPt) const=0;

                virtual void getRoundTripError(const ossimDpt& imagePoint,
                                ossimDpt& errorResult)const;

                virtual void getRoundTripError(const ossimGpt& groundPoint,
                                ossimDpt& errorResult)const;

                virtual void getGroundClipPoints(ossimGeoPolygon& gpts)const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                virtual ossimDpt getMetersPerPixel() const=0;

                virtual bool isAffectedByElevation() const=0;
};
