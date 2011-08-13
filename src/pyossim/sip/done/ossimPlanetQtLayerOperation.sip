%Module pyossim 0

%Import QtGui/QtGuimod.sip

class ossimPlanetQtLayerOperation : QDialog
{

%TypeHeaderCode
#include <ossimPlanetQt/ui_ossimPlanetQtLayerOperation.h>
#include <ossimPlanetQt/ossimPlanetQtExport.h>
#include <ossimPlanetQt/ossimPlanetQtLayerOperation.h> 
%End

public:
   ossimPlanetQtLayerOperation(QWidget *parent=0);
};
