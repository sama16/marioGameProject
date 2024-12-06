#include "fallingRock.h"
#include <QPixmap>

// Constructor for rock class
fallingRock::fallingRock(int x, int y) {
    setPixmap(QPixmap("C:/Users/Rana/Documents/GitHub/marioGameProject/rocknew.png").scaled(30, 30)); // Load coin sprite
    setPos(x, y);

    // Initialize horizontal velocity
    velocityY = 5.2;  // Speed of movement (positive for right, negative for left)
}

// Update the rock's position and movement
void fallingRock::update() {
    // Move the rock horizontally by velocityX
    setPos(x(), y() + velocityY);

    // Get the width of the scene (assuming 800 pixels)
    int sceneWidth = 800;  // Set the scene width

    // Get the width of the rock
    int rockWidth = pixmap().width();  // Get the width of the rock sprite

    // If the rock hits the left boundary (x <= 0), reverse direction
    if (y() <= 0) {
        velocityY = -velocityY;  // Reverse direction
    }

    // If the rock hits the right boundary (x >= sceneWidth - rockWidth), reverse direction
    else if (y() >= sceneWidth - rockWidth) {
        velocityY = -velocityY;  // Reverse direction
    }
}
