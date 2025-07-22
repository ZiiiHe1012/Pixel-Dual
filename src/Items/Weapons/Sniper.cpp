#include "Sniper.h"
#include "../Characters/Character.h"
#include "../Projectiles/BulletProjectile2.h"
#include <QGraphicsScene>
#include <QDateTime>

Sniper::Sniper(QGraphicsItem *parent) 
    : Weapon(parent, ":/Items/Equipment/sniper.png") {
    damage = 12;
    range = 0;
    setScale(0.8);
    usageLimit = 5;
    setVisible(false);
}

void Sniper::attack() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    // 检查射击间隔
    if (currentTime - lastShotTime < shotInterval) {
        return;
    }
    if (!attacking && !isUsedUp() && owner && owner->scene()) {
        attacking = true;
        hasDealtDamage = false;
        usageCount++;
        lastShotTime = currentTime;
        setVisible(true);
        if (owner->isCrouching) {
            setPos(20, 27);
            setZValue(100);
        } else {
            setPos(20, 17);
        }
        bool facingLeft = owner->transform().m11() < 0;
        // 计算子弹发射位置
        QPointF startPos = owner->scenePos();
        if (facingLeft) {
            startPos.setX(startPos.x() - 40);
        } else {
            startPos.setX(startPos.x() + 40);
        }
        if (owner->isCrouching) {
            startPos.setY(startPos.y() + 47);
        } else {
            startPos.setY(startPos.y() + 32);
        }
        // 创建子弹
        BulletProjectile2* bullet = new BulletProjectile2();
        owner->scene()->addItem(bullet);
        bullet->launch(startPos, facingLeft, owner);
        attackTimer->start(800);
    }
}

void Sniper::stopAttack() {
    attacking = false;
    setVisible(false);
}