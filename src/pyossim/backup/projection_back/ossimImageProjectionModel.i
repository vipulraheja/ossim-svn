/*-----------------------------------------------------------------------------
 * Filename        : ossimImageProjectionModel.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageProjectionModel 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimRtti.h>
#include <ossim/imaging/ossimImageModel.h>
#include <ossim/projection/ossimImageProjectionModel.h>

%}

/**
 * @brief Class derived from ossimImageModel, this adds an image projection
 * for lineSampleToWorld and worldToLineSample.
 *
 * Note that image points fed to projection methods should be full
 * resolution with any sub image offset applied.
 */
class ossimImageProjectionModel : public ossimImageModel
{
        public:

                ossimImageProjectionModel();

                virtual void initialize(const ossimImageHandler& ih);

                const ossimProjection* getProjection() const;

        protected:
                /** @brief virtual destructor */
                virtual ~ossimImageProjectionModel();

                ossimProjection* theProjection;

                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
