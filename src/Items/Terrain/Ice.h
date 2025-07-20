#ifndef ICE_H
#define ICE_H

#include "Terrain.h"

class IceTerrain : public Terrain {
public:
    IceTerrain(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif