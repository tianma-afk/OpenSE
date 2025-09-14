#include "componentlist.h"
#include<QStyleOption>
#include<QPainter>
ComponentList::ComponentList(QWidget *parent)
    : QWidget{parent}
{
    this->initialUI();
    this->initialData();
}

void ComponentList::paintEvent(QPaintEvent *event)
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

void ComponentList::initialUI()
{
    this->vLayout=new QVBoxLayout(this);
    this->setLayout(this->vLayout);

    this->treeView=new QTreeView(this);
    this->vLayout->addWidget(this->treeView,1);

    this->bottomWidget=new QWidget(this);
    this->vLayout->addWidget(this->bottomWidget);

    this->hLayout=new QHBoxLayout(this->bottomWidget);
    this->bottomWidget->setLayout(this->hLayout);

    this->btn_changeName=new QPushButton(this->bottomWidget);
    this->btn_delete=new QPushButton(this->bottomWidget);
    this->hLayout->addWidget(this->btn_changeName);
    this->hLayout->addWidget(this->btn_delete);
}

void ComponentList::initialData()
{
    // 初始化model
    m_standardItemModel = new QStandardItemModel();
    // 使用model设置QTreeView表头
    m_standardItemModel->setHorizontalHeaderLabels(QStringList(QStringLiteral("关系树")));
    // TreeView控件载入model
    treeView->setModel(m_standardItemModel);
    // 展开数据
    treeView->expandAll();
    connect(treeView->selectionModel(), &QItemSelectionModel::currentChanged, this, &ComponentList::on_treeView_currentChanged);
    this->btn_changeName->setText("改名");
    this->btn_changeName->setDisabled(true);
    this->btn_delete->setText("删除");
    this->btn_delete->setDisabled(true);
    // 创建根节点，抽象Item，并没有实际数据
    this->root = m_standardItemModel->invisibleRootItem();
    // 创建并添加Item的第一个子节点
    QStandardItem*screen = new QStandardItem(QStringLiteral("屏幕1"));
    root->appendRow(screen);
    this->screens.push_back(screen);
}

void ComponentList::on_treeView_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    this->btn_changeName->setDisabled(false);
    this->btn_delete->setDisabled(false);
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(treeView->model());
    if (model && current.isValid()) {
        QStandardItem *currentItem = model->itemFromIndex(current);
        if (currentItem) {
            for(int i=0;i<this->components.count();i++){
                if(this->components.at(i)->item==currentItem){
                    emit this->signal_componentSelected(this->components.at(i));
                    break;
                }
            }
        }
    }
}

void ComponentList::on_addItemInList(Component *parent, Component *self)
{
    this->screens.at(0)->appendRow(self->item);
    this->components.push_back(self);
}

