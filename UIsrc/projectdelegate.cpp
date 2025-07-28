#include "projectdelegate.h"

ProjectDelegate::ProjectDelegate(QObject* parent): QStyledItemDelegate(parent) {}

// 绘制列表项
void ProjectDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const{
    QStyleOptionButton buttonOption;
    QRect buttonRect = QRect(option.rect.right() - 80, option.rect.y() + 1, 78, option.rect.height() - 2);
    buttonOption.rect = buttonRect;

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
        painter->fillRect(highlightRect, option.palette.highlight());
    }

    // 绘制复选框
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxOption, painter);

    // 绘制按钮
    buttonOption.text = "按钮";
    QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);

    // 绘制文本
    QRect textRect = option.rect.adjusted(checkboxRect.width() + 10, 0, -buttonRect.width() - 10, 0);
    painter->drawText(textRect, Qt::AlignVCenter, index.data().toString());

    painter->restore();
}

// 处理事件，如复选框的点击
bool ProjectDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)  {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* mouseEvent = (QMouseEvent*)event;
        QRect buttonRect = QRect(option.rect.right() - 80, option.rect.y() + 5, 70, option.rect.height() - 10);
        QRect checkboxRect = QRect(option.rect.x() + 5, option.rect.y() + 5, option.rect.height() - 10, option.rect.height() - 10);

        if (buttonRect.contains(mouseEvent->pos())) {
            // 按钮被点击
            qDebug() << "按钮点击，项：" << index.row();
        } else if (checkboxRect.contains(mouseEvent->pos())) {
            // 切换复选框状态
            bool checked = !index.data(Qt::CheckStateRole).toBool();
            model->setData(index, checked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
            qDebug() << "勾选checkbox，项：" << index.row();
        }
        return true; // 事件已处理
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

// 提供项的大小提示
QSize ProjectDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const{
    return QSize(option.rect.width(), 34); // 调整为所需的大小
}
