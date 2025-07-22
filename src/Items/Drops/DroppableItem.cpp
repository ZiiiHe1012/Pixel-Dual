#include "DroppableItem.h"
#include "../Platforms/Platform.h"
#include <QDateTime>

DroppableItem::DroppableItem(ItemType type, const QPointF& startPos, QGraphicsItem* parent)
    : Item(parent, ""), itemType(type) {
    setPos(startPos);
    setZValue(50);
    velocity = QPointF(0, 0);
}

void DroppableItem::updatePhysics(qint64 deltaTime, qreal groundHeight, const QList<Platform*>& platforms) {
    if (!grounded) {
        // 应用重力
        velocity.setY(velocity.y() + gravity * deltaTime);
        if (velocity.y() > 1) velocity.setY(1);
        
        // 更新位置
        setPos(pos() + velocity * deltaTime);
        
        // 平台碰撞
        QRectF dropRect = sceneBoundingRect();
        for (Platform* platform : platforms) {
            QRectF platRect = platform->sceneBoundingRect();
            if (dropRect.left() < platRect.right() && 
                dropRect.right() > platRect.left() &&
                dropRect.bottom() >= platRect.top() - 5 &&
                dropRect.bottom() <= platRect.top() + 15 &&
                velocity.y() >= 0) {
                setPos(pos().x(), platRect.top() - boundingRect().height());
                velocity.setY(0);
                grounded = true;
                return;
            }
        }
        
        // 地面碰撞
        if (pos().y() >= groundHeight + 35) {
            setPos(pos().x(), groundHeight + 35);
            velocity.setY(0);
            grounded = true;
        }
    }
}

void DroppableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
}