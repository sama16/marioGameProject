#include <QString>
#include <QDebug>
#include <QTimer>

class Weapon {
public:
    Weapon(QString name, int damage, int duration)
        : name(name), damage(damage), duration(duration), active(false) {}

    virtual void activate() {
        active = true;
        qDebug() << name << " activated!";
    }

    void deactivate() {
        active = false;
        qDebug() << name << " deactivated.";
    }

    QString getName() { return name; }
    int getDamage() { return damage; }
    bool isActive() { return active; }

protected:
    QString name;
    int damage;
    int duration;
    bool active;
};

// Bullet Weapon
class Bullet : public Weapon {
public:
    Bullet() : Weapon("Bullet", 10, 5) {}

    void shoot() {
        if (isActive()) {
            qDebug() << "Bullet fired!";
        }
    }

};

// Fireball Weapon
class Fireball : public Weapon {
public:
    Fireball() : Weapon("Fireball", 20, 3) {}

    void shoot() {
        if (isActive()) {
            qDebug() << "Fireball fired!";
        }
    }
};
