#include "HealthBar.h"

HealthBar::HealthBar(qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsItem(parent), barWidth(width), barHeight(height), 
      currentHealth(100), maxHealth(100) {
    setZValue(100);
}

void HealthBar::setHealth(int current, int max) {
    currentHealth = current;
    maxHealth = max;
    update(); // 触发重绘
}

void HealthBar::setPosition(qreal x, qreal y) {
    setPos(x, y);
}

QRectF HealthBar::boundingRect() const {
    return QRectF(-2, -2, barWidth + 4, barHeight + 4);
}

void HealthBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    // 抵消父项的水平镜像变换
    if (this->sceneTransform().m11() < 0) {
        painter->translate(barWidth, 0); 
        painter->scale(-1, 1);
    }
    // 绘制背景框
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::darkGray);
    painter->drawRect(0, 0, barWidth, barHeight);
    // 计算健康比例
    qreal healthRatio = (maxHealth > 0) ? (qreal)currentHealth / maxHealth : 0;
    qreal healthWidth = barWidth * healthRatio;
    // 根据健康值选择颜色
    QColor healthColor;
    if (healthRatio > 0.6) {
        healthColor = Qt::green;
    } else if (healthRatio > 0.3) {
        healthColor = QColor(255, 165, 0);
    } else {
        healthColor = Qt::red;
    }
    // 绘制健康条
    painter->setPen(Qt::NoPen);
    painter->setBrush(healthColor);
    painter->drawRect(0, 0, healthWidth, barHeight);
    // 绘制文字
    painter->setPen(QColor(0, 0, 0));
    painter->setFont(QFont("Arial", 6));
    QString healthText = QString("%1/%2").arg(currentHealth).arg(maxHealth);
    painter->drawText(QRectF(0, 0.5, barWidth, barHeight), Qt::AlignCenter, healthText);
    painter->restore();
}