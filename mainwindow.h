#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WINS 500

#include <QPushButton>
#include <QFont>
#include <QFile>
#include <QLabel>
#include <QSlider>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void gotoAbout();
    void gotoMenu();
    void gotoSettings();
    void gotoGame();
    void gotoPause();

private:
    int sound = 0;
    enum {MENU, ABOUT, SETTINGS, PAUSE, GAME} state = MENU;
    QPushButton *mainButton, *aboutButton, *settingsButton;
    QLabel *mainText;

    QLabel *aboutText;
    QPushButton *aboutToMenuButton;

    QLabel *volumeText;
    QSlider *volumeSlider;
    QPushButton *settingsToMenuButton;

    QLabel *animeLabel;
    QPushButton *gameToMenu, *toPause;

    QLabel *pauseText;
    QPushButton *pauseToGame;

    void setupMenu();
    void hideMenu();
    void showMenu();

    void setupAbout();
    void showAbout();
    void hideAbout();

    void setupSettings();
    void showSettings();
    void hideSettings();

    void setupGame();
    void showGame();
    void hideGame();

    void setupPause();
    void showPause();
    void hidePause();

};
#endif // MAINWINDOW_H
