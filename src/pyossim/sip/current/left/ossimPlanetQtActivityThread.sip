%Module pyossim 0

%Import QtCore/QtCoremod.sip

class ossimPlanetQtActivityThread : QThread
{

%TypeHeaderCode
#include <ossimPlanetQtActivityItem.h>
#include <ossimPlanetQtMessageActivity.h>
#include <ossimPlanetQtActivityThread.h>
%End

public:
	ossimPlanetQtActivityThread(ossimPlanetQtActivityItem* item, QObject * parent /TransferThis/ = 0);
	ossimPlanetQtActivityThread(QObject* parent /TransferThis/ = 0);
	virtual void setActivityItem(ossimPlanetQtActivityItem* item);
	virtual void run();
	
	ossimPlanetQtActivityItem* theItem;
};
