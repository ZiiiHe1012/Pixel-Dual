#include "Bandage.h"
#include "../Characters/Character.h"

Bandage::Bandage(QGraphicsItem *parent) 
    : HealthItem(parent, ":/Items/Equipment/bandage.png") {
    healAmount = 20;  // 恢复血量
}

void Bandage::applyToCharacter(Character* character) {
    if (character) {
        character->heal(healAmount);
    }
}