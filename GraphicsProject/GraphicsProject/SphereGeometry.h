/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   April 10, 2014                          */
/* Name:   SphereGeometry.h                        */
/* Description: This file defines the geometry     */
/*         of a sphere.  It uses Catmull-Clark to  */
/*         subdivide a cube 3 times.               */
/***************************************************/

#pragma once
#include "glm/glm.hpp"
#include "Geometry.h"

class SphereGeometry : public Geometry
{
public:
   SphereGeometry();
   ~SphereGeometry();

   virtual void draw(glm::mat4 model);

private:

};

