#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //set window size to 500x500 (or what WINS is)
    this->setFixedSize(WINS, WINS);
    this->setWindowTitle("Simple App [Djivs 2020]");
    this->setWindowIcon(QIcon(":/icon.jpg"));

    //set up and show start menu
    setupMenu();
    showMenu();


}

MainWindow::~MainWindow()
{

}

void MainWindow::setupMenu()
{
    //make buttons
    mainButton = new QPushButton("&Start", this);
    mainButton->move((WINS - mainButton->width())/2, (WINS - mainButton->height())/2 - mainButton->width()/2);

    settingsButton = new QPushButton("&Settings", this);
    settingsButton->move(mainButton->x(), mainButton->y() + mainButton->height() + mainButton->width()/2);

    aboutButton = new QPushButton("&About", this);
    aboutButton->move(settingsButton->x(), settingsButton->y() + settingsButton->height() + settingsButton->width()/2);

    //make logo
    QString string = "Simple menu desktop app";
    int fontSize = 20;
    mainText = new QLabel(this);
    mainText->setFont(QFont("Times", fontSize, QFont::Bold));
    mainText->setFixedWidth(fontSize*string.size());
    mainText->setText(string);
    mainText->move(100, 0);

    connect(aboutButton, SIGNAL(clicked()), this, SLOT(gotoAbout()));
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(gotoSettings()));
    connect(mainButton, SIGNAL(clicked()), this, SLOT(gotoGame()));
}

void MainWindow::showMenu()
{
    mainButton->show();
    settingsButton->show();
    aboutButton->show();
    mainText->show();
}

void MainWindow::hideMenu()
{
    mainButton->hide();
    settingsButton->hide();
    aboutButton->hide();
    mainText->hide();
}

void MainWindow::setupAbout()
{
    aboutText = new QLabel(this);
    QString string;
    QFile file(":/text.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        string = file.readAll();
        file.close();
    }
    int fontSize = 10;
    aboutText->setFont(QFont("Times", fontSize, QFont::Bold));
    aboutText->setFixedWidth(fontSize*string.size());
    aboutText->setFixedHeight(400);
    aboutText->setText(string);

    aboutToMenuButton = new QPushButton("&Go Back", this);
    aboutToMenuButton->move((WINS - aboutToMenuButton->width())/2, WINS/5*4);

    connect(aboutToMenuButton, SIGNAL(clicked()), this, SLOT(gotoMenu()));

}

void MainWindow::showAbout()
{
    aboutText->show();
    aboutToMenuButton->show();
}

void MainWindow::hideAbout()
{
    aboutText->hide();
    aboutToMenuButton->hide();
}

void MainWindow::gotoAbout()
{
    state = ABOUT;
    hideMenu();
    setupAbout();
    showAbout();
}

void MainWindow::gotoMenu()
{
    switch(state)
    {
        case ABOUT:
            hideAbout();
        break;
        case SETTINGS:
            hideSettings();
        break;
        case GAME:
            hideGame();
        break;
        default:
        break;

    }
    state = MENU;
    showMenu();
}

void MainWindow::setupSettings()
{
    volumeSlider = new QSlider(Qt::Orientation::Horizontal, this);
    volumeSlider->setValue(sound);
    volumeSlider->move(200,200);
    volumeText = new QLabel(this);
    volumeText->setText("Sound");
    volumeText->move(200, 220);
    settingsToMenuButton = new QPushButton("&Go back", this);
    settingsToMenuButton->move(200, 250);
    connect(settingsToMenuButton, SIGNAL(clicked()), this, SLOT(gotoMenu()));
}

void MainWindow::showSettings()
{
    volumeSlider->show();
    volumeText->show();
    settingsToMenuButton->show();
}

void MainWindow::hideSettings()
{
    settingsToMenuButton->hide();
    volumeSlider->hide();
    volumeText->hide();
    sound = volumeSlider->value();
}

void MainWindow::gotoSettings()
{
    state = SETTINGS;
    hideMenu();
    setupSettings();
    showSettings();
}

void MainWindow::setupGame()
{
    QPixmap pic (":/anime.jpg");
    animeLabel = new QLabel(this);
    animeLabel->setGeometry((WINS - pic.width())/2, 0, pic.width(), pic.height());
    animeLabel->setPixmap(pic);
    gameToMenu = new QPushButton("&Menu", this);
    toPause = new QPushButton("&Pause", this);
    toPause->move(0, gameToMenu->height()*2);
    connect(gameToMenu, SIGNAL(clicked()), this, SLOT(gotoMenu()));
    connect(toPause, SIGNAL(clicked()), this, SLOT(gotoPause()));
}

void MainWindow::showGame()
{
    animeLabel->show();
    gameToMenu->show();
    toPause->show();
}

void MainWindow::hideGame()
{
   animeLabel->hide();
   gameToMenu->hide();
   toPause->hide();
}

void MainWindow::gotoGame()
{
    switch(state)
    {
        case MENU:
            hideMenu();
        break;
        case PAUSE:
            hidePause();
        break;
        default:
        break;
    }
    state = GAME;
    setupGame();
    showGame();
}

void MainWindow::setupPause()
{
    pauseText = new QLabel("Pause.", this);
    pauseText->move(230, (WINS-4*(pauseText->height()))/2);
    pauseToGame = new QPushButton("&Back to game", this);
    pauseToGame->move((WINS - pauseToGame->width())/2, (WINS-pauseToGame->height())/2);
    connect(pauseToGame, SIGNAL(clicked()), this, SLOT(gotoGame()));

}

void MainWindow::showPause()
{
    pauseText->show();
    pauseToGame->show();

}

void MainWindow::hidePause()
{
    pauseText->hide();
    pauseToGame->hide();

}

void MainWindow::gotoPause()
{
    state = PAUSE;
    hideGame();
    setupPause();
    showPause();

}

