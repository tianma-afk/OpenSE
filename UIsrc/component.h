#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsItem>
#include<QStandardItem>
// 可拖拽的组件项（继承自QGraphicsItem）
class Component : public QGraphicsItem {
public:
    explicit Component(const QString &type);

    // 必须实现的纯虚函数：定义组件边界
    QRectF boundingRect() const override;
    // 必须实现的纯虚函数：绘制组件外观
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QStandardItem*item;
    enum Data{
        objName = Qt::DisplayRole, // 真实值：0
        icon = Qt::DecorationRole,    // 真实值：1
        type = Qt::UserRole + 1,    // 真实值：65536 + 1
        size = Qt::UserRole + 2,    // 真实值：65536 + 2
        color = Qt::UserRole + 3,   // 真实值：65536 + 3
        text = Qt::UserRole + 4     // 真实值：65536 + 4
    };
};

#endif // COMPONENT_H
