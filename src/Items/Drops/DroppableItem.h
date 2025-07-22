#ifndef DROPPABLEITEM_H
#define DROPPABLEITEM_H

#include "../Item.h"
#include <QTimer>

class Character;
class Platform;

class DroppableItem : public Item {
public:
    enum ItemType {
        // 武器
        WEAPON_KNIFE,
        WEAPON_SOLIDBALL,
        WEAPON_RIFLE,
        WEAPON_SNIPER,
        // 治疗物品
        HEALTH_BANDAGE, 
        HEALTH_MEDKIT,      
        HEALTH_ADRENALINE   
    };
    
    DroppableItem(ItemType type, const QPointF& startPos, QGraphicsItem* parent = nullptr);
    
    ItemType getType() const { return itemType; }
    virtual void applyToCharacter(Character* character) = 0;
    
    void updatePhysics(qint64 deltaTime, qreal groundHeight, const QList<Platform*>& platforms);
    bool isGrounded() const { return grounded; }
    
protected:
    ItemType itemType;
    QPointF velocity;
    bool grounded = false;
    qreal gravity = 0.001;
};

#endif