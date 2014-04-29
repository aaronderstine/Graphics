/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   March 15, 2014                          */
/* Name:   LightSource.h                           */
/* Description: This file defines a light source   */
/*         that can be moved about the room.       */
/***************************************************/

#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "Geometry.h"

class LightSource
{
public:
   LightSource(Geometry *geometry);
   ~LightSource();

   static void setULightLocation(GLuint uLightLocation);

   // move the light source
   void changeZ(float delta);
   void changeX(float delta);
   void changeY(float delta);

   void render();

protected:
   void updateUniform();

   static GLuint uLightLocation;
   Geometry *geometry;

private:
   float x;
   float y;
   float z;
};

