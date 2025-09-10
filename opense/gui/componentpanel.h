#ifndef COMPONENTPANEL_H
#define COMPONENTPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include<QListView>
#include"gui/componentpaneldelegate.h"
#include"componentmenuitem.h"
#include"componentpanelmodel.h"
class ComponentPanel:public QWidget
{
    Q_OBJECT
public:
    ComponentPanel(QWidget *parent = nullptr);
private:
    QVBoxLayout*vLayout;
    QListView *listView;
    ComponentPanelDelegate*delegate;
    ComponentPanelModel*model;

    void initialUI();
    void initialData();
    void paintEvent(QPaintEvent*event)override;
private slots:
    void onItemClicked(const QModelIndex &index);
    void onItemAdded(const QModelIndex &parent);
};

#endif // COMPONENTPANEL_H
