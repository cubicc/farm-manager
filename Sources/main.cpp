#include "mainwindow.h"
#include <QApplication>
#include "Load.h"
#include "Store.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
