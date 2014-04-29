/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   Node.h                                  */
/* Description: This file defines a node that can  */
/*         be used in the scene graph.  It takes   */
/*         a geometry that handles the drawing.    */
/*         It has a vector of child nodes that     */
/*         define a grid.                          */
/***************************************************/

#pragma once
#include "glew.h"
#include <vector>
#include "glm/glm.hpp"
#include "Geometry.h"
#include "Color.h"

class Geometry;

class Node
{
public:
   // gridX and gridZ give the size of the grid of children nodes
   // that can be connected to this node
   Node(Geometry *geometry, int gridX, int gridZ);
   // only allows for one child
   Node(Geometry *geometry);
   ~Node();
   
   // adds a child node
   void addChild(Node *child);
   // adds a child node at location given by x and z
   void addChild(Node *child, int locX, int locZ);

   // rotates around axis angle degrees
   void rotate(float angle, glm::vec3 axis);

   // translates amount
   void translate(glm::vec3 amount);

   // scales by scale
   void scale(glm::vec3 scale);

   // returns the model matrix that contains the translation, rotation, and scale
   glm::mat4 getModelMatrix();

   // traverses the children and draws them
   void traverse(glm::mat4 transform);

   void setSelected(bool selected);

   void setGeometry(Geometry *geo);
   Geometry *getGeometry();

   // color of the associated geometry
   Color::Color getGeometryColor();
   void setGeometryColor(Color::Color color);

private:
   // used internally to update the model matrix
   void updateModelMatrix();
   void setChildrenToNull();

   std::vector<Node*> children;
   int gridX;
   int gridZ;

   glm::mat4 translateMatrix;
   glm::mat4 rotateMatrix;
   glm::mat4 scaleMatrix;

   glm::mat4 modelMatrix;

   Geometry *geometry;
   Color::Color geometryColor;

   bool selected;
};

