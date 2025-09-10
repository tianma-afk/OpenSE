#include "componentpaneldelegate.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStyle>
#include <QApplication>
ComponentPanelDelegate::ComponentPanelDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}


QSize ComponentPanelDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget* widget = qobject_cast<QListView*>(this->parent())->indexWidget(index);
    if(this->model->isExpand==true){
        if(index==this->model->expandIndex){
            int h=qobject_cast<ComponentMenuItem*>(widget)->model->rowCount()*34;
            return QSize(option.rect.width(), 34+h);
        }
    }

    return QSize(option.rect.width(), 34); // 调整为所需的大小
}

void ComponentPanelDelegate::setModel(ComponentPanelModel *model)
{
    this->model=model;
}
