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

    void pushButtonResetClicked();

    void pushButtonPauseClicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;
    QGraphicsPixmapItem* head_;
    QGraphicsPixmapItem* food_;

    std::deque<std::pair<int, int>> bodyparts = {};

    int length_ = 400;
    int width_ = 400;
    int seconds_ = 0;
    int minutes_ = 0;
    int snakeSize_ = 1;
    int score_;
    int SCALER = 7;

    std::string direction_ = "w";

    bool paused_ = false;

    QTimer timer_;
    QTimer secondTimer_;
    std::deque<GameBoard> Board;

    void drawImages();
    void playgroundSizeChanged();
    void gameSimulation();
    void gameTimer();

};
#endif // MAINWINDOW_HH
