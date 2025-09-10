#include "componentpanelmodel.h"


ComponentPanelModel::ComponentPanelModel( QObject *parent)
    :QAbstractListModel(parent)
{

}

int ComponentPanelModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return items.count();
}

QVariant ComponentPanelModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

bool ComponentPanelModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}


Qt::ItemFlags ComponentPanelModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

void ComponentPanelModel::addItem(ComponentMenuItem *item)
{
    this->items.push_back(item);
    QModelIndex index = this->index(items.count()-1, 0);
    emit signal_addItem(index);
}

QVariant ComponentPanelModel::getComponentMenuData(const QModelIndex &index, const QString &tag) const
{
    if (!index.isValid() || index.row() >= this->items.count() || index.row() < 0) {
        return QVariant();
    }
    if(tag=="menuName"){
        return items.at(index.row())->getMenuName();
    }else{
        return QVariant();
    }
}

ComponentMenuItem *ComponentPanelModel::getComponentMenuItem(const QModelIndex &index) const
{
    return items.at(index.row());
}
