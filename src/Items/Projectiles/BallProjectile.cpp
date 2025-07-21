#include "BallProjectile.h"
#include "../Characters/Character.h"

BallProjectile::BallProjectile(QGraphicsItem* parent)
    : Projectile(":/Items/Equipment/ball.png", parent) {
    setScale(1.7);
    damage = 8;
    gravity = 0.5;
    maxLifeTime = 3000;
}

void BallProjectile::launch(const QPointF& startPos, bool facingLeft, Character* shooter) {
    this->shooter = shooter;
    setPos(startPos);
    // 斜抛运动
    qreal horizontalSpeed = facingLeft ? -8.0 : 8.0;
    qreal verticalSpeed = -10.0;  // 向上的初速度
    velocity = QPointF(horizontalSpeed, verticalSpeed);
    updateTimer->start(1000 / 90);
}

void BallProjectile::updatePosition() {
    Projectile::updatePosition();
}