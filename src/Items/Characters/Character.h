//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_CHARACTER_H
#define QT_PROGRAMMING_2024_CHARACTER_H

#include <QGraphicsEllipseItem>
#include <QGraphicsColorizeEffect>
#include <QTimer>
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../LegEquipments/LegEquipment.h"
#include "../Platforms/Platform.h"
#include "../Terrain/Terrain.h"
#include "../Weapons/Weapon.h"

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

    // 地形相关
    void checkTerrainEffect(const QList<Terrain*>& terrains);
    bool isInvisible() const { return invisible; }

    // 生命值相关
    void setMaxHealth(int maxHp) { maxHealth = maxHp; currentHealth = maxHp; }
    int getCurrentHealth() const { return currentHealth; }
    int getMaxHealth() const { return maxHealth; }
    void takeDamage(int damage);
    void heal(int amount);
    bool isDead() const { return currentHealth <= 0; }

    // 武器相关
    [[nodiscard]] bool isAttackDown() const;
    void setAttackDown(bool attackDown);
    void attack();
    void checkAttackCollision(Character* target);
    Weapon* getWeapon() const { return weapon; }
    void switchToDefaultWeapon();
    void switchToWeapon(Weapon* newWeapon);

    // 速度相关
    void setBaseSpeed(qreal speed) { baseSpeed = speed; }
    qreal getBaseSpeed() const { return baseSpeed; }

    // 攻击红温
    void showDamageEffect();

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
    bool invisible = false;
    bool onIce = false;

protected:
    HeadEquipment *headEquipment{};
    LegEquipment *legEquipment{};
    Armor *armor{};
    QPointF velocity{};
    Weapon* weapon = nullptr;
    Weapon* defaultWeapon = nullptr;
    int maxHealth = 100;
    int currentHealth = 100;
//    QGraphicsEllipseItem *ellipseItem; // for debugging
private:
    bool leftDown{}, rightDown{}, upDown{}, crouchDown{}, attackDown{}, pickDown{};
    bool lastPickDown{};
    bool picking{};
    bool lastAttackDown{};
    bool isAttacking{};
    QGraphicsPixmapItem* crouchPixmapItem = nullptr;  // 下蹲图像
    QTimer* damageEffectTimer = nullptr; // 红温相关
    QGraphicsColorizeEffect* damageEffect = nullptr;
    qreal baseSpeed = 0.3;  // 基础移动速度 
    qreal gravity = 0.003;  // 重力加速度
    qreal jumpVelocity = -1;  // 跳跃初速度
    qint64 jumpStartTime = 0;
    qint64 lastJumpTime = 0;
    qint64 jumpCooldown = 600; // 跳跃冷却
};


#endif //QT_PROGRAMMING_2024_CHARACTER_H
