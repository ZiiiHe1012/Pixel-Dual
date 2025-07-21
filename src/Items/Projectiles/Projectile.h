#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPointF>

class Character;
class Platform;

class Projectile : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Projectile(const QString& imagePath, QGraphicsItem* parent = nullptr);
    virtual ~Projectile();
    // 发射子弹
    virtual void launch(const QPointF& startPos, bool facingLeft, Character* shooter);
    // 获取属性
    int getDamage() const { return damage; }
    Character* getShooter() const { return shooter; }
    bool hasHit() const { return hit; }
    void setHit() { hit = true; }
    // 碰撞检测
    void checkCollisions(const QList<Character*>& characters, const QList<Platform*>& platforms);
signals:
    void finished(Projectile* projectile);
protected:
    virtual void updatePosition();
    virtual void onHitCharacter(Character* target);
    virtual void onHitPlatform();
    virtual void onOutOfBounds();
protected slots:
    void update();
protected:
    QTimer* updateTimer;
    QPointF velocity;
    Character* shooter = nullptr;
    int damage = 10;
    bool hit = false;
    qreal gravity = 0;
    qint64 lifeTime = 0;
    qint64 maxLifeTime = 5000;  // 5秒后消失
};

#endif