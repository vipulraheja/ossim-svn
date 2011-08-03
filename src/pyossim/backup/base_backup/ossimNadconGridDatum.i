/*-----------------------------------------------------------------------------
 * Filename        : ossimNadconGridDatum.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimNadconGridDatum
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimThreeParamDatum.h>
#include <ossim/base/ossimNadconGridFile.h>
#include <ossim/base/ossimNadconGridDatum.h>
#include <ossim/base/ossimDrect.h>

%}        

/* Wrapping class ossimNadconGridDatum */
class ossimNadconGridDatum : public ossimThreeParamDatum
{
        public:
                ossimNadconGridDatum(const ossimFilename& datumDirectory,
                                const ossimString &code, 
                                const ossimString &name,
                                const ossimEllipsoid* anEllipsoid,
                                double sigmaX,
                                double sigmaY,
                                double sigmaZ,
                                double westLongitude,
                                double eastLongitude,
                                double southLatitude,
                                double northLatitude,
                                double param1,
                                double param2,
                                double param3);

        protected:
                mutable ossimDrect theConusRect;
                mutable ossimDrect theHawaiiRect;
                mutable ossimDrect theAlaskaRect;
                mutable ossimDrect theStGeorgeRect;
                mutable ossimDrect theLatStLaurenceRect;
                mutable ossimDrect theStPaulRect;
                mutable ossimDrect thePrviRect;

                mutable ossimNadconGridFile theLatGrid;
                mutable ossimNadconGridFile theLonGrid;

                mutable ossimDrect    theCurrentGridRect;
                ossimFilename theDatumDirectory;

                void checkGrid(const ossimDpt& latLon)const;
};
