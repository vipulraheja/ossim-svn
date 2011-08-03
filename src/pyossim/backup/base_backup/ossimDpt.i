/*-----------------------------------------------------------------------------
Filename        : ossimHistogramRemapper.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimHistogramRemapper 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <iosfwd>
#include <string>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimDpt.h>

%}

/* Handling operators */
%rename(__cmp__) ossimDpt::operator==;
%rename(__set__) ossimDpt::operator=;
%rename(__ne__) ossimDpt::operator!=;
%rename(__add__) ossimDpt::operator+;
%rename(__sub__) ossimDpt::operator-;
%rename(__mul__) ossimDpt::operator*;
%rename(__div__) ossimDpt::operator/;
%rename(__iadd__) ossimDpt::operator+=;
%rename(__isub__) ossimDpt::operator-=;

%rename(__lshift__) operator<<;
%rename(__rshift__) operator>>;
%rename(ossimDpt_print) print;


/* Wrapping class ossimDpt */
class ossimDpt
{
        public:

                ossimDpt() : x(0), y(0) {}
                ossimDpt(double anX, double aY) : x(anX), y(aY) {}
                ossimDpt(const ossimDpt& pt) : x(pt.x), y(pt.y) {}
                ossimDpt(const ossimFpt& pt);
                ossimDpt(const ossimIpt& pt);
                ossimDpt(const ossimDpt3d &pt);
                ossimDpt(const ossimGpt &pt); // assigns lat, lon only

                const ossimDpt& operator=(const ossimDpt&);
                const ossimDpt& operator=(const ossimFpt&);
                const ossimDpt& operator=(const ossimIpt&);
                const ossimDpt& operator=(const ossimDpt3d&);
                const ossimDpt& operator=(const ossimGpt&); // assigns lat, lon only

                bool operator==(const ossimDpt& pt) const
                {
                        return ( ossim::almostEqual(x, pt.x) && ossim::almostEqual(y, pt.y) ); 
                } 
                bool operator!=(const ossimDpt& pt) const
                {
                        return !(*this == pt ); 
                }

                void makeNan(){x = ossim::nan(); y=ossim::nan();}
                bool hasNans()const
                {
                        return (ossim::isnan(x) || ossim::isnan(y));
                }

                bool isNan()const
                {
                        return (ossim::isnan(x) && ossim::isnan(y));
                }

                /*!
                 * METHOD: length()
                 * Returns the RSS of the components.
                 */
                double length() const { return sqrt(x*x + y*y); }

                /*
                 OPERATORS: +, -, +=, -=
                 Point add/subtract with other point:
                */
                ossimDpt operator+(const ossimDpt& p) const
                {
                        return ossimDpt(x+p.x, y+p.y); 
                }
                ossimDpt operator-(const ossimDpt& p) const
                {
                        return ossimDpt(x-p.x, y-p.y); 
                }
                const ossimDpt& operator+=(const ossimDpt& p)
                {
                        x += p.x; y += p.y; return *this; 
                }
                const ossimDpt& operator-=(const ossimDpt& p)
                {
                        x -= p.x; y -= p.y; return *this; 
                }

                /*
                 OPERATORS: *, /
                 Scale point components by scalar:
                */
                ossimDpt operator*(const double& d) const
                {
                        return ossimDpt(d*x, d*y); 
                }
                ossimDpt operator/(const double& d) const
                {
                        return ossimDpt(x/d, y/d); 
                }

                std::ostream& print(std::ostream& os, ossim_uint32 precision=15) const;

                friend std::ostream& operator<<(std::ostream& os,
                                const ossimDpt& pt);
                ossimString toString(ossim_uint32 precision=15) const;

                void toPoint(const std::string& s);

                friend std::istream& operator>>(std::istream& is,
                                ossimDpt& pt);

                /*
                 Public data members:
                */
                union 
                {
                        double x; double samp; double u; double lon;
                };
                
                union 
                {
                        double y; double line; double v; double lat;
                };

};
