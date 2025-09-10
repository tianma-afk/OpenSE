#include "propertypanel.h"
#include<QStyleOption>
#include<QPainter>
PropertyPanel::PropertyPanel(QWidget *parent)
    : QWidget{parent}
{}

void PropertyPanel::paintEvent(QPaintEvent *event)
{
    //保证样式表正常绘制
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    // 注意：如果有子部件或其他绘制逻辑，需要在这里继续处理
    QWidget::paintEvent(event);
}
