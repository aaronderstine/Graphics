/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   April 9, 2014                           */
/* Name:   HE.h                                    */
/* Description: This file defines the classes used */
/*         in the half-edge data structure         */
/*         representation of geometry.             */
/***************************************************/

#pragma once
#include "glm/glm.hpp"

namespace HE
{
   class Vertex;
   class Face;
   class HalfEdge;

   class HalfEdge
   {
   public:
      HalfEdge() : next(NULL), sym(NULL), vertex(NULL), face(NULL) { }

      HalfEdge *getNext()                 { return next; }
      void      setNext(HalfEdge *next)   { this->next = next; }
      HalfEdge *getSym()                  { return sym; }
      void      setSym(HalfEdge *sym)     { this->sym = sym; }
      Vertex   *getVertex()               { return vertex; }
      void      setVertex(Vertex *vertex) { this->vertex = vertex; }
      Face     *getFace()                 { return face; }
      void      setFace(Face *face)       { this->face = face; }
   private:
      HalfEdge *next;
      HalfEdge *sym;
      Vertex   *vertex;
      Face     *face;
   };

   class Face
   {
   public:
      Face() : he(NULL), normal(glm::vec4(0.0, 0.0, 0.0, 0.0))
      {
         // assign a unique id to the face
         id = ++count;
      }
      int getCount() { return count; }
      int getId()    { return id; }
      HalfEdge *getHalfEdge()               { return he; }
      void      setHalfEdge(HalfEdge *he)   { this->he = he; }
      void      setNormal(glm::vec4 normal) { this->normal = normal; }
      glm::vec4 getNormal()                 { return normal; }
   
   private:
      static int count;
      int id;
      HalfEdge *he;
      glm::vec4 normal;
   };

   class Vertex
   {
   public:
      Vertex(glm::vec4 vertex) : he(NULL), vertex(vertex), normal(glm::vec4(0.0, 0.0, 0.0, 0.0))
      {
         // assign a unique id to the vertex
         id = ++count;
      }
      ~Vertex() { --count; }
      int getCount() { return count; }
      int getId()    { return id; }
      HalfEdge *getHalfEdge()             { return he; }
      void      setHalfEdge(HalfEdge *he) { this->he = he; }
      
      glm::vec4 getVertex()                 { return vertex; }
      void      setVertex(glm::vec4 vertex) { this->vertex = vertex; }
      glm::vec4 getNormal()                 { return normal; }
      void      setNormal(glm::vec4 normal) { this->normal = normal; }
      
   private:
      static int count;
      int id;
      HalfEdge *he;
      glm::vec4 vertex;
      glm::vec4 normal;
   };
}