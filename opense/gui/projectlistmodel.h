#ifndef PROJECTLISTMODEL_H
#define PROJECTLISTMODEL_H

#include <QAbstractListModel>
#include"gui/projectdata.h"
class ProjectListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ProjectRoles{
        NameRole=Qt::UserRole+1,
        CreateTimeRole,
        ModifyTimeRole
    };
    ProjectListModel(QObject* parent = nullptr);
    void addProjectDatas(const QVector<ProjectData>datas);
    void addProjectData(const ProjectData&data);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    int getCheckedNum()const;
    void checkAllchanged(bool checked);
    QStringList getCheckedItemName()const;
    void removeCheckedItems();
private:
    QVector<ProjectData> datas;
    mutable QHash<int, bool> checkedItems; // 存储复选框的状态
    int checkedNum=0;
};

#endif // PROJECTLISTMODEL_H
