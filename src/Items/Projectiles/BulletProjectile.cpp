#include "BulletProjectile.h"
#include "../Characters/Character.h"

BulletProjectile::BulletProjectile(QGraphicsItem* parent)
    : Projectile(":/Items/Equipment/bullet.png", parent) {
    setScale(1);
    setZValue(99);
    damage = 6;
    gravity = 0;
    maxLifeTime = 2000;
}

void BulletProjectile::launch(const QPointF& startPos, bool facingLeft, Character* shooter) {
    this->shooter = shooter;
    setPos(startPos);
    qreal bulletSpeed = 20.0;
    velocity = QPointF(facingLeft ? -bulletSpeed : bulletSpeed, 0);
    // 根据朝向旋转子弹图片
    if (facingLeft) {
        setRotation(180);
    }
    updateTimer->start(1000 / 90);
}