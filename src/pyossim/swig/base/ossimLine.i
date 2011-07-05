/*-----------------------------------------------------------------------------
Filename        : ossimLine.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimLine
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimLine.h>
#include <iosfwd>

%}

class ossimLine
{
        public:
                friend std::ostream& operator <<(std::ostream& out,
                                const ossimLine& rhs);
                ossimLine(const ossimDpt& p1=ossimDpt(0,0),
                                const ossimDpt& p2=ossimDpt(0,0))
                        :theP1(p1),
                        theP2(p2)
        {
        }


                ossimDpt getVector()const
                {
                        return (theP2-theP1);
                }

                ossimDpt intersectInfinite(const ossimLine& line)const;

                ossimDpt intersectSegment(const ossimLine& line)const;

                ossimDpt midPoint()const;
                double length()const;
                ossimDpt normal()const;

                bool isPointWithin(const ossimDpt& point, double delta=FLT_EPSILON)const;

                bool isPointOnInfiniteLine(const ossimDpt& point, double delta=FLT_EPSILON)const;

                ossimDpt   theP1;
                ossimDpt   theP2;
};
