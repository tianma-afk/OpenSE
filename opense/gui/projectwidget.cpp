#include "projectwidget.h"
#include"gui/newprojectdialog.h"
#include"core/projectmanager.h"
ProjectWidget::ProjectWidget(QWidget *parent)
    : QWidget{parent}
{
    initialUI();
    initialData();
    initialCore();
    initialConnect();
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
    delegate = new ProjectDelegate(listView);
    model=new ProjectListModel();
    QVector<ProjectData> datas=ProjectManager::getInstance().getProjectDatas();
    model->addProjectDatas(datas);
    listView->setModel(model);
    listView->setItemDelegate(delegate);
    listView->setUniformItemSizes(true);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void ProjectWidget::initialCore()
{
}

void ProjectWidget::initialConnect()
{
    connect(this->headWidget,&HeadWidget::checkedChanged,model,&ProjectListModel::checkAllchanged);
    connect(delegate,&ProjectDelegate::singleCheckedChange,this->headWidget,&HeadWidget::checkStateChangeForSingle);
    connect(delegate,&ProjectDelegate::openProject,[=](){emit this->openProject();});
    connect(this->newProjectBtn,&QPushButton::clicked,this,&ProjectWidget::onNewProjectBtnClicked);
    connect(this->removeProjectBtn,&QPushButton::clicked,this,&ProjectWidget::onRemoveProjectBtnClicked);
}

void ProjectWidget::onNewProjectBtnClicked()
{
    NewProjectDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.projectName();
        QString path = dialog.savePath();
        ProjectData data=ProjectManager::getInstance().createProject(name, path);
        model->addProjectData(data);
    }
}

void ProjectWidget::onRemoveProjectBtnClicked()
{
    QStringList list=this->model->getCheckedItemName();
    foreach (const QString& entry, list) {
        ProjectManager::getInstance().removeProject(entry);
    }
    this->model->removeCheckedItems();
}
