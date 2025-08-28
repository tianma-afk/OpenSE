#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QTreeView>
#include<QPushButton>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QVector>
#include"component.h"
class ComponentList : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentList(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*event)override;
private:
    QVBoxLayout* vLayout;
    QTreeView* treeView;
    QHBoxLayout* hLayout;
    QPushButton*btn_changeName;
    QPushButton*btn_delete;
    QStandardItemModel* m_standardItemModel;
    QStandardItem* root;
    QVector<QStandardItem*>screens;
    void initialUI();
    void initialData();
signals:
public slots:
    void on_treeView_currentChanged(const QModelIndex& current, const QModelIndex& previous);
    void on_addItemInList(QStandardItem*parent,QStandardItem*self);
};

#endif // COMPONENTLIST_H
