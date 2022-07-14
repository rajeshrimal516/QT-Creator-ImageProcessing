/**
 * @file main.cpp
 * @author Rajesh Rimal (rajeshrimal516@gmail.com)
 * @brief Main CPP file for the GUI 
 * @version 0.1
 * @date 2022-07-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow w;
    w.show();
    return a.exec();
}
