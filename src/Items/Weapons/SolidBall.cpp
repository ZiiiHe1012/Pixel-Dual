#include "SolidBall.h"
#include "../Characters/Character.h"
#include "../Projectiles/BallProjectile.h"
#include <QGraphicsScene>

SolidBall::SolidBall(QGraphicsItem *parent) 
    : Weapon(parent, ":/Items/Equipment/ball.png") {
    damage = 4;
    range = 0; // 无范围判定
    setScale(0.7);
    usageLimit = 5;
}

void SolidBall::attack() {
    if(!attacking && !isUsedUp() && owner && owner->scene()) {
        attacking = true;
        hasDealtDamage = false;
        usageCount++;
        // 计算发射位置
        QPointF startPos = owner->scenePos();
        bool facingLeft = owner->transform().m11() < 0;
        if(facingLeft) {
            startPos.setX(startPos.x() - 40);
        } else {
            startPos.setX(startPos.x()); 
        }
        if(owner->isCrouching) {
            startPos.setY(startPos.y() + 10);
        }
        // 创建投射物
        BallProjectile* projectile = new BallProjectile();
        owner->scene()->addItem(projectile);
        // 发射
        projectile->launch(startPos, facingLeft, owner);
        attackTimer->start(300);
    }
}