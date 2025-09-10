#ifndef COMPONENTPANELDELEGATE_H
#define COMPONENTPANELDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include"gui/componentpanelmodel.h"
class ComponentPanelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComponentPanelDelegate(QObject *parent = nullptr);

    // 计算列表项大小
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    void setModel(ComponentPanelModel*model);
private:
    ComponentPanelModel*model;
};

#endif // COMPONENTPANELDELEGATE_H
