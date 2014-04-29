/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   Camera.h                                */
/* Description: This file defines a spherical      */
/*         camera that can be rotated and zoom.    */
/***************************************************/

#pragma once
#include "glew.h"
#include "glm/glm.hpp"

class Camera
{
public:
   enum MoveDirection
   {
      NONE  = 0,
      UP    = 1,
      DOWN  = -1,
      LEFT  = DOWN,
      RIGHT = UP
   };

   Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
   ~Camera();

   static void setUCameraLocation(GLuint uCameraLocation);
   glm::mat4 getCameraMatrix();

   // rotates left/right by degrees
   void rotateYaw(float degrees);

   // rotates up/down by degrees
   void rotatePitch(float degrees);

   // changes the zoom by distance
   void zoom(float distance);

private:
   void calculateCameraMatrix();

   glm::mat4 cameraMatrix;

   // distance between the eye and the target
   float distance;
   // angle between x-z plane and camera
   float pitch;
   // angle between y-z plane and camera
   float yaw;

   static GLuint uCameraLocation;
};

