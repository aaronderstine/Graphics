/****************************************************/
/* Author: Aaron Derstine                           */
/* Course: COMP 361, Computer Graphics              */
/* Date:   March 29, 2014                           */
/* Name:   Mesh.h                                   */
/* Description: This file defines the a basic mesh. */
/*         It inherits from geometry so it can be   */
/*         used in a scene graph.  It is only built */
/*         using the MeshBuilder class and is       */
/*         created from a config file.              */
/****************************************************/

#pragma once
#include "Geometry.h"
#include <QtCore\QString>

class Mesh : public Geometry
{
public:
   Mesh();
   ~Mesh();

   // draw method
   virtual void draw(glm::mat4 model);

   void setSourceFile(QString filename);
   QString getSourceFilename();

private:
   QString sourceFile;
};

