#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include"wsscene.h"
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QHBoxLayout>
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

    // 可拖拽的组件项（继承自QGraphicsItem）
    class Component : public QGraphicsItem {
    public:
        explicit Component(const QString &type);

        // 必须实现的纯虚函数：定义组件边界
        QRectF boundingRect() const override;
        // 必须实现的纯虚函数：绘制组件外观
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    private:
        QString type;    // 组件类型（如"Button"、"Label"）
        QSizeF size;     // 组件大小
        QColor color;    // 组件背景色
        QString text;    // 组件显示文本
    };
signals:
};

#endif // WORKSPACE_H
