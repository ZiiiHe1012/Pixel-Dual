#ifndef BANDAGE_H
#define BANDAGE_H

#include "HealthItem.h"

class Bandage : public HealthItem {
public:
    explicit Bandage(QGraphicsItem *parent = nullptr);
    
    void applyToCharacter(Character* character) override;
};

#endif