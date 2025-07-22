#include "WeaponDrop.h"
#include "../Characters/Character.h"
#include "../Weapons/Knife.h"
#include "../Weapons/SolidBall.h"
#include "../Weapons/Rifle.h"
#include "../Weapons/Sniper.h"

WeaponDrop::WeaponDrop(ItemType type, const QPointF& startPos, QGraphicsItem* parent)
    : DroppableItem(type, startPos, parent) {
    
    QString iconPath;
    switch(type) {
        case WEAPON_KNIFE:
            iconPath = ":/Items/Equipment/knife.png";
            break;
        case WEAPON_SOLIDBALL:
            iconPath = ":/Items/Equipment/ball.png";
            break;
        case WEAPON_RIFLE:
            iconPath = ":/Items/Equipment/rifle.png";
            break;
        case WEAPON_SNIPER:
            iconPath = ":/Items/Equipment/sniper.png";
            break;
        default:
            break;
    }
    
    if (!iconPath.isEmpty()) {
        pixmapItem = new QGraphicsPixmapItem(QPixmap(iconPath), this);
        pixmapItem->setScale(0.8);
    }
}

void WeaponDrop::applyToCharacter(Character* character) {
    Weapon* weapon = createWeapon(character);
    if (weapon) {
        character->switchToWeapon(weapon);
    }
}

Weapon* WeaponDrop::createWeapon(Character* parent) {
    switch(itemType) {
        case WEAPON_KNIFE:
            return new Knife(parent);
        case WEAPON_SOLIDBALL:
            return new SolidBall(parent);
        case WEAPON_RIFLE:
            return new Rifle(parent);
        case WEAPON_SNIPER:
            return new Sniper(parent);
        default:
            return nullptr;
    }
}