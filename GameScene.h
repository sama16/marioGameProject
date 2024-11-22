#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"

class GameScene : public QGraphicsScene {
    Q_OBJECT

public:
    GameScene(QObject *parent = nullptr);
    void paintEvent(QPaintEvent *event) ;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void generateRandomCoins(int numberOfCoins);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void triggerNewScreen();
    void  triggerEndScreen();
    void showGameOverMessage(const QString &message);



   void clearEnemiesAndCoins();
    void generateEnemies();

    void generateCoins();

    void moveItemsWithPlayer();


    // Check for collisions with coins
    void handleCoinCollisions();

    // Check for collisions with enemies (mushrooms)
    void handleEnemyCollisions();

public slots:
    void updateScene();

private:
      bool newScreenTriggered;
    Player *player;
    QList<Coin *> coins;
    QList<Enemy *> enemies;
    QGraphicsPixmapItem *background;


    int score;                  // Variable to track the score
    QGraphicsTextItem *scoreText;  // Text item to display the score

    void updateScore(int change); // Function to update the score
};

#endif // GAMESCENE_H
