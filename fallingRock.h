#ifndef FALLINGROCK_H
#define FALLINGROCK_H

#include <QGraphicsPixmapItem>

class fallingRock : public QGraphicsPixmapItem {
public:
    fallingRock(int x, int y);

    void update();
    double getVelocityY(){return velocityY; }



private:
    double velocityY;  // Horizontal velocity of the enemy

};

#endif // ENEMY_H
