%Module pyossim 0

%Import QtGui/QtGuimod.sip

class ossimPlanetQtRuler : QDialog
{

%TypeHeaderCode
#include <ossimPlanetQt/ui_ossimPlanetQtRuler.h>
#include <osg/Vec3d>
#include <osg/ref_ptr>
#include <ossimPlanet/ossimPlanet.h>
#include <ossimPlanet/ossimPlanetGeoRefModel.h>
#include <ossimPlanetQt/ossimPlanetQtExport.h>
#include <ossimPlanetQt/ossimPlanetQtRuler.h>
%End

public:
	ossimPlanetQtRuler(QWidget* parent);
	virtual ~ossimPlanetQtRuler();
	void setPlanet(osg::ref_ptr<ossimPlanet> planet);
	void setGlWidget(ossimPlanetQtViewer* widget);
};
