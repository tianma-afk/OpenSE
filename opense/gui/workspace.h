#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include"wsscene.h"
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QHBoxLayout>
#include"core\componentfactory.h"
#include<QProcess>
class WorkSpace : public QWidget
{
    Q_OBJECT
public:
    explicit WorkSpace(QWidget *parent = nullptr);

protected:
    // 处理拖拽进入事件
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event)override;
    // 处理放置事件
    void dropEvent(QDropEvent *event) override;

private:
    WSScene*scene;
    QGraphicsView*view;
    QRectF screenRect;

    void paintEvent(QPaintEvent*event)override;
    void initialUI();
    void initialData();
    void drawComponent(const QString&componentType,const QPointF&scenePos);
public:
signals:
    void signal_addItemInList(Component*parent,Component*self);
};

#endif // WORKSPACE_H
