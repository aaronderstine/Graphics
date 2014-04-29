/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   GraphicsProject.h                       */
/* Description: This file defines the main window  */
/***************************************************/

#ifndef GRAPHICSPROJECT_H
#define GRAPHICSPROJECT_H

#include <QtWidgets/QMainWindow>
#include "ui_GraphicsProject.h"

class GraphicsProject : public QMainWindow
{
    Q_OBJECT

public:
    GraphicsProject(QWidget *parent = 0);
    ~GraphicsProject();

    Ui::GraphicsProjectClass *getUi() { return &ui; }

   public slots:
      void onHelpTriggered();
   private slots:
      void onLoadConfigFileTriggered();

      

private:
    Ui::GraphicsProjectClass ui;
};

#endif // GRAPHICSPROJECT_H
