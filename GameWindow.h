#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "GameScene.h"
#include"level2.h"
class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    void loadLevel2();

private:
    GameScene *scene;
    Level2 *level2Scene;
    QGraphicsView *view;
    QTimer *timer;
     QTimer *level2Timer;
};

#endif // GAMEWINDOW_H
