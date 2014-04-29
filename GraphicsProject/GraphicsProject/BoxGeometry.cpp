/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   BoxGeometry.cpp                         */
/* Description: This file defines the geometry     */
/*         of a box.  It basically is just a cube  */
/*         but it is needed for the scene graph to */
/*         work correctly.                         */
/***************************************************/

#include "BoxGeometry.h"


BoxGeometry::BoxGeometry(CubeGeometry *cube) : cube(cube)
{
   height = 1.0;
}


BoxGeometry::~BoxGeometry()
{

}

void BoxGeometry::draw(glm::mat4 model)
{
   // check if selected
   (selected) ? cube->setSelected(true) : cube->setSelected(false);

   // color of box
   cube->setColor(getColor());

   // draw the box
   cube->draw(model);
}
