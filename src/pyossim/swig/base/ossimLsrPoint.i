/*-----------------------------------------------------------------------------
 * Filename        : ossimLsrPoint.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimLsrPoint
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimLsrSpace.h>
#include <ossim/base/ossimLsrPoint.h>
#include <ossim/base/ossimLsrVector.h>
#include <ossim/base/ossimColumnVector3d.h>
#include <ossim/base/ossimNotify.h>

%}


/* Handling operators */
%rename(__set__) ossimLsrPoint::operator=;
%rename(__add__) ossimLsrPoint::operator+;
%rename(__sub__) ossimLsrPoint::operator-;
%rename(__cmp__) ossimLsrPoint::operator==;
%rename(__ne__) ossimLsrPoint::operator!=;
%rename(ossimLsrPoint_ossimEcefPoint) ossimLsrPoint::operator ossimEcefPoint;
%rename(__lshift__) operator<<;
%rename(ossimLsrPoint_print) print;


class ossimLsrPoint
{
        public:
                /*!
                 * CONSTRUCTORS: 
                 */
                ossimLsrPoint()
                        : theData(0,0,0) {}
                ossimLsrPoint(const ossimLsrPoint& copy_this)
                        : theData(copy_this.theData), theLsrSpace(copy_this.theLsrSpace) {}
                ossimLsrPoint(const ossimColumnVector3d& assign_this,
                                const ossimLsrSpace& space)
                        : theData(assign_this), theLsrSpace(space) {}
                ossimLsrPoint(const double& x,
                                const double& y,
                                const double& z,
                                const ossimLsrSpace& space)
                        : theData(x, y, z), theLsrSpace(space) {}
                ossimLsrPoint(const ossimLsrPoint& convert_this,
                                const ossimLsrSpace&);
                ossimLsrPoint(const ossimGpt& convert_this,
                                const ossimLsrSpace&);
                ossimLsrPoint(const ossimEcefPoint& convert_this,
                                const ossimLsrSpace&);

                /*!
                 * OPERATORS:
                 */
                const ossimLsrPoint& operator= (const ossimLsrPoint&);       //inline below
                ossimLsrVector       operator- (const ossimLsrPoint&)  const;
                ossimLsrPoint        operator+ (const ossimLsrVector&) const;
                bool                 operator==(const ossimLsrPoint&)  const;//inline below
                bool                 operator!=(const ossimLsrPoint&)  const;//inline below

                /*!
                 * CASTING OPERATOR:
                 * Used as: myEcefVector = ossimEcefPoint(this) -- looks like a constructor
                 * but is an operation on this object. ECEF knows nothing about LSR, so
                 * cannot provide an ossimEcefVector(ossimLsrPoint) constructor.
                 */
                operator ossimEcefPoint() const; // inline below

                /*!
                 * DATA ACCESS METHODS: 
                 */
                double    x() const { return theData[0]; }
                double&   x()       { return theData[0]; }
                double    y() const { return theData[1]; }
                double&   y()       { return theData[1]; }
                double    z() const { return theData[2]; }
                double&   z()       { return theData[2]; }


                ossimColumnVector3d&       data()           { return theData; }
                const ossimColumnVector3d& data()     const { return theData; }

                ossimLsrSpace&             lsrSpace()       { return theLsrSpace; }
                const ossimLsrSpace&       lsrSpace() const { return theLsrSpace; }

                bool hasNans()const
                {
                        return (ossim::isnan(theData[0])||
                                        ossim::isnan(theData[1])||
                                        ossim::isnan(theData[2]));
                }

                void makeNan()
                {
                        theData[0] = ossim::nan();
                        theData[1] = ossim::nan();
                        theData[2] = ossim::nan();
                }

                /*!
                 * Debug Dump: 
                 */
                void print(ostream& stream = ossimNotify(ossimNotifyLevel_INFO)) const;

                friend ostream& operator<< (ostream& os , const ossimLsrPoint& instance)
                {
                        instance.print(os); return os; 
                }

        protected:
                /*!
                 * METHOD: initialize(ossimEcefPoint)
                 * Convenience method used by several constructors for initializing theData
                 * given an ECEF point. Assumes theLsrSpace has been previously initialized.
                 */
                void initialize(const ossimEcefPoint& ecef_point);

                ossimColumnVector3d theData;
                ossimLsrSpace       theLsrSpace;
};
