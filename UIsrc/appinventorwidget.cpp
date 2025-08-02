#include "appinventorwidget.h"
#include <QPainter>
#include <QStyleOption>
AppInventorWidget::AppInventorWidget(QWidget *parent)
    : QWidget(parent)
{
    this->initialUI();
    this->initialData();
}

void AppInventorWidget::paintEvent(QPaintEvent *event)
{
    // 1. 初始化样式选项，关联当前窗口
    QStyleOption opt;
    opt.initFrom(this);  // 从当前部件获取样式相关信息（包括QSS设置）

    // 2. 创建画家对象
    QPainter painter(this);

    // 3. 关键：让样式系统根据QSS绘制窗口
    // 这一步会自动读取并应用QSS中对MyWidget的样式定义
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    // 注意：如果有子部件或其他绘制逻辑，需要在这里继续处理
    QWidget::paintEvent(event);
}

void AppInventorWidget::initialUI()
{
    this->vLayout=new QVBoxLayout(this);
    this->setLayout(this->vLayout);
    //头部
    this->headWidget=new QWidget(this);
    this->vLayout->addWidget(this->headWidget,0);
    this->headWidget->setObjectName("inventor_top");

    this->headHLayout=new QHBoxLayout(this);
    this->headWidget->setLayout(this->headHLayout);

    this->nameLabel=new QLabel(this->headWidget);
    this->headHLayout->addWidget(this->nameLabel);
    this->nameLabel->setObjectName("inventor_headName");
    //主体
    this->bodyWidget=new QWidget(this);
    this->vLayout->addWidget(this->bodyWidget,1);

    this->bodyHLayout=new QHBoxLayout(this->bodyWidget);
    this->bodyWidget->setLayout(this->bodyHLayout);
}

void AppInventorWidget::initialData()
{
    this->nameLabel->setText("text");
}
