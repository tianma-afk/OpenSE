#ifndef PROJECTLISTMODEL_H
#define PROJECTLISTMODEL_H

#include <QAbstractListModel>
#include"projectdata.h"
class ProjectListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ProjectListModel(const QVector<ProjectData>datas, QObject* parent = nullptr);

    void addProjectData(const ProjectData&data);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    int getCheckedNum()const;

    QVariant getProjectData(const QModelIndex& index,const QString&tag)const ;
    QVector<ProjectData> datas;
private:
    int itemCount;
    mutable QHash<int, bool> checkedItems; // 存储复选框的状态

    int checkedNum=0;
};

#endif // PROJECTLISTMODEL_H
