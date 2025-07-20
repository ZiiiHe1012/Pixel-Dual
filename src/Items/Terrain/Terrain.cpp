#include "Terrain.h"

Terrain::Terrain(qreal x, qreal y, qreal width, qreal height, TerrainType type, QGraphicsItem *parent)
    : Item(parent, ""), width(width), height(height), terrainType(type) {
    setPos(x, y);
    setZValue(0); 
}

QRectF Terrain::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void Terrain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
}