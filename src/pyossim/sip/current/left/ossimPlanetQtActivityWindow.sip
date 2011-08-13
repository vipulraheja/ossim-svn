%Module pyossim 0

%Import QtGui/QtGuimod.sip

class ossimPlanetQtActivityWindow : QDialog
{

%TypeHeaderCode
#include <ossimPlanetQt/ui_ossimPlanetQtActivityWindow.h>
#include <ossimPlanetQt/ossimPlanetQtExport.h>
%End

public:
	ossimPlanetQtActivityWindow(QWidget* parent /TransferThis/ = 0);	
};
