/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   CubeGeometry.cpp                        */
/* Description: This file defines the geometry     */
/*         of the basic cube.  It overrides the    */
/*         draw method.  It is used by several of  */
/*         the other geometries.                   */
/***************************************************/

#include "CubeGeometry.h"

CubeGeometry::CubeGeometry()
{
   height = 1.0;
}


CubeGeometry::~CubeGeometry()
{

}

void CubeGeometry::draw(glm::mat4 model)
{
   basicDraw(model);
}
