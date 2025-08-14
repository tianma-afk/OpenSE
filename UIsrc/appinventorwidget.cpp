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

    this->component=new QWidget(this->bodyWidget);
    this->bodyHLayout->addWidget(this->component,24);
    this->component->setObjectName("inventor_component");
    this->initialComponent();

    this->workspace=new QWidget(this->bodyWidget);
    this->bodyHLayout->addWidget(this->workspace,83);
    this->workspace->setObjectName("inventor_workspace");
    this->initialWorkspace();

    this->list=new QWidget(this->bodyWidget);
    this->bodyHLayout->addWidget(this->list,22);
    this->list->setObjectName("inventor_list");
    this->initialList();

    this->property=new QWidget(this->bodyWidget);
    this->bodyHLayout->addWidget(this->property,22);
    this->property->setObjectName("inventor_property");
    this->initialProperty();
}

void AppInventorWidget::initialComponent()
{
    this->comVlayout=new QVBoxLayout(this->component);
    this->component->setLayout(this->comVlayout);
    this->comVlayout->setSpacing(0);

    this->componentName=new QLabel(this->component);
    this->componentName->setFixedHeight(35);
    this->comVlayout->addWidget(this->componentName);
    this->componentName->setText("组件面板");
    this->componentName->setObjectName("inventor_body_nameLabel");

    this->cp=new ComponentPanel(this->component);
    this->comVlayout->addWidget(this->cp);
    this->cp->setObjectName("inventor_body_cp");
}

void AppInventorWidget::initialWorkspace()
{
    this->wsVlayout=new QVBoxLayout(this->workspace);
    this->workspace->setLayout(this->wsVlayout);
    this->wsVlayout->setSpacing(0);

    this->workspaceName=new QLabel(this->workspace);
    this->workspaceName->setFixedHeight(35);
    this->wsVlayout->addWidget(this->workspaceName);
    this->workspaceName->setText("工作区");
    this->workspaceName->setObjectName("inventor_body_nameLabel");

    this->ws=new WorkSpace(this->workspace);
    this->ws->setFixedHeight(750);
    this->wsVlayout->addWidget(this->ws);
    this->ws->setObjectName("inventor_body_ws");

    this->wsVlayout->addStretch();
}

void AppInventorWidget::initialList()
{
    this->listVlayout=new QVBoxLayout(this->list);
    this->list->setLayout(this->listVlayout);
    this->listVlayout->setSpacing(0);

    this->listName=new QLabel(this->list);
    this->listName->setFixedHeight(35);
    this->listVlayout->addWidget(this->listName);
    this->listName->setText("组件列表");
    this->listName->setObjectName("inventor_body_nameLabel");

    this->cl=new ComponentList(this->list);
    this->cl->setFixedHeight(500);
    this->listVlayout->addWidget(this->cl);
    this->cl->setObjectName("inventor_body_cl");

    this->listVlayout->addStretch();
}

void AppInventorWidget::initialProperty()
{
    this->proVlayout=new QVBoxLayout(this->property);
    this->property->setLayout(this->proVlayout);
    this->proVlayout->setSpacing(0);

    this->propertyName=new QLabel(this->property);
    this->propertyName->setFixedHeight(35);
    this->proVlayout->addWidget(this->propertyName);
    this->propertyName->setText("属性面板");
    this->propertyName->setObjectName("inventor_body_nameLabel");

    this->pp=new PropertyPanel(this->property);
    this->proVlayout->addWidget(this->pp);
    this->pp->setObjectName("inventor_body_pp");
}

void AppInventorWidget::initialData()
{
    this->nameLabel->setText("text");
}
