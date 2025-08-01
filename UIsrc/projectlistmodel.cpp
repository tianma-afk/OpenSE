#include "projectlistmodel.h"

ProjectListModel::ProjectListModel(const QVector<ProjectData>datas,QObject* parent)
    :QAbstractListModel(parent),itemCount(datas.count()){
    // 初始化数据数组
    this->datas=datas;
}

void ProjectListModel::addProjectData(const ProjectData &data)
{
    this->itemCount++;
    this->datas.push_back(data);
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
        return datas.at(index.row()).projectName;
    case Qt::CheckStateRole:
    {
        auto it = checkedItems.find(index.row());
        if (it != checkedItems.end()) {
            return QVariant(it.value() ? Qt::Checked : Qt::Unchecked);
        }
        return QVariant(Qt::Unchecked);
    }
    default:
        return QVariant();
    }
}

bool ProjectListModel::setData(const QModelIndex& index, const QVariant& value, int role){
    if (!index.isValid() || index.row() >= itemCount || index.row() < 0)
        return false;

    // 更新 checkedItems，记录复选框的状态
    checkedItems[index.row()] = (value.toBool());
    if(value.toBool()==true){
        checkedNum++;
    }else{
        checkedNum--;
    }
    emit dataChanged(index, index, { role });
    return true;

}

Qt::ItemFlags ProjectListModel::flags(const QModelIndex& index) const{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

int ProjectListModel::getCheckedNum() const
{
    return checkedNum;
}

QVariant ProjectListModel::getProjectData(const QModelIndex &index, const QString &tag) const
{
    if (!index.isValid() || index.row() >= itemCount || index.row() < 0) {
        return QVariant();
    }
    if(tag=="projectName"){
        return datas.at(index.row()).projectName;
    }else if(tag=="createTime"){
        return datas.at(index.row()).createTime.toString("yyyy年M月d日H时m分");
    }else if(tag=="modifyTime"){
        return datas.at(index.row()).modifyTime.toString("yyyy年M月d日H时m分");
    }else{
        return QVariant();
    }
}
