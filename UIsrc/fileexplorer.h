#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H
#include <QDockWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include<QApplication>
#include"filetreeview.h"
class FileExplorer : public QDockWidget {
    Q_OBJECT
public:
    explicit FileExplorer(QWidget *parent = nullptr);

    void initData();
    QString rootPath=nullptr;
    FileTreeView *treeView;
    QStandardItemModel *model;


private:
    QPoint dragStartPosition;  // 拖动起始位置
    void buildFileSystemTree(const QString &path, QStandardItem *parentItem);
    void initUI();

};

#endif // FILEEXPLORER_H

