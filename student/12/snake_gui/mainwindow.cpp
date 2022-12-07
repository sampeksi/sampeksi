/*
####################################################################
# COMP.CS.110 Programming 2: Structures, 2022                      #
#                                                                  #
# Project4: Snake                                                  #
# Program description: Implements a game called Snake.             #
#                                                                  #
# File: gameboard.hh                                               #
# Description: Defines a class representing the user interface     #
#                                                                  #
# Author: Sampo Suokuisma, 150422473, sampo.suokuisma@tuni.fi      #
####################################################################
*/

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QKeyEvent>
#include <QFont>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creating the visual gameboard.
    scene_ = new QGraphicsScene(this);

    // Gameboard is placed top left corner.
    // 2* is added since margins take one pixel from each side.
    // Because gameboard is scaled pixel is actually SCALER.
    ui->graphicsView->setGeometry(0, 0, width_ + 2 * SCALER, length_ +
                                  2 * SCALER );
    ui->graphicsView->setScene(scene_);

    // Both length and with are decreased by 1* SCALER since food and snake
    // are considered to be inside sceneRect.
    scene_->setSceneRect(0, 0, width_ + SCALER , length_ +  SCALER);

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
    const vector<string> images = {"rat", "snakehead", "snakeheadLeft",
                                   "snakeheadRight", "snakeheadUp"};

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
    rat->setScale(0.025);

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

    // Creating snakehead for each direction.
    // Images are added to deque called snakeheads_.

    for (auto& image : images) {
    if (image != "rat") {
        string file2 = PREFIX + image + SUFFIX;
        QImage snakeheadImage(QString::fromStdString(file2));
        QGraphicsPixmapItem* snakehead = new QGraphicsPixmapItem(
                                   QPixmap::fromImage(snakeheadImage));
        snakehead->setScale(0.0125);
        snakehead->setFlags(QGraphicsItem::ItemIsMovable);

        snakehead->setZValue(2);

        snakehead->setPos(-100, -100);
        scene_->addItem(snakehead);

        snakeheads_.push_back(snakehead);
        }

    }
    // Snakes default direction is up, so first image to appear is
    // snakehead that is pointing up and it is added in the middle of
    // the gameboard.
    head_ = snakeheads_[3];
    head_->setPos(width_ / 2, length_ /2);

}

void MainWindow::playgroundSizeChanged()
{
    int length = ui->horizontalSliderHeight->value();
    int width = ui->horizontalSliderWidth->value();

    // Updates the dimensions.
    length_ = length;
    width_ = width;

    // Visual gameboard is changed based on given dimensions.
    ui->graphicsView->setGeometry(0, 0, width_ +2, length_ + 2);
    ui->graphicsView->setScene(scene_);
    scene_->setSceneRect(0, 0, width_ , length_);

    ui->graphicsView->setScene(scene_);
    ui->graphicsView->show();

    // Head is also repositioned.
    head_->setPos(width_ / 2, length_ /2);

}

void MainWindow::gameSimulation()
{
    if (paused_) { // Game will stop if pause button has been clicked.
        timer_.stop();
    }
    else {

    // if game has ended timers will be stopped and result of the game stated.
        if (Board.back().gameOver()) {
        endGame();
        }

        else {

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

        deque<int> foodCoordinates = Board.back().returnCoordinates("food");

        // Moving old snakehead image out of the gameboard
        head_->setPos(-100, -100);

        // Choosing new snakehead image.
        selectHeadImage();

        // Mooving head by one step.
        deque<int> headCoordinates = Board.back().returnCoordinates("head");
        head_->setPos(headCoordinates[0] * SCALER
            , headCoordinates[1] * SCALER );


        // Same with food but coordinates are the same if snake didn't eat it.

        food_->setPos(foodCoordinates[0] * SCALER,
                foodCoordinates[1] * SCALER);

        showBody();

        // Score is updated.
        score_ = bodyparts.size();
        ui->lcdNumberScore->display(score_);
        }
    }

}

void MainWindow::selectHeadImage()
{
    if (direction_ == "w") {
        head_ = snakeheads_[3];
    }
    else if (direction_ == "s") {
        head_ = snakeheads_[0];
    }
    else if (direction_ == "a") {
        head_ = snakeheads_[1];
    }
    else if (direction_ == "d") {
        head_ = snakeheads_[2];
    }
}

void MainWindow::showBody()
{
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
            QBrush greenBrush(Qt::darkGreen);
            QPen greenPen(Qt::darkGreen);
            scene_->addRect(bodypart.first, bodypart.second, SCALER, SCALER,
                            greenPen, greenBrush);
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

void MainWindow::endGame()
{
    secondTimer_.stop();
    timer_.stop();

    QFont font("Arial", 45, QFont::Bold);
    ui->labelGameEnd->setFont(font);
    // Screen turns green if player won, else turns red.
    // Text label prints message about the situation.
    if (Board.back().gameLost()) {
        ui->labelGameEnd->setText("You lost :(");
        this->setStyleSheet("QMainWindow { background-color: red; }");

    } else {
        ui->labelGameEnd->setText("You won!");
        this->setStyleSheet("QMainWindow { background-color: green; }");
    }
}


void MainWindow::pushButtonStartClicked()
{
    // Setting start button unenabled because game is already on.
    ui->pushButtonStart->setEnabled(false);
    // On the contrary game can now be paused.
    ui->pushButtonPause->setEnabled(true);
    
    // If game hasn't just been paused, new gameboard object will be created.
    if (!paused_) {
        ui->spinBoxSeed->setEnabled(false);
        ui->horizontalSliderHeight->setEnabled(false);
        ui->horizontalSliderWidth->setEnabled(false);

        const GameBoard field(width_ / SCALER, length_ / SCALER,
                            ui->spinBoxSeed->value());
        Board.push_back(field);
        }
    paused_ = false;
    // function is called and game starts.
    gameSimulation();
    
    // Both timers start.
    timer_.start(timerFreq_);
    secondTimer_.start(secondTimerFreq_);

}


void MainWindow::pushButtonResetClicked()
{
    // Timers are stopped.
    timer_.stop();
    secondTimer_.stop();
    
    // Variables are set to default.
    score_ = 0;
    seconds_ = 0;
    minutes_ = 0;
    snakeSize_ = 1;
    
    // Squares that represent snake's body are turned back to default color.
    for (auto& coordinates : bodyparts) {
        QBrush whiteBrush(Qt::white);
        QPen whitePen(Qt::white);
        scene_->addRect(coordinates.first, coordinates.second,
                        SCALER, SCALER, whitePen, whiteBrush);
    }
    // Snake has no body.
    bodyparts = {};

    direction_ = "w";
    paused_ = false;

    // User interface is returned back to default.
    ui->lcdNumberScore->display(score_);
    ui->lcdNumberTime->display("0:0");

    ui->labelGameEnd->setText("");
    scene_->setForegroundBrush(Qt::NoBrush);

    ui->labelGameEnd->setText("");
    this->setStyleSheet("QMainWindow { background-color: white; }");

    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonPause->setEnabled(false);
    ui->spinBoxSeed->setEnabled(true);

    ui->horizontalSliderHeight->setEnabled(true);
    ui->horizontalSliderWidth->setEnabled(true);
    ui->labelSeed->setEnabled(true);

    ui->horizontalSliderHeight->setValue(SLIDER_MAX_VALUE);
    ui->horizontalSliderWidth->setValue(SLIDER_MAX_VALUE);

    // Head and food are returned back to their default positions.
    food_->setPos(-100, -100);
    head_->setPos(width_ / 2, length_ /2);

}


void MainWindow::pushButtonPauseClicked()
{
    if (timer_.isActive()) {
        ui->pushButtonStart->setEnabled(true);
        paused_ = true;
    }
}

