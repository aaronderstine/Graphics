/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   Camera.cpp                              */
/* Description: This file defines a spherical      */
/*         camera that can be rotated and zoom.    */
/***************************************************/

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLuint Camera::uCameraLocation;

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
   distance =  glm::length(eye - target);
   pitch    = -glm::degrees(asin((eye.y - target.y)/distance));
   yaw      =  glm::degrees(asin((eye.x - target.x)/distance));

   calculateCameraMatrix();
}


Camera::~Camera()
{

}

void Camera::setUCameraLocation(GLuint uCameraLocation)
{
   Camera::uCameraLocation = uCameraLocation;
}

glm::mat4 Camera::getCameraMatrix()
{
   return cameraMatrix;
}

void Camera::rotateYaw(float degrees)
{
   yaw += degrees;
   if (yaw < 0.0) yaw += 360;
   if (yaw >= 360.0) yaw -= 360;

   calculateCameraMatrix();
}

void Camera::rotatePitch(float degrees)
{
   pitch -= degrees;
   if (pitch >=  90.0) pitch =  89.99;
   if (pitch <= -90.0) pitch = -89.99;

   calculateCameraMatrix();
}

void Camera::zoom(float distance)
{
   this->distance += distance;
   if (this->distance <= 0.0) this->distance = 0.01;
   calculateCameraMatrix();
}

void Camera::calculateCameraMatrix()
{
   glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	
	glm::vec4 camPos = rotY * rotX * glm::vec4(0.0f, 0.0f, distance, 1.0f);
	glm::vec4 camUp  = rotY * rotX * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
   
   cameraMatrix = glm::lookAt(glm::vec3(camPos.x, camPos.y, camPos.z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(camUp.x, camUp.y, camUp.z));
   glUniformMatrix4fv(Camera::uCameraLocation, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

