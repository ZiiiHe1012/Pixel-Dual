#ifndef WEAPON_H
#define WEAPON_H

#include "../Item.h"
#include <QTimer>

class Character;

class Weapon : public Item {
public:
    explicit Weapon(QGraphicsItem *parent, const QString &pixmapPath);
    
    virtual void attack();
    virtual void stopAttack();
    virtual int getDamage() const { return damage; }
    virtual qreal getRange() const { return range; }
    
    void setOwner(Character* character) { owner = character; }
    Character* getOwner() const { return owner; }
    
    bool isAttacking() const { return attacking; }

    // 使用次数限制
    bool isUsedUp() const { return usageLimit > 0 && usageCount >= usageLimit; }
    void resetUsage() { usageCount = 0; }
    int getRemainingUses() const { return usageLimit > 0 ? usageLimit - usageCount : -1; }

    bool hasDealtDamage = false; // 该次点击是否已经造成伤害
    
protected:
    int damage = 10; // 攻击伤害
    qreal range = 50.0; // 攻击范围
    int usageLimit = 0;  // 使用次数限制，0表示无限使用
    int usageCount = 0;  // 当前使用次数
    bool attacking = false;
    Character* owner = nullptr;
    QTimer* attackTimer = nullptr;
};

#endif