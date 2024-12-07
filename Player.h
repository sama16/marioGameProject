#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "Weapon.h"  // Include Weapon header

class Player : public QGraphicsPixmapItem {
public:
    Player();  // Constructor for Player

    void handleInput(QKeyEvent* event, bool pressed);  // Handle left, right, and jump inputs
    void reset();  // Reset player state
    void stopMoving();  // Stop player movement
    void update();  // Update player position and physics

    void setCurrentWeapon(Weapon* weapon);  // Set the player's current weapon
    void useWeapon();  // Use the weapon
    bool spendCoins(int cost);  // Spend coins to buy weapons
    void checkForRewards();  // Check if the player earns coins or unlocks a weapon

    int getCoins() const;  // Get the player's coins
    int getScore() const;  // Get the player's score
    int getVelocityX() const;
    int getVelocityY() const;
      void fireBullet();

private:
    void jump();  // Perform jump action
    void applyGravity();  // Apply gravity to the player
    void land();  // Land on the ground

    int velocityX;  // Horizontal velocity
    int velocityY;  // Vertical velocity (used for jumping/falling)
    bool isJumping;  // Flag to check if the player is jumping

    const int jumpStrength = -15;  // Strength of the jump
    const int gravity = 1;  // Gravity strength pulling the player down
    const int maxFallSpeed = 10;  // Maximum fall speed to prevent falling too fast

    int coins;  // Number of coins the player has
    int score;  // Player's current score
    Weapon* currentWeapon;  // The weapon currently equipped by the player
};

#endif // PLAYER_H
