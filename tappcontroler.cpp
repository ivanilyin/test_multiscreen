#include "tappcontroler.h"
#include <QtGui>
#include <QtWebKit>
#include "GraphicsSimpleBrowser.h"

#include "mainwindow.h"

const QString sMainScreen = "MainScreen";
const QString sFullScreen = "FullScreen";

TAppController::TAppController(QApplication *pApp, QObject *parent) :
    QObject(parent)
{
    mApplication = pApp;
    mDesktopWidget = new QDesktopWidget();

    mSettings = new QSettings("MainSettings.ini", QSettings::IniFormat, this);

    mMainScene = new QGraphicsScene(0, 0, 800, 450);
    fillScene();

    mMainWindow = new MainWindow();
    for (int i = 0; i < mDesktopWidget->screenCount() - 1; i++)
    {
        mAddWidgets.append(new TGraphicsView(mMainScene));
    }

    mControlWidget = new TGraphicsView(mMainScene);
    mMainWindow->setCentralWidget(mControlWidget);

    connect(this, SIGNAL(fullScreenValueChanged(bool)), mMainWindow, SLOT(fullScreenValueChanged(bool)));
    connect(mMainWindow, SIGNAL(fullScreenValueChanged_signal(bool)), this, SLOT(fullScreenValueChanged_slot(bool)));
    connect(mMainWindow, SIGNAL(mainScreenValueChanged_signal(int)), this, SLOT(mainScreenValueChanged_slot(int)));
    connect(this, SIGNAL(mainScreenValueChanged(int)), mMainWindow, SLOT(mainScreenValueChanged(int)));
    connect(this, SIGNAL(setMaxScreenCount(int)), mMainWindow, SLOT(setMaxScreenCount(int)));
    connect(mDesktopWidget, SIGNAL(screenCountChanged(int)), this, SIGNAL(setMaxScreenCount(int)));
    connect(mMainWindow, SIGNAL(actionQuitTriggered()), qApp, SLOT(quit()));

    readSettings();
    adaptWindows();

    emit setMaxScreenCount(mDesktopWidget->screenCount() - 1);

    setAllvisible(true);
}

void TAppController::fullScreenValueChanged_slot(bool pValue)
{
    mFullScreen = pValue;

    adaptWindows();
    mSettings->setValue(sFullScreen, pValue);
}

void TAppController::mainScreenValueChanged_slot(int pValue)
{
    mMainScreen = pValue;

    adaptWindows();
    mSettings->setValue(sMainScreen, pValue);
}

void TAppController::readSettings()
{
    emit fullScreenValueChanged(mFullScreen = mSettings->value(sFullScreen, false).toBool());
    emit mainScreenValueChanged(mMainScreen = mSettings->value(sMainScreen, 0).toInt());
}

void TAppController::adaptWindows()
{
    QRect mainScrRect = mDesktopWidget->screenGeometry(mMainScreen);
    QRect curRect = mMainWindow->rect();

    mMainWindow->setGeometry(mainScrRect.x() + 150, mainScrRect.y() + 50, curRect.width(), curRect.height());

    for (int i = 0; i < mDesktopWidget->numScreens(); i++) {
        int curAddWidget = 0;
        QRect mainScrRect = mDesktopWidget->screenGeometry(i);

        if (i == mMainScreen) {

            if (mFullScreen) {
                mMainWindow->setWindowFlags(Qt::FramelessWindowHint);
                mMainWindow->setGeometry(mainScrRect);
            } else {
                QRect curRect = mMainWindow->rect();
                mMainWindow->setWindowFlags(Qt::WindowTitleHint);
                mMainWindow->setGeometry(mainScrRect.x() + 150, mainScrRect.y() + 50, curRect.width(), curRect.height());
            }
            continue;

        } else {
            TGraphicsView *curWebView = mAddWidgets[curAddWidget];
            if (mFullScreen) {
                curWebView->setWindowFlags(Qt::FramelessWindowHint);
                curWebView->setGeometry(mainScrRect);
            } else {
                QRect curRect = curWebView->rect();
                curWebView->setWindowFlags(Qt::WindowTitleHint);
                curWebView->setGeometry(mainScrRect.x() + 150, mainScrRect.y() + 50, curRect.width(), curRect.height());
            }
        }
        curAddWidget++;
    }
    setAllvisible(true);
}

void TAppController::setAllvisible(bool pVisible)
{
    mMainWindow->setVisible(pVisible);
    foreach (TGraphicsView *view, mAddWidgets) {
        view->setVisible(pVisible);
    }
}

void TAppController::fillScene()
{
    GraphicsSimpleBrowser *browser = new GraphicsSimpleBrowser();
    mMainScene->addItem(browser);
    browser->setGeometry(mMainScene->sceneRect());
}
