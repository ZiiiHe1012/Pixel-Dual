//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_BATTLESCENE_H
#define QT_PROGRAMMING_2024_BATTLESCENE_H

#include <QKeyEvent>
#include <QList>
#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/HealthBar/HealthBar.h"
#include "../Items/Projectiles/Projectile.h"

class BattleScene : public Scene {
Q_OBJECT

public:
    explicit BattleScene(QObject *parent);

    void processInput() override;

    void processMovement() override;

    void processPicking() override;

protected slots:

    void update() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private:

    Mountable *findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());

    static Mountable * pickupMountable(Character *character, Mountable *mountable);

    Map *map;
    Character *character;
    Character *character2;  // 第二个角色
    QList<Platform*> platforms;
    QList<Terrain*> terrains;
    HealthBar* characterHealthBar;
    HealthBar* character2HealthBar;  // 第二个角色的血条
    Armor *spareArmor;
    // 子弹类
    QList<Projectile*> activeProjectiles;
    void updateProjectiles();
    void onProjectileFinished(Projectile* projectile);
    // 游戏结束
    bool gameOver = false;
    QGraphicsTextItem* winnerText = nullptr;
    void showWinner(int playerNumber);
    void endGame();
};


#endif //QT_PROGRAMMING_2024_BATTLESCENE_H
