#ifndef ossimQtInformationDialog_HEADER
#define ossimQtInformationDialog_HEADER
#include <qdialog.h>
class QVBoxLayout;
class QTextEdit;

class ossimQtInformationDialog : public QDialog
{
public:
   ossimQtInformationDialog(QWidget* parent=0,
                            bool modal = false,
                            WFlags f = 0);
   void setText(const QString& value);
   QTextEdit*  textEditor();
protected:
   QVBoxLayout* theMainVBox;
   QTextEdit*   theTextEditor;
};

#endif
