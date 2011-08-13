%Module pyossim 0

%Import QtGui/QtGuimod.sip

class ossimPlanetQtImage : QImage
{

%TypeHeaderCode
#include <ossim/imaging/ossimImageData.h>
#include <ossimPlanetQt/ossimPlanetQtExport.h>
#include <ossimPlanetQt/ossimPlanetQtImage.h>
%End

public:
	ossimPlanetQtImage(const QImage& img);
	ossimPlanetQtImage(const ossimPlanetQtImage& img);

	ossimRefPtr<ossimImageData> getOssimImage() const;

	void convertToOssimImage();
};
