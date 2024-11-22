#include "WelcomeWindow.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QWidget(parent) {

    // Set the window size to match the background image size
    setFixedSize(800, 600);  // Adjust based on your image size

    // Create the "Start Game" button
    startButton = new QPushButton("Start Game", this);
    startButton->setGeometry(350, 450, 100, 40);  // Position the button (x, y, width, height)

    // Connect the button to the signal to start the game
    connect(startButton, &QPushButton::clicked, this, &WelcomeWindow::startGameClicked);
}

void WelcomeWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Load and draw the background image
    QPixmap background(":/images/welcomeImage.png");  // Path to your background image
    painter.drawPixmap(0, 0, width(), height(), background);

    // Optionally, you can draw additional elements (like text, logo) on top of the background
}
