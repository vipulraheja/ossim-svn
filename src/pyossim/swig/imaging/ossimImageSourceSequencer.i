/*-----------------------------------------------------------------------------
Filename        : ossimImageSourceSequencer.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageData
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageSourceSequencer.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimConnectableObjectListener.h>

%}

class ossimImageSourceSequencer :
      public ossimImageSource,
      public ossimConnectableObjectListener
{
        public:
                ossimImageSourceSequencer(ossimImageSource* inputSource=NULL,
                                ossimObject* owner=NULL);

                virtual ~ossimImageSourceSequencer();
                ossim_uint32 getNumberOfTiles()const;

                ossim_uint32 getNumberOfTilesHorizontal()const;

                ossim_uint32 getNumberOfTilesVertical()const;

                virtual void initialize();

                virtual void setAreaOfInterest(const ossimIrect& areaOfInterest);

                const ossimIrect& getAreaOfInterest()const;

                virtual void setToStartOfSequence();

                virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& rect,
                                ossim_uint32 resLevel=0);

                virtual ossimRefPtr<ossimImageData> getNextTile(ossim_uint32 resLevel=0);

                virtual bool getTileOrigin(ossim_int32 id,
                                ossimIpt& origin)const;
                virtual ossimRefPtr<ossimImageData> getTile(ossim_int32 id,
                                ossim_uint32 resLevel=0);

                virtual ossimIrect getBoundingRect(ossim_uint32 resLevel=0)const;
                virtual void getDecimationFactor(ossim_uint32 resLevel,
                                ossimDpt& result) const;
                virtual void getDecimationFactors(vector<ossimDpt>& decimations) const;
                virtual ossim_uint32 getNumberOfDecimationLevels()const;

                virtual ossim_uint32 getNumberOfInputBands()const;   

                virtual ossimScalarType getOutputScalarType() const;

                virtual ossim_uint32 getTileWidth()const  { return theTileSize.x; }
                virtual ossim_uint32 getTileHeight()const { return theTileSize.y; }

                virtual void slaveProcessTiles()
                {
                        return;
                }
                virtual bool isMaster()const
                {
                        return true;
                }

                virtual ossimIpt getTileSize()const;
                virtual void setTileSize(const ossimIpt& tileSize);
                virtual void setTileSize(int width, int height);

                virtual void connectInputEvent(ossimConnectionEvent& event);
                virtual void disconnectInputEvent(ossimConnectionEvent& event);

                virtual bool canConnectMyInputTo(ossim_int32 inputIndex,
                                const ossimConnectableObject* object)const;

                virtual double getNullPixelValue(ossim_uint32 band=0)const;
                virtual double getMinPixelValue(ossim_uint32 band=0)const;
                virtual double getMaxPixelValue(ossim_uint32 band=0)const;


        protected:
                ossimImageSource*  theInputConnection;
                ossimRefPtr<ossimImageData> theBlankTile;
                ossimIrect theAreaOfInterest;

                ossimIpt theTileSize;

                ossim_uint32 theNumberOfTilesHorizontal;
                ossim_uint32 theNumberOfTilesVertical;
                ossim_uint32 theCurrentTileNumber;

                virtual void updateTileDimensions();

                TYPE_DATA
};
