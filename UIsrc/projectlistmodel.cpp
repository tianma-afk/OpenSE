#include "projectlistmodel.h"

ProjectListModel::ProjectListModel(int numItems, QObject* parent)
    :QAbstractListModel(parent),itemCount(numItems){
    titles.resize(itemCount); // 初始化标题数组
    for (int i = 0; i < itemCount; ++i) {
        titles[i] = QString("标题文本 %1").arg(i); // 生成初始标题文本
    }
}

int ProjectListModel::rowCount(const QModelIndex& parent)const{
    if (parent.isValid()) {
        return 0;
    }
    return itemCount;
}

QVariant ProjectListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= itemCount || index.row() < 0) {
        return QVariant();
    }
    switch (role) {
    case Qt::DisplayRole:
        return titles.at(index.row());
    case Qt::CheckStateRole:
    {
        auto it = checkedItems.find(index.row());
        if (it != checkedItems.end()) {
            return QVariant(it.value() ? Qt::Checked : Qt::Unchecked);
        }
        return QVariant(Qt::Unchecked);
    }
    case Qt::EditRole: // 处理编辑角色
        return titles[index.row()];
    default:
        return QVariant();
    }
}

bool ProjectListModel::setData(const QModelIndex& index, const QVariant& value, int role){
    if (!index.isValid() || index.row() >= itemCount || index.row() < 0)
        return false;

    switch (role) {
    case Qt::CheckStateRole:
        // 更新 checkedItems，记录复选框的状态
        checkedItems[index.row()] = (value.toBool());
        if(value.toBool()==true){
            checkedNum++;
        }else{
            checkedNum--;
        }
        emit dataChanged(index, index, { role });
        return true;
    case Qt::EditRole:
        // 更新标题文本
        titles[index.row()] = value.toString();
        emit dataChanged(index, index, { role });
        return true;
    default:
        return false;
    }
}

Qt::ItemFlags ProjectListModel::flags(const QModelIndex& index) const{
    if (!index.isValid())
        return Qt::NoItemFlags;
    // 添加 Qt::ItemIsEditable 以支持编辑
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
}

int ProjectListModel::getCheckedNum() const
{
    return checkedNum;
}
