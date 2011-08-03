/*-----------------------------------------------------------------------------
 * Filename        : ossimTransMercatorProjection.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimTransMercatorProjection
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimMapProjection.h>
#include <ossim/projection/ossimTransMercatorProjection.h>

%}

/* Handling operators */
%rename(__cmp__) ossimTransMercatorProjection::operator==;
%rename(ossimTransMercatorProjection_print) print;


/* Wrapping class ossimTransMercatorProjection */
class ossimTransMercatorProjection : public ossimMapProjection
{
        public:
                ossimTransMercatorProjection(const ossimEllipsoid& ellipsoid = ossimEllipsoid(6378137, 6356752.3142),
                                const ossimGpt& origin = ossimGpt());
                ossimTransMercatorProjection(const ossimEllipsoid& ellipsoid,
                                const ossimGpt& origin,
                                double falseEasting,
                                double falseNorthing,
                                double scaleFactor);
                ~ossimTransMercatorProjection(){}

                virtual ossimObject *dup()const{return new ossimTransMercatorProjection(*this);}
                virtual ossimGpt inverse(const ossimDpt &eastingNorthing)const;
                virtual ossimDpt forward(const ossimGpt &latLon)const;
                virtual void update();

                void setFalseEasting(double falseEasting);
                void setFalseNorthing(double falseNorthing);
                void setScaleFactor(double scaleFactor);
                void setFalseEastingNorthing(double falseEasting, double falseNorthing);

                void setParameters(double falseEasting,
                                double falseNorthing,
                                double scaleFactor);

                void setDefaults();

                double getFalseEasting()const{return  TranMerc_False_Easting;}
                double getFalseNorthing()const{return TranMerc_False_Northing;}
                double getScaleFactor()const{return TranMerc_Scale_Factor;}

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix=0)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix=0);

                virtual std::ostream& print(std::ostream& out) const;

                //! Returns TRUE if principal parameters are within epsilon tolerance.
                virtual bool operator==(const ossimProjection& projection) const;


        protected:
                double TranMerc_a;              /* Semi-major axis of ellipsoid i meters */
                double TranMerc_f;      /* Flattening of ellipsoid  */
                double TranMerc_es; /* Eccentricity (0.08181919084262188000) squared */
                double TranMerc_ebs;   /* Second Eccentricity squared */

                /* Transverse_Mercator projection Parameters */
                double TranMerc_Origin_Lat;           /* Latitude of origin in radians */
                double TranMerc_Origin_Long;          /* Longitude of origin in radians */
                double TranMerc_False_Northing;       /* False northing in meters */
                double TranMerc_False_Easting;        /* False easting in meters */
                double TranMerc_Scale_Factor;         /* Scale factor  */

                /* Isometeric to geodetic latitude parameters, default to WGS 84 */
                double TranMerc_ap;
                double TranMerc_bp;
                double TranMerc_cp;
                double TranMerc_dp;
                double TranMerc_ep;

                /* Maximum variance for easting and northing values for WGS 84. */
                double TranMerc_Delta_Easting;
                double TranMerc_Delta_Northing;

                long Set_Transverse_Mercator_Parameters(double a,      
                                double f,
                                double Origin_Latitude,
                                double Central_Meridian,
                                double False_Easting,
                                double False_Northing,
                                double Scale_Factor);

                void Get_Transverse_Mercator_Parameters(double *a,
                                double *f,
                                double *Origin_Latitude,
                                double *Central_Meridian,
                                double *False_Easting,
                                double *False_Northing,
                                double *Scale_Factor)const;

                long Convert_Geodetic_To_Transverse_Mercator (double Latitude,
                                double Longitude,
                                double *Easting,
                                double *Northing)const;


                long Convert_Transverse_Mercator_To_Geodetic (double Easting,
                                double Northing,
                                double *Latitude,
                                double *Longitude)const;

                /* Handling Macro
                TYPE_DATA */
};
