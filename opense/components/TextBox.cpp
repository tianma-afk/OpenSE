#include "TextBox.h"
#include <QPainter>
#include <QFont>
#include <QStandardItem>

TextBox::TextBox() {
    // 初始化QStandardItem并设置默认属性
    item = new QStandardItem();
    item->setData(staticType(), Data::type);       // 类型
    item->setData("Enter text here", Data::text);  // 默认提示文本
    item->setData(QSizeF(150, 30), Data::size);    // 默认尺寸
    item->setData(QIcon(":/icons/TextBox.png"),Data::icon);    //显示图标
    item->setData("textBox",Data::objName); //默认对象名
    // 设置可移动、可选中
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
}

TextBox::~TextBox() {
    delete item;
}

QString TextBox::componentType() const {
    return staticType();
}

QRectF TextBox::boundingRect() const {
    // 从item中获取尺寸属性
    QSizeF size = item->data(Data::size).toSizeF();
    return QRectF(0, 0, size.width(), size.height()).adjusted(-2, -2, 2, 2);
}

void TextBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);

    // 从item中获取属性
    QSizeF size = item->data(Data::size).toSizeF();
    QString hintText = item->data(Data::text).toString();

    // 绘制文本框背景
    painter->setBrush(QBrush(Qt::white));
    painter->setPen(QPen(Qt::gray, 1));
    painter->drawRect(0, 0, size.width(), size.height());

    // 绘制提示文本
    painter->setPen(QPen(Qt::lightGray));
    painter->setFont(QFont("Arial", 9));
    painter->drawText(QRectF(0, 0, size.width(), size.height()).adjusted(5, 0, 0, 0),
                      Qt::AlignVCenter, hintText);

    // 选中状态
    if (isSelected()) {
        painter->setPen(QPen(Qt::blue, 2, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

void TextBox::setProperty(const QString &name, const QVariant &value) {
    if (name == "hintText") {
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

QVariant TextBox::getProperty(const QString &name) const {
    if (name == "hintText") {
        return item->data(Data::text);
    } else if (name == "width") {
        return item->data(Data::size).toSizeF().width();
    } else if (name == "height") {
        return item->data(Data::size).toSizeF().height();
    }
    return QVariant();
}

// 便捷接口实现
void TextBox::setHintText(const QString &text) {
    setProperty("hintText", text);
}

QString TextBox::getHintText() const {
    return getProperty("hintText").toString();
}

void TextBox::setSize(const QSizeF &size) {
    item->setData(size, Data::size);
    update();
}

QSizeF TextBox::getSize() const {
    return item->data(Data::size).toSizeF();
}
