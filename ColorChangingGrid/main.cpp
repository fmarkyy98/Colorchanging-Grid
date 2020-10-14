#include "colorchanginggrid.h"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    ColorChangingGrid w;
    w.show();
    return a.exec();
}
