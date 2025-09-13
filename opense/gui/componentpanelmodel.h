#ifndef COMPONENTPANELMODEL_H
#define COMPONENTPANELMODEL_H

#include <QAbstractListModel>
#include"gui/componentmenuitem.h"
class ComponentPanelModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ComponentPanelModel( QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void addItem(ComponentMenuItem* item);
    QVariant getComponentMenuData(const QModelIndex& index,const QString&tag)const ;
    ComponentMenuItem*getComponentMenuItem(const QModelIndex& index)const;
    bool isExpand=false;
    QModelIndex expandIndex;

signals:
    void signal_addItem(QModelIndex&index);
private:
    QVector<ComponentMenuItem*> items;
};

#endif // COMPONENTPANELMODEL_H
