#include "home.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/imgs/icons/Appico.ico"));
    Home w;
    w.show();
    return a.exec();
}
