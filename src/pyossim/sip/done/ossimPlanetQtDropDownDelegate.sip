%Module pyossim 0

%Import QtGui/QtGuimod.sip

class ossimPlanetQtDropDownDelegate : QItemDelegate
{

%TypeHeaderCode
#include <ossimPlanetQt/ossimPlanetQtDropDownDelegate.h>
%End

public:
	ossimPlanetQtDropDownDelegate(QObject* parent /TransferThis/ =0);
	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	const QModelIndex &index) const;

	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setChoices(const QStringList& choices);
};
