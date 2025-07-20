#ifndef GRASS_H
#define GRASS_H

#include "Terrain.h"

class GrassTerrain : public Terrain {
public:
    GrassTerrain(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif