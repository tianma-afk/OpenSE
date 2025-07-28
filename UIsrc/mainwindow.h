#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"projectwidget.h"
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

    //状态
    bool isSPHelperHidden=true;

    //菜单栏
    void createMenu();

    //主页面
    void initialWidget();

private slots:
    //菜单栏
    void onMenuSerialPortTriggered();


    //状态栏

};
#endif // MAINWINDOW_H
