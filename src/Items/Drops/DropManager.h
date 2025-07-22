#ifndef DROPMANAGER_H
#define DROPMANAGER_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include "DroppableItem.h"

class QGraphicsScene;

class DropManager : public QObject {
    Q_OBJECT
public:
    DropManager(QGraphicsScene* scene, QObject* parent = nullptr);
    
    void startDropping();
    void stopDropping();
    QList<DroppableItem*> getActiveDrops() const { return activeDrops; }
    void removeDrop(DroppableItem* drop);
    void setDropArea(qreal left, qreal right);
    
private slots:
    void spawnItem();
    
private:
    QGraphicsScene* scene;
    QTimer* spawnTimer;
    QList<DroppableItem*> activeDrops;
    QMap<DroppableItem::ItemType, int> itemCounts;
    qreal dropAreaLeft = 100;
    qreal dropAreaRight = 1180;
    
    // 掉落权重
    QMap<DroppableItem::ItemType, int> dropWeights = {
        {DroppableItem::WEAPON_KNIFE, 25},
        {DroppableItem::WEAPON_SOLIDBALL, 20},
        {DroppableItem::WEAPON_RIFLE, 15},
        {DroppableItem::WEAPON_SNIPER, 10},
        {DroppableItem::HEALTH_BANDAGE, 15},
        {DroppableItem::HEALTH_MEDKIT, 5},
        {DroppableItem::HEALTH_ADRENALINE, 10}
    };
    
    DroppableItem::ItemType selectRandomType();
    DroppableItem* createItem(DroppableItem::ItemType type, const QPointF& pos);
};

#endif