//
// Created by gerw on 8/20/24.
//

#include <QTransform>
#include <QDateTime>
#include "Character.h"
#include "../../Scenes/Scene.h"
#include "../Platforms/Platform.h"

Character::Character(QGraphicsItem *parent, const QString &pixmapPath) 
    : Item(parent, pixmapPath) {
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

void Character::processInput() {
    // 变换原点设置为中心
    if (pixmapItem) {
        setTransformOriginPoint(pixmapItem->boundingRect().center());
    }
    auto currentVelocity = getVelocity();
    qreal newXVelocity = 0;
    const auto moveSpeed = 0.3;
    if (isCrouchDown() && isGrounded) {
        // 切换到下蹲状态
        if (!isCrouching) {
            isCrouching = true;
            if (pixmapItem) pixmapItem->setVisible(false);
            if (crouchPixmapItem) crouchPixmapItem->setVisible(true);
        }
        // 下蹲时不能移动
        currentVelocity.setX(0);
    } 
    else {
        // 恢复站立状态
        if (isCrouching) {
            isCrouching = false;
            if (pixmapItem) pixmapItem->setVisible(true);
            if (crouchPixmapItem) crouchPixmapItem->setVisible(false);
        }    
        if (isLeftDown()) {
            newXVelocity -= moveSpeed;
            setTransform(QTransform().scale(-1, 1));
        }
        if (isRightDown()) {
            newXVelocity += moveSpeed;
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
    if (!lastPickDown && pickDown) {
        picking = true;
    } else {
        picking = false;
    }
    lastPickDown = pickDown;
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