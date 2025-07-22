#ifndef WEAPONDROP_H
#define WEAPONDROP_H

#include "DroppableItem.h"

class Weapon;

class WeaponDrop : public DroppableItem {
public:
    WeaponDrop(ItemType type, const QPointF& startPos, QGraphicsItem* parent = nullptr);
    void applyToCharacter(Character* character) override;
    
private:
    Weapon* createWeapon(Character* parent);
};

#endif