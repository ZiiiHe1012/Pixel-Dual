#include "Adrenaline.h"
#include "../Characters/Character.h"
#include <QDebug>

Adrenaline::Adrenaline(QGraphicsItem *parent) 
    : QObject(), HealthItem(parent, ":/Items/Equipment/adrenaline.png") {
    healAmount = HEAL_PER_TICK * TOTAL_HEAL_TICKS;
    // 创建定时器
    healTimer = new QTimer(this);
    healTimer->setInterval(HEAL_INTERVAL);
    connect(healTimer, &QTimer::timeout, this, &Adrenaline::healTick);
    speedTimer = new QTimer(this);
    speedTimer->setSingleShot(true);
    connect(speedTimer, &QTimer::timeout, this, &Adrenaline::endSpeedBoost);
}

Adrenaline::~Adrenaline() {
    if (healTimer) {
        healTimer->stop();
        delete healTimer;
    }
    if (speedTimer) {
        speedTimer->stop();
        delete speedTimer;
    }
}

void Adrenaline::applyToCharacter(Character* character) {
    if (!character) return;
    targetCharacter = character;
    healTickCount = 0;
    // 设置加速状态
    originalSpeed = character->getBaseSpeed();
    character->setBaseSpeed(originalSpeed * SPEED_MULTIPLIER);
    healTick();
    // 启动持续回血定时器
    healTimer->start();
    // 启动速度持续时间定时器
    speedTimer->start(SPEED_DURATION);
}

void Adrenaline::healTick() {
    if (!targetCharacter) {
        healTimer->stop();
        return;
    }
    // 回血
    targetCharacter->heal(HEAL_PER_TICK);
    healTickCount++;
    if (healTickCount >= TOTAL_HEAL_TICKS) {
        healTimer->stop();
    }
}

void Adrenaline::endSpeedBoost() {
    if (!targetCharacter) return;
    // 恢复原始速度
    targetCharacter->setBaseSpeed(originalSpeed);
    targetCharacter = nullptr;
}