/*****************************************************/
/* Author: Aaron Derstine                            */
/* Course: COMP 361, Computer Graphics               */
/* Date:   April 9, 2014                             */
/* Name:   GeometryBuilder.h                         */
/* Description: This file defines a factory that     */
/*         builds geometry and meshes from config    */
/*         files. It keeps track of all the geometry */
/*         it built and tells each geometry where in */
/*         the buffer it is defined.                 */
/*****************************************************/

#pragma once
#include "CubeGeometry.h"
#include "SphereGeometry.h"
#include "HE.h"
#include <vector>
#include <map>
#include "Mesh.h"
#include <QtCore\QString>

class GeometryBuilder
{
public:
   GeometryBuilder();
   ~GeometryBuilder();

   CubeGeometry *buildCube();
   SphereGeometry *buildSphere();
   // takes the text from a config file and returns the mesh that was build
   Mesh *buildMesh(QString filename, int subdivisions = 0);
   Mesh *subdivide(Mesh *mesh, int times);

   // needs to be called after new geometry is generated
   void bindBuffers();

   
private:
   struct GeometryData 
   {
      std::vector<HE::Vertex*> verticies;
      std::vector<HE::Face*>   faces;
      std::vector<glm::vec3>   colors;
      std::map<std::pair<int, int>, HE::HalfEdge*> edges;
      std::vector<unsigned int> indicies;
      void clear()
      {
         std::vector<HE::Vertex*>::iterator vItr;
         for (vItr = verticies.begin(); vItr != verticies.end(); ++vItr) delete *vItr;
         std::vector<HE::Face*>::iterator   fItr;
         for (fItr = faces.begin(); fItr != faces.end(); ++fItr) delete *fItr;
         std::map<std::pair<int, int>, HE::HalfEdge*>::iterator eItr;
         for (eItr = edges.begin(); eItr != edges.end(); ++eItr) delete eItr->second;
         verticies.clear();
         faces.clear();
         edges.clear();
         colors.clear();
      }
   };
   std::vector<GeometryData> geometryData;

   // map of what subdivions and meshes have already been created
   // first: QString - filename, int - number of subdivisions
   // second: Mesh* - mesh, int - index in geometryData of GeometryData for the mesh
   std::map<std::pair<QString, int>, std::pair<Mesh*, int>> subdivisionMap;

   // fills the GeometryData with all the colors based off of how many verticies
   void fillColors(GeometryData &geometryData);
   // fills the edges map with the edges defined by the vector of verticies and the face
   // connects all pointers between face, verticies, and half edges
   // edges can be empty to begin
   void createHalfEdges(HE::Face *face, std::vector<HE::Vertex*> verticies, std::map<std::pair<int, int>, HE::HalfEdge*> &edges);
   // all sym pointers in edges are connected
   void setSymPointers(const std::map<std::pair<int, int>, HE::HalfEdge*> &edges);

   void calculateVertexNormals(GeometryData &data);
   void calculateVertexNormalsNonConvex(GeometryData &data);
   // triangulates each face by filling the index buffer accordingly
   void fillIndicies(GeometryData &data);

   // creates a new GeometryData that is a subdivided version of the input
   GeometryData catmullClark(const GeometryData &data);

   bool isConvex(const std::vector<glm::vec4> &points);

   // shifts the geometry into position and scales it so it is unit size
   // returns the height for stacking
   float makeUnitSize(GeometryData &data);

   Mesh *createExtrusion(std::vector<glm::vec4> &base, float height);
   // rearranges the verticies so that normals all face the correct direction
   // and so verticies are drawn counterclockwise for best rendering
   void rearrangeExtrusionVerticies(std::vector<glm::vec4> &base);
   Mesh *createSurfrev(std::vector<glm::vec4> &base, int slices);

   // creates a new mesh and sets the vertex info for it
   Mesh *generateMesh(GeometryData &data);

   std::vector<Geometry*> createdGeometry;
   
};

