/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   SceneGraph.cpp                          */
/* Description: This file defines the scene graph  */
/*         object that reads the config file and   */
/*         build the scene                         */
/***************************************************/

#include "SceneGraph.h"
#include <QtWidgets/QMessageBox>

SceneGraph::SceneGraph(QGLWidget *glWidget, GeometryBuilder *builder) : geometryBuilder(builder)
{
   root = NULL;
   // create the geometries
   cube  = geometryBuilder->buildCube();
   sphere = geometryBuilder->buildSphere();
   table = new TableGeometry(cube);
   chair = new ChairGeometry(cube);
   room  = new RoomGeometry(cube);
   box   = new BoxGeometry(cube);
   centerOfRoom = glm::vec3(0.0, 0.0, 0.0);
}


SceneGraph::~SceneGraph()
{
   if (root)   delete root;
   if (table)  delete table;
   if (chair)  delete chair;
   if (room)   delete room;
   if (box)    delete box;
}

void SceneGraph::build(QString configFileText)
{
   // if this is not the first time reading a config file delete the old scene
   flush();

   // create the root node
   root = new Node(NULL);

   // separate the file line-by-line
   QStringList strList = configFileText.split("\n", QString::SkipEmptyParts);

   // build scene graph as we go through config file
   // create an index to keep track of what line on currently
   int index = 0;

   // first line is xSize zSize and number of items in scene
   // break it into 3 separate strings
   QStringList firstLine = strList[index++].split(" ", QString::SkipEmptyParts);
   int xSize    = firstLine[0].simplified().toInt();
   int zSize    = firstLine[1].simplified().toInt();
   int numItems = firstLine[2].simplified().toInt();

   room->setRoomParameters(0.1, 0.1, 1.5, xSize, zSize);
   Node *roomNode = new Node(room, xSize, zSize);
   // centering the room on the origin
   centerOfRoom = glm::vec3(0.0, 1.0, 0.0);
   roomNode->translate(glm::vec3(-xSize/2.0, 0.0, -zSize/2.0));
   root->addChild(roomNode);
   roomNode->setSelected(false);

   // second line is empty
   index++;

   // for the rest of the items:
   Mesh *mesh;
   for (int i=0; i<numItems; ++i)
   {
      // first line contains the item name
      QString item = strList[index++].simplified();

      // if item is a mesh
      if (item.compare("mesh") == 0)
      {
         // next line contains xIndex and zIndex for the object
         QStringList fileLine = strList[index++].split(" ", QString::SkipEmptyParts);
         QString filename = fileLine[0].simplified();
         int subdivisions = fileLine[1].simplified().toInt();
         // limit subdivisions to 3
         subdivisions = (subdivisions > 3) ? 3 : subdivisions;

         mesh = geometryBuilder->buildMesh(filename, subdivisions);
      }

      // next line contains xIndex and zIndex for the object
      QStringList indexLine = strList[index++].split(" ", QString::SkipEmptyParts);
      int xIndex = indexLine[0].simplified().toInt();
      int zIndex = indexLine[1].simplified().toInt();
      // next line is rotation
      int rotation = strList[index++].simplified().toInt();
      // next line is scale
      QStringList scaleLine = strList[index++].split(" ", QString::SkipEmptyParts);
      float xScale = scaleLine[0].simplified().toFloat();
      float yScale = scaleLine[1].simplified().toFloat();
      float zScale = scaleLine[2].simplified().toFloat();
      // next line is empty
      ++index;

      // create the item
      if (item.compare("box") == 0)
      {
         Node *node = new Node(box);
         node->scale(glm::vec3(xScale, yScale, zScale));
         node->rotate(rotation, glm::vec3(0, 1, 0));
         node->setGeometryColor(Color::GRAY);
         roomNode->addChild(node, xIndex, zIndex);
         nodes.push_back(node);
      }
      else if (item.compare("table") == 0)
      {
         Node *node = new Node(table);
         node->scale(glm::vec3(xScale, yScale, zScale));
         node->rotate(rotation, glm::vec3(0, 1, 0));
         node->setGeometryColor(Color::CRIMSON);
         roomNode->addChild(node, xIndex, zIndex);
         nodes.push_back(node);
      }
      else if (item.compare("chair") == 0)
      {
         Node *node = new Node(chair);
         node->scale(glm::vec3(xScale, yScale, zScale));
         node->rotate(rotation, glm::vec3(0, 1, 0));
         node->setGeometryColor(Color::BLUE);
         roomNode->addChild(node, xIndex, zIndex);
         nodes.push_back(node);
      }
      else if (item.compare("sphere") == 0)
      {
         Node *node = new Node(sphere);
         node->scale(glm::vec3(xScale, yScale, zScale));
         node->rotate(rotation, glm::vec3(0, 1, 0));
         node->setGeometryColor(Color::YELLOW);
         roomNode->addChild(node, xIndex, zIndex);
         nodes.push_back(node);
      }
      else if (item.compare("mesh") == 0)
      {
         Node *node = new Node(mesh);
         node->scale(glm::vec3(xScale, yScale, zScale));
         node->rotate(rotation, glm::vec3(0, 1, 0));
         node->setGeometryColor(Color::ORANGE);
         roomNode->addChild(node, xIndex, zIndex);
         nodes.push_back(node);
      }
      else
      {
         QMessageBox::critical(glWidget, "Error", "Item not recognized");
      }
   }
   geometryBuilder->bindBuffers();
   selected = nodes.begin();
   (*selected)->setSelected(false);
}

glm::vec3 SceneGraph::getCenterOfRoom()
{
   return centerOfRoom;
}

void SceneGraph::render()
{
   // start with the identity matrix
   if (root) root->traverse(glm::mat4(1.0));
}

void SceneGraph::flush()
{
   if (root) delete root;
}

void SceneGraph::selectNext()
{
   if (++selected == nodes.end())
   {
      selected = nodes.begin();
   }
}

void SceneGraph::selectPrev()
{
   if (selected == nodes.begin())
   {
      selected = --nodes.end();
   }
   else --selected;
}

Node *SceneGraph::getSelected()
{
   return *selected;
}

void SceneGraph::subdivide(Node *node)
{
   if (!node->getGeometry()->isAbleToSubdivide()) return;

   // for now the only things that can subdivide are meshes so this is okay
   Mesh *mesh = dynamic_cast<Mesh*>(node->getGeometry());
   mesh = geometryBuilder->subdivide(mesh, 1);
   node->setGeometry(mesh);
   geometryBuilder->bindBuffers();
}
