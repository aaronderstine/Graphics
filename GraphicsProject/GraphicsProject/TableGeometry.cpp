/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   TableGeometry.cpp                       */
/* Description: This file defines the geometry     */
/*         of the table.  It overrides the draw    */
/*         method. It uses the CubeGeometry.       */
/***************************************************/

#include "TableGeometry.h"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtc/matrix_transform.hpp> 

TableGeometry::TableGeometry(CubeGeometry *cube) : cube(cube)
{
   height = 0.8;
}


TableGeometry::~TableGeometry()
{

}

void TableGeometry::draw(glm::mat4 model)
{
   // check if selected
   (selected) ? cube->setSelected(true) : cube->setSelected(false);

   // color of table
   cube->setColor(getColor());

   // matricies for transformations
   glm::mat4 tr;
   glm::mat4 sc;

   // top
   tr = glm::translate(glm::mat4(1.0), glm::vec3(0, 0.6, 0));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(1, 0.2, 1));
   cube->draw(model * tr * sc);

   // leg1
   tr = glm::translate(glm::mat4(1.0), glm::vec3(-0.4, 0.0, -0.4));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.2, 0.6, 0.2));
   cube->draw(model * tr * sc);

   // leg2
   tr = glm::translate(glm::mat4(1.0), glm::vec3(0.4, 0.0, -0.4));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.2, 0.6, 0.2));
   cube->draw(model * tr * sc);

   // leg3
   tr = glm::translate(glm::mat4(1.0), glm::vec3(0.4, 0.0, 0.4));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.2, 0.6, 0.2));
   cube->draw(model * tr * sc);

   // leg4
   tr = glm::translate(glm::mat4(1.0), glm::vec3(-0.4, 0.0, 0.4));
   sc = glm::scale    (glm::mat4(1.0), glm::vec3(0.2, 0.6, 0.2));
   cube->draw(model * tr * sc);
}