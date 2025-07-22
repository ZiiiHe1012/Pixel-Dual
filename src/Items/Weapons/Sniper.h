#ifndef SNIPER_H
#define SNIPER_H

#include "Weapon.h"

class Sniper : public Weapon {
    Q_OBJECT
    
public:
    explicit Sniper(QGraphicsItem *parent = nullptr);
    
    void attack() override;
    void stopAttack() override;
    
private:
    qint64 lastShotTime = 0;
    qint64 shotInterval = 1000
    ;  // 射击间隔
};

#endif