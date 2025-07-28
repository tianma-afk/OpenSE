#ifndef PROJECTLISTMODEL_H
#define PROJECTLISTMODEL_H

#include <QAbstractListModel>

class ProjectListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ProjectListModel(int numItems, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    int itemCount;
    mutable QHash<int, bool> checkedItems; // 存储复选框的状态
    QVector<QString> titles; // 存储标题文本
};

#endif // PROJECTLISTMODEL_H
