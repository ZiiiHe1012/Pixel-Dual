#include "Adrenaline.h"
#include "../Characters/Character.h"

Adrenaline::Adrenaline(QGraphicsItem *parent) 
    : HealthItem(parent, ":/Items/Equipment/adrenaline.png") {
    healAmount = 30;  // 恢复血量
}

void Adrenaline::applyToCharacter(Character* character) {
    if (character) {
        character->applyAdrenalineEffect();
    }
}