#ifndef WSSCENE_H
#define WSSCENE_H

#include <QGraphicsScene>
#include <QWidget>

class WSScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit WSScene(QObject *parent = nullptr);
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // WSSCENE_H
