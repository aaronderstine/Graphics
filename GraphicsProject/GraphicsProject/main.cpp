/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   main.cpp                                */
/* Description: This file defines main routine     */
/*         that opens up the main window           */
/***************************************************/

#include "GraphicsProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphicsProject w;
    w.showMaximized();
    return a.exec();
}
