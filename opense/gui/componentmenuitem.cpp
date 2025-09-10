#include "componentmenuitem.h"


ComponentMenuItem::ComponentMenuItem(QWidget *parent):QWidget(parent)
{
    this->initialUI();
    this->initialListView();
}

QString ComponentMenuItem::getMenuName() const
{
    return this->menuName;
}


void ComponentMenuItem::setMenuName(const QString menuName)
{
    this->menuName=menuName;
}

void ComponentMenuItem::initialUI()
{
    this->vLayout=new QVBoxLayout(this);
    this->setLayout(this->vLayout);

    this->vLayout->setContentsMargins(0,0,0,0);

    this->nameLabel=new QLabel(this);
    this->vLayout->addWidget(this->nameLabel);
    this->nameLabel->setObjectName("cp_nameLabel");

    this->listView=new QListView(this);
    this->vLayout->addWidget(this->listView);
}

void ComponentMenuItem::initialData()
{
    this->nameLabel->setText(this->menuName);
    nameLabel->installEventFilter(this);
    this->listView->setVisible(false);
    update();
}

void ComponentMenuItem::initialListView()
{
    // 创建模型
    this->model = new ComponentModel(this);

    // 创建视图
    listView->setModel(model);

    // 设置委托
    // this->delegate = new ComponentDelegate(this);
    this->delegate = new ComponentDelegate(this->listView);
    listView->setItemDelegate(delegate);
    // 优化性能
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    listView->setDragDropMode(QAbstractItemView::DragOnly);
    listView->setMouseTracking(true);
    listView->setDragEnabled(true);
}

void ComponentMenuItem::setIndex(const QModelIndex index)
{
    this->index=index;
}

bool ComponentMenuItem::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == nameLabel && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            emit itemClick(this->index);
            return true; // 事件已处理
        }
    }
    return QWidget::eventFilter(watched, event); // 其他事件交给父类处理
}
