#ifndef MEDKIT_H
#define MEDKIT_H

#include "HealthItem.h"

class Medkit : public HealthItem {
public:
    explicit Medkit(QGraphicsItem *parent = nullptr);
    
    void applyToCharacter(Character* character) override;
};

#endif