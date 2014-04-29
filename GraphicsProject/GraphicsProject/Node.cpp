/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   Node.cpp                                */
/* Description: This file defines a node that can  */
/*         be used in the scene graph.  It takes   */
/*         a geometry that handles the drawing.    */
/*         It has a vector of child nodes that     */
/*         define a grid.                          */
/***************************************************/

#include "Node.h"
#include <glm/gtc/matrix_transform.hpp> 



Node::Node(Geometry *geometry) : geometry(geometry)
{
   // make all internal data the identity matrix
   translateMatrix = glm::mat4(1.0f);
   rotateMatrix    = glm::mat4(1.0f);
   scaleMatrix     = glm::mat4(1.0f);
   modelMatrix     = glm::mat4(1.0f);

   gridX = 1;
   gridZ = 1;

   children.reserve(gridX * gridZ);
   setChildrenToNull();

   selected = false;
}

Node::Node(Geometry *geometry, int gridX, int gridZ) : geometry(geometry), gridX(gridX), gridZ(gridZ)
{
   // make all internal data the identity matrix
   translateMatrix = glm::mat4(1.0f);
   rotateMatrix    = glm::mat4(1.0f);
   scaleMatrix     = glm::mat4(1.0f);
   modelMatrix     = glm::mat4(1.0f);

   children.reserve(gridX * gridZ);
   setChildrenToNull();
   geometryColor = Color::WHITE;
}

Node::~Node()
{
   // step through the children and delete them
   std::vector<Node*>::iterator itr;
   for (itr = children.begin(); itr != children.end(); ++itr)
   {
      if (*itr) delete *itr;
   }
   children.clear();
}

Color::Color Node::getGeometryColor()
{
   return geometryColor;
}

void Node::setGeometryColor(Color::Color color)
{
   geometryColor = color;
}

void Node::setSelected(bool selected)
{
   this->selected = selected;
}

void Node::setChildrenToNull()
{
   for (int i=0; i<(gridX * gridZ); ++i)
   {
      children.push_back(NULL);
   }
}

void Node::addChild(Node *child)
{
      if (child == NULL) return;
   
      // if there is already a child here add it to that one instead
      if (children.at(0)) children.at(0)->addChild(child);
      else
      {
         // move up to sit on top of this node
         if (geometry) child->translate(glm::vec3(0.0, geometry->getHeight(), 0.0));
         children.at(0) = child;
      }
}

void Node::addChild(Node *child, int locX, int locZ)
{
   if (child == NULL) return;

   int location = locZ * gridX + locX;

   // if there is already a child here add it to that one instead
   if (children.at(location)) children.at(location)->addChild(child);
   else
   {
      // move up to sit on top of this node
      if (geometry) child->translate(glm::vec3(locX, geometry->getHeight(), locZ));
      children.at(location) = child;
   }
}

void Node::rotate(float angle, glm::vec3 axis)
{
   //rotateMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
   rotateMatrix = glm::rotate(rotateMatrix, angle, axis);
   updateModelMatrix();
}

void Node::translate(glm::vec3 amount)
{
   //translateMatrix = glm::translate(glm::mat4(1.0f), amount);
   translateMatrix = glm::translate(translateMatrix, amount);
   updateModelMatrix();
}

void Node::scale(glm::vec3 scale)
{
   //scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
   scaleMatrix = glm::scale(scaleMatrix, scale);
   updateModelMatrix();
}

void Node::updateModelMatrix()
{
   modelMatrix = translateMatrix * rotateMatrix * scaleMatrix;
}

glm::mat4 Node::getModelMatrix()
{
   return modelMatrix;
}

void Node::traverse(glm::mat4 transform)
{
   // update model matrix with transformation that was passed in from parent
   glm::mat4 model = transform * modelMatrix;

   // draw itself if there is geometry to render
   if (geometry) 
   {
      // check if it is currently selected
      (selected) ? geometry->setSelected(true) : geometry->setSelected(false);

      geometry->setColor(geometryColor);
      geometry->draw(model);
   }

   // traverse children
   std::vector<Node*>::iterator itr;
   for (itr = children.begin(); itr != children.end(); ++itr)
   {
      if (*itr) (*itr)->traverse(model);
   }
}

void Node::setGeometry(Geometry *geo)
{
   geometry = geo;
}

Geometry *Node::getGeometry()
{
   return geometry;
}
