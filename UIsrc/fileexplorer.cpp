#include "fileexplorer.h"
#include <QTransform>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
#include <QFileInfo>
#include <QDir>
#include<QDebug>
FileExplorer::FileExplorer(QWidget *parent) : QDockWidget("文件资源管理器", parent) {
    initUI();
    if(this->rootPath!=nullptr)
    {
        initData();
    }

}


void FileExplorer::initUI() {
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    treeView = new FileTreeView(this);
    treeView->setHeaderHidden(true);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    setWidget(treeView);
}

void FileExplorer::initData() {
    model = new QStandardItemModel(this);
    treeView->setFileModel(model);
    // 从指定的根路径开始构建文件树
    buildFileSystemTree(rootPath, model->invisibleRootItem());
    treeView->expandAll();
}


void FileExplorer::buildFileSystemTree(const QString &path, QStandardItem *parentItem) {
    QDir dir(path);
    if (!dir.exists()) {
        return; // 路径不存在，直接返回
    }

    // 获取目录下的所有条目（文件和文件夹），并过滤掉.和..
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    for (const QFileInfo &fileInfo : fileInfoList) {
        QStandardItem *item = new QStandardItem;
        if (fileInfo.isDir()) {
            // 如果是文件夹，设置文件夹图标和名称
            item->setIcon(QIcon(":/icons/folder.svg"));
            item->setText(fileInfo.fileName());
            // 递归构建子文件夹的树结构
            buildFileSystemTree(fileInfo.absoluteFilePath(), item);
        } else {
            // 如果是文件，设置文件图标和名称，根据文件后缀区分不同图标
            if (fileInfo.suffix() == "cpp") {
                item->setIcon(QIcon(":/icons/cpp_file.svg"));
            } else if (fileInfo.suffix() == "h") {
                item->setIcon(QIcon(":/icons/header_file.svg"));
            } else if (fileInfo.suffix() == "py") {
                item->setIcon(QIcon(":/icons/python_file.svg"));
            }
            item->setText(fileInfo.fileName());
        }
        parentItem->appendRow(item);
    }
}
