//
// Created by gerw on 8/20/24.
//

#include <iostream>
using namespace std;

#include <QDebug>
#include "BattleScene.h"
#include "../Items/Characters/Link.h"
#include "../Items/Maps/Battlefield.h"
#include "../Items/Armors/FlamebreakerArmor.h"
#include "../Items/Platforms/Platform.h"
#include "../Items/Terrain/Grass.h"
#include "../Items/Terrain/Ice.h"
#include "../Items/Weapons/Weapon.h"

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);
    map = new Battlefield();
    character = new Link();
    character2 = new Link();
    // 地图
    addItem(map);
    // 角色
    addItem(character);
    addItem(character2);
    character->setPos(map->getSpawnPos() + QPointF(-320, 0));
    character2->setTransform(QTransform().scale(-1, 1));
    character2->setPos(map->getSpawnPos() + QPointF(238, 0));  // 在第一个角色右边800
    // 平台
    Platform* platform1 = new Platform(234, 338, 220, 30);  // 左边
    Platform* platform2 = new Platform(505, 178, 285, 30);  // 中间
    Platform* platform3 = new Platform(842, 338, 220, 30);  // 右边
    platforms.append(platform1);
    platforms.append(platform2);
    platforms.append(platform3);
    for (auto platform : platforms) {
        addItem(platform);
    }
    // 添加草地
    GrassTerrain* grass1 = new GrassTerrain(0, 420, 368, 200);
    terrains.append(grass1);
    addItem(grass1);
    // 添加冰场
    IceTerrain* ice1 = new IceTerrain(930, 420, 368, 200);
    terrains.append(ice1);
    addItem(ice1);
    // 添加生命条
    characterHealthBar = new HealthBar(60, 8);
    characterHealthBar->setParentItem(character);
    characterHealthBar->setPos(-14, -20);
    character->setMaxHealth(100);
    // 添加第二个角色的生命条
    character2HealthBar = new HealthBar(60, 8);
    character2HealthBar->setParentItem(character2);
    character2HealthBar->setPos(-14, -20);
    character2->setMaxHealth(100);

    map->scaleToFitScene(this);
}

void BattleScene::processInput() {
    Scene::processInput();
    if (character != nullptr) {
        character->processInput();
    }
    if (character2 != nullptr) {
    character2->processInput();
}
}

void BattleScene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_A:
            if (character != nullptr) {
                character->setLeftDown(true);
            }
            break;
        case Qt::Key_D:
            if (character != nullptr) {
                character->setRightDown(true);
            }
            break;
        case Qt::Key_W:
            if (character != nullptr) {
                character->setUpDown(true);
            }
            break;
        case Qt::Key_S:
            if (character != nullptr) {
                character->setCrouchDown(true);
            }
            break;
        case Qt::Key_J:
            if (character != nullptr) {
                character->setAttackDown(true);
            }
            break;
        case Qt::Key_K:
            if (character != nullptr) {
                character->setPickDown(true);
            }
            break;
        // 第二个角色的控制
        case Qt::Key_Left:
            if (character2 != nullptr) {
                character2->setLeftDown(true);
            }
            break;
        case Qt::Key_Right:
            if (character2 != nullptr) {
                character2->setRightDown(true);
            }
            break;
        case Qt::Key_Up:
            if (character2 != nullptr) {
                character2->setUpDown(true);
            }
            break;
        case Qt::Key_Down:
            if (character2 != nullptr) {
                character2->setCrouchDown(true);
            }
            break;
        case Qt::Key_Space:
            if (character2 != nullptr) {
                character2->setAttackDown(true); 
            }
            break;
        default:
            Scene::keyPressEvent(event);
    }
}

void BattleScene::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_A:
            if (character != nullptr) {
                character->setLeftDown(false);
            }
            break;
        case Qt::Key_D:
            if (character != nullptr) {
                character->setRightDown(false);
            }
            break;
        case Qt::Key_W:
            if (character != nullptr) {
                character->setUpDown(false);
            }
            break;
        case Qt::Key_S:
            if (character != nullptr) {
                character->setCrouchDown(false);
            }
            break;
        case Qt::Key_J:
            if (character != nullptr) {
                character->setAttackDown(false);
            }
        case Qt::Key_K:
            if (character != nullptr) {
                character->setPickDown(false);
            }
            break;
        // 第二个角色的控制
        case Qt::Key_Left:
            if (character2 != nullptr) {
                character2->setLeftDown(false);
            }
            break;
        case Qt::Key_Right:
            if (character2 != nullptr) {
                character2->setRightDown(false);
            }
            break;
        case Qt::Key_Up:
            if (character2 != nullptr) {
                character2->setUpDown(false);
            }
            break;
        case Qt::Key_Down:
            if (character2 != nullptr) {
                character2->setCrouchDown(false);
            }
            break;
        case Qt::Key_Space:
            if (character2 != nullptr) {
                character2->setAttackDown(false);
            }
            break;
        default:
            Scene::keyReleaseEvent(event);
    }
}

void BattleScene::update() {
    Scene::update();
    if (character != nullptr) {
        int currentHealth = character->getCurrentHealth();
        int maxHealth = character->getMaxHealth();
        // 更新跟随的血条
        if (characterHealthBar != nullptr) {
            characterHealthBar->setHealth(currentHealth, maxHealth);
        }
        // 检查是否死亡
        if (character->isDead()) {

        }
    }
    if (character2 != nullptr) {
        int currentHealth2 = character2->getCurrentHealth();
        int maxHealth2 = character2->getMaxHealth();
        // 更新第二个角色的血条
        if (character2HealthBar != nullptr) {
            character2HealthBar->setHealth(currentHealth2, maxHealth2);
        }
        // 检查是否死亡
        if (character2->isDead()) {
            
        }
    }
    // 攻击碰撞检测
    if (character != nullptr && character2 != nullptr) {
    character->checkAttackCollision(character2);
    character2->checkAttackCollision(character);
}
}

void BattleScene::processMovement() {
    Scene::processMovement();
    if (character != nullptr) {
        // 处理重力
        character->applyGravity(deltaTime);
        // 更新位置
        character->setPos(character->pos() + character->getVelocity() * (double) deltaTime);
        // 平台碰撞检测
        character->checkPlatformCollision(platforms);
        // 地面碰撞检测
        if (!character->isOnPlatform) {
            qreal groundHeight = map->getFloorHeight();
            character->checkGroundCollision(groundHeight);
        }
        // 地形检测
        character->checkTerrainEffect(terrains);
    }
    if (character2 != nullptr) {
        character2->applyGravity(deltaTime);
        character2->setPos(character2->pos() + character2->getVelocity() * (double) deltaTime);
        character2->checkPlatformCollision(platforms);
        if (!character2->isOnPlatform) {
            qreal groundHeight = map->getFloorHeight();
            character2->checkGroundCollision(groundHeight);
        }
        character2->checkTerrainEffect(terrains);
    }
}

void BattleScene::processPicking() {
    Scene::processPicking();
    if (character->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character->pos(), 100.);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character, mountable));
        }
    }
    if (character2->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character2->pos(), 100.);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character2, mountable));
        }
    }
}

Mountable *BattleScene::findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold) {
    Mountable *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (QGraphicsItem *item: items()) {
        if (auto mountable = dynamic_cast<Mountable *>(item)) {
            if (!mountable->isMounted()) {
                qreal distance = QLineF(pos, item->pos()).length();
                if (distance < minDistance) {
                    minDistance = distance;
                    nearest = mountable;
                }
            }
        }
    }

    return nearest;
}

Mountable *BattleScene::pickupMountable(Character *character, Mountable *mountable) {
    // Limitation: currently only supports armor
    if (auto armor = dynamic_cast<Armor *>(mountable)) {
        return character->pickupArmor(armor);
    }
    return nullptr;
}
