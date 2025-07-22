#ifndef RIFLE_H
#define RIFLE_H

#include "Weapon.h"

class Rifle : public Weapon {
    Q_OBJECT
    
public:
    explicit Rifle(QGraphicsItem *parent = nullptr);
    
    void attack() override;
    void stopAttack() override;
    
private:
    qint64 lastShotTime = 0;
    qint64 shotInterval = 150;  // 射击间隔
};

#endif