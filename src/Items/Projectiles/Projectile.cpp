#include "Projectile.h"
#include "../Characters/Character.h"
#include "../Platforms/Platform.h"
#include <QGraphicsScene>

Projectile::Projectile(const QString& imagePath, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(imagePath));
    setZValue(100);
    // 创建更新定时器
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Projectile::update);
}

Projectile::~Projectile() {
    if(updateTimer) {
        updateTimer->stop();
    }
}

void Projectile::launch(const QPointF& startPos, bool facingLeft, Character* shooter) {
    this->shooter = shooter;
    setPos(startPos);
    qreal speed = 10.0;
    velocity = QPointF(facingLeft ? -speed : speed, 0);
    updateTimer->start(1000 / 90);
}

void Projectile::update() {
    if(hit) {
        updateTimer->stop();
        emit finished(this);
        return;
    }
    // 更新位置
    updatePosition();
    // 更新生存时间
    lifeTime += 1000 / 90;
    // 检查是否超时或超出边界
    if(!scene()) return;
    QRectF sceneRect = scene()->sceneRect();
    QPointF currentPos = pos();
    if(currentPos.x() < sceneRect.left() - 100 || 
        currentPos.x() > sceneRect.right() + 100 ||
        currentPos.y() < sceneRect.top() - 100 ||
        currentPos.y() > sceneRect.bottom() + 100 ||
        lifeTime > maxLifeTime) {
        onOutOfBounds();
        updateTimer->stop();
        emit finished(this);
    }
}

void Projectile::updatePosition() {
    // 应用重力
    if(gravity != 0) {
        velocity.setY(velocity.y() + gravity);
    }
    // 更新位置
    setPos(pos() + velocity);
}

void Projectile::checkCollisions(const QList<Character*>& characters, const QList<Platform*>& platforms) {
    if(hit) return;
    // 检查平台碰撞
    for(Platform* platform : platforms) {
        if (collidesWithItem(platform)) {
            onHitPlatform();
            setHit();
            return;
        }
    }
    // 检查角色碰撞
    for(Character* character : characters) {
        if(character && character != shooter && collidesWithItem(character)) {
            if(!character->isInvisible()) {
                onHitCharacter(character);
                setHit();
                return;
            }
        }
    }
}

void Projectile::onHitCharacter(Character* target) {
    if(target) {
        target->takeDamage(damage);
    }
}

void Projectile::onHitPlatform() {
}

void Projectile::onOutOfBounds() {
}