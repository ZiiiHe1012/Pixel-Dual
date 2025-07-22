#ifndef ADRENALINE_H
#define ADRENALINE_H

#include "HealthItem.h"

class Adrenaline : public HealthItem {
public:
    explicit Adrenaline(QGraphicsItem *parent = nullptr);
    
    void applyToCharacter(Character* character) override;
};

#endif