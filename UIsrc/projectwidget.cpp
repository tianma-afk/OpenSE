#include "projectwidget.h"
#include"projectlistmodel.h"
#include"projectdelegate.h"
ProjectWidget::ProjectWidget(QWidget *parent)
    : QWidget{parent}
{
    initialUI();
    initialData();

}

void ProjectWidget::initialUI()
{
    //整个页面为垂直布局
    this->vLayout=new QVBoxLayout(this);
    this->setLayout(vLayout);

    //初始化头部
    this->topWidget=new QWidget(this);
    this->vLayout->addWidget(this->topWidget,0);
    this->topWidget->setObjectName("project_top");

    this->topHLayout=new QHBoxLayout(this->topWidget);
    this->topWidget->setLayout(topHLayout);
    this->topHLayout->setSpacing(10);

    this->headLabel=new QLabel(this->topWidget);
    this->topHLayout->addWidget(headLabel);
    this->headLabel->setText("项目");
    this->headLabel->setObjectName("project_top");

    this->newProjectBtn=new QPushButton(this->topWidget);
    this->topHLayout->addWidget(newProjectBtn);
    this->newProjectBtn->setText("新项目");

    this->removeProjectBtn=new QPushButton(this->topWidget);
    this->topHLayout->addWidget(removeProjectBtn);
    this->removeProjectBtn->setText("删除项目");

    this->topHLayout->addStretch(1);
    //初始化主体
    this->bodyWidget=new QWidget(this);
    this->vLayout->addWidget(this->bodyWidget,1);
    this->bodyWidget->setObjectName("project_body");

    this->bodyVLayout=new QVBoxLayout(this->bodyWidget);
    this->bodyWidget->setLayout(this->bodyVLayout);
    this->bodyVLayout->setSpacing(0);

    this->headWidget=new HeadWidget(this->bodyWidget);
    this->bodyVLayout->addWidget(this->headWidget,0);
    this->headWidget->setObjectName("project_body_head");

    this->listView = new QListView(this->bodyWidget);
    this->bodyVLayout->addWidget(listView,1);


}

void ProjectWidget::initialData()
{
    auto insertCount = 10;// 构造展示10条数据
    ProjectDelegate* delegate = new ProjectDelegate(listView);


    ProjectListModel *model=new ProjectListModel(insertCount);
    listView->setModel(model);
    delegate->setModel(model);

    listView->setItemDelegate(delegate);

    connect(this->headWidget,&HeadWidget::checkedChanged,delegate,&ProjectDelegate::checkAllchanged);
    connect(delegate,&ProjectDelegate::singleCheckedChange,this->headWidget,&HeadWidget::checkStateChangeForSingle);
    // 优化性能
    listView->setUniformItemSizes(true);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    // listView->show();
}
