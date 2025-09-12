#ifndef COMPONENTMENUITEM_H
#define COMPONENTMENUITEM_H

#include <QWidget>
#include<QMouseEvent>
#include<QStandardItem>
#include<QLabel>
#include<QVBoxLayout>
#include<QListView>
#include "componentmodel.h"
#include"componentdelegate.h"
class ComponentMenuItem:public QWidget
{
    Q_OBJECT
public:
    ComponentMenuItem(QWidget*parent=nullptr);

    QString getMenuName()const;
    void setMenuName(const QString menuName);
    void initialUI();
    void initialData();
    void initialListView();
    void setIndex(const QModelIndex index);

    QVBoxLayout*vLayout;
    QLabel*nameLabel;
    QListView*listView;
    ComponentModel* model;
    ComponentDelegate*delegate;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;


private:
    QString menuName;
    QModelIndex index;


signals:
    void itemClick(QModelIndex &index);
};

#endif // COMPONENTMENUITEM_H
