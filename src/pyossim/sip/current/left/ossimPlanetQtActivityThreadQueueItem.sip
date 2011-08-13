%Module pyossim 0

%Import QtGui/QtGuimod.sip
%Import QtCore/QtCoremod.sip

class ossimPlanetQtActivityThreadQueueItem : QObject, QTreeWidgetItem
{

%TypeHeaderCode
#include <ossimPlanetQt/ossimPlanetQtExport.h>
#include <ossimPlanetQt/ossimPlanetQtActivityItem.h>
#include <ossimPlanetQt/ossimPlanetQtActivityThread.h>
#include <ossimPlanetQt/ossimPlanetQtActivityThreadQueueItem.h>
%End

public:
	ossimPlanetQtActivityThreadQueueItem(QTreeWidget* parent,
                                        const QString& queueName,
                                        ossimPlanetQtActivityThread* thread=0,
                                        int type = Type);

	virtual void start();
	virtual void updateGui();
	bool deletableFlag()const;
	void setDeletableFlag(bool flag);
  
	QThread* thread();

protected slots:
	void finished();
	void terminated();
};
