/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   ChairGeometry.cpp                       */
/* Description: This file defines the geometry     */
/*         of the chair.  It overrides the draw    */
/*         method.  It uses the CubeGeometry.      */
/***************************************************/

#include "ChairGeometry.h"
#include <glm/gtc/matrix_transform.hpp> 

ChairGeometry::ChairGeometry(CubeGeometry *cube) : cube(cube)
{
   height = 1.0;
}


ChairGeometry::~ChairGeometry()
{

}

void ChairGeometry::draw(glm::mat4 model)
{
   // check if selected
   (selected) ? cube->setSelected(true) : cube->setSelected(false);

   // chair color
   cube->setColor(getColor());

   // matricies for transformations
   glm::mat4 tr;
   glm::mat4 sc;

   // seat
   tr = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.4, 0.0));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.5, 0.1, 0.5));
   cube->draw(model * tr * sc);

   // back
   tr = glm::translate(glm::mat4(1.0), glm::vec3(0, 0.5, -0.2));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.5, 0.5, 0.1));
   cube->draw(model * tr * sc);

   // leg1
   tr = glm::translate(glm::mat4(1.0), glm::vec3(-0.2, 0.0, -0.2));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.1, 0.4, 0.1));
   cube->draw(model * tr * sc);

   // leg2
   tr = glm::translate(glm::mat4(1.0), glm::vec3(0.2, 0.0, -0.2));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.1, 0.4, 0.1));
   cube->draw(model * tr * sc);

   // leg3
   tr = glm::translate(glm::mat4(1.0), glm::vec3(0.2, 0.0, 0.2));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.1, 0.4, 0.1));
   cube->draw(model * tr * sc);

   // leg4
   tr = glm::translate(glm::mat4(1.0), glm::vec3(-0.2, 0.0, 0.2));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.1, 0.4, 0.1));
   cube->draw(model * tr * sc);
}
