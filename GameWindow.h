#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "GameScene.h"

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);

private:
    GameScene *scene;
    QGraphicsView *view;
    QTimer *timer;
};

#endif // GAMEWINDOW_H
