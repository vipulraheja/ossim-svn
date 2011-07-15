/*-----------------------------------------------------------------------------
 * Filename        : ossimObliqueMercatorProjection.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimObliqueMercatorProjection
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimMapProjection.h>
#include <ossim/projection/ossimObliqueMercatorProjection.h>

%}

/* Handling operators */
%rename(__cmp__) ossimObliqueMercatorProjection::operator==;

/* Wrapping class ossimObliqueMercatorProjection */
class ossimObliqueMercatorProjection : public ossimMapProjection
{
        public:   
                ossimObliqueMercatorProjection(const ossimEllipsoid& ellipsoid = ossimEllipsoid(),
                                const ossimGpt& origin = ossimGpt());

                /*!
                 * Points 1 and 2 lie along the central line.
                 */
                ossimObliqueMercatorProjection(const ossimEllipsoid& ellipsoid,
                                const ossimGpt& origin,
                                const ossimGpt& point1,
                                const ossimGpt& point2,
                                double falseEasting,
                                double falseNorthing,
                                double scaleFactor);

                ~ossimObliqueMercatorProjection(){}
                virtual ossimObject *dup()const
                {
                        return new ossimObliqueMercatorProjection(*this);
                }

                virtual ossimGpt inverse(const ossimDpt &eastingNorthing)const;
                virtual ossimDpt forward(const ossimGpt &latLon)const;
                virtual void update();

                /*!
                 * SetFalseEasting.  The value is in meters.
                 * Update is then called so we can pre-compute paramters
                 */
                void setFalseEasting(double falseEasting);

                /*!
                 * SetFalseNorthing.  The value is in meters.
                 * Update is then called so we can pre-compute paramters
                 */
                void setFalseNorthing(double falseNorthing);

                void setCentralPoint1(const ossimGpt& point);
                void setCentralPoint2(const ossimGpt& point);
                void setScaleFactor(double scaleFactor);

                void setParameters(const ossimGpt& point1,
                                const ossimGpt& point2,
                                double falseEasting,
                                double falseNorthing,
                                double scaleFactor);
                /*!
                 * Sets both false easting and northing values.  The values are
                 * expected to be in meters.
                 * Update is then called so we can pre-compute paramters
                 */
                void setFalseEastingNorthing(double falseEasting, double falseNorthing);

                void setDefaults();

                double getFalseEasting()const{return  OMerc_False_Easting;}
                double getFalseNorthing()const{return OMerc_False_Northing;}
                const ossimGpt& getCentralPoint1()const{return theCentralPoint1;}
                const ossimGpt& getCentralPoint2()const{return theCentralPoint2;}
                double getScaleFactor()const{return OMerc_Scale_Factor;}
                /*!
                 * Method to save the state of an object to a keyword list.
                 * Return true if ok or false on error.
                 */
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;

                /*!
                 * Method to the load (recreate) the state of an object from a keyword
                 * list.  Return true if ok or false on error.
                 */
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                //! Returns TRUE if principal parameters are within epsilon tolerance.
                virtual bool operator==(const ossimProjection& projection) const;

        protected:

                ossimGpt theCentralPoint1;
                ossimGpt theCentralPoint2;

                mutable double OMerc_a;                   /* Semi-major axis of ellipsoid, in meters */
                mutable double OMerc_f;           /* Flattening of ellipsoid */
                mutable double es;
                mutable double es_OVER_2;
                mutable double OMerc_A;
                mutable double OMerc_B;
                mutable double OMerc_E;
                mutable double OMerc_gamma;
                mutable double OMerc_azimuth;       /* Azimuth of central line as it crosses origin lat */
                mutable double OMerc_Origin_Long;  /* Longitude at center of projection */
                mutable double cos_gamma;
                mutable double sin_gamma;
                mutable double sin_azimuth;  
                mutable double cos_azimuth;
                mutable double A_over_B;
                mutable double B_over_A;
                mutable double OMerc_u;             /* Coordinates for center point (uc , vc), vc = 0 */
                /* at center lat and lon */
                /* Oblique Mercator projection Parameters */
                mutable double OMerc_Origin_Lat;/* Latitude of projection center, in radians */
                mutable double OMerc_Lat_1;     /* Latitude of first point lying on central line */
                mutable double OMerc_Lon_1;     /* Longitude of first point lying on central line */
                mutable double OMerc_Lat_2;     /* Latitude of second point lying on central line */
                mutable double OMerc_Lon_2;      /* Longitude of second point lying on central line */
                mutable double OMerc_Scale_Factor;                /* Scale factor at projection center */
                mutable double OMerc_False_Northing;              /* False northing, in meters, at projection center */
                mutable double OMerc_False_Easting;               /* False easting, in meters, at projection center */

                mutable double OMerc_Delta_Northing;
                mutable double OMerc_Delta_Easting;

                long Set_Oblique_Mercator_Parameters(double a,
                                double f,
                                double Origin_Latitude,
                                double Latitude_1,
                                double Longitude_1,
                                double Latitude_2,
                                double Longitude_2,
                                double False_Easting,
                                double False_Northing,
                                double Scale_Factor);

                void Get_Oblique_Mercator_Parameters(double *a,
                                double *f,
                                double *Origin_Latitude,
                                double *Latitude_1,
                                double *Longitude_1,
                                double *Latitude_2,
                                double *Longitude_2,
                                double *False_Easting,
                                double *False_Northing,
                                double *Scale_Factor)const;

                long Convert_Geodetic_To_Oblique_Mercator(double Latitude,
                                double Longitude,
                                double *Easting,
                                double *Northing)const;

                long Convert_Oblique_Mercator_To_Geodetic(double Easting,
                                double Northing,
                                double *Latitude,
                                double *Longitude)const;

                /* Ignoring Macro
                TYPE_DATA */
};
