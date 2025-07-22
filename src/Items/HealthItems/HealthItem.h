#ifndef HEALTHITEM_H
#define HEALTHITEM_H

#include "../Item.h"

class Character;

class HealthItem : public Item {
public:
    explicit HealthItem(QGraphicsItem *parent, const QString &pixmapPath);
    
    virtual void applyToCharacter(Character* character) = 0;
    virtual int getHealAmount() const { return healAmount; }
    
protected:
    int healAmount = 0;
};

#endif