#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QSettings;
class QSpinBox;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    int readMainScreen() const;

signals:
    void fullScreenValueChanged_signal(bool pChanged);
    void mainScreenValueChanged_signal(int pChanged);
    void actionQuitTriggered();

private slots:
    void fullScreenValueChanged(bool pChanged);
    void mainScreenValueChanged(int pValue);
    void setMaxScreenCount(int pValue);

    void on_actionFull_screen_toggled(bool pToggle);
    
private:
    Ui::MainWindow *ui;
    QSettings *mSettings;
    QSpinBox *spb_mMainScreen;
};

#endif // MAINWINDOW_H
