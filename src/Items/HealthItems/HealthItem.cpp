#include "HealthItem.h"
#include "../Characters/Character.h"

HealthItem::HealthItem(QGraphicsItem *parent, const QString &pixmapPath) 
    : Item(parent, pixmapPath) {
    setScale(0.8);
}