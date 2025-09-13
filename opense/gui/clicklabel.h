#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>
#include <QPixmap>
#include <QPicture>
class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget *parent = nullptr);
    void setUrl(const QString &url);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString url; // 存储目标URL
};

#endif // CLICKLABEL_H
