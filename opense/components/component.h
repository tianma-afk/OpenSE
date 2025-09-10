#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsItem>
#include<QStandardItem>
// 可拖拽的组件项（继承自QGraphicsItem）
class Component : public QGraphicsItem {
public:
    virtual ~Component() = default;
    // 组件类型标识
    virtual QString componentType() const = 0;
    // 绘制接口
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override = 0;
    // 边界接口
    virtual QRectF boundingRect() const override = 0;
    // 属性操作接口
    virtual void setProperty(const QString &name, const QVariant &value) = 0;
    virtual QVariant getProperty(const QString &name) const = 0;
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
