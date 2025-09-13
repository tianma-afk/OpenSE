#include "headwidget.h"

HeadWidget::HeadWidget(QWidget *parent)
    : QWidget{parent}
{}

void HeadWidget::paintEvent(QPaintEvent *event)
{
    //保证样式表正常绘制
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.save();



    QStyleOptionButton checkboxOption;
    QRect checkboxRect = QRect(this->rect().x() + 5, this->rect().y() + 5, this->rect().height() - 10, this->rect().height() - 10);
    checkboxOption.rect = checkboxRect;
    checkboxOption.state |= QStyle::State_Enabled;
    if (this->checkState) {
        checkboxOption.state |= QStyle::State_On;
    } else {
        checkboxOption.state |= QStyle::State_Off;
    }

    // 绘制复选框
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxOption, &painter);

    // // 绘制按钮
    // buttonOption.text = "按钮";
    // QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, &painter);

    // 绘制文本
    QRect nameTextRect = this->rect().adjusted(checkboxRect.width() + 10, 0, - 200, 0);
    painter.drawText(nameTextRect, Qt::AlignVCenter, "项目名");

    QRect createTimeTextRect = this->rect().adjusted(this->rect().right()-300, 0, -150, 0);
    painter.drawText(createTimeTextRect, Qt::AlignVCenter, "创建时间");

    QRect modifyTimeTextRect = this->rect().adjusted(this->rect().right()-100, 0, -50, 0);
    painter.drawText(modifyTimeTextRect, Qt::AlignVCenter, "修改时间");
    painter.restore();

}

void HeadWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    // 检查是否点击了复选框区域
    QRect checkBoxRect = QRect(rect().x() + 5,
                               rect().y() + 5,
                               rect().height() - 10,
                               rect().height() - 10);
    if (checkBoxRect.contains(event->pos())) {
        checkState = !checkState;
        emit checkedChanged(checkState);
        update();
    }
}

QSize HeadWidget::sizeHint() const {
    return QSize(400, 34);
}

void HeadWidget::checkStateChangeForSingle(bool checked)
{
    qDebug()<<checked;
    checkState=checked;
    update();
}
