#include "Medkit.h"
#include "../Characters/Character.h"

Medkit::Medkit(QGraphicsItem *parent) 
    : HealthItem(parent, ":/Items/Equipment/medkit.png") {
    healAmount = 40;  // 恢复血量
}

void Medkit::applyToCharacter(Character* character) {
    if (character) {
        character->heal(healAmount);
    }
}