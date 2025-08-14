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
    if(this->model->isExpand==true){
        if(index==this->model->expandIndex){
            return QSize(option.rect.width(), 134);
        }
    }
    return QSize(option.rect.width(), 34); // 调整为所需的大小
}

void ComponentPanelDelegate::setModel(ComponentPanelModel *model)
{
    this->model=model;
}

bool ComponentPanelDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        // 检查点击位置是否在项目范围内
        if (option.rect.contains(mouseEvent->pos())) {
            emit itemClicked(index);
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
