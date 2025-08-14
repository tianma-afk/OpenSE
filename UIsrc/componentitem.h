#ifndef COMPONENTITEM_H
#define COMPONENTITEM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QMouseEvent>
#include<QPixmap>
class ComponentItem : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentItem(QWidget *parent = nullptr);
    const static int height=20;

    void setTitle(const QString title);
    void setPicmap(const QPixmap pic);
protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
    QString title;
    QPixmap pic;
signals:
};

#endif // COMPONENTITEM_H
