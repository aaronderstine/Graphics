/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   Geometry.h                              */
/* Description: This file defines the abstract     */
/*         base class of the different types of    */
/*         geometry.  Derived classes need to      */
/*         override the draw method.               */
/***************************************************/

#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "Color.h"

class Geometry
{
public:
   Geometry();
   ~Geometry();

   // draw method
   virtual void draw(glm::mat4 model) = 0;

   // sets the color
   void setColor(Color::Color color);
   Color::Color getColor();

   // whether to draw brightly or normal
   // typically used for showing that it is selected for transformations
   // also used to draw the light source
   void setSelected(bool selected);

   // height of the standard geometry
   // needs to be set by derived classes
   float getHeight();
   void  setHeight(float height);

   // offsets in the buffers
   void setColorOffset(int offset);
   void setIndexOffset(int offset);
   void setVertexAndNormalOffset(int offset);

   // number of indicies
   void setNumberOfIndicies(int indicies);
   void setNumberOfVerticies(int verticies);

   // for subdivisions
   int getTimesSubdivided();
   void setTimesSubdivided(int times);
   bool isAbleToSubdivide();

   // static methods to set the various openGL handles needed to draw
   static void setVBO(GLuint vbo);
   static GLuint getVBO();
   static void setVLocation(GLuint vlocation);
   static void setCBO(GLuint cbo);
   static GLuint getCBO();
   static void setCLocation(GLuint clocation);
   static void setIBO(GLuint ibo);
   static GLuint getIBO();
   static void setNBO(GLuint nbo);
   static GLuint getNBO();
   static void setNLocation(GLuint nlocation);
   static void setUModelLocation(GLuint uModelLocation);
   static void setUSelectedLocation(GLuint uSelected);

protected:
   static GLuint vbo;
   static GLuint vlocation;
   static GLuint cbo;
   static GLuint clocation;
   static GLuint ibo;
   static GLuint nbo;
   static GLuint nlocation;
   static GLuint uModelLocation;
   static GLuint uSelected;

   float height;
   Color::Color color;
   bool selected;

   // buffer offsets
   int cOffset;
   int iOffset;
   int vnOffset;

   // number of indicies and verticies
   int indicies;
   int verticies;

   // for handling subdivision
   int  timesSubdivided;
   bool canSubdivide;

   // basic drawing of a geometry - handles all offsets and colors and if it is selected
   void basicDraw(glm::mat4 model);

private:

};

