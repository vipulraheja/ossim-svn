/*-----------------------------------------------------------------------------
 * Filename        : ossimImageModel.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageModel 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimPropertyInterfaceFactory.h>

%}

%import "ossim/base/ossimObject.h";
%import "ossim/base/ossimPropertyInterface.h";

class OSSIMDLLEXPORT ossimPropertyInterfaceFactory : public ossimObjectFactory
{
        public:
                ossimPropertyInterfaceFactory()
                        :ossimObjectFactory() {}
                virtual ~ossimPropertyInterfaceFactory() {}

                virtual ossimPropertyInterface* createInterface( const ossimObject* obj ) const = 0;

                TYPE_DATA
};
