#include "componentmodel.h"

ComponentModel::ComponentModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

// 返回数据项数量
int ComponentModel::rowCount(const QModelIndex &parent) const
{
    // 对于列表模型，父索引有效时返回0（不支持子项）
    if (parent.isValid())
        return 0;

    return m_items.count();
}

// 返回指定索引和角色的数据
QVariant ComponentModel::data(const QModelIndex &index, int role) const
{
    // 检查索引有效性
    if (!index.isValid() || index.row() >= m_items.count())
        return QVariant();

    // 获取对应的数据项
    ComponentMeta* item = m_items[index.row()];

    // 根据角色返回不同类型的数据
    switch (role) {
    case NameRole:
        return item->type;
    case IconRole:
        return QIcon(item->iconPath);
    case DescriptionRole:
        return item->description;
    default:
        return QVariant();
    }
}

// 定义角色名称，用于QML访问（C++中也建议实现）
QHash<int, QByteArray> ComponentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[DescriptionRole] = "description";
    return roles;
}

// 添加新的组件项
void ComponentModel::addItem(ComponentMeta *item)
{
    if (!item) return;

    // 通知视图即将添加数据
    beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
    m_items.append(item);
    // 通知视图数据添加完成
    endInsertRows();
}

// 获取指定索引的组件项
ComponentMeta *ComponentModel::getItem(const QModelIndex &index) const
{
    if (index.isValid() && index.row() < m_items.count()) {
        return m_items[index.row()];
    }
    return nullptr;
}
