#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QKeyEvent>
#include <QFont>
#include <fstream>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_ = new QGraphicsScene(this);

    ui->graphicsView->setGeometry(0, 0, length_ +2, width_ + 2);
    ui->graphicsView->setScene(scene_);
    scene_->setSceneRect(0, 0, length_ - 1, width_ - 1);

    ui->graphicsView->setScene(scene_);

    ui->graphicsView->show();

    drawImages();
    updateLeaderboard();

    ui->horizontalSliderHeight->setRange(0, SLIDER_MAX_VALUE);
    ui->horizontalSliderWidth->setRange(0, SLIDER_MAX_VALUE);

    ui->horizontalSliderHeight->setValue(SLIDER_MAX_VALUE);
    ui->horizontalSliderWidth->setValue(SLIDER_MAX_VALUE);

    connect(ui->horizontalSliderHeight, &QSlider::valueChanged, this,
            &MainWindow::playgroundSizeChanged);
    connect(ui->horizontalSliderWidth, &QSlider::valueChanged, this,
            &MainWindow::playgroundSizeChanged);

    connect(ui->pushButtonStart, &QPushButton::clicked, this,
            &MainWindow::pushButtonStartClicked);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::green);
    ui->lcdNumberScore->setAutoFillBackground(true);
    ui->lcdNumberScore->setPalette(pal);

    pal.setColor(QPalette::Window, Qt::blue);
    ui->lcdNumberTime->setAutoFillBackground(true);
    ui->lcdNumberTime->setPalette(pal);

    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this,
           &MainWindow::gameSimulation);

    secondTimer_.setSingleShot(false),
    connect(&secondTimer_, &QTimer::timeout, this,
           &MainWindow::gameTimer);

    connect(ui->pushButtonPause, SIGNAL(clicked()), this,
            SLOT(pushButtonPauseClicked()));

    connect(ui->pushButtonReset, SIGNAL(clicked()), this,
            SLOT(pushButtonResetClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!paused_) {

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

    const vector<string> images = {"rat", "snakehead"};

    const string PREFIX(":/");
    const string SUFFIX(".png");

    //rat
    string file1 = PREFIX + images[0] + SUFFIX;
    QImage ratImage(QString::fromStdString(file1));
    QGraphicsPixmapItem* rat = new QGraphicsPixmapItem(
                                   QPixmap::fromImage(ratImage));
    rat->setScale(0.02);
    rat->setFlags(QGraphicsItem::ItemIsMovable);
    food_ = rat;

    food_->setPos(-100, -100);
    food_->setZValue(2);
    scene_->addItem(rat);

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

    length_ = length;
    width_ = width;

    ui->graphicsView->setGeometry(0, 0, length_ +2, width_ + 2);
    ui->graphicsView->setScene(scene_);
    scene_->setSceneRect(0, 0, length_ - 1, width_ - 1);

    ui->graphicsView->setScene(scene_);
    ui->graphicsView->show();

    head_->setPos(length_ / 2, width_ /2);

}

void MainWindow::gameSimulation()
{
    if (paused_) {
        timer_.stop();
    } else {

    if (Board.back().gameOver()) {
        if (Board.back().gameLost()) {
            ui->labelGameEnd->setText("You lost :(");
            scene_->setForegroundBrush(Qt::red);

        } else {
            ui->labelGameEnd->setText("You won!");
            scene_->setForegroundBrush(Qt::green);
        }
    } else {

    pair<int, int> lastHeadPosition = make_pair(
                                  Board.back().returnCoordinates("head")[0]
                                  * SCALER +7,
                                  Board.back().returnCoordinates("head")[1]
                                  * SCALER +4);

    Board[0].moveSnake(direction_);

    int currentSnakeSize = Board.back().returnCoordinates("head")[2];
    deque<int> foodCoordinates = Board.back().returnCoordinates("food");

    if (snakeSize_ != currentSnakeSize) {
        bodyparts.push_front(lastHeadPosition);
        snakeSize_ += 1;
    } else {
        bodyparts.push_front(lastHeadPosition);
        QBrush whiteBrush(Qt::white);
        QPen whitePen(Qt::white);
        scene_->addRect(bodyparts.back().first, bodyparts.back().second,
                        SCALER, SCALER, whitePen, whiteBrush);

        bodyparts.pop_back();
    }

    deque<int> headCoordinates = Board.back().returnCoordinates("head");
    head_->setPos(headCoordinates[0] * SCALER, headCoordinates[1] * SCALER);

    food_->setPos(foodCoordinates[0] * SCALER, foodCoordinates[1] * SCALER);

    for (auto& bodypart : bodyparts) {

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
    QString time = QString::number(minutes_);
    time += QString::fromStdString(":");
    time += QString::number(seconds_);

    ui->lcdNumberTime->display(time);
    seconds_ += 1;
    }
}

void MainWindow::updateScores()
{
    ofstream scores("scores.txt");

    QString score = QString::number(ui->lcdNumberScore->value());
    QString name = ui->lineEditGameTag->text();

    scores << score.toStdString() << ";" << name.toStdString();

}

void MainWindow::updateLeaderboard()
{
    ifstream scores("scores.txt");
    string line;
    while (getline(scores, line)) {
        int i = line.find(';');
        int points = stoi(line.substr(0, i));
        string name = line.substr(i+1);
        playerScores_.insert({points,name});
    }
    int rank = 1;

    for (auto& score : playerScores_) {
        QString text = QString::number(score.first);
        text += ": ";
        text += QString::fromStdString(score.second);

        if (rank == 1) {
            ui->labelFirst->setText(text);
        } else if (rank == 2) {
            ui->labelSecond->setText(text);
        } else if (rank == 3) {
            ui->labelThird->setText(text);
        } else {
            break;
        }
        rank += 1;
    }
}

void MainWindow::pushButtonStartClicked()
{
    if (!paused_) {
        ui->pushButtonStart->setEnabled(false);
        ui->spinBoxSeed->setEnabled(false);
        ui->horizontalSliderHeight->setEnabled(false);
        ui->horizontalSliderWidth->setEnabled(false);

        const GameBoard field(length_ / SCALER, width_ / SCALER,
                            ui->spinBoxSeed->value());
        Board.push_back(field);
        }
    paused_ = false;
    gameSimulation();
    timer_.start(60);
    secondTimer_.start(1000);
}


void MainWindow::pushButtonResetClicked()
{
    timer_.stop();
    secondTimer_.stop();

    updateScores();

    score_ = 0;
    seconds_ = 0;
    minutes_ = 0;
    snakeSize_ = 1;

    direction_ = "w";

    ui->lcdNumberScore->display(score_);
    ui->lcdNumberTime->display("0:0");

    ui->labelGameEnd->setText("");
    scene_->setForegroundBrush(Qt::NoBrush);

    ui->pushButtonStart->setEnabled(true);
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

