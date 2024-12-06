#include "GameScene.h"
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QRandomGenerator>
#include<QGraphicsView>
GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent),newScreenTriggered(false), score(0) {
    // Set scene size to match the background size
    QPixmap bgPixmap(":/images/bg2.png");
    setSceneRect(0, 0, bgPixmap.width(), bgPixmap.height());
  //  Create the background item and add it to the scene
    background = new QGraphicsPixmapItem(bgPixmap);
    addItem(background);
    background->setPos(0, 0);  // Set background position to (0, 0)
    // Add the player
    player = new Player();
    addItem(player);
    player->setPosition(100,  380);  // S
    // Add score display
    scoreText = new QGraphicsTextItem("Score: 0");
    scoreText->setDefaultTextColor(Qt::black);
    scoreText->setFont(QFont("Arial", 16));
    scoreText->setPos(30, 30); // Top-left corner
    addItem(scoreText);
    generateEnemies();
    generateRocks();
    generateCoins();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::updateScene);
    timer->start(20);
    updateScene();
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect) {
    // Load the background image and stretch it to cover the entire scene
    QPixmap backgroundPixmap(":/images/back.jpg");  // Path to background image
    painter->drawPixmap(0, 0, this->sceneRect().width(), this->sceneRect().height(), backgroundPixmap);
}

void GameScene::keyPressEvent(QKeyEvent *event) {
    player->handleInput(event, true);  // true means the key is pressed
}

void GameScene::keyReleaseEvent(QKeyEvent *event) {
    player->handleInput(event, false);  // false means the key is released
}
void GameScene::triggerNewScreen() {

    QPixmap bgPixmap2(":/images/bg3.png");
    setSceneRect(0, 0, bgPixmap2.width(), bgPixmap2.height());
    background->setPixmap(bgPixmap2);
    background->setPos(0, 0);

    // Reset Mario's position to the left
    player->reset();
    player->update();
    player->setPosition(0, 380);


    // Optionally regenerate coins and enemies for the new screen
    clearEnemiesAndCoins();
    generateEnemies();
    generateCoins();
    generateRocks();
        // Now that we're on the new screen, check if the player is at the end of the screen
    // if (newScreenTriggered && ) {
    //     // Trigger end screen after Mario reaches the right edge
    //     triggerEndScreen();
    // }
}
void GameScene::triggerEndScreen() {
    // Set up the end screen background
    QPixmap bgPixmap3(":/images/end.jpg");

    // Get the scene dimensions (width and height)
    double sceneWidth = sceneRect().width();
    double sceneHeight = sceneRect().height();

    // Scale the background image to match the scene size
    QPixmap scaledBgPixmap = bgPixmap3.scaled(sceneWidth, sceneHeight, Qt::KeepAspectRatioByExpanding);

    // Update the scene with the new scaled background
    setSceneRect(0, 0, scaledBgPixmap.width(), scaledBgPixmap.height());
    background->setPixmap(scaledBgPixmap);
    background->setPos(0, 0);  // Position the background at the top-left corner
// Reset Mario's position to the calculated ground level
    player->setPosition(450, 290);
      player->stopMoving();
    clearEnemiesAndCoins() ;

   // Create a dark overlay to show a message
    QGraphicsRectItem *overlay = new QGraphicsRectItem();
    overlay->setRect(sceneRect());  // Ensure it covers the whole scene
    overlay->setBrush(QColor(0, 0, 0, 150));  // Black with some opacity
    overlay->setZValue(1);  // Overlay should be above the background
    addItem(overlay);

    // Create the game over message
    QGraphicsTextItem *textItem = new QGraphicsTextItem("Game Complete! Thank you for playing!");
    textItem->setDefaultTextColor(Qt::white);
    textItem->setFont(QFont("Arial", 24, QFont::Bold));
    textItem->setZValue(2);  // Make sure the text is above the overlay
    textItem->setPos(sceneRect().width() / 2 - textItem->boundingRect().width() / 2,
                     sceneRect().height() / 2 - textItem->boundingRect().height() / 2);  // Center the text
    addItem(textItem);
}

void GameScene::updateScene() {

    player->update();

    // Move coins and enemies with the player
    for (Coin *coin : coins) {
        coin->setPos(coin->x() - player->getVelocityX(), coin->y());
    }

    // Move enemies with the player
    for (Enemy *enemy : enemies) {
        enemy->update();  // Update the movement of the enemies
    }

    for (fallingRock *rockfall : rocks) {
        rockfall->update();  // Update the movement of the enemies
    }

    // Check for collisions with coins
    for (Coin *coin : coins) {
        if (player->collidesWithItem(coin)) {
            updateScore(1); // Increase score
            removeItem(coin);
            coins.removeOne(coin);
            delete coin;
            break;
        }
    }

    // Check for collisions with enemies (mushrooms)
    for (int i = 0; i < enemies.size(); ++i) {
        handleEnemyCollisions();
    }
    if (!newScreenTriggered && player->x() >= sceneRect().width()) {
         newScreenTriggered = true;
        triggerNewScreen();
         // Prevent further triggering
    }
    // Trigger a new screen if the player reaches the right edge

    if (newScreenTriggered && player->x() >= sceneRect().width()) {
        triggerEndScreen();
    }
    // Trigger a new screen if Mario reaches the right edge of the first screen

}



void GameScene::showGameOverMessage(const QString &message) {
    QGraphicsRectItem *overlay = new QGraphicsRectItem();
    overlay->setRect(sceneRect());  // Ensure it covers the whole scene
    overlay->setBrush(QColor(0, 0, 0, 150));  // Black with 50% opacity
    overlay->setZValue(1);  // Make sure the overlay is above the background
    addItem(overlay);

    // Create a text item to display the message
    QGraphicsTextItem *textItem = new QGraphicsTextItem(message);
    textItem->setDefaultTextColor(Qt::white);
    textItem->setFont(QFont("Arial", 24, QFont::Bold));
    textItem->setZValue(2);  // Make sure the text is above the overlay
    textItem->setPos(sceneRect().width() / 2 - textItem->boundingRect().width() / 2,
                     sceneRect().height() / 2 - textItem->boundingRect().height() / 2);  // Center the text
    addItem(textItem);

    // Stop the game updates by stopping the timer or game loop


}
void GameScene::clearEnemiesAndCoins() {
    // Remove existing enemies and coins from the scene
    for (Enemy *enemy : enemies) {
        removeItem(enemy);
        delete enemy;
    }
    enemies.clear();

    for (Coin *coin : coins) {
        removeItem(coin);
        delete coin;
    }
    coins.clear();

    for (fallingRock *rock : rocks) {
        removeItem(rock);
        delete rock;
    }
    rocks.clear();
}

void GameScene::generateEnemies() {

        for (int i = 0; i < 5; ++i) {  // Adjust the number of enemies as needed
            bool validPosition = false;
            int randomX;
            // Try finding a valid position for the enemy
            while (!validPosition) {
                randomX = QRandomGenerator::global()->bounded(100, 800);  // Random x-coordinate (100 to 800)

                // Check if the new enemy overlaps with any existing enemy
                validPosition = true;
                for (Enemy *existingEnemy : enemies) {
                    if (qAbs(existingEnemy->x() - randomX) < 100) {  // Ensure minimum distance (100 pixels in this case)
                        validPosition = false;
                        break;  // Skip to the next iteration if overlap is detected
                    }
                }
            }

            // Create the enemy at the valid random position
            Enemy *enemy = new Enemy(randomX, 420);  // y-position fixed at 530 (ground level)
            enemies.append(enemy);
            addItem(enemy);
        }
}

void GameScene::generateRocks() {

    for (int i = 0; i < 5; ++i) {  // Adjust the number of enemies as needed
        bool validPosition = false;
        int randomY;
        // Try finding a valid position for the enemy
        while (!validPosition) {
            randomY = QRandomGenerator::global()->bounded(100, 800);  // Random x-coordinate (100 to 800)
            randomY = QRandomGenerator::global()->bounded(100, 800);
            randomY = QRandomGenerator::global()->bounded(100, 800);
            // Check if the new enemy overlaps with any existing enemy
            validPosition = true;
            for (fallingRock *existingrock : rocks) {
                if (qAbs(existingrock->y() - randomY) < 100) {  // Ensure minimum distance (100 pixels in this case)
                    validPosition = false;
                    break;  // Skip to the next iteration if overlap is detected
                }
            }
        }

        // Create the enemy at the valid random position
        fallingRock *fallingrock = new fallingRock(420, randomY);  // y-position fixed at 530 (ground level)
        rocks.append(fallingrock);
        addItem(fallingrock);
    }
}

void GameScene::generateCoins() {
    // Add coins randomly on the y-axis and ensure they are separated from mushrooms
        for (int i = 0; i < 10; ++i) {
            bool validPosition = false;
            int randomX, randomY;

            // Try finding a valid position for the coin
            while (!validPosition) {
                randomX = QRandomGenerator::global()->bounded(100, 800);  // Random x-coordinate (100 to 800)
                randomY = QRandomGenerator::global()->bounded(250, 350);  // Adjust y-coordinate (higher than before)

                // Check if the new coin overlaps with any existing coin
                validPosition = true;
                for (Coin *existingCoin : coins) {
                    if (qAbs(existingCoin->x() - randomX) < 50 && qAbs(existingCoin->y() - randomY) < 50) {
                        validPosition = false;
                        break;  // Skip to the next iteration if overlap is detected
                    }
                }

                // Ensure coins don't overlap with enemies
                for (Enemy *existingEnemy : enemies) {
                    if (qAbs(existingEnemy->x() - randomX) < 50 && qAbs(existingEnemy->y() - randomY) < 50) {
                        validPosition = false;
                        break;  // Skip to the next iteration if overlap with enemy is detected
                    }
                }
            }

            // Create the coin at the valid random position
            Coin *coin = new Coin(randomX, randomY);
            coins.append(coin);
            addItem(coin);
        }
}


void GameScene::handleEnemyCollisions() {
    // Check for collisions with enemies (mushrooms)
    for (Enemy *enemy : enemies) {
        if (player->collidesWithItem(enemy) && player->getVelocityY() > 0) {
            // Mario defeats the enemy by jumping on top
            updateScore(1);
            removeItem(enemy);
            enemies.removeOne(enemy);
            delete enemy;
            break;  // Exit loop since this enemy is handled
        }

        if (player->collidesWithItem(enemy) && player->y() == 380) {
            // Mario collides with the enemy (not jumping)
            updateScore(2);  // Decrease score by 10
            qDebug() << "Player hit by enemy! Score decreased by 10.";
        }
    }

    for (fallingRock *rockfall : rocks) {
        if (player->collidesWithItem(rockfall) && player->getVelocityY() > 0) {
            // Mario defeats the rockfall by jumping on top
            updateScore(1);
            removeItem(rockfall);
            rocks.removeOne(rockfall);
            delete rockfall;
            break;  // Exit loop since this rockfall is handled
        }

       if (player->collidesWithItem(rockfall) && player->y() == 380) {
            // Mario collides with the enemy (not jumping)
            updateScore(2);  // Decrease score by 10
            qDebug() << "Player hit by rock! Score decreased by 10.";
        }
    }
}

void GameScene::updateScore(int change) {

    if(change==1){
        score=score+10;
    }
    if(change==2){
        score=score-100;
    }
    if(score<0){
        score=0;
    }


    // Update the score display
    scoreText->setPlainText(QString("Score: %1").arg(score));
}
