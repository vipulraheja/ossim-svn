/*-----------------------------------------------------------------------------
Filename        : ossimDpt3d.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimDpt3d 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <cmath>
#include <iosfwd>
#include <string>

#include <ossim/base/ossimCommon.h>             /* for ossim::isnan */
#include <ossim/base/ossimColumnVector3d.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimDpt3d.h>

%}

/* Handling operators */
%rename(__cmp__) ossimDpt3d::operator==;
%rename(__ne__) ossimDpt3d::operator!=;
%rename(__add__) ossimDpt3d::operator+;
%rename(__sub__) ossimDpt3d::operator-;
%rename(__mul__) ossimDpt3d::operator*;
%rename(__div__) ossimDpt3d::operator/;
%rename(__iadd__) ossimDpt3d::operator+=;
%rename(__isub__) ossimDpt3d::operator-=;
%rename(__imul__) ossimDpt3d::operator*=;
%rename(__idiv__) ossimDpt3d::operator/=;
%rename(__lshift__) operator<<;

/* Wrapping the class ossimDpt3d */
class ossimDpt3d
{
        public:
                friend std::ostream & operator <<(std::ostream &out,
                                const ossimDpt3d &rhs);

                ossimDpt3d(const double &aX=0, const double &aY=0, const double &aZ=0)
                        :x(aX), y(aY), z(aZ) {}

                ossimDpt3d(const ossimDpt &aPt);
                ossimDpt3d(const ossimIpt &aPt);

                ossimDpt3d(const ossimColumnVector3d &pt)
                        : x(pt[0]), y(pt[1]), z(pt[2]) {}

                bool operator ==(const ossimDpt3d &rhs) const
                {
                        return ( (x == rhs.x) &&
                                        (y == rhs.y) &&
                                        (z == rhs.z));
                }
                bool operator !=(const ossimDpt3d &rhs) const
                {
                        return ( (x != rhs.x) ||
                                        (y != rhs.y) ||
                                        (z != rhs.z) );
                }

                void makeNan()
                {
                        x = ossim::nan(); y=ossim::nan(); z=ossim::nan();
                }

                bool hasNans()const
                {
                        return (ossim::isnan(x) || ossim::isnan(y) || ossim::isnan(z));
                }
                
                /*!
                 * METHOD: length()
                 * Returns the RSS of the components.
                 */
                double length() const { return std::sqrt(x*x + y*y + z*z); }
                double length2() const { return x*x + y*y + z*z; }

                
                /* OPERATORS: +, -, +=, -=              */
                /* Point add/subtract with other point: */
                ossimDpt3d operator+(const ossimDpt3d& p) const
                {
                        return ossimDpt3d(x+p.x, y+p.y, z+p.z); 
                }

                ossimDpt3d operator-(const ossimDpt3d& p) const
                {
                        return ossimDpt3d(x-p.x, y-p.y, z-p.z); 
                }
                
                const ossimDpt3d& operator+=(const ossimDpt3d& p)
                {
                        x += p.x; y += p.y; z += p.z; return *this; 
                }
                
                const ossimDpt3d& operator-=(const ossimDpt3d& p)
                {
                        x -= p.x; y -= p.y; z -= p.z; return *this; 
                }

                /* OPERATORS: *, /                      */
                /* Scale point components by scalar:    */
                
                ossimDpt3d operator*(const double& d) const
                {
                        return ossimDpt3d(d*x, d*y, d*z); 
                }
                
                ossimDpt3d operator/(const double& d) const
                {
                        return ossimDpt3d(x/d, y/d, z/d); 
                }
                
                void operator /=(double value)
                {
                        x /= value;
                        y /= value;
                        z /= value;
                }
                
                void operator *=(double value) 
                {
                        x *=value;
                        y *= value;
                        z *= value;
                }
                
                double operator *(const ossimDpt3d& src)const
                {
                        return (x*src.x + y*src.y + z*src.z);
                }
                
                inline const ossimDpt3d operator ^ (const ossimDpt3d& rhs) const
                {
                        return ossimDpt3d(y*rhs.z-z*rhs.y,
                                        z*rhs.x-x*rhs.z ,
                                        x*rhs.y-y*rhs.x);
                }

               std::string toString(ossim_uint32 precision=15) const;

               void toPoint(const std::string& s); 

                double x;
                double y;
                double z;
};
