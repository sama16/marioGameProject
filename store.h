#ifndef STORE_H
#define STORE_H

#include "Weapon.h"
#include "Player.h"
#include <QList>

class Store {
public:
    Store();
    ~Store();

    void showStore();  // Display available weapons in the store
    void purchaseWeapon(Player* player, int choice);  // Allow the player to purchase a weapon

private:
    QList<Weapon*> availableWeapons;  // List of available weapons for purchase

    int getWeaponCost(Weapon* weapon);  // Get the cost of a weapon
};

#endif // STORE_H

