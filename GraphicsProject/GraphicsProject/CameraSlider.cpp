/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   CameraSlider.cpp                        */
/* Description: This file defines a slider control */
/*         that sends a signal while it is being   */
/*         held either up or down by the user.     */
/***************************************************/

#include "CameraSlider.h"

CameraSlider::CameraSlider(QWidget *parent) : QSlider(parent)
{
   // only allow -1, 0, 1
   this->setRange(-1, 1);
   timerInterval = 1000; // default is 1 sec

   connect(this, SIGNAL(valueChanged(int)), this, SLOT(cameraSliderValueChanged(int)));
   connect(this, SIGNAL(sliderReleased()),  this, SLOT(cameraSliderReleased()));

   // set up the timer
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(timerExpired()));
}

CameraSlider::~CameraSlider()
{
   if (timer) delete timer;
}

void CameraSlider::setSignalInterval(int ms)
{
   timerInterval = ms;
}

void CameraSlider::timerExpired()
{
   // tell the camera to move in the desired direction
   emit cameraMove((Camera::MoveDirection)sliderPosition());
}

void CameraSlider::cameraSliderValueChanged(int value)
{
   if (isSliderDown())
   {
      // start moving the the desired direction
      emit cameraMove((Camera::MoveDirection)value);

      // start sending the move signal
      timer->start(timerInterval);
   }
   else
   {
      // slider was not pressed so don't do anything
      // just make sure the indicater is still at 0
      setSliderPosition(0);
   }
}

void CameraSlider::cameraSliderReleased()
{
   // stop the camera from rotating
   timer->stop();

   // move the slider position back to middle
   setSliderPosition(0);

   // send the signal that it is not moving
   emit cameraMove(Camera::MoveDirection::NONE);
}

