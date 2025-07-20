#include "Platform.h"

Platform::Platform(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : Item(parent, ""), width(width), height(height) {
    setPos(x, y);
    setZValue(1); 
}

QRectF Platform::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}