#include "mainwindow.h"
#include <QApplication>
#include "converter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //convertDbToCsv("testDB", "T2", "testDBT2");

    return a.exec();
}
