/*-----------------------------------------------------------------------------
 * Filename        : ossimOrthoGraphicProjection.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimOrthoGraphicProjection
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimMapProjection.h>
#include <ossim/projection/ossimOrthoGraphicProjection.h>

%}

/* Wrapping class ossimOrthoGraphicProjection */
class ossimOrthoGraphicProjection : public ossimMapProjection
{
        public:

                ossimOrthoGraphicProjection(const ossimEllipsoid& ellipsoid = ossimEllipsoid(),
                                const ossimGpt& origin = ossimGpt());
                ossimOrthoGraphicProjection(const ossimEllipsoid& ellipsoid,
                                const ossimGpt& origin,
                                const double falseEasting,
                                const double falseNorthing);
                ~ossimOrthoGraphicProjection(){}

                virtual ossimObject *dup()const
                {
                        return new ossimOrthoGraphicProjection(*this);
                }
                virtual void getGroundClipPoints(ossimGeoPolygon& gpts)const;
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

                /*!
                 * Sets both false easting and northing values.  The values are
                 * expected to be in meters.
                 * Update is then called so we can pre-compute paramters
                 */
                void setFalseEastingNorthing(double falseEasting, double falseNorthing);

                void setDefaults();

                double getFalseEasting()const{return  Orth_False_Easting;}
                double getFalseNorthing()const{return Orth_False_Northing;}

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

        private:
                mutable double Orth_a;                      /* Semi-major axis of ellipsoid in meters */
                mutable double Orth_f;              /* Flattening of ellipsoid */
                mutable double es2;             /* Eccentricity (0.08181919084262188000) squared         */
                mutable double es4;              /* es2 * es2 */
                mutable double es6;              /* es4 * es2 */
                mutable double Ra;                    /* Spherical Radius */

                /* Orthographic projection Parameters */
                mutable double Orth_Origin_Lat;                   /* Latitude of origin in radians     */
                mutable double Orth_Origin_Long;                  /* Longitude of origin in radians    */
                mutable double Orth_False_Easting;
                mutable double Orth_False_Northing;
                mutable double Sin_Orth_Origin_Lat;               /* sin(Orth_Origin_Lat) */
                mutable double Cos_Orth_Origin_Lat;               /* cos(Orth_Origin_Lat) */

                long Set_Orthographic_Parameters(double a,
                                double f,
                                double Origin_Latitude,
                                double Central_Meridian,
                                double False_Easting,
                                double False_Northing);


                void Get_Orthographic_Parameters(double *a,
                                double *f,
                                double *Origin_Latitude,
                                double *Origin_Longitude,
                                double *False_Easting,
                                double *False_Northing)const;


                long Convert_Geodetic_To_Orthographic (double Latitude,
                                double Longitude,
                                double *Easting,
                                double *Northing)const;

                long Convert_Orthographic_To_Geodetic(double Easting,
                                double Northing,
                                double *Latitude,
                                double *Longitude)const;

                /* Ignoring Macro 
                TYPE_DATA */
};
