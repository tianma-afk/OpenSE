#include "clicklabel.h"

ClickLabel::ClickLabel(const QString &url, QWidget *parent)
    : QLabel(parent), url(url) {
    // 设置鼠标悬停时显示手型光标
    setCursor(Qt::PointingHandCursor);
}

void ClickLabel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        // 打开指定URL
        QDesktopServices::openUrl(QUrl(url));
    }
    QLabel::mousePressEvent(event);
}
