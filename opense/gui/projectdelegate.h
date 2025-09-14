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
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override ;
signals:
    void singleCheckedChange(bool checked);
    void openProject();
public slots:
};

#endif // PROJECTDELEGATE_H
