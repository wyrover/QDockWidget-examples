#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << u8"中文测试";

    MainWindow w;
    w.show();

    

    return a.exec();
}
