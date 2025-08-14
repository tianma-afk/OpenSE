#ifndef COMPONENTMENUITEM_H
#define COMPONENTMENUITEM_H

#include <QWidget>
#include<QStandardItem>
#include<componentitem.h>
#include<QLabel>
#include<QVBoxLayout>
#include<QListView>
class ComponentMenuItem:public QWidget
{
    Q_OBJECT
public:
    ComponentMenuItem(QWidget*parent=nullptr);
    QVector<ComponentItem*> items;
    QString getMenuName()const;
    void setMenuName(const QString menuName);
    void initialUI();
    void initialData();
private:
    QString menuName;

    QVBoxLayout*vLayout;
    QLabel*nameLabel;
    QListView*listView;
signals:
};

#endif // COMPONENTMENUITEM_H
