#include "GameWindow.h"
#include <QGraphicsView>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Create the game scene

    scene = new GameScene(this);

    // Create the view to display the scene
    view = new QGraphicsView(scene, this);
    // Set the fixed size of the view to match the scene (background size)
    view->setFixedSize(scene->sceneRect().width(), scene->sceneRect().height());

    // Set the view as the central widget
    setCentralWidget(view);

    connect(scene, &GameScene::level2Requested, this, &GameWindow::loadLevel2);


  // Set the timer for game updates
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &GameScene::updateScene);
    timer->start(20); // Approx 60 FPS
     level2Timer = new QTimer(this);


}
void GameWindow::loadLevel2() {
    qDebug() << "Loading Level 2...";

    // Stop the GameScene timer
    if (timer->isActive()) {
        timer->stop();
    }

    // Create Level 2 scene if not already created
    if (!level2Scene) {
        int level1Score = scene->getScore();
        level2Scene = new Level2(level1Score,this);
    }

    // Set Level 2 scene to the view
    view->setScene(level2Scene);

    // Connect and start the Level 2 timer
    connect(level2Timer, &QTimer::timeout, level2Scene, &Level2::updateScene);
    level2Timer->start(10); // ~60 FPS
}

