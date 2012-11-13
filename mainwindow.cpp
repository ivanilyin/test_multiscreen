#include "mainwindow.h"
#include "ui_mainwindow.h"


const QString tMainScreen = "MainScreen";


#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mSettings = new QSettings("settings.ini", QSettings::IniFormat, this);

    ui->setupUi(this);

    spb_mMainScreen = new QSpinBox(this);

    //    spb_mMainScreen->setMaximumWidth(20);

    ui->mainToolBar->addWidget(spb_mMainScreen);

    connect(spb_mMainScreen, SIGNAL(valueChanged(int)), this, SIGNAL(mainScreenValueChanged_signal(int)));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SIGNAL(actionQuitTriggered()));
}

int MainWindow::readMainScreen() const
{
    return mSettings->value(tMainScreen, 0).toInt();
}

void MainWindow::fullScreenValueChanged(bool pChanged)
{
    ui->actionFull_screen->setChecked(pChanged);
}

void MainWindow::mainScreenValueChanged(int pValue)
{
    spb_mMainScreen->setValue(pValue);
}

void MainWindow::on_actionFull_screen_toggled(bool pToggle)
{
    emit fullScreenValueChanged_signal(pToggle);
}

void MainWindow::setMaxScreenCount(int pValue)
{
    spb_mMainScreen->setMaximum(pValue);
}




MainWindow::~MainWindow()
{
    delete ui;
}
