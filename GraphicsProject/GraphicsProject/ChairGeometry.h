/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   ChairGeometry.h                         */
/* Description: This file defines the geometry     */
/*         of the chair.  It overrides the draw    */
/*         method.  It uses the CubeGeometry.      */
/***************************************************/

#pragma once

#include "Geometry.h"
#include "CubeGeometry.h"

class ChairGeometry : public Geometry
{
public:
   ChairGeometry(CubeGeometry *cube);
   ~ChairGeometry();

   virtual void draw(glm::mat4 model);

private:
   CubeGeometry *cube;
};

