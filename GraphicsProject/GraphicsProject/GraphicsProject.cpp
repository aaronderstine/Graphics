/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   GraphicsProject.cpp                     */
/* Description: This file defines the main window  */
/***************************************************/

#include "GraphicsProject.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QTextStream>
#include "Color.h"

GraphicsProject::GraphicsProject(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

   // connect the load config file menu button to the slot
   connect(ui.actionLoad_Config_File, SIGNAL(triggered()),  this, SLOT(onLoadConfigFileTriggered()));

   // connect the help menu button to the slot
   connect(ui.actionHelp, SIGNAL(triggered()), this, SLOT(onHelpTriggered()));

   // set up how fast the camera moves
   ui.zoomSlider    ->setSignalInterval(75);
   ui.rotateLRSlider->setSignalInterval(50);
   ui.rotateUDSlider->setSignalInterval(50);
   ui.lightXSlider  ->setSignalInterval(500);
   ui.lightYSlider  ->setSignalInterval(500);
   ui.lightZSlider  ->setSignalInterval(500);

   // fill the color selector box
   ui.colorPicker->setMaxVisibleItems(Color::NUM_OF_COLORS);
   ui.colorPicker->addItem("");
   ui.colorPicker->addItem("Blue");
   ui.colorPicker->addItem("Brown");
   ui.colorPicker->addItem("Crimson");
   ui.colorPicker->addItem("Cyan");
   ui.colorPicker->addItem("Gray");
   ui.colorPicker->addItem("Green");
   ui.colorPicker->addItem("Lime");
   ui.colorPicker->addItem("Magenta");
   ui.colorPicker->addItem("Orange");
   ui.colorPicker->addItem("Red");
   ui.colorPicker->addItem("White");
   ui.colorPicker->addItem("Yellow");
}

GraphicsProject::~GraphicsProject()
{

}

void GraphicsProject::onLoadConfigFileTriggered()
{
   QString fileName = QFileDialog::getOpenFileName(this, "Open Config File");
   
   if (!fileName.isEmpty()) 
   {
      QFile file(fileName);
      if (!file.open(QIODevice::ReadOnly)) 
      {
         QMessageBox::critical(this, "Error", "Could not open file");
         return;
      }
      // read the entire file into a string and pass it into the widget
      QTextStream in(&file);
      ui.widget->config(in.readAll());
      file.close();
   }
   else
   {
      QMessageBox::critical(this, "Error", "No config file specified");
      return;
   }
}

void GraphicsProject::onHelpTriggered()
{
   QFile file("HelpText.txt");
   if (!file.open(QIODevice::ReadOnly)) 
   {
      QMessageBox::critical(this, "Error", "Could not open help text file");
      return;
   }
   // read the entire file into a string and pass it into the widget
   QTextStream in(&file);
   QMessageBox::information(this, "Help", in.readAll());
   file.close();
}