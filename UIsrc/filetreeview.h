#ifndef FILETREEVIEW_H
#define FILETREEVIEW_H

#include <QTreeView>
#include <QMouseEvent>
#include <QStandardItemModel>

class FileTreeView : public QTreeView {
    Q_OBJECT
public:
    explicit FileTreeView(QWidget *parent = nullptr);

    // 设置文件模型（用于获取选中项数据）
    void setFileModel(QStandardItemModel *model);

signals:
    // 自定义信号：当拖拽开始时发射（传递文件名和路径）
    void dragStarted(const QString &fileName, const QString &filePath);

protected:
    // 重写鼠标按压事件（确保捕获）
    void mousePressEvent(QMouseEvent *event) override;
    // 重写鼠标移动事件（触发拖拽）
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QStandardItemModel *m_model = nullptr; // 文件模型指针
    QPoint m_dragStartPos; // 拖拽起始位置
    QModelIndex m_dragIndex; // 拖拽项的索引
};

#endif // FILETREEVIEW_H
