#ifndef HEALTHDROP_H
#define HEALTHDROP_H

#include "DroppableItem.h"

class HealthItem;

class HealthDrop : public DroppableItem {
public:
    HealthDrop(ItemType type, const QPointF& startPos, QGraphicsItem* parent = nullptr);
    void applyToCharacter(Character* character) override;
    
private:
    HealthItem* createHealthItem(Character* parent);
};

#endif