#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsItem>
#include <QPainter>

class HealthBar : public QGraphicsItem {
public:
    HealthBar(qreal width = 100, qreal height = 10, QGraphicsItem *parent = nullptr);
    void setHealth(int current, int max);
    void setPosition(qreal x, qreal y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    
private:
    qreal barWidth;
    qreal barHeight;
    int currentHealth;
    int maxHealth;
};

#endif