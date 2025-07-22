#ifndef BULLETPROJECTILE2_H
#define BULLETPROJECTILE2_H

#include "Projectile.h"

class BulletProjectile2 : public Projectile {
    Q_OBJECT
    
public:
    explicit BulletProjectile2(QGraphicsItem* parent = nullptr);
    
    void launch(const QPointF& startPos, bool facingLeft, Character* shooter) override;
};

#endif