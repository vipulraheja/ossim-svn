/*-----------------------------------------------------------------------------
Filename        : ossimGpt.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimGpt
-----------------------------------------------------------------------------*/

%module pyossim

%{
        
#include <iosfwd>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimDatumFactory.h>
#include <ossim/base/ossimString.h>

%}

/* Handling operators */
%rename(__set__) ossimGpt::operator=;
%rename(__lshift__) operator>>;
%rename(__rshift__) operator<<;

%rename(ossimGpt_print) print;

class ossimGpt
{
        public:
                /**
                 * Constructor.  The values are assumed to be in DEGREES.
                 */
                ossimGpt(const double alat=0,  
                                const double alon=0,  
                                const double ahgt=0,
                                const ossimDatum* aDatum=ossimDatumFactory::instance()->wgs84()) :
                        lat(alat),
                        lon(alon),
                        hgt(ahgt),  
                        theDatum(aDatum) {} 

                ossimGpt(const ossimGpt& src);
                ossimGpt(const ossimEcefPoint &aPt,
                                const ossimDatum* aDatum=ossimDatumFactory::instance()->wgs84());

                double latr()const{return lat*RAD_PER_DEG;}
                void latr(double radianValue){lat = radianValue*DEG_PER_RAD;}

                double lonr()const{return lon*RAD_PER_DEG;}
                void lonr(double radianValue)
                {
                        lon = radianValue*DEG_PER_RAD; 
                }

                double latd()const{return lat;}
                void latd(double degreeValue) {lat = degreeValue;}

                double lond()const{return lon;}
                void lond(double degreeValue) {lon = degreeValue; }

                double height()const{return hgt;}
                double heightMSL() const;
                void height(double height){hgt = height;}
                void heightMSL(double heightMSL);

                void makeNan(){lat=ossim::nan(); lon=ossim::nan(); hgt=ossim::nan();}
                bool isNan()const
                {
                        return (ossim::isnan(lat)&&ossim::isnan(lon)&&ossim::isnan(hgt));
                }
                bool hasNans()const
                {
                        return (ossim::isnan(lat)||ossim::isnan(lon)||ossim::isnan(hgt));
                }
                bool isLatNan()const{return ossim::isnan(lat);}
                bool isLonNan()const{return ossim::isnan(lon);}
                bool isHgtNan()const{return ossim::isnan(hgt);}

                std::ostream& print(std::ostream& os, ossim_uint32 precision=15) const;

                friend std::ostream& operator<<(std::ostream& os,
                                const ossimGpt& pt);

                /**
                 * @param precision Output floating point precision.
                 * 
                 * @return ossimString representing point.
                 *
                 * Output format:
                 * ( 30.00000000000000, -90.00000000000000, 0.00000000000000, WGE )
                 *   -----latitude----  -----longitude----  ------height----  datum
                 */
                ossimString toString(ossim_uint32 precision=15) const;

                void toPoint(const std::string& s);
                friend std::istream& operator>>(std::istream& is,
                                ossimGpt& pt);
                const ossimDatum* datum()const{return theDatum;}
                void datum(const ossimDatum* aDatum){theDatum = aDatum?aDatum:theDatum;}

                /**
                 * This will actually perform a shift.
                 */
                void changeDatum(const ossimDatum *datum);

                const ossimGpt& operator = (const ossimGpt &aPt);
                bool operator ==(const ossimGpt& gpt)const
                {
                        return ( ossim::almostEqual(lat, gpt.lat)&&
                                        ossim::almostEqual(lon, gpt.lon)&&
                                        ossim::almostEqual(hgt, gpt.hgt)&&
                                        (theDatum == gpt.theDatum));
                }
                bool operator != (const ossimGpt& gpt) const { return !(*this == gpt); }

                /**
                 * METHOD: limitLonTo180()
                 * Converts the lon data member to a value between -180 and +180:
                 */
                void  limitLonTo180()
                {
                        if (lon < -180.0) lon += 360.0; else if (lon > 180.0) lon -= 360.0; 
                }

                /**
                 * @brief Wrap method to maintain longitude between -180 and +180 and latitude between
                 * -90 and +90.  Inlined below.
                 */
                void wrap();

                void clampLon(double low, double high)
                {
                        if(lon < low) lon = low;
                        if(lon > high) lon = high;
                }
                void clampLat(double low, double high)
                {
                        if(lat < low) lat = low;
                        if(lat > high) lat = high;
                }
                void clampHgt(double low, double high)
                {
                        if(hgt < low) hgt = low;
                        if(hgt > high) hgt = high;
                }

                /**
                 * METHOD: distanceTo(ossimGpt)
                 * Computes straight-line distance in meters between this and arg gpt:
                 */
                double distanceTo(const ossimGpt& arg_gpt) const;
                double azimuthTo(const ossimGpt& arg_gpt) const;

                ossimDpt metersPerDegree() const;
                ossimString toDmsString()const;

                ossim_float64 lat; //> latitude in degrees measure
                ossim_float64 lon; //> longitude in degrees measure

                /**
                 * Height in meters above the ellipsiod.
                 *
                 * @note This is NOT the same as "height msl".  "Height msl" is above
                 * the geoid or better know as mean sea level.
                 */ 
                ossim_float64 hgt;

        private:

                /**
                 * Know reference location plus an implied ellipsoid.
                 */
                const ossimDatum* theDatum;

};

%inline 
%{
const ossimGpt& ossimGpt::operator=(const ossimGpt& aPt)
{
        if ( this != &aPt )
        {
                lat = aPt.lat;
                lon = aPt.lon;
                hgt = aPt.hgt;

                if(aPt.datum())
                {
                        theDatum = aPt.datum();
                }
                if(!theDatum)
                {
                        theDatum = ossimDatumFactory::instance()->wgs84();
                }
        }
        return *this;
}

void ossimGpt::wrap()
{
        if ( lon > 180.0 )
        {
                do
                {
                        lon = lon - 360.0;
                } while ( lon > 180.0 );
        }
        else if ( lon < -180.0  )
        {
                do
                {
                        lon = lon + 360.0;
                } while ( lon < -180.0 );
        }
        if ( lat > 90.0 )
        {
                if ( lat > 360.0 ) // Remove total wraps.
                {
                        do
                        {
                                lat = lat - 360.0;
                        } while ( lat > 360.0);
                }
                if ( lat > 270.0 ) // Between 270 and 360.
                {
                        lat = lat - 360.0;
                }
                else if ( lat > 90 ) // Between 90 and 270.
                {
                        lat = 180.0 - lat;
                }
        }
        else if ( lat < -90.0  )
        {
                if ( lat < -360.0 ) // Remove total wraps.
                {
                        do
                        {
                                lat = lat + 360.0;
                        } while ( lat < -360.0);
                }
                if ( lat < -270.0 ) 
                {
                        lat = 360.0 + lat; // Between -270 and -360;
                }
                else if ( lat < -90.0 )
                {
                        lat = -180.0 - lat;
                }
        }
}

%}
