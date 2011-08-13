%Module pyossim 0

class ossimPlanetQtActionAdapter 
{

%TypeHeaderCode
#include <osgGA/GUIActionAdapter>
#include <ossimPlanetQt/ossimPlanetQtExport.h>
#include <ossimPlanetQt/ossimPlanetQtActionAdapter.h>
%End

public:
	ossimPlanetQtActionAdapter();

	void reset();

	virtual ~ossimPlanetQtActionAdapter();

	virtual void requestRedraw();
	virtual void requestContinuousUpdate(bool needed=true);
	virtual void requestWarpPointer(float x,float y);

	virtual void clearWarpRequest();

	void setNeedRedraw(bool flag);
	void setNeedContinuousUpdate(bool flag);
	bool getNeedRedraw() const;
	bool getNeedContinuousUpdate() const;

	bool getNeedWarpPointer(float &x,float &y) const;
};
