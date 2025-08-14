#ifndef COMPONENTPANELDELEGATE_H
#define COMPONENTPANELDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include<componentpanelmodel.h>
class ComponentPanelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComponentPanelDelegate(QObject *parent = nullptr);

    // 计算列表项大小
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    void setModel(ComponentPanelModel*model);

    // 处理鼠标事件
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    // 当项目被点击时发出信号
    void itemClicked(const QModelIndex &index);
private:
    ComponentPanelModel*model;
};

#endif // COMPONENTPANELDELEGATE_H
