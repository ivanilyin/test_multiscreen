#include <QtGui/QApplication>
#include "mainwindow.h"

#include "tappcontroler.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    TAppController mAppController(&a);
    Q_UNUSED(mAppController);
//    MainWindow w;
//    w.show();
    
    return a.exec();
}
