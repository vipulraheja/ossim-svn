/*-----------------------------------------------------------------------------
 * Filename        : ossimLsrRay.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimLsrRay
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimLsrPoint.h>
#include <ossim/base/ossimLsrRay.h>
#include <ossim/base/ossimLsrVector.h>
#include <ossim/base/ossimEcefRay.h>
#include <ossim/base/ossimNotifyContext.h>

%}

/* Handling operators */
%rename(__set__) ossimLsrRay::operator=;
%rename(__cmp__) ossimLsrRay::operator==;
%rename(__ne__) ossimLsrRay::operator!=;
%rename(__lshift__) operator<<;
%rename(ossimLsrRay_print) print;
%rename(ossimLsrRay_ossimEcefRay) operator ossimEcefRay;


/* Wrapping class ossimLsrRay */
class ossimLsrRay
{
        public:
                /*!
                 * CONSTRUCTORS: 
                 */
                ossimLsrRay() {}
                ossimLsrRay(const ossimLsrRay& copy_this)
                        : theOrigin(copy_this.theOrigin), theDirection(copy_this.theDirection) {}
                ossimLsrRay(const ossimLsrPoint&  origin,
                                const ossimLsrVector& direction);
                ossimLsrRay(const ossimLsrPoint&  origin,
                                const ossimLsrPoint&  towards);
                ossimLsrRay(const ossimLsrRay& convert_this,
                                const ossimLsrSpace& new_space)
                        : theOrigin(convert_this.theOrigin, new_space),
                        theDirection(convert_this.theDirection, new_space) {}

                const ossimLsrRay&  operator= (const ossimLsrRay& r);       // inline below
                bool                operator==(const ossimLsrRay& r) const; // inline below
                bool                operator!=(const ossimLsrRay& r) const; // inline below

                const ossimLsrPoint&  origin()    const { return theOrigin; }
                const ossimLsrVector& direction() const { return theDirection; }
                const ossimLsrSpace&  lsrSpace()  const { return theOrigin.lsrSpace(); }

                operator ossimEcefRay () const;  // inline below

                bool hasNans()const
                {
                        return (theOrigin.hasNans()||theDirection.hasNans());
                }

                void makeNan()
                {
                        theOrigin.makeNan();
                        theDirection.makeNan();
                }
                
                ossimLsrPoint extend(const double& t) const
                {
                        if(!hasNans())
                        {
                                return (theOrigin + theDirection*t);
                        }

                        ossimLsrPoint p;
                        p.makeNan();
                        return p;
                }

                /*!
                 * Debug Dump: 
                 */
                void print(ostream& stream = ossimNotify(ossimNotifyLevel_INFO)) const;  // inline below

                friend ostream& operator<< (ostream& os , const ossimLsrRay& instance)
                {
                        instance.print(os); return os; 
                }

        private:
                ossimLsrPoint  theOrigin;
                ossimLsrVector theDirection;

};
