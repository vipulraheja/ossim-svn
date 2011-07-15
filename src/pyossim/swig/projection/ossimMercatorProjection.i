/*-----------------------------------------------------------------------------
 * Filename        : ossimMercatorProjection.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimMercatorProjection
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimMapProjection.h>
#include <ossim/projection/ossimMercatorProjection.h>

%}

/* Handling operators */
%rename(__set__) ossimMercatorProjection::operator==;

/* Wrapping class ossimMercatorProjection */
class ossimMercatorProjection : public ossimMapProjection
{
        public:

                ossimMercatorProjection(const ossimEllipsoid& ellipsoid = ossimEllipsoid(),
                                const ossimGpt& origin = ossimGpt());

                ossimMercatorProjection(const ossimEllipsoid& ellipsoid,
                                const ossimGpt& origin,
                                double falseEasting,
                                double falseNorthing,
                                double scaleFactor);
                ~ossimMercatorProjection(){}
                virtual ossimObject *dup()const{return new ossimMercatorProjection(*this);}

                virtual ossimGpt inverse(const ossimDpt &eastingNorthing)const;
                virtual ossimDpt forward(const ossimGpt &latLon)const;
                virtual void update();   

                void setFalseEasting(double falseEasting);
                void setFalseNorthing(double falseNorthing);
                void setFalseEastingNorthing(double falseEasting, double falseNorthing);

                /*!
                 * sets the scale.
                 */
                void setScaleFactor(double scaleFactor);
                void setParameters(double falseEasting,
                                double falseNorthing,
                                double scaleFactor);  
                void setDefaults();

                double getFalseEasting()const{return Merc_False_Easting;}
                double getFalseNorthing()const{return Merc_False_Northing;}
                double getScaleFactor()const{return Merc_Scale_Factor;}

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                //! Returns TRUE if principal parameters are within epsilon tolerance.
                virtual bool operator==(const ossimProjection& projection) const;


        private:
                mutable double Merc_a;    /* Semi-major axis of ellipsoid in meters */
                mutable double Merc_f;      /* Flattening of ellipsoid */
                mutable double Merc_e; /* Eccentricity of ellipsoid    */
                mutable double Merc_es; /* Eccentricity squared         */

                /* Mercator projection Parameters */
                mutable double Merc_Origin_Lat;      /* Latitude of origin in radians     */
                mutable double Merc_Origin_Long;     /* Longitude of origin in radians    */
                mutable double Merc_False_Northing;  /* False northing in meters          */
                mutable double Merc_False_Easting;   /* False easting in meters           */
                mutable double Merc_Scale_Factor;    /* Scale factor                      */

                /* Isometric to geodetic latitude parameters, default to WGS 84 */
                mutable double Merc_ab;
                mutable double Merc_bb;
                mutable double Merc_cb;
                mutable double Merc_db;

                /* Maximum variance for easting and northing values for WGS 84.
                 */
                mutable double Merc_Delta_Easting;
                mutable double Merc_Delta_Northing;


                bool theSphericalFlag;
                long Set_Mercator_Parameters(double a,      
                                double f,
                                double Origin_Latitude,
                                double Central_Meridian,
                                double False_Easting,
                                double False_Northing,
                                double *Scale_Factor);

                void Get_Mercator_Parameters(double *a,
                                double *f,
                                double *Origin_Latitude,
                                double *Central_Meridian,
                                double *False_Easting,
                                double *False_Northing,
                                double *Scale_Factor)const;

                long Convert_Geodetic_To_Mercator (double Latitude,
                                double Longitude,
                                double *Easting,
                                double *Northing)const;

                long Convert_Mercator_To_Geodetic(double Easting,
                                double Northing,
                                double *Latitude,
                                double *Longitude)const;

                /* Ignoring Macro 
                TYPE_DATA */
};
