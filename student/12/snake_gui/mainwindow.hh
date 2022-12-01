/*
 * Kuvaus:
 * Ohjelmassa toteututaan perinteinen matopeli.
 * Pelissä pelaaja koittaa kasvattaa matoa syömällä peliruudulle ilmestyviä
 * ruokia ja kasvattaa tällä tavoin matoa.
 * Pelaaja voittaa, jos mato täyttää koko peliruudun, ja häviää madon
 * törmätessä peliruudun seinään tai omaan häntäänsä.
 * Ohjelma ilmoittaa voitosta ilmoituksella ja pelikenttä muuttuu vihreäksi.
 * Vähitessä kenttä muuttuu punaiseksi.
 *  Pelin alussa pelaajat kysytään siemenluku, jonka avulla ohjelma generoi
 * satunnaisposition ruoalle joka kerta kun mato syö sen.
 * Käyttöliittymässä on liukusäätimet, joiden avulla pelaaja voi muuttaa peli-
 * kentän kokoa. Lisäksi käyttöliittymässä näkyvät pelin ajallinen kesto ja
 * pelaajan pisteet. Lisäksi pelaajan on mahdollista pysäyttää tai resetoida
 * peli tai halutessaan sulkea ikkuna painonapeilla.
####################################################################
# COMP.CS.110 Programming 2: Structures, 2022                      #
#                                                                  #
# Project4: Snake                                                  #
# Program description: Implements a game called Snake.             #
#                                                                  #
# File: gameboard.hh                                               #
# Description: Declares a class representing the user interface    #
#                                                                  #
# Author: Sampo Suokuisma, 150422473, sampo.suokuisma@tuni.fi      #
####################################################################
*/

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

    int SCALER = 10; // Multiplier to scale graffic gameboard and gameboard
                    // object.
    int xSCALER = 7; // Since head of the snake is unsymmetric object
    int ySCALER = 3; // Scalers are required to make the tail look realistic.

    std::string direction_ = "w"; // Snake's default direction.

    bool paused_ = false; // Tells has pause button been clicked.

    QTimer timer_; // Timer to automatically move snake on board.
    QTimer secondTimer_; // Timer to update playtime.

    std::deque<GameBoard> Board; // Container for every gameboard object.
                                 // New object is added each time new game
                                 // has been sarted.

    int timerFreq_ = 80; // Timer calls function gameSimulation so snake
                         // moves automatically.
    int secondTimerFreq_ = 1000; // Game time is updated every second.

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
