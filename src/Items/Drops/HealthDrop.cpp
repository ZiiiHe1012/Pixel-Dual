#include "HealthDrop.h"
#include "../Characters/Character.h"
#include "../HealthItems/Bandage.h"

HealthDrop::HealthDrop(ItemType type, const QPointF& startPos, QGraphicsItem* parent)
    : DroppableItem(type, startPos, parent) {
    
    QString iconPath;
    switch(type) {
        case HEALTH_BANDAGE:
            iconPath = ":/Items/HealthItems/Bandage.png";
            break;
        // 其他治疗物品以后添加
        default:
            break;
    }
    
    if (!iconPath.isEmpty()) {
        pixmapItem = new QGraphicsPixmapItem(QPixmap(iconPath), this);
        pixmapItem->setScale(0.8);
    }
}

void HealthDrop::applyToCharacter(Character* character) {
    HealthItem* item = createHealthItem(character);
    if (item) {
        item->applyToCharacter(character);
        delete item;  // 使用后删除
    }
}

HealthItem* HealthDrop::createHealthItem(Character* parent) {
    switch(itemType) {
        case HEALTH_BANDAGE:
            return new Bandage(parent);
        // 其他治疗物品以后添加
        default:
            return nullptr;
    }
}