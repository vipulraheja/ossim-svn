%Module pyossim 0

%Import QtGui/QtGuimod.sip

class ossimPlanetQtPreferences : QDialog
{

%TypeHeaderCode	
#include <ossimPlanetQt/ui_ossimPlanetQtPreferences.h>
#include <ossimPlanetQt/ossimPlanetQtExport.h>
#include <ossimPlanetQt/ossimPlanetQtPreferences.h>
%End

public:
	ossimPlanetQtPreferences(QWidget* parent /TransferThis/ = 0);
};
