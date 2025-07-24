#include "FileTreeView.h"
#include <QMimeData>
#include <QDrag>
#include <QDir>
#include <QDebug>
#include<QApplication>
FileTreeView::FileTreeView(QWidget *parent) : QTreeView(parent) {
    // 基础设置：禁用编辑、启用拖拽
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setDragEnabled(true); // 允许拖拽
    setSelectionMode(QAbstractItemView::SingleSelection); // 单选模式
}

// 设置文件模型（外部传入，用于获取数据）
void FileTreeView::setFileModel(QStandardItemModel *model) {
    m_model = model;
    setModel(model); // 同时设置为视图的模型
}

// 重写鼠标按压事件：记录点击位置和索引
void FileTreeView::mousePressEvent(QMouseEvent *event) {

    qDebug() << "FileTreeView 捕获鼠标按压事件";
    // 先调用父类方法，确保选中项等原生功能正常
    QTreeView::mousePressEvent(event);

    // 只处理左键点击
    if (event->button() == Qt::LeftButton) {
        // 获取点击位置的索引（当前视图的局部坐标）
        m_dragIndex = indexAt(event->pos());
        qDebug()<<m_dragIndex;
        if (m_dragIndex.isValid()&&m_model) {
            // 发射点击信号（供外部处理）
            QString fileName = m_model->data(m_dragIndex, Qt::DisplayRole).toString();
            qDebug() << "显示文本：" << fileName;
            // 记录拖拽起始位置
            m_dragStartPos = event->pos();
        }
    }
}

// 重写鼠标移动事件：触发拖拽
void FileTreeView::mouseMoveEvent(QMouseEvent *event) {
    qDebug() << "FileTreeView 捕获鼠标移动事件";

    // 检查条件：左键按住 + 有效索引 + 移动距离足够
    if (!(event->buttons() & Qt::LeftButton) || !m_dragIndex.isValid()) {
        // 不满足条件，调用父类默认处理
        QTreeView::mouseMoveEvent(event);
        return;
    }

    qDebug()<<(event->pos() - m_dragStartPos).manhattanLength()<<"\n"<<QApplication::startDragDistance();
    // 计算移动距离（避免误触）
    if ((event->pos() - m_dragStartPos).manhattanLength()
        < QApplication::startDragDistance()) {
        QTreeView::mouseMoveEvent(event);
        return;
    }

    // // 构建完整文件路径
    // QString fileName = m_model->data(m_dragIndex, Qt::DisplayRole).toString();
    // QString filePath = "";
    // if (m_model) {
    //     filePath = fileName; // 从当前项开始
    //     QModelIndex parentIndex = m_dragIndex.parent();
    //     // 向上遍历父节点，拼接完整路径
    //     while (parentIndex.isValid()) {
    //         QString parentName = m_model->data(parentIndex, Qt::DisplayRole).toString();
    //         filePath = QDir(parentName).filePath(filePath); // 父目录 + 当前路径
    //         parentIndex = parentIndex.parent();
    //     }
    // }

    // // 发射拖拽开始信号（供外部处理额外逻辑）
    // emit dragStarted(fileName, filePath);

    // // 执行拖拽操作
    // QDrag *drag = new QDrag(this);
    // QMimeData *mimeData = new QMimeData;
    // mimeData->setText(fileName); // 文件名
    // mimeData->setData("application/x-filepath", filePath.toUtf8()); // 完整路径
    // drag->setMimeData(mimeData);

    // // 执行拖拽（复制模式）
    // drag->exec(Qt::CopyAction);
}
