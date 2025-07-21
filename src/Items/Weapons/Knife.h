#ifndef KNIFE_H
#define KNIFE_H

#include "Weapon.h"
#include <QPropertyAnimation>

class Knife : public Weapon {
    Q_OBJECT
    Q_PROPERTY(qreal angle READ angle WRITE setAngle)
    
public:
    explicit Knife(QGraphicsItem *parent = nullptr);
    ~Knife();
    
    void attack() override;
    void stopAttack() override;
    
    qreal angle() const { return m_angle; }
    void setAngle(qreal angle);
    
private:
    QPropertyAnimation* rotationAnimation = nullptr;
    qreal m_angle = 0;
    void setupAnimation();
};

#endif