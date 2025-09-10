#include "components/Button.h"
#include <QPainter>
#include <QFont>
#include <QStandardItem>

Button::Button() {
    // 初始化QStandardItem并设置默认属性
    item = new QStandardItem();
    item->setData(staticType(), Data::type);       // 类型
    item->setData("Button", Data::text);           // 默认文本
    item->setData(QSizeF(100, 40), Data::size);    // 默认尺寸
    item->setData(QIcon(":/icons/Button.png"),Data::icon);    //显示图标
    item->setData("button",Data::objName); //默认对象名

    // 设置可移动、可选中
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
}

Button::~Button() {
    delete item;
}

QString Button::componentType() const {
    return staticType();
}

QRectF Button::boundingRect() const {
    // 从item中获取尺寸属性
    QSizeF size = item->data(Data::size).toSizeF();
    return QRectF(0, 0, size.width(), size.height()).adjusted(-2, -2, 2, 2);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);

    // 从item中获取属性
    QSizeF size = item->data(Data::size).toSizeF();
    QString text = item->data(Data::text).toString();

    // 绘制按钮背景
    painter->setBrush(QBrush(QColor(60, 130, 240)));
    painter->setPen(QPen(Qt::darkBlue, 1));
    painter->drawRoundedRect(0, 0, size.width(), size.height(), 6, 6);

    // 绘制按钮文本
    painter->setPen(QPen(Qt::white));
    painter->setFont(QFont("Arial", 10, QFont::Bold));
    painter->drawText(QRectF(0, 0, size.width(), size.height()), Qt::AlignCenter, text);

    // 选中状态
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 2, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

void Button::setProperty(const QString &name, const QVariant &value) {
    if (name == "text") {
        item->setData(value, Data::text);
        update();
    } else if (name == "width") {
        QSizeF size = item->data(Data::size).toSizeF();
        size.setWidth(value.toDouble());
        item->setData(size, Data::size);
        update();
    } else if (name == "height") {
        QSizeF size = item->data(Data::size).toSizeF();
        size.setHeight(value.toDouble());
        item->setData(size, Data::size);
        update();
    }
}

QVariant Button::getProperty(const QString &name) const {
    if (name == "text") {
        return item->data(Data::text);
    } else if (name == "width") {
        return item->data(Data::size).toSizeF().width();
    } else if (name == "height") {
        return item->data(Data::size).toSizeF().height();
    }
    return QVariant();
}

// 便捷接口实现
void Button::setText(const QString &text) {
    setProperty("text", text);
}

QString Button::getText() const {
    return getProperty("text").toString();
}

void Button::setSize(const QSizeF &size) {
    item->setData(size, Data::size);
    update();
}

QSizeF Button::getSize() const {
    return item->data(Data::size).toSizeF();
}
