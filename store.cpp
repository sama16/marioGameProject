#include <QList>
#include <QDebug>
#include <Player.h>
#include <weapon.h>

class Store {
public:
    Store() {
        availableWeapons.append(new Bullet());
        availableWeapons.append(new Fireball());
    }

    void showStore() {
        qDebug() << "Welcome to the Store!";
        for (int i = 0; i < availableWeapons.size(); ++i) {
            qDebug() << i + 1 << ". " << availableWeapons[i]->getName();
        }
    }

    void purchaseWeapon(Player* player, int choice) {
        if (choice - 1 >= 0 && choice - 1 < availableWeapons.size()) {
            Weapon* weapon = availableWeapons[choice - 1];
            int cost = getWeaponCost(weapon);
            if (player->spendCoins(cost)) {
                player->setCurrentWeapon(weapon);
                qDebug() << weapon->getName() << " purchased!";
            } else {
                qDebug() << "Not enough coins!";
            }
        } else {
            qDebug() << "Invalid choice!";
        }
    }

private:
    QList<Weapon*> availableWeapons;

    int getWeaponCost(Weapon* weapon) {
        if (weapon->getName() == "Bullet") return 2;
        if (weapon->getName() == "Fireball") return 3;
        return 0;
    }
};

