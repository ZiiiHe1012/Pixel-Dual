#include "HealthDrop.h"
#include "../Characters/Character.h"
#include "../HealthItems/Bandage.h"
#include "../HealthItems/Medkit.h"
#include "../HealthItems/Adrenaline.h"

HealthDrop::HealthDrop(ItemType type, const QPointF& startPos, QGraphicsItem* parent)
    : DroppableItem(type, startPos, parent) {
    
    QString iconPath;
    switch(type) {
        case HEALTH_BANDAGE:
            iconPath = ":/Items/Equipment/bandage.png";
            break;
        case HEALTH_MEDKIT:
            iconPath = ":/Items/Equipment/medkit.png";
            break;
        case HEALTH_ADRENALINE:
            iconPath = ":/Items/Equipment/adrenaline.png";
            break;
        default:
            break;
    }
    if (!iconPath.isEmpty()) {
        pixmapItem = new QGraphicsPixmapItem(QPixmap(iconPath), this);
        pixmapItem->setScale(1);
    }
}

void HealthDrop::applyToCharacter(Character* character) {
    HealthItem* item = createHealthItem(character);
    if (item) {
        item->applyToCharacter(character);
        delete item;
    }
}

HealthItem* HealthDrop::createHealthItem(Character* parent) {
    switch(itemType) {
        case HEALTH_BANDAGE:
            return new Bandage(parent);
        case HEALTH_MEDKIT:
            return new Medkit(parent);
        case HEALTH_ADRENALINE:
            return new Adrenaline(parent);
        default:
            return nullptr;
    }
}