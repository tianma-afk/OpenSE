#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include<QGraphicsScene>
#include<QGraphicsView>
class WorkSpace : public QWidget
{
    Q_OBJECT
public:
    explicit WorkSpace(QWidget *parent = nullptr);

private:
    QGraphicsScene*scene;
    QGraphicsView*view;

    void paintEvent(QPaintEvent*event)override;

    void initialUI();
    void initialData();
signals:
};

#endif // WORKSPACE_H
