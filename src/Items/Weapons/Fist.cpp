#include "Fist.h"
#include "../Characters/Character.h"
#include <QTransform>

Fist::Fist(QGraphicsItem *parent) 
    : Weapon(parent, ":/Items/Equipment/fist.png") {
    damage = 2;
    range = 60.0;
    setScale(0.5);  // 调整拳头大小
}

void Fist::attack() {
    Weapon::attack();
    if(owner) {
        if(owner->isCrouching) {
            setPos(24, 32);
            setZValue(100); 
        }
        else {
            setPos(24, 22);
        }
    }
}