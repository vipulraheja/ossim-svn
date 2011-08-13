%Module pyossim 0

class ossimPlanetQtAlertIconCallout
{

%TypeHeaderCode
#include <osg/Drawable>
#include <osg/Geode>
#include <osg/Vec3>
#include <osg/Image>
#include <ossimPlanet/ossimPlanetLayer.h>
#include <ossimPlanet/ossimPlanetId.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimGeoid.h>
#include <ossim/base/ossimGeoidManager.h>
#include <ossim/base/ossimRefPtr.h>
#include <OpenThreads/Mutex>
#include <ossimPlanetQt/ossimPlanetQtExport.h>
#include <ossimPlanetQt/ossimPlanetQtAlertIconCallout.h>
%End

public:   
	struct AlertInfo
	{
		%TypeHeaderCode
		#include <ossimPlanet/ossimPlanetId.h>
		%End

		ossimPlanetId theId;
		osg::Vec3d    theLandPosition;
	};

	ossimPlanetQtAlertIconCallout();
	
	ossimPlanetQtAlertIconCallout(const ossimPlanetQtAlertIconCallout& iconCallout,
		const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

	virtual osg::Object* cloneType() const;

	virtual Object* clone(const osg::CopyOp& copyop) const;

	virtual bool isSameKindAs(const Object* obj) const;

	virtual const char* libraryName()const;

	virtual const char* className()const;
		
	virtual void drawImplementation(osg::RenderInfo& state)const;

	virtual osg::BoundingBox computeBound()const;
	virtual void addOrUpdateAlert(const AlertInfo& info);

/*
protected:

		ossimPlanetQtAlertIconCallout& operator = (const ossimPlanetQtAlertIconCallout&)
		{
			return *this;
		}

		virtual ~ossimPlanetQtAlertIconCallout();

		osg::ref_ptr<osg::Image>           theImage;
		unsigned short                     theStemHeight; 
		std::map<ossimPlanetId, AlertInfo> theAlerts;
		std::vector<unsigned char>         theLinePixelBuffer; 
*/
};

