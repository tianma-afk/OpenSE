#include "projectdelegate.h"
#include"projectlistmodel.h"
#include"core/projectmanager.h"
ProjectDelegate::ProjectDelegate(QObject* parent): QStyledItemDelegate(parent) {}

// 绘制列表项
void ProjectDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const{

    QStyleOptionButton checkboxOption;
    QRect checkboxRect = QRect(option.rect.x() + 5, option.rect.y() + 5, option.rect.height() - 10, option.rect.height() - 10);
    checkboxOption.rect = checkboxRect;
    checkboxOption.state |= QStyle::State_Enabled;
    if (index.data(Qt::CheckStateRole).toBool()) {
        checkboxOption.state |= QStyle::State_On;
    } else {
        checkboxOption.state |= QStyle::State_Off;
    }

    painter->save();

    // 根据是否有鼠标悬停，绘制高亮背景
    if (option.state & QStyle::State_MouseOver) {
        QRect highlightRect = option.rect;
        painter->fillRect(highlightRect, QColor(255, 240, 176));
    }

    // 绘制复选框
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxOption, painter);

    // 绘制文本
    QRect nameTextRect = option.rect.adjusted(checkboxRect.width() + 10, 0, - 200, 0);
    painter->drawText(nameTextRect, Qt::AlignVCenter, index.data(ProjectListModel::ProjectRoles::NameRole).toString());

    QRect createTimeTextRect = option.rect.adjusted(option.rect.right()-350, 0, -150, 0);
    painter->drawText(createTimeTextRect, Qt::AlignVCenter, index.data(ProjectListModel::ProjectRoles::CreateTimeRole).toString());

    QRect modifyTimeTextRect = option.rect.adjusted(option.rect.right()-150, 0, 0, 0);
    painter->drawText(modifyTimeTextRect, Qt::AlignVCenter, index.data(ProjectListModel::ProjectRoles::ModifyTimeRole).toString());

    painter->restore();
}

// 处理事件，如复选框的点击
bool ProjectDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)  {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* mouseEvent = (QMouseEvent*)event;
        QRect checkboxRect = QRect(option.rect.x() + 5, option.rect.y() + 5, option.rect.height() - 10, option.rect.height() - 10);
        QRect projectNameRect=QRect(checkboxRect.width() + 10, 0, option.rect.right()-checkboxRect.width(), option.rect.height());
        if (checkboxRect.contains(mouseEvent->pos())) {
            // 切换复选框状态
            bool checked = !index.data(Qt::CheckStateRole).toBool();
            model->setData(index, checked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
            if(((ProjectListModel*)model)->getCheckedNum()==((ProjectListModel*)model)->rowCount()){
                emit singleCheckedChange(true);
            }else{
                emit singleCheckedChange(false);
            }
        }else if(projectNameRect.contains(mouseEvent->pos())){
            //打开项目
            qDebug()<<index.data(ProjectListModel::ProjectRoles::NameRole).toString();
            ProjectManager::getInstance().setWorkProject(index.data(ProjectListModel::ProjectRoles::NameRole).toString());
            emit openProject();
        }
        return true; // 事件已处理
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

// 提供项的大小提示
QSize ProjectDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const{
    return QSize(option.rect.width(), 34); // 调整为所需的大小
}
