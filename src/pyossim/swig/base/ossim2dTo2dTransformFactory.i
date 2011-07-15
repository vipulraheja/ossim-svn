/*-----------------------------------------------------------------------------
 * Filename        : ossim2dTo2dTransformFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dTransformFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossim2dTo2dTransformFactoryBase.h>
#include <ossim/base/ossim2dTo2dTransformFactory.h>

%}

/* Wrapping class ossim2dTo2dTransformFactory */
class ossim2dTo2dTransformFactory : public ossim2dTo2dTransformFactoryBase
{
        public:
                ossim2dTo2dTransformFactory(){}
                static ossim2dTo2dTransformFactory* instance();

                /**
                 * Take a transform type name.
                 */
                virtual ossim2dTo2dTransform* createTransform(const ossimString& name)const;

                /**
                 * Take a keywordlist.
                 */
                virtual ossim2dTo2dTransform* createTransform(const ossimKeywordlist& kwl,
                                const char* prefix)const;

                /*!
                 * This should return the type name of all objects in all factories.
                 * This is the name used to construct the objects dynamially and this
                 * name must be unique.
                 */
                virtual void getTypeNameList(std::vector<ossimString>& typeList)const;

        protected:
                static ossim2dTo2dTransformFactory* m_instance;
};
