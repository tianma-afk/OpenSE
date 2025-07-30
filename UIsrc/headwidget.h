#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QWidget>
#include<QPainter>
#include<QPushButton>
#include<QCheckBox>
#include<QMouseEvent>
#include<QStyleOptionButton>
#include<QApplication>
#include<QStyleOption>
class HeadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HeadWidget(QWidget *parent = nullptr);

private:
    bool checkState=false;
    void paintEvent(QPaintEvent*event)override;
    void mousePressEvent(QMouseEvent *event)override;
    QSize sizeHint() const override;

signals:
    void checkedChanged(bool checked);

public slots:
    void checkStateChangeForSingle(bool checked);
};

#endif // HEADWIDGET_H
