#include "Knife.h"
#include "../Characters/Character.h"
#include <QTransform>

Knife::Knife(QGraphicsItem *parent) 
    : Weapon(parent, ":/Items/Equipment/knife.png") {
    damage = 4;    
    range = 80.0;   
    setScale(0.6);  
    setupAnimation();
}

Knife::~Knife() {
    if(rotationAnimation) {
        rotationAnimation->stop();
        delete rotationAnimation;
    }
}

// 设置角度
void Knife::setAngle(qreal angle) {
    m_angle = angle;
    setRotation(angle);
}

// 攻击动画
void Knife::setupAnimation() {
    rotationAnimation = new QPropertyAnimation(this, "angle");
    rotationAnimation->setDuration(300);
    rotationAnimation->setEasingCurve(QEasingCurve::Linear);
}

void Knife::attack() {
    Weapon::attack();
    if(owner) {
        if(pixmapItem) {
            QRectF rect = pixmapItem->boundingRect();
            setTransformOriginPoint(rect.left(), rect.bottom());
        }
        if(owner->isCrouching) {
            setPos(27, 7);  
            setZValue(100); 
        }
        else {
            setPos(27, -3);  
        }
        // 旋转角度
        rotationAnimation->setStartValue(0);
        rotationAnimation->setEndValue(90);
    }
    rotationAnimation->start();
}

void Knife::stopAttack() {
    Weapon::stopAttack();
    if(rotationAnimation) {
        rotationAnimation->stop();
        setRotation(0);
    }
}