#ifndef PROJECTDELEGATE_H
#define PROJECTDELEGATE_H

#include <QApplication>
#include <QCheckBox>
#include <QListView>
#include <QPainter>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QAbstractListModel>
#include <QHash>
#include <QVariant>
#include<QMouseEvent>
class ProjectDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ProjectDelegate(QObject* parent = nullptr);

    // 绘制列表项
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;


    // 处理事件，如复选框的点击
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

    // 提供项的大小提示
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override ;
};

#endif // PROJECTDELEGATE_H
