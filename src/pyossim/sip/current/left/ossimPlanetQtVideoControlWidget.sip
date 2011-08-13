%Module pyossim 0

%Import QtGui/QtGuimod.sip

class ossimPlanetQtVideoControlWidget : QWidget
{

%TypeHeaderCode
#include "ui_ossimPlanetQtVideoControlWidget.h"
#include "ossimPlanetQtExport.h"
#include <ossimPlanet/ossimPlanetVideoLayerNode.h>
%End

public:
	ossimPlanetQtVideoControlWidget(QWidget * parent /TransferThis/ = 0,
			Qt::WindowFlags f = 0 );
	virtual ~ossimPlanetQtVideoControlWidget();
	void setVideoLayerNode(osg::ref_ptr<ossimPlanetVideoLayerNode> videoNode);

	osg::ref_ptr<ossimPlanetVideoLayerNode> videoLayerNode();
	const osg::ref_ptr<ossimPlanetVideoLayerNode> videoLayerNode() const;
	void setCallback(osg::ref_ptr<ossimPlanetNodeCallback> callback);
};
