#ifndef BALLPROJECTILE_H
#define BALLPROJECTILE_H

#include "Projectile.h"

class BallProjectile : public Projectile {
    Q_OBJECT
public:
    explicit BallProjectile(QGraphicsItem* parent = nullptr);
    void launch(const QPointF& startPos, bool facingLeft, Character* shooter) override;
protected:
    void updatePosition() override;
private:
    qreal rotationSpeed = 0;
};

#endif