// Copied and adapted from ossimPlanetQtActionAdapter


#ifndef ossimPlanetCocoaActionAdapter_HEADER
#define ossimPlanetCocoaActionAdapter_HEADER

#include <osgGA/GUIActionAdapter>

/// CocoaActionAdapter allows window-system-agnostic osgGA classes to tell
/// the window system what to do

/**
 * CocoaActionAdapter - a class to adapt osgGA-specified actions into feedback for our app.
 */

class ossimPlanetCocoaActionAdapter : public osgGA::GUIActionAdapter
{
    public:

        ossimPlanetCocoaActionAdapter():theNeedRedraw(false),
			    theNeedContinuousUpdate(true),
			    theNeedWarpPointer(false),
			    theX(-1),theY(-1) {};

        virtual ~ossimPlanetCocoaActionAdapter() {}

	virtual void requestRedraw()
           {
              theNeedRedraw=true;
           }

	virtual void requestContinuousUpdate(bool needed=true)
           {
              theNeedContinuousUpdate=needed;
           }

	virtual void requestWarpPointer(float x,float y)
           {
              theNeedWarpPointer=true;
              theX=x;
              theY=y;
           }

	virtual void clearWarpRequest()
           {
              theNeedWarpPointer = false;
           }

	bool getNeedRedraw() const		{return theNeedRedraw;}
	bool getNeedContinuousUpdate() const	{return theNeedContinuousUpdate;}
	bool getNeedWarpPointer(float &x,float &y) const
           {
              if(theNeedWarpPointer)
              {
                 x=theX;
                 y=theY;
                 return theNeedWarpPointer;
              }
              
              return false;
           }

 private:

	bool theNeedRedraw;
	bool theNeedContinuousUpdate;
	bool theNeedWarpPointer;
	float theX,theY;
};

#endif
