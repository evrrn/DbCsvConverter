#include "mainwindow.h"
#include <QApplication>
#include "dbtocsv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    convertDbToCsv("testDB", "T2", "testDBT2");

    return a.exec();
}
