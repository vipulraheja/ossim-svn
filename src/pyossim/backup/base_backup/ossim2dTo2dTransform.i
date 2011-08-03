/*-----------------------------------------------------------------------------
 * Filename        : ossim2dTo2dTransform.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dTransform
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossim2dTo2dTransform.h>

%}

/* Handling operators */
%rename(__set__) ossim2dTo2dTransform::operator=;
%rename(ossim2dTo2dTransform_print) print;

/* Wrapping class ossim2dTo2dTransform */
class ossim2dTo2dTransform : public ossimObject
{
        public:
                virtual void forward(const ossimDpt& input,
                                ossimDpt& output) const=0;

                virtual void forward(ossimDpt&  modify_this) const;

                virtual void inverse(const ossimDpt& input,
                                ossimDpt&       output) const;

                virtual void inverse(ossimDpt&  modify_this) const;

                virtual const ossim2dTo2dTransform& operator=(
                                const ossim2dTo2dTransform& rhs);

                /*!
                 * Used by the inverse iterator.  This will give it a good initial value
                 * that is within the input transforms
                 */
                virtual ossimDpt getOrigin() const;

                virtual std::ostream& print(std::ostream& out) const;

                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix = 0)const;

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix = 0);

                void setConvergenceThreshold(const double& new_threshold);

                void setMaxIterations(int new_max_iters);

                void setDxDy(const ossimDpt& dxdy);

        protected:
                ossim2dTo2dTransform();
                virtual ~ossim2dTo2dTransform(){}
                double theConvergenceThreshold;
                int    theMaxIterations;

                ossimDpt theDxDy;

                /* Ignoring Macro
                TYPE_DATA  */
};
