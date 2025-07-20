#ifndef PLATFORM_H
#define PLATFORM_H

#include "../Item.h"

// 平台类
class Platform : public Item {
public:
    Platform(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal getTopY() const { return pos().y(); }
private:
    qreal width;
    qreal height;
};

#endif