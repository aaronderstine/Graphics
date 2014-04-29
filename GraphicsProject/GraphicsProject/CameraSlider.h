/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   CameraSlider.h                          */
/* Description: This file defines a slider control */
/*         that sends a signal while it is being   */
/*         held either up or down by the user.     */
/***************************************************/

#pragma once
#include <QtWidgets/QSlider>
#include <QtCore/QTimer>
#include "Camera.h"

class CameraSlider : public QSlider
{
   Q_OBJECT
public:
   CameraSlider(QWidget *parent);
   ~CameraSlider();

   // sets how fast it sends a change signal while being held in
   void setSignalInterval(int ms);

   private slots:
      void cameraSliderValueChanged(int value);
      void cameraSliderReleased();
      void timerExpired();

signals:
      void cameraMove(Camera::MoveDirection direction);

private:
   int timerInterval;

   QTimer *timer;
};

