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

// Max side size for visual gameboard.
const int SLIDER_MAX_VALUE = 400;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // method for key commands.
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void pushButtonStartClicked();

    void pushButtonResetClicked();

    void pushButtonPauseClicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_; // Array for visual gameboard.

    QGraphicsPixmapItem* head_; // Arrays for graphical items.
    QGraphicsPixmapItem* food_;

    // Container for snake bodyparts and their coordinates
    std::deque<std::pair<int, int>> bodyparts = {};


    int length_ = 400; // Default length and with for graphicscene.
    int width_ = 400;

    int seconds_ = 0; // Variables to track time.
    int minutes_ = 0;

    int snakeSize_ = 1; // Snake's size at first, when head is the only part.

    int score_; // Player points. Increases by one every time snake grows.

    int SCALER = 7; // Multiplier to scale graffic gameboard and gameboard
                    // object.
    int xSCALER = 6; // Since head of the snake is unsymmetric object
    int ySCALER = 3; // Scalers are required to make the tail look realistic.

    std::string direction_ = "w"; // Snake's default direction.

    bool paused_ = false; // Tells has pause button been clicked.

    QTimer timer_; // Timer to automatically move snake on board.
    QTimer secondTimer_; // Timer to update playtime.

    std::deque<GameBoard> Board; // Container for every gameboard object.
                                 // New object is added each time new game
                                 // has been sarted.

    // Method to transfrom .png files into graphic items.
    void drawImages();

    // Method to change size of the graphical gameboard
    void playgroundSizeChanged();

    // Method to showcase actions.
    void gameSimulation();

    // Updates time.¨
    void gameTimer();

};
#endif // MAINWINDOW_HH
