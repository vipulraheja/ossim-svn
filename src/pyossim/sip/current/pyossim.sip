%Module pyossim 0

%Import QtGui/QtGuimod.sip
%Import QtCore/QtCoremod.sip

class ossimPlanetQtLegendAnimationPathItem 
{

%TypeHeaderCode
#include <ossimPlanetQt/ossimPlanetQtLegendItem.h>
#include <ossimPlanetQt/ossimPlanetQtLegendAnimationPathItem.h>
#include <osg/AnimationPath>
#include <osg/ref_ptr>
%End

public:
	ossimPlanetQtLegendAnimationPathItem(QTreeWidgetItem* item,
			const QString& name);
	ossimPlanetQtLegendAnimationPathItem(QTreeWidget* treeWidget,
		const QString& s);
	ossimPlanetQtLegendAnimationPathItem();

	void setAnimationPath(osg::ref_ptr<osg::AnimationPath> animationPath);
	osg::ref_ptr<osg::AnimationPath> animationPath();

	virtual void deleteLayer(bool deleteThis=false);
	virtual ossimRefPtr<ossimXmlNode> saveXml()const;
	virtual void loadXml(ossimRefPtr<ossimXmlNode> node,
	std::vector<ossimPlanetOperation*>& activityList);

	virtual const osg::ref_ptr<ossimPlanetLookAt> getLookAt()const;
	virtual void setLookAt(osg::ref_ptr<ossimPlanetLookAt> lookAt);

	virtual const osg::ref_ptr<ossimPlanetExtents> getExtents()const;

	void getAnimationPathAsString(std::string& animationPath);
	void setAnimationPathFromString(const std::string& animationPath);
};
