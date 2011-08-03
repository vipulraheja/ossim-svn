/*-----------------------------------------------------------------------------
 * Filename        : ossimImageViewTransformFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageViewTransformFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObject.h>
#include <ossim/projection/ossimImageViewTransformFactory.h>

%}

/* Handling the assignment operator */
%rename(__set__) ossimImageViewTransformFactory::operator=;

/* Wrapping the class ossimImageViewTransformFactory */
class ossimImageViewTransformFactory : public ossimObject
{
        public:
                static ossimImageViewTransformFactory* instance();
                virtual ossimImageViewTransform* createTransform(const ossimKeywordlist& kwl,
                                const char* prefix = 0);

        protected:
                ossimImageViewTransformFactory(){}      //hide
                ossimImageViewTransformFactory(const ossimImageViewTransformFactory&){}
                void operator =(const ossimImageViewTransformFactory&){}

                static ossimImageViewTransformFactory* theInstance;

                /* Ignored due to unclean parsing of MACROS     */
                /* TYPE_DATA                                    */
};
