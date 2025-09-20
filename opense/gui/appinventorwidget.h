#ifndef APPINVENTORWIDGET_H
#define APPINVENTORWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include"gui/workspace.h"
#include"gui/componentpanel.h"
#include"gui/componentlist.h"
#include<gui/propertypanel.h>
#include<QThread>
#include"core/coder.h"
#include"core/inventworker.h"
#include"gui/projectdata.h"
class AppInventorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppInventorWidget(QWidget *parent = nullptr);
    void appInvent();
    void updateData();
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

    //后端
    Coder*coder;
    QThread*inventThread;
    InventWorker*inventWorker;
    ProjectData project;

    void initialUI();
    void initialComponent();
    void initialWorkspace();
    void initialList();
    void initialProperty();
    void initialData();
    void initialCore();
    void initialConnect();

signals:
    void signal_inventOutput(const QString &output);
public slots:
    void onInventWorkerOutput(const QString &output);
    void onInventWorkerError(const QString &error);
    void onInventWorkerFinished(int exitCode);
};

#endif // APPINVENTORWIDGET_H
