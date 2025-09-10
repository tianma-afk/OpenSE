#ifndef PROPERTYPANEL_H
#define PROPERTYPANEL_H

#include <QWidget>

class PropertyPanel : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyPanel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*event)override;
signals:
};

#endif // PROPERTYPANEL_H
