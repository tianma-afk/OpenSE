#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"projectwidget.h"
#include"appinventorwidget.h"
#include"clicklabel.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //UI组件
    ProjectWidget *projectWidget=nullptr;
    ClickLabel *githubLabel;
    QWidget *SPHelper=nullptr;
    /*AppInventorWidget*/QWidget*inventor=nullptr;
    //状态
    bool isSPHelperHidden=true;
    bool isInventorHidden=true;
    //菜单栏
    void createMenu();

    //主页面
    void initialWidget();


    //其他函数
    void floatWidget(QWidget*widget,bool isToFloat);
    void openProject();

private slots:
    //菜单栏
    void onMenuMyProjectsTriggered();
    void onMenuSerialPortTriggered();


    //状态栏

};
#endif // MAINWINDOW_H
