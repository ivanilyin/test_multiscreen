#ifndef TAPPCONTROLER_H
#define TAPPCONTROLER_H

#include <QObject>
#include <QtGui>

class TGraphicsView;
class QApplication;
class MainWindow;
class QSettings;
class QDesktopWidget;
class QResizeEvent;
class QGraphicsView;
class QGraphicsScene;

class TGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    TGraphicsView(QGraphicsScene *scene, QWidget *parent = 0) : QGraphicsView(scene, parent)
    {
    }
    virtual void resizeEvent(QResizeEvent */*event*/)
    {
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};


class TAppController : public QObject
{
    Q_OBJECT
public:
    explicit TAppController(QApplication *pApp, QObject *parent = 0);
    void readSettings();
    void setAllvisible(bool pVisible);
    void fillScene();

signals:
    void fullScreenValueChanged(bool pChanged);
    void mainScreenValueChanged(int pChanged);
    void setMaxScreenCount(int pScreensCount);

public slots:
    void fullScreenValueChanged_slot(bool pValue);
    void mainScreenValueChanged_slot(int pValue);

private:
    void adaptWindows();

private:
    TGraphicsView *mControlWidget;
    QList<TGraphicsView*> mAddWidgets;
    QApplication *mApplication;
    MainWindow *mMainWindow;
    QSettings *mSettings;
    QDesktopWidget *mDesktopWidget;
    QGraphicsScene *mMainScene;
    int mMainScreen;
    bool mFullScreen;
    int mNumScreens;
};

#endif // TAPPCONTROLER_H
