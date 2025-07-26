#include "mainwindow.h"
#include <cpr/cpr.h>
#include <QApplication>
#include "workWithCout.h"

int main(int argc, char *argv[])
{
    enableVirtualTerminal();
    SetConsoleOutputCP(CP_UTF8);
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
