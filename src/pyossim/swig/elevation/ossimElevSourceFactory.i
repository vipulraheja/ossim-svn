/*-----------------------------------------------------------------------------
 * Filename        : ossimElevSourceFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimElevSourceFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/elevation/ossimElevSourceFactory.h>
%}

/* Wrapping class ossimElevSourceFactory */
class ossimElevSourceFactory : public ossimObject
{
        public:

                /** default constructor */
                ossimElevSourceFactory();

                /** virtual destructor */
                virtual ~ossimElevSourceFactory();

                /**
                 *  Pure virtual method.
                 *  return an elevation source pointer that has elevation coverage for the
                 *  ground point passed in.
                 *  Note the caller of this method is responsible for managing the memory
                 *  allocated.
                 */
                virtual ossimElevSource* getNewElevSource(const ossimGpt& gpt)const=0;

                /**
                 * @return The directory the factory returns data from.
                 */
                virtual ossimFilename getDirectory() const;

                /**
                 * @param directory The directory to return data from.
                 */
                virtual void setDirectory(const ossimFilename& directory);

        protected:
                ossimFilename theDirectory;

                /* Ignoring Macro 
                   TYPE_DATA */
}; 
