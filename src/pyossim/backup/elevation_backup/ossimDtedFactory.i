/*-----------------------------------------------------------------------------
 * Filename        : ossimDtedFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimDtedFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/elevation/ossimElevSourceFactory.h>
#include <ossim/elevation/ossimDtedFactory.h>

%}
        
/* Wrapping class ossimDtedFactory */
class ossimDtedFactory : public ossimElevSourceFactory
{
        public:

                ossimDtedFactory();
                ossimDtedFactory(const ossimFilename& dir);


                virtual ossimElevSource* getNewElevSource(const ossimGpt& gpt) const;
                virtual void createIndex();
        protected:
                virtual ~ossimDtedFactory();

                /* Ignoring Macro 
                   TYPE_DATA */
};
