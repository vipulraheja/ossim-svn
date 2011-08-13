%Module pyossim 0

%Import osgGA/GUIActionAdapter

class ossimPlanetQtActionAdapter : osgGA :: GUIActionAdapter
{

%TypeHeaderCode
#include <GUIActionAdapter>
#include <ossimPlanetQtExport.h>
%End

public:
	ossimPlanetQtActionAdapter():theNeedRedraw(false),
		theNeedContinuousUpdate(false),
		theNeedWarpPointer(false),
		theX(-1),theY(-1);

	void reset();

	virtual ~ossimPlanetQtActionAdapter() {}
	virtual void requestRedraw();
	virtual void requestContinuousUpdate(bool needed=true);
	virtual void requestWarpPointer(float x,float y);
	virtual void clearWarpRequest();

	void setNeedRedraw(bool flag);
	void setNeedContinuousUpdate(bool flag);

	bool getNeedRedraw() const;
	bool getNeedContinuousUpdate() const;
	bool getNeedWarpPointer(float &x,float &y) const;

private:
	bool theNeedRedraw;
	bool theNeedContinuousUpdate;
	bool theNeedWarpPointer;
	float theX,theY;
};
