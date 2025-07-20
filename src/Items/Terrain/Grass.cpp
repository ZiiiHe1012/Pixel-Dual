#include "Grass.h"
#include <QPainter>

GrassTerrain::GrassTerrain(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : Terrain(x, y, width, height, GRASS, parent) {
}

void GrassTerrain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
}