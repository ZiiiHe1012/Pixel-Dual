//
// Created by gerw on 8/20/24.
//

#include <QTransform>
#include <QDateTime>
#include "Character.h"
#include "../../Scenes/Scene.h"
#include "../Platforms/Platform.h"
#include "../../Scenes/BattleScene.h"
#include "../Weapons/Fist.h"
#include "../Weapons/Knife.h"
#include "../Weapons/SolidBall.h"
#include "../Weapons/Rifle.h"
#include "../Weapons/Sniper.h"
#include "../HealthItems/Adrenaline.h"

Character::Character(QGraphicsItem *parent, const QString &pixmapPath) 
    : Item(parent, pixmapPath) {
    defaultWeapon = new Fist(this);// 默认武器
    defaultWeapon->setOwner(this);
    weapon = defaultWeapon;
    // 红温
    damageEffect = new QGraphicsColorizeEffect();
    damageEffect->setColor(Qt::red);
    damageEffect->setStrength(0);
    setGraphicsEffect(damageEffect);
    // 创建伤害效果计时器
    damageEffectTimer = new QTimer();
    damageEffectTimer->setSingleShot(true);
    QObject::connect(damageEffectTimer, &QTimer::timeout, [this]() {
        if (damageEffect) {
            damageEffect->setStrength(0);  // 恢复正常
        }
    });
    // 创建肾上腺素定时器
    adrenalineHealTimer = new QTimer();
    QObject::connect(adrenalineHealTimer, &QTimer::timeout, [this]() {
        heal(6);  // 每次回复6点
        adrenalineHealCount++;
        if (adrenalineHealCount >= 5) {
            adrenalineHealTimer->stop();
            adrenalineHealCount = 0;
        }
    });
    adrenalineSpeedTimer = new QTimer();
    adrenalineSpeedTimer->setSingleShot(true);
    QObject::connect(adrenalineSpeedTimer, &QTimer::timeout, [this]() {
        setBaseSpeed(originalSpeed);  // 恢复原速度
    });
}

bool Character::isLeftDown() const {
    return leftDown;
}

void Character::setLeftDown(bool leftDown) {
    Character::leftDown = leftDown;
}


bool Character::isRightDown() const {
    return rightDown;
}

void Character::setRightDown(bool rightDown) {
    Character::rightDown = rightDown;
}

bool Character::isUpDown() const {
    return upDown;
}

void Character::setUpDown(bool upDown) {
    Character::upDown = upDown;
}

bool Character::isCrouchDown() const {
    return crouchDown;
}

void Character::setCrouchDown(bool crouchDown) {
    Character::crouchDown = crouchDown;
}

void Character::setCrouchImage(const QString& crouchImagePath) {
    if (!crouchImagePath.isEmpty()) {
        crouchPixmapItem = new QGraphicsPixmapItem(QPixmap(crouchImagePath), this);
        crouchPixmapItem->setVisible(false);
    }
}

bool Character::isAttackDown() const {
    return attackDown;
}

void Character::attack() {
    if (weapon) {
        // 检查武器是否用完
        if (weapon->isUsedUp()) {
            switchToDefaultWeapon();
        }
        if (!weapon->isAttacking()) {
            weapon->attack();
        }
    }
}

void Character::setAttackDown(bool attackDown) {
    Character::attackDown = attackDown;
}

void Character::switchToDefaultWeapon() {
    if (weapon != defaultWeapon) {
        if (weapon) {
            weapon->setVisible(false);
            delete weapon;
        }
        weapon = defaultWeapon;
    }
}

void Character::switchToWeapon(Weapon* newWeapon) {
    if (weapon && weapon != defaultWeapon) {
        weapon->setVisible(false);
        delete weapon;
    }
    weapon = newWeapon;
    if (weapon) {
        weapon->setOwner(this);
    }
}

void Character::showDamageEffect() {
    if (damageEffect) {
        damageEffect->setStrength(0.6);  // 设置红色强度
        damageEffectTimer->start(200);   // 持续200
    }
}

bool Character::isPickDown() const {
    return pickDown;
}

void Character::setPickDown(bool pickDown) {
    Character::pickDown = pickDown;
}

const QPointF &Character::getVelocity() const {
    return velocity;
}

void Character::setVelocity(const QPointF &velocity) {
    Character::velocity = velocity;
}

// 伤害判定
void Character::takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
    showDamageEffect();
}

// 治疗判定
void Character::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

void Character::processInput() {
    // 变换原点设置为中心
    if (pixmapItem) {
        setTransformOriginPoint(pixmapItem->boundingRect().center());
    }
    auto currentVelocity = getVelocity();
    qreal newXVelocity = 0;
    // 冰面速度增加
    qreal currentMoveSpeed = onIce ? baseSpeed * 1.8 : baseSpeed; 
    if (isCrouchDown() && isGrounded) {
        // 切换到下蹲状态
        if (!isCrouching) {
            isCrouching = true;
            if (pixmapItem) pixmapItem->setVisible(false);
            if (crouchPixmapItem) crouchPixmapItem->setVisible(true);
        }
        crouchPixmapItem->setPos(0, 11); 
        // 下蹲时不能移动
        currentVelocity.setX(0);
    } 
    else {
        // 恢复站立状态
        if (isCrouching) {
            isCrouching = false;
            if (pixmapItem) pixmapItem->setVisible(true);
            if (crouchPixmapItem) crouchPixmapItem->setVisible(false);
            crouchPixmapItem->setPos(0, 0); 
        }    
        if (isLeftDown()) {
            newXVelocity -= currentMoveSpeed;
            setTransform(QTransform().scale(-1, 1));
        }
        if (isRightDown()) {
            newXVelocity += currentMoveSpeed;
            setTransform(QTransform().scale(1, 1));
        }
        currentVelocity.setX(newXVelocity);
    }
    // 跳跃逻辑
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    if (!isCrouching && isUpDown() && isGrounded && (currentTime - lastJumpTime >= jumpCooldown)) {
        currentVelocity.setY(jumpVelocity);
        isGrounded = false;
        jumpStartTime = currentTime;
        lastJumpTime = currentTime;
    }
    setVelocity(currentVelocity);
    // 拾取逻辑
    if (!lastPickDown && crouchDown && isGrounded) {
        picking = true;
    } else {
        picking = false;
    }
    lastPickDown = crouchDown;
    // 攻击逻辑
    if (!lastAttackDown && attackDown) {
        attack();
    }
    lastAttackDown = attackDown;
}

bool Character::isPicking() const {
    return picking;
}

Armor *Character::pickupArmor(Armor *newArmor) {
    auto oldArmor = armor;
    if (oldArmor != nullptr) {
        oldArmor->unmount();
        oldArmor->setPos(newArmor->pos());
        oldArmor->setParentItem(parentItem());
    }
    newArmor->setParentItem(this);
    newArmor->mountToParent();
    armor = newArmor;
    return oldArmor;
}

// 重力
void Character::applyGravity(qint64 deltaTime) {
    if (!isGrounded) {
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        qint64 timeSinceJump = currentTime - jumpStartTime;  // 从跳跃开始经过的时间
        qreal VelocityY = jumpVelocity + gravity * (double)timeSinceJump;
        if(VelocityY > 1) VelocityY = 1;
        velocity.setY(VelocityY);
    }
}

// 检查地面碰撞
void Character::checkGroundCollision(qreal groundHeight) {
    if (pos().y() >= groundHeight) {
        setPos(pos().x(), groundHeight);
        velocity.setY(0);
        isGrounded = true;
    }
}

// 检查平台碰撞
void Character::checkPlatformCollision(const QList<Platform*>& platforms) {
    QRectF charRect = sceneBoundingRect(); 
    if (isOnPlatform) {
        bool stillOnPlatform = false;
        for (Platform* platform : platforms) {
            QRectF platformRect = platform->sceneBoundingRect(); 
            if (charRect.left() < platformRect.right() && 
                charRect.right() > platformRect.left()) {
                stillOnPlatform = true;
                break;
            }
        }
        // 如果横向离开了平台，立即开始坠落
        if (!stillOnPlatform) {
            isGrounded = false;
            isOnPlatform = false;
            return;
        }
    }
    if (velocity.y() >= 0) {
        for (Platform* platform : platforms) {
            QRectF platformRect = platform->sceneBoundingRect();
            // 检测水平重叠
            if (charRect.left() < platformRect.right() && 
                charRect.right() > platformRect.left()) {
                qreal charBottom = charRect.bottom();
                qreal platformTop = platformRect.top();
                // 检测垂直位置
                if (charBottom >= platformTop - 5 && 
                    charBottom <= platformTop + 25 &&
                    velocity.y() >= 0) {
                    // 站在平台上
                    setPos(pos().x(), platformTop - 63);
                    velocity.setY(0);
                    isGrounded = true;
                    isOnPlatform = true;
                    return;
                }
            }
        }
        // 离开平台的检测
        isOnPlatform = false;
    }
}

// 检查地形效果
void Character::checkTerrainEffect(const QList<Terrain*>& terrains) {
    QRectF charRect = sceneBoundingRect();
    bool onGrass = false;
    onIce = false;
    for (Terrain* terrain : terrains) {
        QRectF terrainRect = terrain->sceneBoundingRect();
        // 检测角色是否在地形上
        if (charRect.intersects(terrainRect)) {
            if (terrain->getType() == Terrain::GRASS) {
                onGrass = true;
            } else if (terrain->getType() == Terrain::ICE) {
                onIce = true;
            }
        }
    }
    // 草地下蹲隐身
    invisible = onGrass && isCrouching && isGrounded;
    if (invisible) setOpacity(0.3);
    else setOpacity(1.0);
}

// 检查攻击碰撞
void Character::checkAttackCollision(Character* target) {
    if (!weapon || !weapon->isAttacking() || !target || target == this) {
        return;
    }
    if (weapon->hasDealtDamage) {
        return;
    }
    QRectF attackRect;
    if (transform().m11() < 0) {  // 面向左边
        attackRect = QRectF(pos().x() - weapon->getRange(), 
                           pos().y() - 30, 
                           weapon->getRange(), 
                           60);
    } else {
        attackRect = QRectF(pos().x(), 
                           pos().y() - 30, 
                           weapon->getRange(), 
                           60);
    }
    // 检查目标是否在攻击范围内
    QRectF targetRect = target->sceneBoundingRect();
    if (attackRect.intersects(targetRect) && !target->isInvisible()) {
        target->takeDamage(weapon->getDamage());
        weapon->hasDealtDamage = true;
    }
}

// 应用肾上腺素效果
void Character::applyAdrenalineEffect() {
    if (adrenalineHealTimer->isActive()) {
        adrenalineHealTimer->stop();
    }
    if (adrenalineSpeedTimer->isActive()) {
        adrenalineSpeedTimer->stop();
        setBaseSpeed(originalSpeed);  // 恢复原速度
    }
    adrenalineHealCount = 0;
    originalSpeed = getBaseSpeed();
    setBaseSpeed(originalSpeed * 1.5);  // 1.5倍速度
    heal(6);
    adrenalineHealCount++;
    adrenalineHealTimer->start(1000);  // 每秒触发
    adrenalineSpeedTimer->start(5000);  // 恢复速度
}