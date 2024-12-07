#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(bool isFacingRight);

    void move();
    bool isActive() const;

private:
    bool active;  // Bullet state (active or inactive)
    bool facingRight;  // Direction the bullet is facing
};

#endif // BULLET_H

