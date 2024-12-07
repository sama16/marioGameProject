#include "Bullet.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsItem>
#include "Enemy.h" // Assuming you have an Enemy class

Bullet::Bullet(bool isFacingRight) : facingRight(isFacingRight), active(true) {
    // Load the bullet image from resources
    QPixmap bulletPixmap(":/images/bullet.png");  // Assuming you added it to the .qrc file
    setPixmap(bulletPixmap);

    // Set the bullet's initial position in front of Mario
    setPos(facingRight ? 100 : -100, 380); // Start bullet to the right or left of Mario

    // Set the timer to move the bullet across the screen
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(20); // Move the bullet every 20ms
}

void Bullet::move() {
    // Move the bullet in the direction it's facing (left or right)
    if (facingRight) {
        setPos(x() + 10, y());  // Move right by 10 units
    } else {
        setPos(x() - 10, y());  // Move left by 10 units
    }

    // Check for collision with enemies
    QList<QGraphicsItem*> collidingItems = collidingItems();
    for (auto item : collidingItems) {
        if (dynamic_cast<Enemy*>(item)) {  // Check if the item is an Enemy
            Enemy* enemy = dynamic_cast<Enemy*>(item);
            enemy->takeDamage(damage);  // Deal damage to the enemy
            active = false;
            scene()->removeItem(this);  // Remove bullet from scene
            delete this;  // Clean up
            break;
        }
    }

    // Remove bullet if off-screen
    if (x() < 0 || x() > 800) { // Assuming screen width is 800
        active = false;
        scene()->removeItem(this);
        delete this;
    }
}

bool Bullet::isActive() const {
    return active;
}

