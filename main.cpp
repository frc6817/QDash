#include "mainwindow.h"
#include <QApplication>
#include <QtWebEngineWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("FRC 6817- QDash");
    w.show();


    return a.exec();
}
