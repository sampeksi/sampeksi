#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "gameboard.hh"
#include "point.hh"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QTimer>
#include <utility>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const int SLIDER_MAX_VALUE = 400;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void pushButtonStartClicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;
    QGraphicsPixmapItem* head_;
    QGraphicsPixmapItem* food_;

    std::deque<std::pair<int, int>> bodyparts = {};

    int length_ = 400;
    int width_ = 400;
    int time_ = 0;
    int snakeSize_ = 1;
    std::string direction_ = "w";

    QTimer* timer_;
    std::deque<GameBoard> Board;
    std::deque<std::pair<std::pair<int, int>, QGraphicsItem*>> boxes = {};

    void drawImages();
    void playgroundSizeChanged();
    void gameSimulation();

};
#endif // MAINWINDOW_HH
