#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Item.h"

class Terrain : public Item {
public:
    enum TerrainType { // 类型
        NORMAL,
        GRASS,
        ICE
    };
    Terrain(qreal x, qreal y, qreal width, qreal height, TerrainType type, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    TerrainType getType() const { return terrainType; }
protected:
    qreal width;
    qreal height;
    TerrainType terrainType;
};

#endif