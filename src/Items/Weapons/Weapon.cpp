#include <QObject>
#include <QTimer>
#include "Weapon.h"
#include "../Characters/Character.h"

Weapon::Weapon(QGraphicsItem *parent, const QString &pixmapPath) 
    : QObject(), Item(parent, pixmapPath) {
    setVisible(false);  // 默认隐藏
    attackTimer = new QTimer();
    attackTimer->setSingleShot(true);
    QObject::connect(attackTimer, &QTimer::timeout, [this]() {
        stopAttack();
    });
}

void Weapon::attack() {
    if(!attacking && !isUsedUp()) {
        attacking = true;
        hasDealtDamage = false;
        setVisible(true);
        usageCount++;  // 增加使用次数
        // 攻击持续300毫秒
        attackTimer->start(300);
    }
}

void Weapon::stopAttack() {
    attacking = false;
    setVisible(false);
}