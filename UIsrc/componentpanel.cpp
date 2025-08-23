#include "componentpanel.h"
#include<QStyleOption>
#include<QPainter>

ComponentPanel::ComponentPanel(QWidget *parent):QWidget(parent)
{
    this->initialUI();
    this->initialData();
}

void ComponentPanel::onItemClicked(const QModelIndex &index)
{
    if(this->model->isExpand==false){
        this->model->isExpand=true;
        this->model->expandIndex=index;
        QWidget*widget=this->listView->indexWidget(index);
        qobject_cast<ComponentMenuItem*>(widget)->listView->setVisible(true);
        emit model->dataChanged(index, index);
    }else{
        if(this->model->expandIndex==index){
            this->model->isExpand=false;
            QWidget*widget=this->listView->indexWidget(index);
            qobject_cast<ComponentMenuItem*>(widget)->listView->setVisible(false);
            emit model->dataChanged(index, index);
        }else{
            QWidget*widget1=this->listView->indexWidget(this->model->expandIndex);
            qobject_cast<ComponentMenuItem*>(widget1)->listView->setVisible(false);
            emit model->dataChanged(this->model->expandIndex, this->model->expandIndex);
            this->model->expandIndex=index;
            QWidget*widget2=this->listView->indexWidget(index);
            qobject_cast<ComponentMenuItem*>(widget2)->listView->setVisible(true);
            emit model->dataChanged(index, index);
        }
    }
}

void ComponentPanel::onItemAdded(const QModelIndex &index)
{
    ComponentMenuItem *widget = model->getComponentMenuItem(index);
    widget->setParent(this->listView);
    this->listView->setIndexWidget(index, widget); // 绑定Widget到Item
    widget->setIndex(index);
    widget->initialData(); // 初始化数据

}

void ComponentPanel::initialUI()
{
    this->vLayout=new QVBoxLayout(this);
    this->setLayout(this->vLayout);
    this->vLayout->setContentsMargins(2,6,2,0);

    // 初始化视图
    listView = new QListView(this);
    this->vLayout->addWidget(listView);
    listView->setObjectName("componentpanel_listview");
}

void ComponentPanel::initialData()
{
    // 初始化
    delegate = new ComponentPanelDelegate(listView);
    model=new ComponentPanelModel();
    listView->setModel(model);
    delegate->setModel(model);
    listView->setItemDelegate(delegate);
    // 连接信号槽
    connect(model,&ComponentPanelModel::signal_addItem,
            this,&ComponentPanel::onItemAdded);
    // 优化性能
    listView->setUniformItemSizes(false);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    //加入数据
    ComponentMenuItem* item1=new ComponentMenuItem();
    item1->setMenuName("用户界面");
    item1->model->addItem(new ComponentItem("button", QIcon(":/icons/button.png"), "用于触发点击事件"));
    item1->model->addItem(new ComponentItem("label", QIcon(":/icons/label.png"), "用于显示文本"));

    ComponentMenuItem*item2=new ComponentMenuItem();
    item2->setMenuName("界面布局");
    ComponentMenuItem*item3=new ComponentMenuItem();
    item3->setMenuName("传感器");
    model->addItem(item1);
    model->addItem(item2);
    model->addItem(item3);
    connect(item1,&ComponentMenuItem::itemClick,this,&ComponentPanel::onItemClicked);
    connect(item2,&ComponentMenuItem::itemClick,this,&ComponentPanel::onItemClicked);
    connect(item3,&ComponentMenuItem::itemClick,this,&ComponentPanel::onItemClicked);
}

void ComponentPanel::paintEvent(QPaintEvent *event)
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

