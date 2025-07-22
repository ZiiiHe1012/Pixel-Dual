#include "DropManager.h"
#include "WeaponDrop.h"
#include "HealthDrop.h"
#include <QGraphicsScene>
#include <QRandomGenerator>

DropManager::DropManager(QGraphicsScene* scene, QObject* parent)
    : QObject(parent), scene(scene) {
    
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &DropManager::spawnItem);
}

void DropManager::startDropping() {
    spawnTimer->start(500 + QRandomGenerator::global()->bounded(1000));
}

void DropManager::stopDropping() {
    spawnTimer->stop();
}

void DropManager::setDropArea(qreal left, qreal right) {
    // 掉落区域
    dropAreaLeft = left;
    dropAreaRight = right;
}

void DropManager::removeDrop(DroppableItem* drop) {
    if (activeDrops.contains(drop)) {
        activeDrops.removeOne(drop);
        itemCounts[drop->getType()]--;
        scene->removeItem(drop);
        delete drop;
    }
}

void DropManager::spawnItem() {
    DroppableItem::ItemType type = selectRandomType();
    
    // 每种最多2个
    if (itemCounts[type] >= 2) {
        return;
    }
    
    qreal x = dropAreaLeft + QRandomGenerator::global()->bounded(dropAreaRight - dropAreaLeft);
    QPointF dropPos(x, -50);
    
    DroppableItem* item = createItem(type, dropPos);
    if (item) {
        scene->addItem(item);
        activeDrops.append(item);
        itemCounts[type]++;
    }
    // 掉落时间间隔
    spawnTimer->setInterval(1500 + QRandomGenerator::global()->bounded(3000));
}

DroppableItem::ItemType DropManager::selectRandomType() {
    int totalWeight = 0;
    for (auto weight : dropWeights) {
        totalWeight += weight;
    }
    
    int random = QRandomGenerator::global()->bounded(totalWeight);
    int currentWeight = 0;
    
    for (auto it = dropWeights.begin(); it != dropWeights.end(); ++it) {
        currentWeight += it.value();
        if (random < currentWeight) {
            return it.key();
        }
    }
    
    return DroppableItem::WEAPON_KNIFE;
}

DroppableItem* DropManager::createItem(DroppableItem::ItemType type, const QPointF& pos) {
    switch(type) {
        case DroppableItem::WEAPON_KNIFE:
        case DroppableItem::WEAPON_SOLIDBALL:
        case DroppableItem::WEAPON_RIFLE:
        case DroppableItem::WEAPON_SNIPER:
            return new WeaponDrop(type, pos);
        case DroppableItem::HEALTH_BANDAGE:
        case DroppableItem::HEALTH_MEDKIT:
        case DroppableItem::HEALTH_ADRENALINE:
            return new HealthDrop(type, pos);
        default:
            return nullptr;
    }
}