#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QActionGroup>
#include <QToolBar>
#include <QDebug>
#include<QFileDialog>
#include "TabWidget.h"
#include"terminalwidget.h"
#include"measurewidget.h"
#include"simulatewidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenu();
    createToolBar();
    createCodeEditor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu() {
    // 文件菜单
    QMenu *fileMenu = menuBar()->addMenu("文件");
    fileMenu->addAction("新建", this, [=]() {onMenuNewFileTriggered();});
    fileMenu->addAction("打开",this, [=]() {onMenuOpenFileTriggered();});
    fileMenu->addAction("保存", this, []() { /* 保存文件逻辑 */ });
    fileMenu->addSeparator();
    fileMenu->addAction("退出", this, &QMainWindow::close);

    // 编辑菜单
    QMenu *editMenu = menuBar()->addMenu("编辑");
    editMenu->addAction("撤销", this, []() { /* 撤销逻辑 */ });
    editMenu->addAction("重做", this, []() { /* 重做逻辑 */ });
    editMenu->addSeparator();
    editMenu->addAction("剪切", this, []() { /* 剪切逻辑 */ });
    editMenu->addAction("复制", this, []() { /* 复制逻辑 */ });
    editMenu->addAction("粘贴", this, []() { /* 粘贴逻辑 */ });

    // 帮助菜单
    QMenu *helpMenu = menuBar()->addMenu("帮助");
    helpMenu->addAction("关于", this, []() { /* 关于对话框 */ });
    helpMenu->addAction("帮助", this, []() { /* 帮助文档 */ });

    // 外观菜单
    QMenu *viewMenu = menuBar()->addMenu("外观");
    QActionGroup *themeGroup = new QActionGroup(this);
    QAction *lightTheme = themeGroup->addAction("浅色主题");
    QAction *darkTheme = themeGroup->addAction("深色主题");
    lightTheme->setCheckable(true);
    darkTheme->setCheckable(true);
    lightTheme->setChecked(true);
    viewMenu->addActions(themeGroup->actions());

    //窗口菜单
    QMenu *windowMenu=menuBar()->addMenu("窗口");
    windowMenu->addAction("终端",this,[=](){onMenuTerminalTriggered();});
    windowMenu->addAction("测量",this,[=](){onMenuMeasureTriggered();});
    windowMenu->addAction("仿真",this,[=](){onMenuSimulateTriggered();});
    windowMenu->addAction("串口",this,[](){/*显示串口窗口*/});
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar=new QToolBar("主工具栏");
    this->addToolBar(Qt::LeftToolBarArea,toolBar);
    toolBar->setIconSize(QSize(32,32));

    //文件资源管理器
    QAction*fileAction=new QAction("文件资源管理",this);
    fileAction->setIcon(QIcon(":/icons/fileAction.svg"));
    connect(fileAction, &QAction::triggered, this, &MainWindow::onFileExplorerTriggered);
    toolBar->addAction(fileAction);
    fileExplorer=new FileExplorer(this);
    addDockWidget(Qt::LeftDockWidgetArea, fileExplorer);

    //运行与调试
    QAction*runAction=new QAction("运行",this);
    runAction->setIcon(QIcon(":/icons/runAction.svg"));
    connect(runAction, &QAction::triggered, this, &MainWindow::onRunTriggered);
    toolBar->addAction(runAction);
}

void MainWindow::createCodeEditor()
{
    tabWidget = new TabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    setCentralWidget(tabWidget);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(fileExplorer->treeView, &QTreeView::clicked, this, &MainWindow::openFile);
}

void MainWindow::onMenuNewFileTriggered()
{

}

void MainWindow::onMenuOpenFileTriggered()
{
    QString folderPath = QFileDialog::getExistingDirectory(
        nullptr,                   // 父窗口，设为nullptr表示没有父窗口
        "选择文件夹",              // 对话框标题
        QDir::homePath(),          // 默认打开的目录（这里使用用户主目录）
        QFileDialog::ShowDirsOnly  // 只显示目录
        );
    fileExplorer->rootPath=folderPath;
    fileExplorer->initData();
}

void MainWindow::onMenuTerminalTriggered()
{
    TerminalWidget *terminalTab=new TerminalWidget(fileExplorer->rootPath);
    // 添加终端到标签页
    int tabIndex=tabWidget->addTab(terminalTab,"terminal",fileExplorer->rootPath,TabWidget::terminal);
    tabWidget->setCurrentIndex(tabIndex);
}

void MainWindow::onMenuMeasureTriggered()
{
    MeasureWidget *measureTab=new MeasureWidget();
    //添加测量到标签页
    int tabIndex=tabWidget->addTab(measureTab,"measure","measure",TabWidget::measure);
    tabWidget->setCurrentIndex(tabIndex);
}

void MainWindow::onMenuSimulateTriggered()
{
    SimulateWidget *simulateTab=new SimulateWidget();
    //添加仿真到标签页
    int tabIndex=tabWidget->addTab(simulateTab,"simulate","simulate",TabWidget::simulate);
    tabWidget->setCurrentIndex(tabIndex);
}

void MainWindow::onFileExplorerTriggered()
{
    fileExplorerVisible = !fileExplorerVisible;

    if (fileExplorerVisible) {
        fileExplorer->show();
    } else {
        fileExplorer->hide();
    }
}

void MainWindow::onRunTriggered()
{

}

//打开标签页
void MainWindow::openFile(const QModelIndex &index) {
    // 获取选中的文件路径
    QStandardItem *item = fileExplorer->model->itemFromIndex(index);
    if (!item) return;

    // 构建完整路径
    QString filePath = getFullPath(item);

    // 如果文件已在标签页中打开，则切换到该标签页
    int tabIndex = tabWidget->findTabByFilePath(filePath);
    if (tabIndex != -1) {
        tabWidget->setCurrentIndex(tabIndex);
        return;
    }

    // 打开新文件
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        // 创建新的编辑器
        QPlainTextEdit *editor = new QPlainTextEdit(tabWidget);
        editor->setPlainText(content);

        // 设置编辑器字体
        QFont font("Consolas", 12);
        font.setStyleHint(QFont::Monospace);
        editor->setFont(font);

        // 添加到标签页
        int tabIndex=tabWidget->addTab(editor, QFileInfo(filePath).fileName(), filePath);
        tabWidget->setCurrentIndex(tabIndex);
    }
}

QString MainWindow::getFullPath(QStandardItem *item) {
    QString path = item->text();
    QStandardItem *parent = item->parent();

    while (parent) {
        path = parent->text() + "/" + path;
        parent = parent->parent();
    }

    // 添加根目录
    return fileExplorer->rootPath + "/" + path;
}

// 关闭标签页
void MainWindow::closeTab(int index) {
    tabWidget->removeTab(index);
}
