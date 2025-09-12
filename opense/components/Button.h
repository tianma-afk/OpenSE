#ifndef BUTTON_H
#define BUTTON_H

#include "component.h"
#include <QRectF>
#include"core/componentregister.h"
class Button : public Component {
public:
    Button();
    ~Button() override;

    static QString staticType() { return "Button"; }
    QString componentType() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setProperty(const QString &name, const QVariant &value) override;
    QVariant getProperty(const QString &name) const override;

    // 便捷接口（封装属性操作）
    void setText(const QString &text);
    QString getText() const;
    void setSize(const QSizeF &size);
    QSizeF getSize() const;
};

// 注册组件
REGISTER_COMPONENT(Button, ":/icons/Button.png", "用于触发点击事件")

#endif // BUTTON_H
