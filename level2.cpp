#include "level2.h"
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QRandomGenerator>
#include <QGraphicsView>

Level2::Level2(int score,QObject *parent)
    : QGraphicsScene(parent), newScreenTriggered(false) {
    this->score=score;
    // Set scene size to match the background size
    QPixmap bgPixmap(":/images/bg2.png");
    setSceneRect(0, 0, bgPixmap.width(), bgPixmap.height());
    // Create the background item and add it to the scene
    background = new QGraphicsPixmapItem(bgPixmap);
    addItem(background);
    background->setPos(0, 0); // Set background position to (0, 0)

    // Add the player
    player = new Player();
    addItem(player);
    player->setPosition(100, 380);
 // Add score display
    scoreText = new QGraphicsTextItem("Score: "+QString::number(score));
    scoreText->setDefaultTextColor(Qt::black);
    scoreText->setFont(QFont("Arial", 16));
    scoreText->setPos(30, 30); // Top-left corner
    addItem(scoreText);

    // Generate enemies and coins
    generateEnemies();
    generateCoins();

    // Set up a timer to update the scene periodically
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level2::updateScene);
    timer->start(20);
    updateScene();
}
void Level2::drawBackground(QPainter *painter, const QRectF &rect) {
    QPixmap backgroundPixmap(":/images/back.jpg"); // Path to background image
    painter->drawPixmap(0, 0, this->sceneRect().width(), this->sceneRect().height(), backgroundPixmap);
}

void Level2::keyPressEvent(QKeyEvent *event) {
    player->handleInput(event, true); // true means the key is pressed
}

void Level2::keyReleaseEvent(QKeyEvent *event) {
    player->handleInput(event, false); // false means the key is released
}

void Level2::triggerNewScreen() {
    QPixmap bgPixmap2(":/images/bg3.png");
    setSceneRect(0, 0, bgPixmap2.width(), bgPixmap2.height());
    background->setPixmap(bgPixmap2);
    background->setPos(0, 0);

    // Reset player position
    player->reset();
    player->update();
    player->setPosition(0, 380);

    // Optionally regenerate coins and enemies
    clearEnemiesAndCoins();
    generateEnemies();
    generateCoins();
}

void Level2::triggerEndScreen() {
    QPixmap bgPixmap3(":/images/end.jpg");

    // Scale and set up the end screen background
    QPixmap scaledBgPixmap = bgPixmap3.scaled(sceneRect().width(), sceneRect().height(), Qt::KeepAspectRatioByExpanding);
    setSceneRect(0, 0, scaledBgPixmap.width(), scaledBgPixmap.height());
    background->setPixmap(scaledBgPixmap);
    background->setPos(0, 0);

    // Reset player position
    player->setPosition(450, 290);
    player->stopMoving();

    clearEnemiesAndCoins();

    // Add overlay and game over message
    QGraphicsRectItem *overlay = new QGraphicsRectItem();
    overlay->setRect(sceneRect());
    overlay->setBrush(QColor(0, 0, 0, 150));
    overlay->setZValue(1);
    addItem(overlay);

    QGraphicsTextItem *textItem = new QGraphicsTextItem("Game Complete! Thank you for playing!");
    textItem->setDefaultTextColor(Qt::white);
    textItem->setFont(QFont("Arial", 24, QFont::Bold));
    textItem->setZValue(2);
    textItem->setPos(sceneRect().width() / 2 - textItem->boundingRect().width() / 2,
                     sceneRect().height() / 2 - textItem->boundingRect().height() / 2);
    addItem(textItem);
}

void Level2::updateScene() {
    player->update();

    for (Coin *coin : coins) {
        coin->setPos(coin->x() - player->getVelocityX(), coin->y());
    }

    for (Enemy *enemy : enemies) {
        enemy->update();
    }

    for (Coin *coin : coins) {
        if (player->collidesWithItem(coin)) {
            updateScore(10);
            removeItem(coin);
            coins.removeOne(coin);
            delete coin;
            break;
        }
    }

    handleEnemyCollisions();

    if (!newScreenTriggered && player->x() >= sceneRect().width()) {
        newScreenTriggered = true;
        triggerNewScreen();
    }

    if (newScreenTriggered && player->x() >= sceneRect().width()) {
        triggerEndScreen();
    }
}

// void Level2::showGameOverMessage(const QString &message) {
//     QGraphicsRectItem *overlay = new QGraphicsRectItem();
//     overlay->setRect(sceneRect());
//     overlay->setBrush(QColor(0, 0, 0, 150));
//     overlay->setZValue(1);
//     addItem(overlay);

//     QGraphicsTextItem *textItem = new QGraphicsTextItem(message);
//     textItem->setDefaultTextColor(Qt::white);
//     textItem->setFont(QFont("Arial", 24, QFont::Bold));
//     textItem->setZValue(2);
//     textItem->setPos(sceneRect().width() / 2 - textItem->boundingRect().width() / 2,
//                      sceneRect().height() / 2 - textItem->boundingRect().height() / 2);
//     addItem(textItem);
// }

void Level2::clearEnemiesAndCoins() {
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
}

void Level2::generateEnemies() {
    for (int i = 0; i < 5; ++i) {
        bool validPosition = false;
        int randomX;

        while (!validPosition) {
            randomX = QRandomGenerator::global()->bounded(100, 800);
            validPosition = true;

            for (Enemy *existingEnemy : enemies) {
                if (qAbs(existingEnemy->x() - randomX) < 100) {
                    validPosition = false;
                    break;
                }
            }
        }

        Enemy *enemy = new Enemy(randomX, 420);
        enemies.append(enemy);
        addItem(enemy);
    }
}

void Level2::generateCoins() {
    for (int i = 0; i < 10; ++i) {
        bool validPosition = false;
        int randomX, randomY;

        while (!validPosition) {
            randomX = QRandomGenerator::global()->bounded(100, 800);
            randomY = QRandomGenerator::global()->bounded(250, 350);

            validPosition = true;

            for (Coin *existingCoin : coins) {
                if (qAbs(existingCoin->x() - randomX) < 50 && qAbs(existingCoin->y() - randomY) < 50) {
                    validPosition = false;
                    break;
                }
            }

            for (Enemy *existingEnemy : enemies) {
                if (qAbs(existingEnemy->x() - randomX) < 50 && qAbs(existingEnemy->y() - randomY) < 50) {
                    validPosition = false;
                    break;
                }
            }
        }

        Coin *coin = new Coin(randomX, randomY);
        coins.append(coin);
        addItem(coin);
    }
}


void Level2::handleEnemyCollisions() {
    for (Enemy *enemy : enemies) {
        if (player->collidesWithItem(enemy) && player->getVelocityY() > 0) {
            updateScore(10);
            removeItem(enemy);
            enemies.removeOne(enemy);
            delete enemy;
            break;
        }

        if (player->collidesWithItem(enemy) && player->y() == 380) {
            // updateScore(-10);
            qDebug() << "Player hit by enemy! Score decreased.";
        }
    }
}
void Level2::updateScore(int change) {
    score += change;
    // Update the score display
    scoreText->setPlainText(QString("Score: %1").arg(score));
}
