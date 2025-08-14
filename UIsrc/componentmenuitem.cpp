#include "componentmenuitem.h"


ComponentMenuItem::ComponentMenuItem(QWidget *parent):QWidget(parent)
{
    this->initialUI();
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

    this->nameLabel=new QLabel(this);
    this->vLayout->addWidget(this->nameLabel);

    this->listView=new QListView(this);
    this->vLayout->addWidget(this->listView);
}

void ComponentMenuItem::initialData()
{
    this->nameLabel->setText(this->menuName);
    qDebug()<<"更新";
    update();
}
