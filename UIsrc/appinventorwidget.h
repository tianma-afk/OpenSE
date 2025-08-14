#ifndef APPINVENTORWIDGET_H
#define APPINVENTORWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<workspace.h>
#include<componentpanel.h>
#include<componentlist.h>
#include<propertypanel.h>
class AppInventorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppInventorWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVBoxLayout*vLayout;

    //头部
    QWidget*headWidget;
    QHBoxLayout*headHLayout;
    QLabel*nameLabel;

    //主体
    QWidget*bodyWidget;
    QHBoxLayout*bodyHLayout;

        //组件面板
    QWidget*component;
    QVBoxLayout*comVlayout;
    QLabel*componentName;
    ComponentPanel*cp;

        //工作区
    QWidget*workspace;
    QVBoxLayout*wsVlayout;
    QLabel*workspaceName;
    WorkSpace*ws;

        //组件列表
    QWidget*list;
    QVBoxLayout*listVlayout;
    QLabel*listName;
    ComponentList*cl;

        //属性面板
    QWidget*property;
    QVBoxLayout*proVlayout;
    QLabel*propertyName;
    PropertyPanel*pp;

    void initialUI();
    void initialComponent();
    void initialWorkspace();
    void initialList();
    void initialProperty();
    void initialData();

signals:
};

#endif // APPINVENTORWIDGET_H
