/*-----------------------------------------------------------------------------
 * Filename        : ossimSrtmFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimSrtmFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/elevation/ossimElevSourceFactory.h>
#include <ossim/elevation/ossimSrtmFactory.h>
%}

class ossimSrtmFactory : public ossimElevSourceFactory
{
        public:

                /** default constructor */
                ossimSrtmFactory();

                /** Constructor that takes a directory name. */
                ossimSrtmFactory(const ossimFilename& dir);

                /** destructor */
                virtual ~ossimSrtmFactory();

                /**
                 * Open the appropriate ossimSrtmElevSource that covers given a
                 * ground point.
                 *
                 * @param gpt Ground point that an elevation source is need for.
                 *
                 * @return Returns a pointer to an ossimElevSource if an srtm file is found
                 * that can cover the ground point.  Returns NULL if no cell is found
                 * for the point.
                 */
                virtual ossimElevSource* getNewElevSource(const ossimGpt& gpt) const;

        protected:

                /* Ignoring Macro
                   TYPE_DATA */
};
