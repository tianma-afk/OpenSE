#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "component.h"
#include <QRectF>
#include"core/componentregister.h"
class TextBox : public Component {
public:
    TextBox();
    ~TextBox() override;

    static QString staticType() { return "TextBox"; }
    QString componentType() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setProperty(const QString &name, const QVariant &value) override;
    QVariant getProperty(const QString &name) const override;

    // 便捷接口
    void setHintText(const QString &text);
    QString getHintText() const;
    void setSize(const QSizeF &size);
    QSizeF getSize() const;

private:
         // 所有属性通过item存储，无单独成员变量
};

// 注册组件
REGISTER_COMPONENT(TextBox, ":/icons/TextBox.png", "用于显示文本")

#endif // TEXTBOX_H
