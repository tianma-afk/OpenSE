#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QWidget>

class ComponentList : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentList(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*event)override;
signals:
};

#endif // COMPONENTLIST_H
