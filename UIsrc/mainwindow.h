#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fileexplorer.h"
#include<QPlainTextEdit>
#include"TabWidget.h"

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

    //菜单栏
    void createMenu();

    //工具栏
    void createToolBar();
    FileExplorer *fileExplorer;
    bool fileExplorerVisible=true;

    //代码编辑区
    void createCodeEditor();
    QPlainTextEdit *codeEditor;
    TabWidget *tabWidget;

private slots:
    //菜单栏
    void onMenuNewFileTriggered();
    void onMenuOpenFileTriggered();
    void onMenuTerminalTriggered();
    void onMenuMeasureTriggered();
    void onMenuSimulateTriggered();
    //工具栏
    void onFileExplorerTriggered();
    void onRunTriggered();
    //状态栏

    //代码编辑区
    void openFile(const QModelIndex &index);
    QString getFullPath(QStandardItem *item);
    void closeTab(int index);
};
#endif // MAINWINDOW_H
