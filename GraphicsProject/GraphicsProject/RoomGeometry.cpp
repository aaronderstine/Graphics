/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   RoomGeometry.cpp                        */
/* Description: This file defines the geometry     */
/*         of the room.  It overrides the draw     */
/*         method.  It uses the CubeGeometry.      */
/***************************************************/

#include "RoomGeometry.h"
#include <glm/gtc/matrix_transform.hpp> 

RoomGeometry::RoomGeometry(CubeGeometry *cube) : cube(cube)
{
   height = 0.1;

   floorThickness = 0.1;
   wallThickness = 0.1;
   wallHeight = 3.0;
   xSize = 1;
   zSize = 1;
}


RoomGeometry::~RoomGeometry()
{

}

void RoomGeometry::setRoomParameters(float floorThickness, float wallThickness, float wallHeight, int xSize, int zSize)
{
   this->floorThickness = floorThickness;
   this->wallThickness = wallThickness;
   this->wallHeight = wallHeight;
   this->xSize = xSize;
   this->zSize = zSize;

   height = floorThickness;
}

void RoomGeometry::draw(glm::mat4 model)
{
   // room cannot be selected
   cube->setSelected(false);

   // shift the floor so that the objects are in the correct locations
   // 0.5 is so they are centered in the middle of their respective regions
   float floorXoffset = xSize/2.0 - 0.5;
   float floorZoffset = zSize/2.0 - 0.5;

   // matricies for transformations
   glm::mat4 tr;
   glm::mat4 sc;
   glm::mat4 ro;

   // color of floor
   cube->setColor(Color::GREEN);

   // floor
   //tr = glm::translate(glm::mat4(1.0), glm::vec3(floorXoffset, 0.0, floorZoffset));
   //sc = glm::scale    (glm::mat4(1.0), glm::vec3(xSize, floorThickness, zSize));
   //cube->draw(model * tr * sc);

   // for better lighting of the floor - break into smaller sections
   int floorSections = xSize;
   float floorXoffset2 = xSize/floorSections/2.0 - 0.5;
   float floorZoffset2 = zSize/floorSections/2.0 - 0.5;
   for(int i=0; i<xSize; i += xSize/floorSections)
   {
      for(int j=0; j<zSize; j += zSize/floorSections)
      {
         tr = glm::translate(glm::mat4(1.0), glm::vec3(floorXoffset2 + i, 0.0, floorZoffset2 + j));
         sc = glm::scale    (glm::mat4(1.0), glm::vec3(xSize/floorSections, floorThickness, zSize/floorSections));
         cube->draw(model * tr * sc);
      }
   }

   // color of walls
   cube->setColor(Color::BROWN);

   // wall1
   tr = glm::translate(glm::mat4(1.0), glm::vec3(floorXoffset, 0.0, -zSize/2.0 + floorZoffset));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(xSize + wallThickness, wallHeight, wallThickness));
   cube->draw(model * tr * sc);

   // wall2
   tr = glm::translate(glm::mat4(1.0), glm::vec3(-xSize/2.0 + floorXoffset, 0.0, floorZoffset));
   //sc = glm::scale    (glm::mat4(1.0), glm::vec3(wallThickness, wallHeight, zSize + wallThickness));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(zSize, wallHeight, wallThickness));
   ro = glm::rotate   (glm::mat4(1.0), 90.0f, glm::vec3(0, 1, 0));
   cube->draw(model * tr * ro * sc);

   // wall3
   tr = glm::translate(glm::mat4(1.0), glm::vec3(floorXoffset, 0.0, zSize/2.0 + floorZoffset));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(xSize + wallThickness, wallHeight, wallThickness));
   cube->draw(model * tr * sc);

   // wall4
   tr = glm::translate(glm::mat4(1.0), glm::vec3(xSize/2.0 + floorXoffset, 0.0, floorZoffset));
   //sc = glm::scale    (glm::mat4(1.0), glm::vec3(wallThickness, wallHeight, zSize + wallThickness));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(zSize, wallHeight, wallThickness));
   ro = glm::rotate   (glm::mat4(1.0), 90.0f, glm::vec3(0, 1, 0));
   cube->draw(model * tr * ro * sc);
}
