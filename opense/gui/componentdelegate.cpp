#include "componentdelegate.h"
#include "componentmodel.h"
#include <QApplication>
#include<QMouseEvent>
#include<QListView>
#include<QToolTip>
ComponentDelegate::ComponentDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

// 绘制列表项
void ComponentDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save(); // 保存当前绘制状态

    // 获取绘制区域
    QRect rect = option.rect;

    // 根据是否有鼠标悬停，绘制高亮背景
    if (option.state & QStyle::State_MouseOver) {
        QRect highlightRect = option.rect;
        painter->fillRect(highlightRect, QColor(255, 240, 176));
    }

    // 绘制边框
    painter->setPen(QPen(QColor(19,19,19), 1));
    painter->drawLine(rect.bottomLeft(), rect.bottomRight());

    // 从模型获取数据
    QString name = index.data(ComponentModel::NameRole).toString();
    QIcon icon = index.data(ComponentModel::IconRole).value<QIcon>();

    // 绘制图标
    QRect iconRect =QRect(rect.left()+10,rect.top()+9,18,18);// 图标位置和大小
    if (!icon.isNull()) {
        icon.paint(painter, iconRect, Qt::AlignCenter);
    }

    // 绘制文本（组件名称）
    QRect textRect = rect.adjusted(50, 0, 0, 0); // 文本位置（图标右侧）
    QPen textPen = QPen(QColor(19,19,19),1);
    painter->setPen(textPen);
    painter->drawText(textRect, Qt::AlignVCenter | Qt::TextSingleLine, name);

    QRect helpRect = QRect(rect.right() - 20,rect.top()+10,16,16);
    QIcon help = QIcon("://icons/help.png");
    if (!help.isNull()) {
        help.paint(painter,helpRect,Qt::AlignCenter);
    }

    painter->restore(); // 恢复绘制状态
}

// 定义每个列表项的大小
QSize ComponentDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(option.rect.width(), 34); // 高度34像素，宽度使用可用宽度
}

bool ComponentDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    static QPoint dragStartPos; // 记录拖拽起始位置
    static bool isDragging = false;

    // 鼠标按下：记录起始位置
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            dragStartPos = mouseEvent->pos(); // 记录点击位置
            isDragging = false;
        }
    }

    // 鼠标移动：判断是否触发拖拽（移动距离超过阈值）
    else if (event->type() == QEvent::MouseMove) {
        if (!isDragging) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            // 计算移动距离（曼哈顿距离，避免微小移动触发拖拽）
            int distance = (mouseEvent->pos() - dragStartPos).manhattanLength();
            if (distance >= QApplication::startDragDistance()) {
                // 启动拖拽
                startDrag(index);
                isDragging = true;
            }
        }
    }


    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        // 计算 icon 区域
        QRect rect = option.rect;
        QRect helpRect = QRect(rect.right() - 20,rect.top()+10,16,16);

        // 如果鼠标在 icon 区域内，显示提示
        if (helpRect.contains(mouseEvent->pos())) {
            QString tip = index.data(ComponentModel::DescriptionRole).toString();
            QToolTip::showText(mouseEvent->globalPosition().toPoint(), tip); // 显示 ToolTip
        } else {
            QToolTip::hideText(); // 离开区域时隐藏
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void ComponentDelegate::startDrag(const QModelIndex &index) const
{
    // 获取组件类型（从 model 中取 Qt::UserRole 存储的数据）
    QString componentType = index.data(ComponentModel::NameRole).toString();
    if (componentType.isEmpty()) return;
    // 创建 mime 数据
    QMimeData *mimeData = new QMimeData();
    mimeData->setText(componentType); // 用文本传递类型，方便工作区解析
    // 创建拖拽对象
    QDrag *drag = new QDrag(const_cast<ComponentDelegate*>(this));
    drag->setMimeData(mimeData);
    // 设置拖拽时的图标
    QIcon icon = index.data(ComponentModel::IconRole).value<QIcon>();
    drag->setPixmap(icon.pixmap(32, 32)); // 拖拽时显示的小图标
    // 执行拖拽（支持复制模式，对应 APP Inventor 的"复制组件"逻辑）
    drag->exec(Qt::CopyAction);
}
