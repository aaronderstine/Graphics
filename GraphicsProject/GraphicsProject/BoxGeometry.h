/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   BoxGeometry.h                           */
/* Description: This file defines the geometry     */
/*         of a box.  It basically is just a cube  */
/*         but it is needed for the scene graph to */
/*         work correctly.                         */
/***************************************************/

#pragma once
#include "Geometry.h"
#include "CubeGeometry.h"

class BoxGeometry : public Geometry
{
public:
   BoxGeometry(CubeGeometry *cube);
   ~BoxGeometry();

   virtual void draw(glm::mat4 model);

private:
   CubeGeometry *cube;
};

