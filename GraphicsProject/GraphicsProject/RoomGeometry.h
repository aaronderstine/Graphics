/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   RoomGeometry.h                          */
/* Description: This file defines the geometry     */
/*         of the room.  It overrides the draw     */
/*         method.  It uses the CubeGeometry.      */
/***************************************************/

#pragma once

#include "Geometry.h"
#include "CubeGeometry.h"

class RoomGeometry : public Geometry
{
public:
   RoomGeometry(CubeGeometry *cube);
   ~RoomGeometry();

   virtual void draw(glm::mat4 model);

   // sets the dimensions of the floor and walls
   void setRoomParameters(float floorThickness, float wallThickness, float wallHeight, int xSize, int zSize);

private:
   CubeGeometry *cube;

   float floorThickness;
   float wallThickness;
   float wallHeight;
   int xSize;
   int zSize;
};

