%Module pyossim 0

%Import QtGui/QtGuimod.sip

class ossimPlanetQtAboutDialog : QDialog
{

%TypeHeaderCode
#include <ossimPlanetQt/ui_ossimPlanetQtAboutDialog.h>
#include <ossimPlanetQt/ossimPlanetQtAboutDialog.h>
%End

public:
	ossimPlanetQtAboutDialog (QWidget *parent /TransferThis/ = 0);
};
