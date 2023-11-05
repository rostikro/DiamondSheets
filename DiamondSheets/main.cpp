#include "DiamondSheets.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiamondSheets w;
    w.show();
    return a.exec();
}