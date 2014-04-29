/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   CubeGeometry.h                          */
/* Description: This file defines the geometry     */
/*         of the basic cube.  It overrides the    */
/*         draw method.  It is used by several of  */
/*         the other geometries.                   */
/***************************************************/

#pragma once
#include "glm/glm.hpp"
#include "Geometry.h"

class CubeGeometry : public Geometry
{
public:
   CubeGeometry();
   ~CubeGeometry();

   virtual void draw(glm::mat4 model);

private:

};

