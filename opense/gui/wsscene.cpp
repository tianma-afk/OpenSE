#include "wsscene.h"
#include<QPainter>
#include<QGraphicsView>
WSScene::WSScene(QObject *parent)
    : QGraphicsScene{parent}
{}

void WSScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(views().count() == 0) return;

    // 加载背景图片
    QPixmap pixmap("://icons/phone.png");
    if (pixmap.isNull()) return; // 检查图片是否加载成功

    // 计算保持比例的缩放尺寸
    QSizeF targetSize = rect.size();
    QSizeF originalSize = pixmap.size();

    // 计算缩放比例（取宽高比例中的较小值，确保图片完全显示在目标区域内）
    qreal scale = targetSize.height() / originalSize.height();

    // 计算缩放后的尺寸
    QSizeF scaledSize = originalSize * scale;

    qreal x=- (scaledSize.width()/ 2);
    qreal y=- (scaledSize.height() / 2);
    QPointF drawPos(x,y);
    // qDebug()<<drawPos;
    // 绘制缩放后的图片
    painter->drawPixmap(QRectF(drawPos, scaledSize), pixmap, QRectF(pixmap.rect()));
}
