#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QKeyEvent>
#include <QFont>

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
    //ui->graphicsView->fitInView(scene.sceneRect());
    ui->graphicsView->show();

    drawImages();

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

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this,
           &MainWindow::gameSimulation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
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
    if (Board[0].gameOver()) {
        if (Board[0].gameLost()) {
            ui->labelGameEnd->setText("You lost :(");
            scene_->setForegroundBrush(Qt::red);

        } else {
            ui->labelGameEnd->setText("You won!");
            scene_->setForegroundBrush(Qt::green);
        }
    } else {

    pair<int, int> lastHeadPosition = make_pair(
                                  Board[0].returnCoordinates("head")[0] *5 +7,
                                  Board[0].returnCoordinates("head")[1] *5 +4);

    Board[0].moveSnake(direction_);

    int currentSnakeSize = Board[0].returnCoordinates("head")[2];
    deque<int> foodCoordinates = Board[0].returnCoordinates("food");

    if (snakeSize_ != currentSnakeSize) {
        bodyparts.push_front(lastHeadPosition);
        snakeSize_ += 1;
    } else {
        bodyparts.push_front(lastHeadPosition);
        QBrush whiteBrush(Qt::white);
        QPen whitePen(Qt::white);
        scene_->addRect(bodyparts.back().first, bodyparts.back().second, 5, 5,
                        whitePen, whiteBrush);

        bodyparts.pop_back();
    }

    deque<int> headCoordinates = Board[0].returnCoordinates("head");
    head_->setPos(headCoordinates[0] * 5, headCoordinates[1] * 5);

    food_->setPos(foodCoordinates[0] * 5, foodCoordinates[1] * 5);

    for (auto& bodypart : bodyparts) {

        if (bodypart == bodyparts.back()) {

            QBrush blackBrush(Qt::black);
            QPen blackPen(Qt::black);
            scene_->addRect(bodypart.first, bodypart.second, 5, 5,
                            blackPen, blackBrush);

        } else {
            QBrush greenBrush(Qt::green);
            QPen greenPen(Qt::green);
            scene_->addRect(bodypart.first, bodypart.second, 5, 5,
                            greenPen, greenBrush);
        }
    }
    }

}

void MainWindow::pushButtonStartClicked()
{

    ui->spinBoxSeed->setEnabled(false);
    ui->horizontalSliderHeight->setEnabled(false);
    ui->horizontalSliderWidth->setEnabled(false);

    const GameBoard field(length_ / 5, width_ / 5, ui->spinBoxSeed->value());
    Board.push_back(field);
    gameSimulation();
    timer_->start(60);
}

