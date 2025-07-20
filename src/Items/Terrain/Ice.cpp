#include "Ice.h"
#include <QPainter>

IceTerrain::IceTerrain(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : Terrain(x, y, width, height, ICE, parent) {
}

void IceTerrain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
}