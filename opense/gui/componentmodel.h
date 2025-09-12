#ifndef COMPONENTMODEL_H
#define COMPONENTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "core/componentmeta.h"

// 组件模型，管理组件数据并提供给视图
class ComponentModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // 自定义数据角色，用于获取不同类型的数据
    enum ComponentRoles {
        NameRole = Qt::UserRole + 1,      // 组件名称
        IconRole,                         // 组件图标
        DescriptionRole                   // 组件描述
    };

    explicit ComponentModel(QObject *parent = nullptr);

    // 重写模型基本方法
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // 添加组件项
    void addItem(ComponentMeta* item);
    // 获取指定索引的组件项
    ComponentMeta* getItem(const QModelIndex& index) const;

private:
    QList<ComponentMeta*> m_items; // 存储组件数据的列表
};

#endif // COMPONENTMODEL_H
