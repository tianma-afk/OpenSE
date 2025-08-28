#include "component.h"
#include<QPainter>
// 组件项构造函数：根据类型初始化样式
Component::Component(const QString &type){
    setFlag(QGraphicsItem::ItemIsMovable);    // 允许移动
    setFlag(QGraphicsItem::ItemIsSelectable); // 允许选中
    this->item=new QStandardItem();
    // 根据组件类型设置样式
    if (type == "button") {
        this->item->setData(QSizeF(100, 30),Data::size);
        this->item->setData(QColor(Qt::green),Data::color);
        this->item->setData("按钮",Data::text);
    } else if (type == "label") {
        this->item->setData(QSizeF(120, 25),Data::size);
        this->item->setData(QColor(Qt::yellow),Data::color);
        this->item->setData("文本标签",Data::text);
    } else if (type == "textbox") {
        this->item->setData(QSizeF(150, 30),Data::size);
        this->item->setData(QColor(Qt::white),Data::color);
        this->item->setData("输入框",Data::text);
    } else {
        this->item->setData(QSizeF(80, 80),Data::size);
        this->item->setData(QColor(Qt::gray),Data::color);
        this->item->setData("组件",Data::text);
    }
    this->item->setData(type,Data::type);
    this->item->setData(type,Data::objName);
    this->item->setData(QIcon("://icons/"+type+".png"),Data::icon);

}

// 定义组件边界（用于碰撞检测和绘制范围）
QRectF Component::boundingRect() const {
    return QRectF(0, 0, this->item->data(Data::size).value<QSizeF>().width(),this->item->data(Data::size).value<QSizeF>().height());
}

// 绘制组件外观
void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    qDebug()<<"绘制组件";
    // 绘制组件背景（圆角矩形）
    painter->setPen(Qt::black); // 边框色
    painter->setBrush(this->item->data(Data::color).value<QColor>()); // 背景色
    painter->drawRoundedRect(boundingRect(), 5, 5); // 圆角

    // 绘制组件文本（居中）
    painter->drawText(boundingRect(), Qt::AlignCenter, this->item->data(Data::text).value<QString>());
}
