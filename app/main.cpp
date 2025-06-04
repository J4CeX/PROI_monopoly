#include <iostream>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    std::cout << "BoardGame v. 1.0.0" << std::endl;

    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();

    return a.exec();
}