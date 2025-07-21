#ifndef FIST_H
#define FIST_H

#include "Weapon.h"

class Fist : public Weapon {
public:
    explicit Fist(QGraphicsItem *parent = nullptr);
    
    void attack() override;
};

#endif