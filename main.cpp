#include "mainwindow.h"
#include <QApplication>
#include<QDebug>

#include<ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
