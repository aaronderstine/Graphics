/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   SceneGraph.h                            */
/* Description: This file defines the scene graph  */
/*         object that reads the config file and   */
/*         build the scene                         */
/***************************************************/

#pragma once
#include "glew.h"
#include "Node.h"
#include "glm/glm.hpp"
#include <QGLWidget>
#include "CubeGeometry.h"
#include "TableGeometry.h"
#include "ChairGeometry.h"
#include "RoomGeometry.h"
#include "BoxGeometry.h"
#include "GeometryBuilder.h"
#include "SphereGeometry.h"
#include "Mesh.h"
#include <map>
#include <vector>

class QGLWidget;
class QString;
class Node;

class SceneGraph
{
public:
   SceneGraph(QGLWidget *glWidget, GeometryBuilder *builder);
   ~SceneGraph();

   // parses the config file and builds the scene
   void build(QString configFileText);

   // used to center the camera
   glm::vec3 getCenterOfRoom();

   // starts at the root and traverses the graph
   void render();

   // clears the scene graph
   void flush();

   // for iterating through the scene
   void selectNext();
   void selectPrev();
   Node *getSelected();

   void subdivide(Node *node);

private:
   Node *root;

   std::vector<Node*> nodes;
   std::vector<Node*>::iterator selected;

   GeometryBuilder *geometryBuilder;
   SphereGeometry *sphere;

   QGLWidget *glWidget;
   CubeGeometry *cube;
   TableGeometry *table;
   ChairGeometry *chair;
   RoomGeometry *room;
   BoxGeometry  *box;

   glm::vec3 centerOfRoom;
};

