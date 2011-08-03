/*-----------------------------------------------------------------------------
 * Filename        : ossim2dTo2dTransform.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dTransform
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossim2dTo2dTransform.h>
#include <ossim/base/ossim2dTo2dIdentityTransform.h>

%}

/* Handling operators */
%rename(__set__) ossim2dTo2dIdentityTransform::operator=;

/**
 * This is the identity transform and just passes the input to the output.
 */
class ossim2dTo2dIdentityTransform : public ossim2dTo2dTransform
{
        public:
                /**
                 * forward transform just passes the point to the output.
                 */
                virtual void forward(const ossimDpt& input,
                                ossimDpt& output) const
                {
                        output = input;
                }

                /**
                 * forward transform nothing is modified on the input point.
                 */
                virtual void forward(ossimDpt&  /* modify_this */) const
                {
                        // do nothing this is identity
                }

                /**
                 * inverse transform just passes the point to the output.
                 */
                virtual void inverse(const ossimDpt& input,
                                ossimDpt&       output) const
                {
                        output = input;
                }

                /**
                 * inverse transform nothing is modified on the input point.
                 */
                virtual void inverse(ossimDpt&  ) const
                {
                        // do nothing this is identity
                }

                /**
                 * Pass equality to the parent
                 */
                virtual const ossim2dTo2dIdentityTransform& operator=(
                                const ossim2dTo2dIdentityTransform& rhs)
                {
                        ossim2dTo2dTransform::operator =(rhs);

                        return *this;
                }

        protected:
                /* Ignoring Macro
                TYPE_DATA */
};
