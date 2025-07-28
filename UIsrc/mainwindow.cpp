#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QActionGroup>
#include <QToolBar>
#include <QDebug>
#include<QFileDialog>
#include<QPropertyAnimation>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenu();
    initialWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu() {
    QMenuBar *menuBar=new QMenuBar();
    // 项目菜单
    QMenu *fileMenu = menuBar->addMenu("项目");
    fileMenu->addAction("我的项目", this, [=]() {});
    fileMenu->addAction("新项目",this, [=]() {});
    fileMenu->addAction("删除项目", this,[=](){});
    fileMenu->addSeparator();
    fileMenu->addAction("保存项目", this, []() { /* 保存逻辑 */ });

    //构建菜单
    QMenu *buildMenu = menuBar->addMenu("构建");
    buildMenu->addAction("生成app", this, [=]() {});

    //串口菜单
    QMenu*serialPortMenu=menuBar->addMenu("串口");
    serialPortMenu->addAction("串口调试助手",this,[=](){onMenuSerialPortTriggered();});

    // 帮助菜单
    QMenu *helpMenu = menuBar->addMenu("帮助");
    helpMenu->addAction("关于", this, []() { /* 关于对话框 */ });
    helpMenu->addAction("帮助", this, []() { /* 帮助文档 */ });

    this->setMenuBar(menuBar);
}

void MainWindow::initialWidget()
{
    this->projectWidget=new ProjectWidget(this);

    this->setCentralWidget(projectWidget);
    this->githubLabel=new ClickLabel("https://github.com/tianma-afk/OpenSE",this);
    this->githubLabel->setPixmap(QPixmap(":/icons/github.svg"));
    this->statusBar()->addPermanentWidget(this->githubLabel);
}


void MainWindow::onMenuSerialPortTriggered()
{
    if(this->SPHelper==nullptr)
    {
        this->SPHelper=new QWidget(this);
        this->SPHelper->setStyleSheet("background-color: #000000;");
        this->SPHelper->hide();
    }

    if(this->isSPHelperHidden==true)
    {
        this->statusBar()->showMessage("串口助手打开");
        this->isSPHelperHidden=false;
        int statusBarHeight = statusBar()->height();
        int menuBarHeight = menuBar()->height();
        int windowHeight = this->height();

        // 设置SPHelper的初始位置和大小
        this->SPHelper->setGeometry(0, windowHeight - statusBarHeight, this->width(),0);
        this->SPHelper->show();

        // 创建并启动动画，让部件向上移动到菜单栏下方
        QPropertyAnimation *animation = new QPropertyAnimation(this->SPHelper, "geometry");
        animation->setDuration(300); // 动画持续时间，单位毫秒
        animation->setStartValue(QRect(0, windowHeight - statusBarHeight, this->width(), 0));
        animation->setEndValue(QRect(0, menuBarHeight, this->width(), windowHeight - menuBarHeight-statusBarHeight));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }else{
        this->statusBar()->showMessage("串口助手关闭");
        this->isSPHelperHidden=true;
        int statusBarHeight = statusBar()->height();
        int menuBarHeight = menuBar()->height();
        int windowHeight = this->height();

        // 创建并启动动画，让部件向下移动到状态栏位置
        QPropertyAnimation *animation = new QPropertyAnimation(this->SPHelper, "geometry");
        animation->setDuration(300);
        animation->setStartValue(QRect(0, menuBarHeight, this->width(), windowHeight - menuBarHeight-statusBarHeight));
        animation->setEndValue(QRect(0, windowHeight - statusBarHeight, this->width(), 0));
        connect(animation, &QPropertyAnimation::finished, this, [this]() {
            this->SPHelper->hide();
        });
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}


