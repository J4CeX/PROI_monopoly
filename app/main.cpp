#include <iostream>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    std::cout << "0" << std::endl;

    std::cout << "BoardGame v. 0.0.1" << std::endl;

    std::cout << "1" << std::endl;

    QApplication a(argc, argv);

    std::cout << "2"<< std::endl;;

    MainWindow mw;

    std::cout << "3"<< std::endl;;

    mw.show();

    std::cout << "4"<< std::endl;;

    return a.exec();
}