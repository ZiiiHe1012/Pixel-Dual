#include "BulletProjectile2.h"
#include "../Characters/Character.h"

BulletProjectile2::BulletProjectile2(QGraphicsItem* parent)
    : Projectile(":/Items/Equipment/bullet2.png", parent) {
    setScale(1);
    setZValue(99);
    damage = 15;
    gravity = 0;
    maxLifeTime = 2000;
}

void BulletProjectile2::launch(const QPointF& startPos, bool facingLeft, Character* shooter) {
    this->shooter = shooter;
    setPos(startPos);
    qreal bulletSpeed = 40.0;
    velocity = QPointF(facingLeft ? -bulletSpeed : bulletSpeed, 0);
    // 根据朝向旋转子弹图片
    if (facingLeft) {
        setRotation(180);
    }
    updateTimer->start(1000 / 90);
}