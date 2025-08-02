#include "projectdelegate.h"

ProjectDelegate::ProjectDelegate(QObject* parent): QStyledItemDelegate(parent) {}

// 绘制列表项
void ProjectDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const{
    // QStyleOptionButton buttonOption;
    // QRect buttonRect = QRect(option.rect.right() - 80, option.rect.y() + 1, 78, option.rect.height() - 2);
    // buttonOption.rect = buttonRect;

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

    if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(option.rect, option.palette.light());
    }
    // 根据是否有鼠标悬停，绘制高亮背景
    if (option.state & QStyle::State_MouseOver) {
        QRect highlightRect = option.rect;
        painter->fillRect(highlightRect, QColor(255, 240, 176));
    }

    // 绘制复选框
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxOption, painter);

    // // 绘制按钮
    // buttonOption.text = "按钮";
    // QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);

    // 绘制文本
    QRect nameTextRect = option.rect.adjusted(checkboxRect.width() + 10, 0, - 200, 0);
    painter->drawText(nameTextRect, Qt::AlignVCenter, this->model->getProjectData(index,"projectName").toString());

    QRect createTimeTextRect = option.rect.adjusted(option.rect.right()-350, 0, -150, 0);
    painter->drawText(createTimeTextRect, Qt::AlignVCenter, this->model->getProjectData(index,"createTime").toString());

    QRect modifyTimeTextRect = option.rect.adjusted(option.rect.right()-150, 0, 0, 0);
    painter->drawText(modifyTimeTextRect, Qt::AlignVCenter, this->model->getProjectData(index,"modifyTime").toString());

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

void ProjectDelegate::setModel(ProjectListModel *model)
{
    this->model=model;
}


void ProjectDelegate::checkAllchanged(bool checked)
{
    // 遍历所有行，更新选中状态
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, 0); // 假设第0列存储复选框状态
        if (index.isValid()) {
            // 设置所有项的选中状态
            model->setData(index,
                           checked ? Qt::Checked : Qt::Unchecked,
                           Qt::CheckStateRole);
        }
    }
}
