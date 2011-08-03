/*-----------------------------------------------------------------------------
 * Filename        : ossimNadconNarDatum.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimNadconNarDatum
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimNadconGridDatum.h>
#include <ossim/base/ossimNadconGridFile.h>
#include <ossim/base/ossimNadconNarDatum.h>

%}

class ossimNadconNarDatum : public ossimNadconGridDatum
{
        public:
                ossimNadconNarDatum(const ossimFilename& nadconDirectory);

                // Argument holds the source point and datum.  Returns another
                // point with this datum.
                //
                virtual ossimGpt shift(const ossimGpt    &aPt)const;
                //utility functions to shift to and from the standard coordinates.
                //Users should use the shift instead!!!
                //

};
