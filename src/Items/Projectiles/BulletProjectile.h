#ifndef BULLETPROJECTILE_H
#define BULLETPROJECTILE_H

#include "Projectile.h"

class BulletProjectile : public Projectile {
    Q_OBJECT
    
public:
    explicit BulletProjectile(QGraphicsItem* parent = nullptr);
    
    void launch(const QPointF& startPos, bool facingLeft, Character* shooter) override;
};

#endif