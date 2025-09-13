#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent)
    : QLabel(parent){
    setCursor(Qt::PointingHandCursor);
}

void ClickLabel::setUrl(const QString &url)
{
    this->url=url;
}

void ClickLabel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        QDesktopServices::openUrl(QUrl(url));
    }
    QLabel::mousePressEvent(event);
}
