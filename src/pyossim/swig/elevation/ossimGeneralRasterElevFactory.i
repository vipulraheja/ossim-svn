/*-----------------------------------------------------------------------------
 * Filename        : ossimGeneralRasterElevFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimGeneralRasterElevFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/elevation/ossimElevSourceFactory.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/elevation/ossimGeneralRasterElevHandler.h>
#include <ossim/elevation/ossimGeneralRasterElevFactory.h>
%}

/* Wrapping class ossimGeneralRasterElevFactory */
class ossimGeneralRasterElevFactory : public ossimElevSourceFactory
{
        public:
                typedef std::vector<ossimGeneralRasterElevHandler::GeneralRasterInfo> BoundingRectListType;

                ossimGeneralRasterElevFactory();
                ossimGeneralRasterElevFactory(const ossimFilename& dir);

                virtual ~ossimGeneralRasterElevFactory();

                void setDirectory(const ossimFilename& directory);

                virtual ossimElevSource* getNewElevSource(const ossimGpt& gpt) const;

                virtual void createIndex();


        protected:
                void addInfo(const ossimGeneralRasterElevHandler::GeneralRasterInfo& info);

                std::vector<ossimGeneralRasterElevHandler::GeneralRasterInfo>  theGeneralRasterInfoList;
                ossimDrect            theBoundingRect;
                mutable ossim_int32   theCurrentIdx;
                mutable bool theHandlerReturnedFlag;

                /* Ignoring Macro
                   TYPE_DATA */
};
