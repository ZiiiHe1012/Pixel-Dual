#ifndef SOLIDBALL_H
#define SOLIDBALL_H

#include "Weapon.h"

class SolidBall : public Weapon {
    Q_OBJECT
    
public:
    explicit SolidBall(QGraphicsItem *parent = nullptr);
    
    void attack() override;
};

#endif