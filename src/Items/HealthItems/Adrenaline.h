#ifndef ADRENALINE_H
#define ADRENALINE_H

#include "HealthItem.h"
#include <QTimer>
#include <QObject>

class Adrenaline : public QObject, public HealthItem {
    Q_OBJECT
    
public:
    explicit Adrenaline(QGraphicsItem *parent = nullptr);
    ~Adrenaline();
    
    void applyToCharacter(Character* character) override;
    
private slots:
    void healTick();
    void endSpeedBoost();
    
private:
    QTimer* healTimer = nullptr;
    QTimer* speedTimer = nullptr;
    Character* targetCharacter = nullptr;
    int healTickCount = 0;
    qreal originalSpeed = 0;  // 原始速度

    static constexpr int HEAL_PER_TICK = 6;      // 每秒回血量
    static constexpr int TOTAL_HEAL_TICKS = 5;   // 总共回血5次
    static constexpr int HEAL_INTERVAL = 1000;   // 回血间隔
    static constexpr int SPEED_DURATION = 5000;  // 加速持续时间
    static constexpr qreal SPEED_MULTIPLIER = 1.5; // 速度倍数
};

#endif