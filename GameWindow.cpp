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


    // Set the timer for game updates
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &GameScene::updateScene);
    timer->start(16); // Approx 60 FPS
}
