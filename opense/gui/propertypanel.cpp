#include "propertypanel.h"
#include<QStyleOption>
#include<QPainter>
#include<QLineEdit>
#include<QLabel>
PropertyPanel::PropertyPanel(QWidget *parent)
    : QWidget{parent}
{
    this->initialUI();
}

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

void PropertyPanel::initialUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    // 初始显示提示
    QLabel *hintLabel = new QLabel("请选择一个组件查看属性", this);
    hintLabel->setStyleSheet("color: #999; font-style: italic;");
    mainLayout->addWidget(hintLabel);
}

void PropertyPanel::slot_ComponentSelected(Component *component)
{
    clearProperties();

    if (!component) {
        // 未选中组件时显示提示
        QLabel *hintLabel = new QLabel("请选择一个组件查看属性", this);
        hintLabel->setStyleSheet("color: #999; font-style: italic;");
        mainLayout->addWidget(hintLabel);
        return;
    }
    // 为选中的组件创建属性控件
    this->component=component;
    createProperties();
}

void PropertyPanel::clearProperties()
{
    // 清空现有布局
    QLayoutItem *item;
    while ((item = mainLayout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }
    this->propertyWidgets.clear();
}

void PropertyPanel::createProperties()
{
    QString objName=this->component->getProperty("objName").toString();
    QLabel*label=new QLabel(this);
    label->setText("对象名");
    QLineEdit*lineEdit=new QLineEdit(this);
    lineEdit->setText(objName);
    this->mainLayout->addWidget(label);
    this->mainLayout->addWidget(lineEdit);
    this->propertyWidgets["objName"]=label;
    this->propertyWidgets["objName_data"]=lineEdit;
    connect(lineEdit, &QLineEdit::textChanged,[=](const QString &value) {
        this->component->setProperty("objName",value);
    });
}
