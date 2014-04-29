/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   TableGeometry.h                         */
/* Description: This file defines the geometry     */
/*         of the table.  It overrides the draw    */
/*         method.  It uses the CubeGeometry.      */
/***************************************************/

#pragma once

#include "Geometry.h"
#include "CubeGeometry.h"

class TableGeometry : public Geometry
{
public:
   TableGeometry(CubeGeometry *cube);
   ~TableGeometry();

   virtual void draw(glm::mat4 model);

private:
   CubeGeometry *cube;
};

