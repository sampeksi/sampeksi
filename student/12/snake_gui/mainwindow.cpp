#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QKeyEvent>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creating the visual gameboard.
    scene_ = new QGraphicsScene(this);

    // Gameboard is placed top left corner.
    // +2 is added since margins take one pixel from each side.
    ui->graphicsView->setGeometry(0, 0, length_ +2, width_ + 2);
    ui->graphicsView->setScene(scene_);

    // Both length and with are decreased by one since food and snake
    // are considered to be inside sceneRect.
    scene_->setSceneRect(0, 0, length_ - 1, width_ - 1);

    ui->graphicsView->show();

    // Drawimages is called to make head appear immidiately.
    drawImages();

    // Setting ranges for slider that are used to change visual gameboard's
    // size
    ui->horizontalSliderHeight->setRange(0, SLIDER_MAX_VALUE);
    ui->horizontalSliderWidth->setRange(0, SLIDER_MAX_VALUE);

    // At first gameboard's size is at max.¨
    ui->horizontalSliderHeight->setValue(SLIDER_MAX_VALUE);
    ui->horizontalSliderWidth->setValue(SLIDER_MAX_VALUE);

    // Connecting buttons.
    connect(ui->horizontalSliderHeight, &QSlider::valueChanged, this,
            &MainWindow::playgroundSizeChanged);
    connect(ui->horizontalSliderWidth, &QSlider::valueChanged, this,
            &MainWindow::playgroundSizeChanged);

    connect(ui->pushButtonStart, &QPushButton::clicked, this,
            &MainWindow::pushButtonStartClicked);

    // Stenning colors for timer and scoreboard.
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::green);
    ui->lcdNumberScore->setAutoFillBackground(true);
    ui->lcdNumberScore->setPalette(pal);

    pal.setColor(QPalette::Window, Qt::blue);
    ui->lcdNumberTime->setAutoFillBackground(true);
    ui->lcdNumberTime->setPalette(pal);

    // Connecting both timers with right slots.
    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this,
           &MainWindow::gameSimulation);

    secondTimer_.setSingleShot(false),
    connect(&secondTimer_, &QTimer::timeout, this,
           &MainWindow::gameTimer);

    // Connecting pause and reset putton with right slots.
    connect(ui->pushButtonPause, SIGNAL(clicked()), this,
            SLOT(pushButtonPauseClicked()));

    connect(ui->pushButtonReset, SIGNAL(clicked()), this,
            SLOT(pushButtonResetClicked()));

    // Setting pause button unenable, since game is not running.
    ui->pushButtonPause->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!paused_) { // If game is paused, nothing happens.

    if (event->key() == Qt::Key_W and direction_ != "s") {
        direction_ = "w";
    }
    if (event->key() == Qt::Key_S and direction_ != "w") {
        direction_ = "s";
    }
    if (event->key() == Qt::Key_A and direction_ != "d") {
        direction_ = "a";
    }
    if (event->key() == Qt::Key_D and direction_ != "a") {
        direction_ = "d";
    }
    }
}

void MainWindow::drawImages()
{
    // Creating vector with filenames.
    const vector<string> images = {"rat", "snakehead"};

    // Defining path for .png files.
    const string PREFIX(":/");
    const string SUFFIX(".png");

    // Image of rat is found from this path.
    string file1 = PREFIX + images[0] + SUFFIX;

    // Creating graphic image from the image inside the file.
    QImage ratImage(QString::fromStdString(file1));
    QGraphicsPixmapItem* rat = new QGraphicsPixmapItem(
                                   QPixmap::fromImage(ratImage));

    // Decreasing size of the image.
    rat->setScale(0.02);

    // DEfining that item is movable.
    rat->setFlags(QGraphicsItem::ItemIsMovable);

    // Making variable out of the graphic item.
    food_ = rat;

    // Setting image outside of the screen so it won't show at first.
    food_->setPos(-100, -100);

    // setZValue is used to "lift" the image above the board.
    // This is critical when painting squares back to default color.
    food_->setZValue(2);
    scene_->addItem(rat);

    // Same steps for snake besides the image will appear on the screen
    // right away.
    string file2 = PREFIX + images[1] + SUFFIX;
    QImage snakeheadImage(QString::fromStdString(file2));
    QGraphicsPixmapItem* snakehead = new QGraphicsPixmapItem(
                                   QPixmap::fromImage(snakeheadImage));
    snakehead->setScale(0.01);
    snakehead->setFlags(QGraphicsItem::ItemIsMovable);
    head_ = snakehead;

    head_->setZValue(2);
    head_->setPos(length_ / 2, width_ / 2);
    scene_->addItem(snakehead);
}

void MainWindow::playgroundSizeChanged()
{
    int length = ui->horizontalSliderHeight->value();
    int width = ui->horizontalSliderWidth->value();

    // Updates the dimensions.
    length_ = length;
    width_ = width;

    // Visual gameboard is changed based on given dimensions.
    ui->graphicsView->setGeometry(0, 0, length_ +2, width_ + 2);
    ui->graphicsView->setScene(scene_);
    scene_->setSceneRect(0, 0, length_ - 1, width_ - 1);

    ui->graphicsView->setScene(scene_);
    ui->graphicsView->show();

    // Head is also repositioned.
    head_->setPos(length_ / 2, width_ /2);

}

void MainWindow::gameSimulation()
{
    if (paused_) { // Game will stop if pause button has been clicked.
        timer_.stop();
    } else {

    // if game has ended timers will be stopped and result of the game stated.
    if (Board.back().gameOver()) {
        secondTimer_.stop();
        timer_.stop();

        // Screen turns green if player won, else turns red.
        // Text label prints message about the situation.
        if (Board.back().gameLost()) {
            ui->labelGameEnd->setText("You lost :(");
            scene_->setForegroundBrush(Qt::red);

        } else {
            ui->labelGameEnd->setText("You won!");
            scene_->setForegroundBrush(Qt::green);
        }
    } else {

    // Saving the last position of the head.
    // This is tells, where neck should be next.
    pair<int, int> lastHeadPosition = make_pair(
                                  Board.back().returnCoordinates("head")[0]
                                  * SCALER + xSCALER,
                                  Board.back().returnCoordinates("head")[1]
                                  * SCALER + ySCALER);

    // Moving the snake.
    Board.back().moveSnake(direction_);

    // The third value in deque that function returnCoordinates returns
    // is the uptated size of the snake.
    int currentSnakeSize = Board.back().returnCoordinates("head")[2];

    // If snake size has changed new neckpart is added to bodyparts.
    // Else the same but last part is deleted since snake has mooved.
    if (snakeSize_ != currentSnakeSize) {
        bodyparts.push_front(lastHeadPosition);
        snakeSize_ += 1;
    } else {
        bodyparts.push_front(lastHeadPosition);
        // Before deleting the last part, square with the same coordinates
        // is turned back to default color.
        QBrush whiteBrush(Qt::white);
        QPen whitePen(Qt::white);
        scene_->addRect(bodyparts.back().first, bodyparts.back().second,
                        SCALER, SCALER, whitePen, whiteBrush);

        bodyparts.pop_back();
    }
    // Mooving head by one step.
    deque<int> headCoordinates = Board.back().returnCoordinates("head");
    head_->setPos(headCoordinates[0] * SCALER, headCoordinates[1] * SCALER);

    // Same with food but coordinates are the same if snake didn't eat it.
    deque<int> foodCoordinates = Board.back().returnCoordinates("food");
    food_->setPos(foodCoordinates[0] * SCALER, foodCoordinates[1] * SCALER);

    // Painting squares on the board that have the same coordinates as
    // snake's bodyparts.
    for (auto& bodypart : bodyparts) {

        // Snake's tail is black and rest of the body green.
        if (bodypart == bodyparts.back()) {

            QBrush blackBrush(Qt::black);
            QPen blackPen(Qt::black);
            scene_->addRect(bodypart.first, bodypart.second, SCALER, SCALER,
                            blackPen, blackBrush);

        } else {
            QBrush greenBrush(Qt::green);
            QPen greenPen(Qt::green);
            scene_->addRect(bodypart.first, bodypart.second, SCALER, SCALER,
                            greenPen, greenBrush);
        }
    }
    // Score is updated.
    score_ = bodyparts.size();
    ui->lcdNumberScore->display(score_);
    }
    }

}

void MainWindow::gameTimer()
{
    if (paused_) {
        secondTimer_.stop();
    } else {

    if (seconds_ == 60) {
        minutes_ += 1;
        seconds_ = 0;
    }
    // Turning the values into qstring that can be displayed.
    QString time = QString::number(minutes_);
    time += QString::fromStdString(":");
    time += QString::number(seconds_);

    ui->lcdNumberTime->display(time);
    seconds_ += 1;
    }
}


void MainWindow::pushButtonStartClicked()
{

    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonPause->setEnabled(true);

    if (!paused_) {
        ui->spinBoxSeed->setEnabled(false);
        ui->horizontalSliderHeight->setEnabled(false);
        ui->horizontalSliderWidth->setEnabled(false);

        const GameBoard field(length_ / SCALER, width_ / SCALER,
                            ui->spinBoxSeed->value());
        Board.push_back(field);
        }
    paused_ = false;
    gameSimulation();
    timer_.start(70);
    secondTimer_.start(1000);

}


void MainWindow::pushButtonResetClicked()
{
    timer_.stop();
    secondTimer_.stop();

    score_ = 0;
    seconds_ = 0;
    minutes_ = 0;
    snakeSize_ = 1;

    for (auto& coordinates : bodyparts) {
        QBrush whiteBrush(Qt::white);
        QPen whitePen(Qt::white);
        scene_->addRect(coordinates.first, coordinates.second,
                        SCALER, SCALER, whitePen, whiteBrush);
    }
    bodyparts = {};

    direction_ = "w";
    paused_ = false;

    ui->lcdNumberScore->display(score_);
    ui->lcdNumberTime->display("0:0");

    ui->labelGameEnd->setText("");
    scene_->setForegroundBrush(Qt::NoBrush);

    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonPause->setEnabled(false);

    ui->horizontalSliderHeight->setEnabled(true);
    ui->horizontalSliderWidth->setEnabled(true);
    ui->labelSeed->setEnabled(true);

    ui->horizontalSliderHeight->setValue(SLIDER_MAX_VALUE);
    ui->horizontalSliderWidth->setValue(SLIDER_MAX_VALUE);

}


void MainWindow::pushButtonPauseClicked()
{
    if (timer_.isActive()) {
        ui->pushButtonStart->setEnabled(true);
        paused_ = true;
    }
}

