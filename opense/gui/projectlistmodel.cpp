#include "projectlistmodel.h"

ProjectListModel::ProjectListModel(QObject* parent)
    :QAbstractListModel(parent){}

void ProjectListModel::addProjectDatas(const QVector<ProjectData> datas)
{
    qDebug()<<datas.count();
    for(int i=0;i<datas.count();i++){
        this->datas.push_back(datas.at(i));
    }
}

void ProjectListModel::addProjectData(const ProjectData &data)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    this->datas.push_back(data);
    endInsertRows();
}

int ProjectListModel::rowCount(const QModelIndex& parent)const{
    if (parent.isValid()) {
        return 0;
    }
    return datas.size();
}

QVariant ProjectListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= datas.size() || index.row() < 0) {
        return QVariant();
    }
    switch (role) {
    case Qt::DisplayRole:
        return datas.at(index.row()).getProjectName();
    case ProjectRoles::NameRole:
        return datas.at(index.row()).getProjectName();
    case ProjectRoles::CreateTimeRole:
        return datas.at(index.row()).getCreateTime().toString("yyyy年M月d日H:m");
    case ProjectRoles::ModifyTimeRole:
        return datas.at(index.row()).getModifyTime().toString("yyyy年M月d日H:m");
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
    if (!index.isValid() || index.row() >= datas.size() || index.row() < 0)
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

void ProjectListModel::checkAllchanged(bool checked)
{
    for (int row = 0; row < this->rowCount(); ++row) {
        QModelIndex index = this->index(row, 0); // 假设第0列存储复选框状态
        if (index.isValid()) {
            this->setData(index,
                           checked ? Qt::Checked : Qt::Unchecked,
                           Qt::CheckStateRole);
        }
    }
}
