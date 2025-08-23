#ifndef COMPONENTDELEGATE_H
#define COMPONENTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QDrag>
#include <QMimeData>
// 组件委托，负责绘制列表中的每个项
class ComponentDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComponentDelegate(QObject *parent = nullptr);

    // 重写绘制方法
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // 重写尺寸提示方法，定义每个项的大小
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    // 监控鼠标事件
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    bool m_isHoveringHelp = false;
    QModelIndex m_hoverIndex =QModelIndex();
    void startDrag(const QModelIndex &index) const;

};

#endif // COMPONENTDELEGATE_H
