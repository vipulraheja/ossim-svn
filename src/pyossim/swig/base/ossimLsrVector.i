/*-----------------------------------------------------------------------------
 * Filename        : ossimLsrVector.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimLsrVector
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <iosfwd>

#include <ossim/base/ossimCommon.h>
#include <ossim/base/ossimLsrPoint.h>
#include <ossim/base/ossimLsrSpace.h>
#include <ossim/base/ossimLsrVector.h>
#include <ossim/base/ossimEcefVector.h>
#include <ossim/base/ossimColumnVector3d.h>

%}

/* Handling operators */
%rename(__set__) ossimLsrVector::operator=;
%rename(__cmp__) ossimLsrVector::operator==;
%rename(__ne__) ossimLsrVector::operator!=;
%rename(__add__) ossimLsrVector::operator+;
%rename(__sub__) ossimLsrVector::operator-;
%rename(__mul__) ossimLsrVector::operator*;
%rename(__div__) ossimLsrVector::operator/;
%rename(__lshift__) operator<<;
%rename(ossimLsrVector_print) print;
%rename(ossimLsrVector_ossimEcefVector) operator ossimEcefVector;

/* Wrapping class ossimLsrVector */
class ossimLsrVector
{
        public:
                /*!
                 * CONSTRUCTORS: 
                 */
                ossimLsrVector()
                        : theData (0,0,0) {}
                ossimLsrVector(const ossimLsrVector& copy_this)
                        : theData(copy_this.theData), theLsrSpace(copy_this.theLsrSpace) {}
                ossimLsrVector(const ossimColumnVector3d& assign_this,
                                const ossimLsrSpace& space)
                        : theData(assign_this), theLsrSpace(space) {}
                ossimLsrVector(const double& x,
                                const double& y,
                                const double& z,
                                const ossimLsrSpace& space)
                        : theData(x,y,z), theLsrSpace(space) {}
                ossimLsrVector(const ossimEcefVector& convert_this,
                                const ossimLsrSpace&);
                ossimLsrVector(const ossimLsrVector& convert_this,
                                const ossimLsrSpace&);

                /*!
                 * OPERATORS: (all methods inlined below)
                 */
                const ossimLsrVector&  operator= (const ossimLsrVector&);
                ossimLsrVector         operator- ()                      const;
                ossimLsrVector         operator+ (const ossimLsrVector&) const;
                ossimLsrVector         operator- (const ossimLsrVector&) const;
                ossimLsrPoint          operator+ (const ossimLsrPoint&)  const;
                ossimLsrVector         operator* (const double& scalar)  const;
                ossimLsrVector         operator/ (const double& scalar)  const;
                bool                   operator==(const ossimLsrVector&) const;
                bool                   operator!=(const ossimLsrVector&) const;

                /*!
                 * CASTING OPERATOR:
                 * Used as: myEcefVector = ossimEcefVector(this) -- looks like a constructor
                 * but is an operation on this object. ECEF knows nothing about LSR, so
                 * cannot provide an ossimEcefVector(ossimLsrVector) constructor.
                 */
                operator ossimEcefVector() const; // inline below

                /*!
                 * Vector-related functions: 
                 */
                double                 dot(const ossimLsrVector&)       const;
                double                 angleTo(const ossimLsrVector&)   const;
                ossimLsrVector         cross(const ossimLsrVector&)     const;
                ossimLsrVector         unitVector()                     const;//inline below
                double                 magnitude()                      const;//inline below
                void                   normalize(); // inline below

                /*!
                 * DATA ACCESS METHODS: 
                 */
                double    x() const { return theData[0]; }
                double&   x()       { return theData[0]; }
                double    y() const { return theData[1]; }
                double&   y()       { return theData[1]; }
                double    z() const { return theData[2]; }
                double&   z()       { return theData[2]; }

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
                ossimColumnVector3d&       data()           { return theData; }
                const ossimColumnVector3d& data()     const { return theData; }

                ossimLsrSpace&             lsrSpace()       { return theLsrSpace; }
                const ossimLsrSpace&       lsrSpace() const { return theLsrSpace; }

                /*!
                 * Debug Dump: 
                 */
                std::ostream& print(ostream& stream) const;

                friend std::ostream& operator<< (std::ostream& os ,
                                const ossimLsrVector& instance);

        protected:
                /*!
                 * METHOD: initialize(ossimEcefVector)
                 * Convenience method used by several constructors for initializing theData
                 * given an ECEF vector. Assumes theLsrSpace has been previously initialized
                 */
                void initialize(const ossimEcefVector& ecef_point);

                ossimColumnVector3d theData;
                ossimLsrSpace       theLsrSpace;
};
