/*-----------------------------------------------------------------------------
 * Filename        : ossimElevCellHandlerFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevCellHandlerFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <list>
#include <ossim/base/ossimFactoryBaseTemplate.h>
#include <ossim/base/ossimString.h>
#include <ossim/elevation/ossimElevCellHandlerFactory.h>

%}

/* Wrapping class ossimElevCellHandlerFactory */
class ossimElevCellHandlerFactory :
        public ossimFactoryBase <ossimElevCellHandler>
{
        public:
                static ossimElevCellHandlerFactory* instance();

                virtual ossimElevCellHandler* create(const ossimString&) const;
                virtual ossimElevCellHandler* create(const ossimKeywordlist& kwl,
                                const char* prefix) const;

                virtual std::list<ossimString> getList() const;

        protected:
                ossimElevCellHandlerFactory();

                static ossimElevCellHandlerFactory*  theInstance;
};
