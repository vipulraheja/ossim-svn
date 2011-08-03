/*-----------------------------------------------------------------------------
Filename        : ossimDatum.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimDatum
-----------------------------------------------------------------------------*/

%module pyossim

%{
        
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimDatum.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimEllipsoid.h>

%}        

/* Handling ossimHistogramRemapper assignment operator */
%rename(__cmp__) ossimHistogramRemapper::operator==;
%rename(__ne__) ossimHistogramRemapper::operator!=;


/* Wrapping the class ossimDatum */
class ossimDatum
{
        friend class ossimDatumFactory;

        public:
                ossimDatum(const ossimString &alpha_code, const ossimString &name,
                                const ossimEllipsoid* anEllipsoid,
                                ossim_float64 sigmaX, ossim_float64 sigmaY, ossim_float64 sigmaZ,
                                ossim_float64 westLongitude, ossim_float64 eastLongitude,
                                ossim_float64 southLatitude, ossim_float64 northLatitude);

                virtual ossimGpt shift(const ossimGpt    &aPt)const=0;
                virtual ossimGpt       shiftToWgs84(const ossimGpt &aPt)const = 0;
                virtual ossimGpt       shiftFromWgs84(const ossimGpt &aPt)const = 0;


                virtual bool  isTheSameAs(const ossimDatum *aDatum)const
                {
                        return this == aDatum;
                }

                virtual const ossimString& code()const{return theCode;}
                virtual const ossimString& name()const{return theName;}
                virtual ossim_uint32 epsgCode()const{return theEpsgCode;}
                virtual const ossimEllipsoid* ellipsoid()const{return theEllipsoid;}
                virtual ossim_float64 sigmaX()const{return theSigmaX;}
                virtual ossim_float64 sigmaY()const{return theSigmaY;}
                virtual ossim_float64 sigmaZ()const{return theSigmaZ;}

                virtual ossim_float64 westLongitude()const{return theWestLongitude;}
                virtual ossim_float64 eastLongitude()const{return theEastLongitude;}
                virtual ossim_float64 southLatitude()const{return theSouthLatitude;}
                virtual ossim_float64 northLatitude()const{return theNorthLatitude;}

                virtual ossim_float64 param1()const=0;
                virtual ossim_float64 param2()const=0;
                virtual ossim_float64 param3()const=0;
                virtual ossim_float64 param4()const=0;
                virtual ossim_float64 param5()const=0;
                virtual ossim_float64 param6()const=0;
                virtual ossim_float64 param7()const=0;

                virtual bool isInside(ossim_float64 latitude, ossim_float64 longitude)const
                {
                        return ((theSouthLatitude <= latitude) &&
                                        (latitude <= theNorthLatitude) &&
                                        (theWestLongitude <= longitude) &&
                                        (longitude <= theEastLongitude));
                }

                bool operator==(const ossimDatum& rhs) const;
                bool operator!=(const ossimDatum& rhs)const
                {
                        return (!(*this == rhs));
                }


        protected:
                /* Only friend ossimDatumFactory is permitted to delete */
                virtual ~ossimDatum(){};

                virtual void    molodenskyShift( double a,
                                double da,
                                double f,
                                double df,
                                double dx,
                                double dy,
                                double dz,
                                double Lat_in,
                                double Lon_in,
                                double Hgt_in,
                                double &Lat_out,
                                double &Lon_out,
                                double &Hgt_out)const;
                bool withinMolodenskyRange(const ossimGpt& pt)const
                {
                        double lat = pt.latd();

                        return ((lat < 89.75) && (lat > -89.75));
                }


        private:
                ossimString           theCode;
                ossim_uint32          theEpsgCode;
                ossimString           theName;
                const ossimEllipsoid *theEllipsoid;

                ossim_float64        theSigmaX;
                ossim_float64        theSigmaY;
                ossim_float64        theSigmaZ;

                ossim_float64        theWestLongitude;
                ossim_float64        theEastLongitude;
                ossim_float64        theSouthLatitude;
                ossim_float64        theNorthLatitude;   
};
