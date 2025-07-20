//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_CHARACTER_H
#define QT_PROGRAMMING_2024_CHARACTER_H

#include <QGraphicsEllipseItem>
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../LegEquipments/LegEquipment.h"
#include "../Platforms/Platform.h"

class Character : public Item {
public:
    explicit Character(QGraphicsItem *parent, const QString &pixmapPath = "");

    [[nodiscard]] bool isLeftDown() const;

    void setLeftDown(bool leftDown);

    [[nodiscard]] bool isRightDown() const;

    void setRightDown(bool rightDown);

    // 跳跃相关
    [[nodiscard]] bool isUpDown() const;

    void setUpDown(bool upDown);

    void applyGravity(qint64 deltaTime);
    void checkPlatformCollision(const QList<Platform*>& platforms);
    void checkGroundCollision(qreal groundHeight);

    // 下蹲相关
    [[nodiscard]] bool isCrouchDown() const;
    void setCrouchDown(bool crouchDown);
    void setCrouchImage(const QString& crouchImagePath);  // 设置下蹲图像

    [[nodiscard]] bool isPickDown() const;

    void setPickDown(bool pickDown);

    [[nodiscard]] const QPointF &getVelocity() const;

    [[nodiscard]] bool isPicking() const;

    void setVelocity(const QPointF &velocity);

    void processInput();

    Armor* pickupArmor(Armor* newArmor);

    bool isOnPlatform = false;
    bool isGrounded = true;
    bool isCrouching = false;  

protected:
    HeadEquipment *headEquipment{};
    LegEquipment *legEquipment{};
    Armor *armor{};
    QPointF velocity{};
//    QGraphicsEllipseItem *ellipseItem; // for debugging
private:
    bool leftDown{}, rightDown{}, upDown{}, crouchDown{}, pickDown{};
    bool lastPickDown{};
    bool picking{};
    QGraphicsPixmapItem* crouchPixmapItem = nullptr;  // 下蹲图像
    qreal gravity = 0.003;  // 重力加速度
    qreal jumpVelocity = -1;  // 跳跃初速度
    qint64 jumpStartTime = 0;
    qint64 lastJumpTime = 0;
    qint64 jumpCooldown = 600; // 跳跃冷却
};


#endif //QT_PROGRAMMING_2024_CHARACTER_H
