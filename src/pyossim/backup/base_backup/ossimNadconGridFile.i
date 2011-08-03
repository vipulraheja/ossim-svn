/*-----------------------------------------------------------------------------
 * Filename        : ossimNadconGridFile.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimNadconGridFile
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimNadconGridHeader.h>
#include <ossim/base/ossimNadconGridFile.h>
#include <fstream>
        
%}

/* Wrapping class ossimNadconGridFile */
class ossimNadconGridFile
{
        public:
                ossimNadconGridFile():
                        theFileOkFlag(false) {}
                ~ossimNadconGridFile();

                bool open(const ossimFilename& file);
                void close();

                double getShiftAtLatLon(double lat, double lon)const;
                
                bool pointWithin(double lat, double lon)const;

                const ossimDrect getBoundingRect()const
                {
                        return theBoundingRect;
                }

                const ossimFilename& getFilename()const
                {
                        return theFilename;
                }

                bool getFileOkFlag()const
                {
                        return theFileOkFlag;
                }

                ossimDpt getSpacing()const
                {
                        return theHeader.getSpacing();
                }

        protected:
                mutable std::ifstream theInputFile;
                mutable bool theFileOkFlag;
                ossimFilename         theFilename;
                ossimNadconGridHeader theHeader;
                ossimDrect            theBoundingRect;
                ossimDpt               theLatLonOrigin;
};
