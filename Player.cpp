#include "Player.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QDebug>
#include "Weapon.h"  // Include Weapon header here

// Constructor
Player::Player() {
    // Load the image for Mario
    QPixmap marioPixmap(":/images/mario.png");  // Path to your image file
    marioPixmap = marioPixmap.scaled(70, 70, Qt::KeepAspectRatio);  // Resize
    setPixmap(marioPixmap);

    // Initialize Mario's velocity and state
    velocityX = 0;  // Horizontal velocity (no movement initially)
    velocityY = 0;  // Initial vertical velocity (not jumping initially)
    isJumping = false;
    setPos(100, 380);  // Initial position at x=100, y=380 (ground level)

    // Initialize coins and score
    coins = 0;
    score = 0;
    currentWeapon = nullptr;
}

// Handle input (left, right, spacebar for jump and weapon usage)
void Player::handleInput(QKeyEvent* event, bool pressed) {
    // Handle left and right movement based on key press
    if (event->key() == Qt::Key_Left) {
        velocityX = pressed ? -5 : 0;  // Move left (negative velocity) when pressed
    } else if (event->key() == Qt::Key_Right) {
        velocityX = pressed ? 5 : 0;  // Move right (positive velocity) when pressed
    }

    // Handle jump action based on the spacebar
    if (event->key() == Qt::Key_Space && pressed && !isJumping) {
        jump();  // If Space is pressed and Mario is not already jumping
    }

    if (event->key() == Qt::Key_Space && pressed && currentWeapon && currentWeapon->getName() == "Bullet") {
        fireBullet();
    }
}

// Reset player state (used when respawning or after dying)
void Player::reset() {
    velocityX = 0;
    velocityY = 0;
    isJumping = false;
}

// Stop the player from moving (used when pausing or other conditions)
void Player::stopMoving() {
    velocityX = 0;
    velocityY = 0;
}

// Update player position, gravity, and jumping
void Player::update() {
    applyGravity();  // Apply gravity to pull Mario down

    // Update Mario's position based on horizontal and vertical velocities
    setPos(x() + velocityX, y() + velocityY);

    // Ensure Mario doesn't fall through the ground (or any platforms)
    if (y() >= 380) {
        land();  // If Mario reaches the ground, he lands
    }

    // Limit the falling speed
    if (velocityY > maxFallSpeed) {
        velocityY = maxFallSpeed;
    }

    // Check if the player has earned a reward or unlocked a new weapon
    checkForRewards();
}

// Perform a jump
void Player::jump() {
    velocityY = jumpStrength;
    isJumping = true;
}

// Apply gravity effect (pulls the player down if in the air)
void Player::applyGravity() {
    if (isJumping) {
        velocityY += gravity;
    }
}

// Land on the ground and stop falling
void Player::land() {
    if (y() >= 380) {
        velocityY = 0;
        isJumping = false;
        setPos(x(), 380);  // Set y-position to the ground level
    }
}

// Set the current weapon for the player
void Player::setCurrentWeapon(Weapon* weapon) {
    currentWeapon = weapon;
    qDebug() << "Weapon set to:" << weapon->getName();
}

// Use the current weapon (if equipped)
void Player::useWeapon() {
    if (currentWeapon) {
        currentWeapon->activate();  // Activate the weapon
        if (currentWeapon->getName() == "Bullet") {
            Bullet* bullet = dynamic_cast<Bullet*>(currentWeapon);
            if (bullet) {
                bullet->shoot();  // Trigger the shoot method for bullet
            }
        }
    }
}

// Check if the player should earn coins or unlock a weapon
void Player::checkForRewards() {
    if (score == 70 && currentWeapon == nullptr) {
        // Unlock the Bullet weapon when score reaches 70
        Bullet* bullet = new Bullet();
        setCurrentWeapon(bullet);  // Equip the Bullet weapon to the player
        qDebug() << "New weapon unlocked: Bullet!";
    }
}

// Getter for coins
int Player::getCoins() const {
    return coins;
}

// Getter for score
int Player::getScore() const {
    return score;
}

int Player::getVelocityX() const {
    return velocityX;
}

int Player::getVelocityY() const {
    return velocityY;
}

void Player::fireBullet() {
    Bullet* bullet = new Bullet(true);  // Set 'true' for facing right
    bullet->setPos(x() + 30, y() + 10); // Position the bullet in front of Mario (adjust if needed)
    scene()->addItem(bullet);  // Add the bullet to the scene
    qDebug() << "Bullet fired!";
