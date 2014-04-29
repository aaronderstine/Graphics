/*****************************************************/
/* Author: Aaron Derstine                            */
/* Course: COMP 361, Computer Graphics               */
/* Date:   April 9, 2014                             */
/* Name:   GeometryBuilder.cpp                       */
/* Description: This file defines a factory that     */
/*         builds geometry and meshes from config    */
/*         files. It keeps track of all the geometry */
/*         it built and tells each geometry where in */
/*         the buffer it is defined.                 */
/*****************************************************/

#include "GeometryBuilder.h"
#include "glm\gtx\rotate_vector.hpp"
#include <QtCore\QStringList>
#include <QtWidgets/QMessageBox>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
using namespace HE;

GeometryBuilder::GeometryBuilder()
{

}


GeometryBuilder::~GeometryBuilder()
{
   for (std::vector<GeometryData>::iterator itr = geometryData.begin(); itr != geometryData.end(); ++itr)
      itr->clear();
   for (std::vector<Geometry*>::iterator itr = createdGeometry.begin(); itr != createdGeometry.end(); ++itr)
      if (*itr) delete *itr;
}

Mesh *GeometryBuilder::subdivide(Mesh *mesh, int times)
{
   // check if it can subdivide - if not return itself
   if (!mesh->isAbleToSubdivide()) return mesh;

   QString filename = mesh->getSourceFilename();
   int timesDone = mesh->getTimesSubdivided();

   // max of 3 subdivisions
   int total = (timesDone + times > 3) ? 3 : timesDone + times;

   // check if it is already done
   std::map<std::pair<QString, int>, std::pair<Mesh*, int>>::iterator itr, prev;
   if ((itr = subdivisionMap.find(std::pair<QString, int>(filename, total))) != subdivisionMap.end())
   {
      return (*itr).second.first;
   }

   // create if first time
   else if (total == 0) // first time through
   {
      mesh->setSourceFile(filename);
      mesh->setTimesSubdivided(0);
      subdivisionMap[std::pair<QString, int>(filename, 0)] = std::pair<Mesh*, int>(mesh, geometryData.size()-1);
   }

   // subdivide and save each intermittent mesh for future since it needs to create it most of the way in the process
   // this could save time later
   prev = subdivisionMap.end();
   for (int i=timesDone; i<=total; ++i)
   {
      // check if already subdivided
      if ((itr = subdivisionMap.find(std::pair<QString, int>(filename, i))) != subdivisionMap.end())
      {
         prev = itr;
         continue;
      }

      // otherwise subdivide last found mesh
      GeometryData subdivided = catmullClark(geometryData[(*prev).second.second]);
      mesh = generateMesh(subdivided);
      mesh->setSourceFile(filename);
      mesh->setTimesSubdivided(i);
      subdivisionMap[std::pair<QString, int>(filename, i)] = std::pair<Mesh*, int>(mesh, geometryData.size()-1);
   }

   return mesh;
}

void GeometryBuilder::fillColors(GeometryData &geometryData)
{
   int index = 0;
   for(int color=0; color<=Color::NUM_OF_COLORS; ++color)
   {
      for(int j=0; j<geometryData.verticies.size(); ++j, ++index)
      {
         switch (color)
         {
         case Color::TEST:
            geometryData.colors.push_back(Color::Test);
            break;
         case Color::BLUE:
            geometryData.colors.push_back(Color::Blue);
            break;
         case Color::BROWN:
            geometryData.colors.push_back(Color::Brown);
            break;
         case Color::CRIMSON:
            geometryData.colors.push_back(Color::Crimson);
            break;
         case Color::CYAN:
            geometryData.colors.push_back(Color::Cyan);
            break;
         case Color::GRAY:
            geometryData.colors.push_back(Color::Gray);
            break;
         case Color::GREEN:
            geometryData.colors.push_back(Color::Green);
            break;
         case Color::LIME:
            geometryData.colors.push_back(Color::Lime);
            break;
         case Color::MAGENTA:
            geometryData.colors.push_back(Color::Magenta);
            break;
         case Color::ORANGE:
            geometryData.colors.push_back(Color::Orange);
            break;
         case Color::RED:
            geometryData.colors.push_back(Color::Red);
            break;
         case Color::WHITE:
            geometryData.colors.push_back(Color::White);
            break;
         case Color::YELLOW:
            geometryData.colors.push_back(Color::Yellow);
            break;
         default:
            break;
         }
      }
   }
}

void GeometryBuilder::createHalfEdges(Face *face, std::vector<Vertex*> verticies, std::map<std::pair<int, int>, HalfEdge*> &edges)
{
   // simpler to keep track of verticies this way
   int *ids = new int[verticies.size()];
   for (int i=0; i<verticies.size(); ++i) ids[i] = verticies[i]->getId();

   int last = verticies.size()-1;
   typedef std::pair<int, int> Edge;
   for (int i=0; i<verticies.size()-1; ++i)
   {
      edges[Edge(ids[i], ids[i+1])] = new HalfEdge();
      verticies[i+1]->setHalfEdge(edges[Edge(ids[i], ids[i+1])]);
   }
   edges[Edge(ids[last], ids[0])] = new HalfEdge();
   verticies[0]->setHalfEdge(edges[Edge(ids[last], ids[0])]);

   // set face normal
   glm::vec3 v0 = glm::vec3(verticies[0]->getVertex());
   glm::vec3 v1 = glm::vec3(verticies[1]->getVertex());
   glm::vec3 v2 = glm::vec3(verticies[verticies.size()-1]->getVertex());
   face->setNormal(glm::vec4(glm::normalize(glm::cross(v1-v0, v2-v0)), 0.0));
   face->setHalfEdge(edges[Edge(ids[0], ids[1])]);

   for (int i=0; i<verticies.size()-2; ++i)
   {
      edges[Edge(ids[i], ids[i+1])]->setNext(edges[Edge(ids[i+1], ids[i+2])]); 
      edges[Edge(ids[i], ids[i+1])]->setFace(face); 
      edges[Edge(ids[i], ids[i+1])]->setVertex(verticies[i+1]);
   }
   // 2nd to last one
   edges[Edge(ids[last-1], ids[last])]->setNext(edges[Edge(ids[last], ids[0])]); 
   edges[Edge(ids[last-1], ids[last])]->setFace(face); 
   edges[Edge(ids[last-1], ids[last])]->setVertex(verticies[last]);
   // last one
   edges[Edge(ids[last], ids[0])]->setNext(edges[Edge(ids[0], ids[1])]); 
   edges[Edge(ids[last], ids[0])]->setFace(face); 
   edges[Edge(ids[last], ids[0])]->setVertex(verticies[0]);
   delete [] ids;
}

void GeometryBuilder::setSymPointers(const std::map<std::pair<int, int>, HalfEdge*> &edges)
{
   std::map<std::pair<int, int>, HalfEdge*>::const_iterator itr;
   for (itr = edges.begin(); itr != edges.end(); ++itr)
   {
      std::pair<int, int> opp = std::pair<int, int>(itr->first.second, itr->first.first);
      std::map<std::pair<int, int>, HalfEdge*>::const_iterator other = edges.find(opp);
      if (other != edges.end())
      {
         other->second->setSym(itr->second);
         itr->second->setSym(other->second);
      }
   }
}

void GeometryBuilder::calculateVertexNormals(GeometryData &data)
{
   std::vector<Vertex*>::iterator itr;
   for (itr = data.verticies.begin(); itr != data.verticies.end(); ++itr)
   {
      glm::vec4 total = glm::vec4(0.0, 0.0, 0.0, 0.0);
      int count = 0;
      HalfEdge *he = (*itr)->getHalfEdge();
      total += he->getFace()->getNormal();
      ++count;
      HalfEdge *next = he->getNext()->getSym();
      while (next && next != he)
      {
         total += next->getFace()->getNormal();
         ++count;
         next = next->getNext()->getSym();
      }
      (*itr)->setNormal(glm::vec4(glm::normalize(glm::vec3(total.x/count, total.y/count, total.z/count)), 0.0));
   }
}

void GeometryBuilder::calculateVertexNormalsNonConvex(GeometryData &data)
{
   std::vector<Face*>::iterator itr;
   for (itr = data.faces.begin(); itr != data.faces.end(); ++itr)
   {
      glm::vec4 total = glm::vec4(0.0, 0.0, 0.0, 0.0);
      Face *f1 = *itr;
      Face *f2;
      Vertex *v1;
      Vertex *v2;
      // find the next face
      HalfEdge *he1 = f1->getHalfEdge();
      HalfEdge *he2;
      while (!he1->getSym()) he1 = he1->getNext();
      he2 = he1->getSym();
      f2 = he2->getFace();
      total += f1->getNormal();
      total += f2->getNormal();
      v1 = he1->getVertex();
      v2 = he2->getVertex();
      v1->setNormal(glm::vec4(glm::normalize(glm::vec3(total.x/2, total.y/2, total.z/2)), 0.0));
      v2->setNormal(glm::vec4(glm::normalize(glm::vec3(total.x/2, total.y/2, total.z/2)), 0.0));
   }
}

void GeometryBuilder::fillIndicies(GeometryData &data)
{
   // index is different than id because of the buffer offset
   int diff = data.verticies[0]->getId();
   std::vector<Face*>::iterator itr;
   for (itr = data.faces.begin(); itr != data.faces.end(); ++itr)
   {
      HalfEdge *he = (*itr)->getHalfEdge();
      unsigned int start = he->getVertex()->getId() - diff;
      HalfEdge *next = he->getNext();
      while (he != next->getNext())
      {
         data.indicies.push_back(start);
         data.indicies.push_back(next->getVertex()->getId() - diff);
         next = next->getNext();
         data.indicies.push_back(next->getVertex()->getId() - diff); 
      }
   }
}

GeometryBuilder::GeometryData GeometryBuilder::catmullClark(const GeometryData &data)
{
   GeometryData subdivided;
   // keep an association between the face and the new vertex centered on it
   std::map<Face*, Vertex*> fvMap;

   // insert new vertex in middle of each face
   std::vector<Face*>::const_iterator faceItr;
   for (faceItr = data.faces.begin(); faceItr != data.faces.end(); ++faceItr)
   {
      // sum up all of the verticies
      HalfEdge *start = (*faceItr)->getHalfEdge();
      HalfEdge *next = start->getNext();
      glm::vec4 total = start->getVertex()->getVertex();
      while (start != next)
      {
         total += next->getVertex()->getVertex();
         next = next->getNext();
      }
      // w coord of total is the number of verticies since it is 1.0 for all of them
      Vertex *newVertex = new Vertex(glm::vec4(total.x/total.w, total.y/total.w, total.z/total.w, 1.0));
      // set normal to be what the face was
      newVertex->setNormal((*faceItr)->getNormal());
      subdivided.verticies.push_back(newVertex);
      fvMap[*faceItr] = newVertex;
   }

   // keep an association between the old verticies and the new edge verticies
   std::map<Vertex*, std::vector<std::pair<Vertex*, Vertex*>>> vMap;

   // add a vertex on the edges between the new face verticies
   std::vector<Vertex*>::const_iterator vertexItr;
   // keep track of if edge has been done
   std::map<std::pair<int, int>, Vertex*> edgeMap;
   std::map<std::pair<int, int>, Vertex*>::iterator edgeItr;
   for (vertexItr = data.verticies.begin(); vertexItr != data.verticies.end(); ++vertexItr)
   {
      HalfEdge *start = (*vertexItr)->getHalfEdge();
      HalfEdge *next = start;
      do
      {
         Vertex *vert1 = next->getVertex();
         Vertex *vert2 = next->getSym()->getVertex();
         Vertex *face1 = fvMap[next->getFace()];
         Vertex *face2 = fvMap[next->getSym()->getFace()];
         glm::vec4 v1 = vert1->getVertex();
         glm::vec4 v2 = vert2->getVertex();
         glm::vec4 f1 = face1->getVertex();
         glm::vec4 f2 = face2->getVertex();
         glm::vec4 total = v1 + v2 + f1 + f2;
         // only add the new vertex if not already done
         Vertex *newEdgeVertex;
         if ((edgeItr = edgeMap.find(std::pair<int, int>(vert2->getId(), vert1->getId()))) == edgeMap.end()) 
         {
            newEdgeVertex = new Vertex(glm::vec4(total.x/4, total.y/4, total.z/4, 1.0));
            // calculate normal = average of the 4 verticies making up this new one
            glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
            normal += vert1->getNormal();
            normal += vert2->getNormal();
            normal += face1->getNormal();
            normal += face2->getNormal();
            newEdgeVertex->setNormal(glm::vec4(glm::normalize(glm::vec3((float)normal.x/4, (float)normal.y/4, (float)normal.z/4)), 0.0));
            subdivided.verticies.push_back(newEdgeVertex);
         } else
         {
            newEdgeVertex = edgeItr->second;
         } 
         vMap[vert1].push_back(std::pair<Vertex*, Vertex*>(newEdgeVertex, fvMap[next->getFace()]));
         edgeMap[std::pair<int, int>(vert1->getId(), vert2->getId())] = newEdgeVertex;
         next = next->getNext()->getSym();
      } while (start != next);
   }

   // keep an association between the old verticies and where they move
   std::map<Vertex*, Vertex*> nvMap;

   // move the original verticies
   for (vertexItr = data.verticies.begin(); vertexItr != data.verticies.end(); ++vertexItr)
   {
      int n = vMap[*vertexItr].size();
      glm::vec4 edgeTotal = glm::vec4(0.0, 0.0, 0.0, 0.0);
      glm::vec4 faceTotal = glm::vec4(0.0, 0.0, 0.0, 0.0);
      glm::vec4 normal = glm::vec4(0.0, 0.0, 0.0, 0.0);
      for (int i=0; i<n; ++i)
      {
         Vertex *e = vMap[*vertexItr][i].first;
         edgeTotal += e->getVertex();
         Vertex *f = vMap[*vertexItr][i].second;
         faceTotal += f->getVertex();
         normal += e->getNormal();
         normal += f->getNormal();
      }
      glm::vec4 v = (*vertexItr)->getVertex();
      float x = (float)v.x * (n-2)/n + (float)edgeTotal.x/(n*n) + (float)faceTotal.x/(n*n);
      float y = (float)v.y * (n-2)/n + (float)edgeTotal.y/(n*n) + (float)faceTotal.y/(n*n);
      float z = (float)v.z * (n-2)/n + (float)edgeTotal.z/(n*n) + (float)faceTotal.z/(n*n);
      Vertex *newVertex = new Vertex(glm::vec4(x, y, z, 1.0));
      newVertex->setNormal(glm::vec4(glm::normalize(glm::vec3((float)normal.x/(2*n), (float)normal.y/(2*n), (float)normal.z/(2*n))), 0.0));
      nvMap[*vertexItr] = newVertex;
      subdivided.verticies.push_back(newVertex);
   }

   // construct the halfedges and faces
   std::map<Vertex*, Vertex*>::const_iterator vMapItr;
   for (vMapItr = nvMap.begin(); vMapItr != nvMap.end(); ++vMapItr)
   {
      // do every face around the original vertex
      for (int i=0; i<vMap[vMapItr->first].size()-1; ++i)
      {
         // construct a new face
         Face *face = new Face();
         subdivided.faces.push_back(face);
         std::vector<Vertex*> temp;
         // get the 4 verticies bounding face
         // moved vertex
         Vertex *v = vMapItr->second;
         // edge vertex
         Vertex *e1 = vMap[vMapItr->first][i].first;
         // face vertex
         Vertex *f = vMap[vMapItr->first][i].second;
         // returning edge
         Vertex *e2 = vMap[vMapItr->first][i+1].first;
         
         temp.push_back(v);
         temp.push_back(e1);
         temp.push_back(f);
         temp.push_back(e2);
         createHalfEdges(face, temp, subdivided.edges);
         // override the normal calculation in createHalfEdges
         glm::vec4 normal = v->getNormal() + e1->getNormal() + f->getNormal() + e2->getNormal();
         face->setNormal(glm::vec4(glm::normalize(glm::vec3(normal.x/4, normal.y/4, normal.z/4)), 0.0));
      }
      // now do last one
      // construct a new face
      Face *face = new Face();
      subdivided.faces.push_back(face);
      std::vector<Vertex*> temp;
      // get the 4 verticies bounding face
      // moved vertex
      Vertex *v = vMapItr->second;
      // edge vertex
      Vertex *e1 = vMap[vMapItr->first][vMap[vMapItr->first].size()-1].first;
      // face vertex
      Vertex *f = vMap[vMapItr->first][vMap[vMapItr->first].size()-1].second;
      // returning edge
      Vertex *e2 = vMap[vMapItr->first][0].first;
      
      temp.push_back(v);
      temp.push_back(e1);
      temp.push_back(f);
      temp.push_back(e2);
      createHalfEdges(face, temp, subdivided.edges);
      // override the normal calculation in createHalfEdges
      glm::vec4 normal = v->getNormal() + e1->getNormal() + f->getNormal() + e2->getNormal();
      face->setNormal(glm::vec4(glm::normalize(glm::vec3(normal.x/4, normal.y/4, normal.z/4)), 0.0));
   }
   setSymPointers(subdivided.edges);
   calculateVertexNormals(subdivided);

   // set colors
   fillColors(subdivided);

   // fill index buffer
   fillIndicies(subdivided);

   return subdivided;
}

float GeometryBuilder::makeUnitSize(GeometryData &data)
{
   float minX = 0.0;
   float minY = 0.0;
   float minZ = 0.0;
   float maxX = 0.0;
   float maxY = 0.0;
   float maxZ = 0.0;

   for (std::vector<Vertex*>::const_iterator itr = data.verticies.begin(); itr != data.verticies.end(); ++itr)
   {
      glm::vec4 vertex = (*itr)->getVertex();
      minX = (vertex.x < minX) ? vertex.x : minX;
      maxX = (vertex.x > maxX) ? vertex.x : maxX;
      minY = (vertex.y < minY) ? vertex.y : minY;
      maxY = (vertex.y > maxY) ? vertex.y : maxY;
      minZ = (vertex.z < minZ) ? vertex.z : minZ;
      maxZ = (vertex.z > maxZ) ? vertex.z : maxZ;
   }
   float diffX = maxX - minX;
   float diffY = maxY - minY;
   float diffZ = maxZ - minZ;
   float shiftX = (diffX)/2.0 + minX;
   float shiftY = minY;
   float shiftZ = (diffZ)/2.0 + minZ;

   float scale = (diffX >= diffY && diffX >= diffZ) ? diffX : (diffY >= diffX && diffY >= diffZ) ? diffY : diffZ;
   
   for (std::vector<Vertex*>::iterator itr = data.verticies.begin(); itr != data.verticies.end(); ++itr)
   {
      glm::vec4 v = (*itr)->getVertex();
      (*itr)->setVertex(glm::vec4((v.x - shiftX)/scale, (v.y - shiftY)/scale, (v.z - shiftZ)/scale, 1.0));
   }
   return diffY/scale;
}

bool GeometryBuilder::isConvex(const std::vector<glm::vec4> &points)
{
   // if there are 3 or less points then it is guaranteed to be convex
   if (points.size() <= 3) return true;

   // otherwise check cross products and make sure they are all the same of consecutive points
   glm::vec3 v1 = glm::vec3(points[1] - points[0]);
   glm::vec3 v2 = glm::vec3(points[points.size()-2] - points[0]); // -2 since last point is same as first
   glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
   for (int i=1; i<points.size()-1; ++i)
   {
      v1 = glm::vec3(points[i+1] - points[i]);
      v2 = glm::vec3(points[i-1] - points[i]);
      if (-normal == glm::normalize(glm::cross(v1, v2))) return false;
   }
   return true;
}

void GeometryBuilder::bindBuffers()
{
   // determine size of arrays
   int cSize = 0, vnSize = 0, iSize = 0;
   for (int i=0; i<geometryData.size(); ++i)
   {
      vnSize += geometryData[i].verticies.size();
      cSize += geometryData[i].colors.size();
      iSize += geometryData[i].indicies.size();
   }
   if (vnSize == 0) return;

   // create vertex buffer
   glm::vec4 *verticies = new glm::vec4[vnSize];
   // create normal buffer
   glm::vec4 *normals = new glm::vec4[vnSize];
   // create color buffer (different size since contains many colors)
   glm::vec3 *colors = new glm::vec3[cSize];
   // create index buffer
   unsigned int *indicies = new unsigned int[iSize];
   int vnIndex = 0, cIndex = 0, iIndex = 0;
   for (int i=0; i<geometryData.size(); ++i)
   {
      for (int j=0; j<geometryData[i].verticies.size(); ++j)
      {
         verticies[vnIndex] = geometryData[i].verticies[j]->getVertex();
         normals[vnIndex++] = geometryData[i].verticies[j]->getNormal();
      }
      for (int j=0; j<geometryData[i].colors.size(); ++j)
         colors[cIndex++] = geometryData[i].colors[j];
      for (int j=0; j<geometryData[i].indicies.size(); ++j)
         indicies[iIndex++] = geometryData[i].indicies[j];
   }
   glBindBuffer(GL_ARRAY_BUFFER, Geometry::getVBO());
	glBufferData(GL_ARRAY_BUFFER, vnSize * sizeof(glm::vec4), verticies, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, Geometry::getNBO());
	glBufferData(GL_ARRAY_BUFFER, vnSize * sizeof(glm::vec4), normals, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, Geometry::getCBO());
	glBufferData(GL_ARRAY_BUFFER, cSize * sizeof(glm::vec3), colors, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Geometry::getIBO());
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(unsigned int), indicies, GL_STATIC_DRAW);
   delete [] verticies;
   delete [] normals;
   delete [] colors;  
   delete [] indicies;
}

CubeGeometry *GeometryBuilder::buildCube()
{
   GeometryData cubeData;

   // store verticies
   // 1st face
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 0.0, 0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 1.0, 0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 1.0, 0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 0.0, 0.5, 1.0)));
   // 2nd face
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 0.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 1.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 1.0, 0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 0.0, 0.5, 1.0)));
   // 3rd face
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 0.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 1.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 1.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 0.0, -0.5, 1.0)));
   // 4th face
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 0.0, 0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 1.0, 0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 1.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 0.0, -0.5, 1.0)));
   // 5th face
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 1.0, 0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 1.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 1.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 1.0, 0.5, 1.0)));
   // 6th face
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 0.0, 0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(-0.5, 0.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 0.0, -0.5, 1.0)));
   cubeData.verticies.push_back(new Vertex(glm::vec4(0.5, 0.0, 0.5, 1.0)));

   // insert normals
   int i = 0;
   // 1st face
   for (int j=0; j<4; ++j) cubeData.verticies[i++]->setNormal(glm::vec4(0.0, 0.0, 1.0, 0.0));
   // 2nd face
   for (int j=0; j<4; ++j) cubeData.verticies[i++]->setNormal(glm::vec4(1.0, 0.0, 0.0, 0.0));
   // 3rd face
   for (int j=0; j<4; ++j) cubeData.verticies[i++]->setNormal(glm::vec4(0.0, 0.0, -1.0, 0.0));
   // 4th face
   for (int j=0; j<4; ++j) cubeData.verticies[i++]->setNormal(glm::vec4(-1.0, 0.0, 0.0, 0.0));
   // 5th face
   for (int j=0; j<4; ++j) cubeData.verticies[i++]->setNormal(glm::vec4(0.0, 1.0, 0.0, 0.0));
   // 6th face
   for (int j=0; j<4; ++j) cubeData.verticies[i++]->setNormal(glm::vec4(0.0, -1.0, 0.0, 0.0));

   // insert colors
   fillColors(cubeData);

   // determine where the index buffer starts
   unsigned int index = 0;
   //for (int i=0; i<geometryData.size(); ++i) index += geometryData[i].verticies.size(); 

   // insert indicies
   for (int i=0; i<6; ++i)
   {
      unsigned int start = index;
      cubeData.indicies.push_back(index++);
      cubeData.indicies.push_back(index++);
      cubeData.indicies.push_back(index);
      cubeData.indicies.push_back(index++);
      cubeData.indicies.push_back(index++);
      cubeData.indicies.push_back(start);
   }

   // determine other offsets
   int colorOffset = 0;
   int vnOffset = 0;
   int indexOffset = 0;
   for (int i=0; i<geometryData.size(); ++i) 
   {
      colorOffset += geometryData[i].colors.size(); 
      vnOffset += geometryData[i].verticies.size();
      indexOffset += geometryData[i].indicies.size();
   }

   // create the cubeGeometry
   CubeGeometry *cube = new CubeGeometry();

   cube->setNumberOfIndicies(36);
   cube->setNumberOfVerticies(24);
   cube->setColorOffset(colorOffset);
   cube->setIndexOffset(indexOffset);
   cube->setVertexAndNormalOffset(vnOffset);

   // add cube data to geometryData for rendering
   geometryData.push_back(cubeData);

   createdGeometry.push_back(cube);
   return cube;
}

SphereGeometry *GeometryBuilder::buildSphere()
{
   GeometryData sphereData;

   // build the 6 faces
   for (int i=0; i<6; ++i) sphereData.faces.push_back(new Face());

   // create the 8 verticies
   sphereData.verticies.push_back(new Vertex(glm::vec4(-0.5, -0.5, 0.5, 1.0)));
   sphereData.verticies.push_back(new Vertex(glm::vec4(0.5, -0.5, 0.5, 1.0)));
   sphereData.verticies.push_back(new Vertex(glm::vec4(0.5, 0.5, 0.5, 1.0)));
   sphereData.verticies.push_back(new Vertex(glm::vec4(-0.5, 0.5, 0.5, 1.0)));
      
   sphereData.verticies.push_back(new Vertex(glm::vec4(-0.5, -0.5, -0.5, 1.0)));
   sphereData.verticies.push_back(new Vertex(glm::vec4(-0.5, 0.5, -0.5, 1.0)));
   sphereData.verticies.push_back(new Vertex(glm::vec4(0.5, 0.5, -0.5, 1.0)));
   sphereData.verticies.push_back(new Vertex(glm::vec4(0.5, -0.5, -0.5, 1.0)));

   // create the halfedge data structure
   std::vector<Vertex*> temp;
   // 1st face
   temp.push_back(sphereData.verticies[0]);
   temp.push_back(sphereData.verticies[1]);
   temp.push_back(sphereData.verticies[2]);
   temp.push_back(sphereData.verticies[3]);
   createHalfEdges(sphereData.faces[0], temp, sphereData.edges);
   // 2nd face
   temp.clear();
   temp.push_back(sphereData.verticies[1]);
   temp.push_back(sphereData.verticies[7]);
   temp.push_back(sphereData.verticies[6]);
   temp.push_back(sphereData.verticies[2]);
   createHalfEdges(sphereData.faces[1], temp, sphereData.edges);
   // 3rd face
   temp.clear();
   temp.push_back(sphereData.verticies[7]);
   temp.push_back(sphereData.verticies[4]);
   temp.push_back(sphereData.verticies[5]);
   temp.push_back(sphereData.verticies[6]);
   createHalfEdges(sphereData.faces[2], temp, sphereData.edges);
   // 4th face
   temp.clear();
   temp.push_back(sphereData.verticies[4]);
   temp.push_back(sphereData.verticies[0]);
   temp.push_back(sphereData.verticies[3]);
   temp.push_back(sphereData.verticies[5]);
   createHalfEdges(sphereData.faces[3], temp, sphereData.edges);
   // 5th face
   temp.clear();
   temp.push_back(sphereData.verticies[3]);
   temp.push_back(sphereData.verticies[2]);
   temp.push_back(sphereData.verticies[6]);
   temp.push_back(sphereData.verticies[5]);
   createHalfEdges(sphereData.faces[4], temp, sphereData.edges);
   // 6th face
   temp.clear();
   temp.push_back(sphereData.verticies[0]);
   temp.push_back(sphereData.verticies[4]);
   temp.push_back(sphereData.verticies[7]);
   temp.push_back(sphereData.verticies[1]);
   createHalfEdges(sphereData.faces[5], temp, sphereData.edges);

   setSymPointers(sphereData.edges);

   calculateVertexNormals(sphereData);

   // set colors
   fillColors(sphereData);

   GeometryData tempData[2];
   tempData[0] = catmullClark(sphereData);
   sphereData.clear();
   // do second iteration
   tempData[1] = catmullClark(tempData[0]);
   // do third iteration
   sphereData = catmullClark(tempData[1]);
   
   tempData[0].clear();
   tempData[1].clear();

   // determine buffer offsets
   int colorOffset = 0;
   int vnOffset = 0;
   int indexOffset = 0;
   for (int i=0; i<geometryData.size(); ++i) 
   {
      colorOffset += geometryData[i].colors.size(); 
      vnOffset += geometryData[i].verticies.size();
      indexOffset += geometryData[i].indicies.size();
   }

   // create the SphereGeometry
   SphereGeometry *sphere = new SphereGeometry();

   sphere->setNumberOfIndicies(sphereData.indicies.size());
   sphere->setNumberOfVerticies(sphereData.verticies.size());
   sphere->setColorOffset(colorOffset);
   sphere->setIndexOffset(indexOffset);
   sphere->setVertexAndNormalOffset(vnOffset);

   float height = makeUnitSize(sphereData);
   sphere->setHeight(height);
   geometryData.push_back(sphereData);

   createdGeometry.push_back(sphere);
   return sphere;
}

Mesh *GeometryBuilder::buildMesh(QString filename, int subdivisions)
{
   // see if it was already created
   std::map<std::pair<QString, int>, std::pair<Mesh*, int>>::iterator itr;
   if ((itr = subdivisionMap.find(std::pair<QString, int>(filename, subdivisions))) != subdivisionMap.end())
   {
      return (*itr).second.first;
   }

   // read the config file text
   QFile file(filename);
   if (!file.open(QIODevice::ReadOnly)) 
   {
      QMessageBox::critical(NULL, "Error", "Could not open mesh config file");
      return NULL;
   }
   // read the entire file into a string and pass it into the widget
   QTextStream in(&file);
   QString configFileText = in.readAll();
   file.close();

   // separate the file line-by-line
   QStringList strList = configFileText.split("\n", QString::SkipEmptyParts);

   // create an index to keep track of what line on currently
   int index = 0;

   // holds the verticies
   std::vector<glm::vec4> points;

   // first line is type of mesh
   QString type = strList[index++].simplified();

   if (type == "extrusion")
   {
      // second line is height
      float height = strList[index++].simplified().toFloat();

      // 3rd line is number of points
      int num = strList[index++].simplified().toInt();

      // insert verticies into glm::vec4
      for(int i=0; i<num; ++i)
      {
         // each line contains an x and a z coordinate
         QStringList indexLine = strList[index++].split(" ", QString::SkipEmptyParts);
         float x = indexLine[0].simplified().toFloat();
         float z = indexLine[1].simplified().toFloat();
         points.push_back(glm::vec4(x, 0.0, z, 1.0));
      }

      Mesh *extrusion =  createExtrusion(points, height);
      extrusion->setSourceFile(filename);
      return subdivide(extrusion, subdivisions);
   }
   else if (type == "surfrev")
   {
      // second line is number of slices
      int slices = strList[index++].simplified().toInt();

      // 3rd line is number of points
      int num = strList[index++].simplified().toInt();

      // insert verticies into glm::vec4
      for(int i=0; i<num; ++i)
      {
         // each line contains an x and a z coordinate
         QStringList indexLine = strList[index++].split(" ", QString::SkipEmptyParts);
         float x = indexLine[0].simplified().toFloat();
         float y = indexLine[1].simplified().toFloat();
         points.push_back(glm::vec4(x, y, 0.0, 1.0));
      }

      Mesh *surfrev = createSurfrev(points, slices);
      surfrev->setSourceFile(filename);
      return subdivide(surfrev, subdivisions);
   }
   return NULL;
}

Mesh *GeometryBuilder::createExtrusion(std::vector<glm::vec4> &base, float height)
{
   GeometryData extrusion;

   // make sure verticies are in the correct order
   rearrangeExtrusionVerticies(base);

   bool convex = isConvex(base);

   // remove last verticie since it is not needed
   base.pop_back();

   // insert the verticies - base then top
   for (int i=0; i<base.size(); ++i) extrusion.verticies.push_back(new Vertex(base[i]));
   for (int i=0; i<base.size(); ++i) extrusion.verticies.push_back(new Vertex(glm::vec4(base[i].x, height, base[i].z, 1.0)));

   // create side faces and halfedge data structure
   for (int i=0; i<base.size()-1; ++i)
   {
      Face *face = new Face();
      Vertex *v1 = extrusion.verticies[i];
      Vertex *v2 = extrusion.verticies[i+base.size()];
      Vertex *v3 = extrusion.verticies[i+1+base.size()];
      Vertex *v4 = extrusion.verticies[i+1];
      std::vector<Vertex*> temp;
      temp.push_back(v1);
      temp.push_back(v2);
      temp.push_back(v3);
      temp.push_back(v4);
      createHalfEdges(face, temp, extrusion.edges);
      // calculate face normal
      glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(v2->getVertex()) - glm::vec3(v1->getVertex()), 
                                                   glm::vec3(v4->getVertex()) - glm::vec3(v1->getVertex()))); 
      face->setNormal(glm::vec4(normal, 0.0));
      extrusion.faces.push_back(face);
   }
   // now do last one
   Face *face = new Face();
   Vertex *v1 = extrusion.verticies[base.size()-1];
   Vertex *v2 = extrusion.verticies[base.size()-1+base.size()];
   Vertex *v3 = extrusion.verticies[base.size()];
   Vertex *v4 = extrusion.verticies[0];
   std::vector<Vertex*> temp;
   temp.push_back(v1);
   temp.push_back(v2);
   temp.push_back(v3);
   temp.push_back(v4);
   createHalfEdges(face, temp, extrusion.edges);
   // calculate face normal
   glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(v2->getVertex()) - glm::vec3(v1->getVertex()), 
                                                glm::vec3(v4->getVertex()) - glm::vec3(v1->getVertex()))); 
   face->setNormal(glm::vec4(normal, 0.0));
   extrusion.faces.push_back(face);

   // if it is convex triangulate base and add that face to mesh
   if (convex)
   {
      // bottom
      Face *bottom = new Face();
      std::vector<Vertex*> temp;
      for (int i=0; i<base.size(); ++i) temp.push_back(extrusion.verticies[i]);
      createHalfEdges(bottom, temp, extrusion.edges);
      bottom->setNormal(glm::vec4(0.0, -1.0, 0.0, 0.0));
      extrusion.faces.push_back(bottom);
      // top
      Face *top = new Face();
      temp.clear();
      for (int i=base.size()-1; i>=0; --i) temp.push_back(extrusion.verticies[i + base.size()]);
      createHalfEdges(top, temp, extrusion.edges);
      top->setNormal(glm::vec4(0.0, 1.0, 0.0, 0.0));
      extrusion.faces.push_back(top);
   }

   setSymPointers(extrusion.edges);
   if (convex) calculateVertexNormals(extrusion);
   else calculateVertexNormalsNonConvex(extrusion);

   // set colors
   fillColors(extrusion);

   // fill index buffer
   fillIndicies(extrusion);

   // create the extrusion
   return generateMesh(extrusion);
}

void GeometryBuilder::rearrangeExtrusionVerticies(std::vector<glm::vec4> &base)
{
   // find verticie that is farthest down z axis
   int min = 0; // index of the vertex
   for (int i=1; i<base.size()-1; ++i)
      min = (base[i].z < base[min].z) ? i : min;
   
   bool flip = false;
   glm::vec4 newStart = base[min];
   glm::vec4 prev     = (min > 0) ? base[min-1] : base[base.size() - 2];
   glm::vec4 next     = base[min + 1];

   // make sure verticies are ordered correctly for calculating normals
   if (glm::normalize(glm::cross(glm::vec3(next - newStart), glm::vec3(prev - newStart))).y > 0) flip = true;

   if (min == 0 && !flip) return; // already ordered correctly

   std::vector<glm::vec4> newBaseVector;
   base.pop_back(); // remove original extra start/stop vertex

   if (flip) // reorder backwards
   {
      for (int i=min; i>=0; --i)
         newBaseVector.push_back(base[i]);
      for (int i=base.size()-1; i>=min; --i)
         newBaseVector.push_back(base[i]);
   }
   else // reorder in same sequence
   {
      for (int i=min; i<base.size(); ++i)
         newBaseVector.push_back(base[i]);
      for (int i=0; i<=min; ++i)
         newBaseVector.push_back(base[i]);      
   }
   base = newBaseVector;
}

Mesh *GeometryBuilder::createSurfrev(std::vector<glm::vec4> &base, int slices)
{
   GeometryData surfrev;
   
   // if first and last point are the same then remove last one and set flag
   bool needToConnect = false;
   if (base[0] == base[base.size()-1])
   {
      needToConnect = true;
      base.pop_back();
   }
   if (!(base[0].x == 0.0 && base[base.size()-1].x == 0.0))
   {
      needToConnect = true;
   }
   // if it will be connecting on the y axis add a point just above it so it can be subdivided correctly if needed
   if (needToConnect && base[0].x == 0.0)
   {
      base.push_back(glm::vec4(0.0, 0.01, 0.0, 1.0)); 
      needToConnect = false;
   }

   // make sure there are at least 3 slices
   slices = (slices < 3) ? 3 : slices;

   // create all the verticies
   float degrees = 360.0/slices;
   for (int i=0; i<base.size(); ++i)
   {
      surfrev.verticies.push_back(new Vertex(base[i]));
      // if on y axis do not break into slices
      if (base[i].x == 0.0) continue;
      for (int j=1; j<slices; ++j)
         surfrev.verticies.push_back(new Vertex(glm::rotate(base[i], -j*degrees, glm::vec3(0,1,0))));
   }

   // create side faces
   int index = 0;
   for (int i=0; i<base.size()-1; ++i)
   {
      // if two consecutive points are on the y axis then skip
      if (base[i].x == 0.0 && base[i+1].x == 0) 
      {
         ++index;
         continue;
      }
      
      for (int j=0; j<slices-1; ++j)
      {
         Vertex *v1, *v2, *v3, *v4;  
         std::vector<Vertex*> temp;
         // check if base[i] is on y axis
         if (base[i].x == 0.0)
         {
            // make triangle
            v1 = surfrev.verticies[index];
            v2 = surfrev.verticies[index + j + 1];
            v3 = surfrev.verticies[index + j + 2];
            v4 = v3; // for normal calculation
            temp.push_back(v1);
            temp.push_back(v2);
            temp.push_back(v3);
         }
         else
         {
            // check if next point is on y axis
            if (base[i+1].x == 0.0)
            {
               // make triangle
               v1 = surfrev.verticies[index + j];
               v2 = surfrev.verticies[index + slices];
               v3 = surfrev.verticies[index + j + 1];
               v4 = v3; // for normal calculation
               temp.push_back(v1);
               temp.push_back(v2);
               temp.push_back(v3);
            }
            else // make square
            {
               v1 = surfrev.verticies[index + j];
               v2 = surfrev.verticies[index + j + slices];
               v3 = surfrev.verticies[index + j + slices + 1];
               v4 = surfrev.verticies[index + j + 1];
               temp.push_back(v1);
               temp.push_back(v2);
               temp.push_back(v3);
               temp.push_back(v4);
            }
         }
         Face *face = new Face();
         createHalfEdges(face, temp, surfrev.edges);
         // calculate face normal
         glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(v2->getVertex()) - glm::vec3(v1->getVertex()), 
                                                      glm::vec3(v4->getVertex()) - glm::vec3(v1->getVertex()))); 
         face->setNormal(glm::vec4(normal, 0.0));
         surfrev.faces.push_back(face);
      }
     
      // connect last slice to start
      Vertex *v1, *v2, *v3, *v4;  
      std::vector<Vertex*> temp;
      // check if base[i] is on y axis
      if (base[i].x == 0.0)
      {
         // make triangle
         v1 = surfrev.verticies[index];
         v2 = surfrev.verticies[index + slices];
         v3 = surfrev.verticies[index + 1];
         v4 = v3; // for normal calculation
         temp.push_back(v1);
         temp.push_back(v2);
         temp.push_back(v3);
      }
      else
      {
         // check if next point is on y axis
         if (base[i+1].x == 0.0)
         {
            // make triangle
            v1 = surfrev.verticies[index + slices - 1];
            v2 = surfrev.verticies[index + slices];
            v3 = surfrev.verticies[index];
            v4 = v3; // for normal calculation
            temp.push_back(v1);
            temp.push_back(v2);
            temp.push_back(v3);
         }
         else // make square
         {
            v1 = surfrev.verticies[index + slices - 1];
            v2 = surfrev.verticies[index + 2*slices - 1];
            v3 = surfrev.verticies[index + slices];
            v4 = surfrev.verticies[index];
            temp.push_back(v1);
            temp.push_back(v2);
            temp.push_back(v3);
            temp.push_back(v4);
         }
      }
      Face *face = new Face();
      createHalfEdges(face, temp, surfrev.edges);
      // calculate face normal
      glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(v2->getVertex()) - glm::vec3(v1->getVertex()), 
                                                   glm::vec3(v4->getVertex()) - glm::vec3(v1->getVertex()))); 
      face->setNormal(glm::vec4(normal, 0.0));
      surfrev.faces.push_back(face);
      
      // increment the index
      index += (base[i].x == 0) ? 1 : slices;
   }

   // check if need to connect the surfrev
   int end = base.size()-1;
   if (needToConnect)
   {
      int finalRev = (base[end].x == 0.0) ? surfrev.verticies.size()-1 : surfrev.verticies.size() - slices;
      for (int i=0; i<slices-1; ++i)
      {
         Vertex *v1, *v2, *v3, *v4;  
         std::vector<Vertex*> temp;
         // check if base[end] is on y axis
         if (base[end].x == 0.0)
         {
            // make triangle
            v1 = surfrev.verticies[finalRev];
            v2 = surfrev.verticies[i];
            v3 = surfrev.verticies[i+1];
            v4 = v3; // for normal calculation
            temp.push_back(v1);
            temp.push_back(v2);
            temp.push_back(v3);
         }
         else
         {
            // check if first point is on y axis
            if (base[0].x == 0.0)
            {
               // make triangle
               v1 = surfrev.verticies[finalRev + i];
               v2 = surfrev.verticies[0];
               v3 = surfrev.verticies[finalRev + i + 1];
               v4 = v3; // for normal calculation
               temp.push_back(v1);
               temp.push_back(v2);
               temp.push_back(v3);
            }
            else // make square
            {
               v1 = surfrev.verticies[finalRev + i];
               v2 = surfrev.verticies[i];
               v3 = surfrev.verticies[i + 1];
               v4 = surfrev.verticies[finalRev + i + 1];
               temp.push_back(v1);
               temp.push_back(v2);
               temp.push_back(v3);
               temp.push_back(v4);
            }
         }
         Face *face = new Face();
         createHalfEdges(face, temp, surfrev.edges);
         // calculate face normal
         glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(v2->getVertex()) - glm::vec3(v1->getVertex()), 
                                                      glm::vec3(v4->getVertex()) - glm::vec3(v1->getVertex()))); 
         face->setNormal(glm::vec4(normal, 0.0));
         surfrev.faces.push_back(face);
      }
      // connect last slice to start
      Vertex *v1, *v2, *v3, *v4;  
      std::vector<Vertex*> temp;
      // check if base[end] is on y axis
      if (base[end].x == 0.0)
      {
         // make triangle
         v1 = surfrev.verticies[finalRev];
         v2 = surfrev.verticies[slices - 1];
         v3 = surfrev.verticies[0];
         v4 = v3; // for normal calculation
         temp.push_back(v1);
         temp.push_back(v2);
         temp.push_back(v3);
      }
      else
      {
         // check if first point is on y axis
         if (base[0].x == 0.0)
         {
            // make triangle
            v1 = surfrev.verticies[finalRev + slices - 1];
            v2 = surfrev.verticies[0];
            v3 = surfrev.verticies[finalRev];
            v4 = v3; // for normal calculation
            temp.push_back(v1);
            temp.push_back(v2);
            temp.push_back(v3);
         }
         else // make square
         {
            v1 = surfrev.verticies[finalRev + slices - 1];
            v2 = surfrev.verticies[slices - 1];
            v3 = surfrev.verticies[0];
            v4 = surfrev.verticies[finalRev];
            temp.push_back(v1);
            temp.push_back(v2);
            temp.push_back(v3);
            temp.push_back(v4);
         }
      }
      Face *face = new Face();
      createHalfEdges(face, temp, surfrev.edges);
      // calculate face normal
      glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(v2->getVertex()) - glm::vec3(v1->getVertex()), 
                                                   glm::vec3(v4->getVertex()) - glm::vec3(v1->getVertex()))); 
      face->setNormal(glm::vec4(normal, 0.0));
      surfrev.faces.push_back(face);
   }

   setSymPointers(surfrev.edges);
   calculateVertexNormals(surfrev);

   // set colors
   fillColors(surfrev);

   // fill index buffer
   fillIndicies(surfrev);

   // create the survrev
   return generateMesh(surfrev);
}

Mesh *GeometryBuilder::generateMesh(GeometryData &data)
{
   // determine buffer offsets
   int colorOffset = 0;
   int vnOffset = 0;
   int indexOffset = 0;
   for (int i=0; i<geometryData.size(); ++i) 
   {
      colorOffset += geometryData[i].colors.size(); 
      vnOffset += geometryData[i].verticies.size();
      indexOffset += geometryData[i].indicies.size();
   }

   // create the Mesh
   Mesh *mesh = new Mesh;

   mesh->setNumberOfIndicies(data.indicies.size());
   mesh->setNumberOfVerticies(data.verticies.size());
   mesh->setColorOffset(colorOffset);
   mesh->setIndexOffset(indexOffset);
   mesh->setVertexAndNormalOffset(vnOffset);

   float height = makeUnitSize(data);
   mesh->setHeight(height);
   geometryData.push_back(data);

   createdGeometry.push_back(mesh);
   return mesh;
}