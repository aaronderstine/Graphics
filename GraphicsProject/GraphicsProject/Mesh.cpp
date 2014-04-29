/****************************************************/
/* Author: Aaron Derstine                           */
/* Course: COMP 361, Computer Graphics              */
/* Date:   March 29, 2014                           */
/* Name:   Mesh.cpp                                 */
/* Description: This file defines the a basic mesh. */
/*         It inherits from geometry so it can be   */
/*         used in a scene graph.  It is only built */
/*         using the MeshBuilder class and is       */
/*         created from a config file.              */
/****************************************************/

#include "Mesh.h"
#include "glm/gtc/type_ptr.hpp"

Mesh::Mesh()
{
   height = 0.0;
   canSubdivide = true;
}


Mesh::~Mesh()
{

}

void Mesh::draw(glm::mat4 model)
{
   basicDraw(model);
}

void Mesh::setSourceFile(QString filename)
{
   sourceFile = filename;
}

QString Mesh::getSourceFilename()
{
   return sourceFile;
}
