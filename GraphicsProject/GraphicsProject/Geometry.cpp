/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 18, 2014                       */
/* Name:   Geometry.cpp                            */
/* Description: This file defines the abstract     */
/*         base class of the different types of    */
/*         geometry.  Derived classes need to      */
/*         override the draw method.               */
/***************************************************/

#include "Geometry.h"
#include "glm/gtc/type_ptr.hpp"

GLuint Geometry::vbo;
GLuint Geometry::cbo;
GLuint Geometry::vlocation;
GLuint Geometry::clocation;
GLuint Geometry::ibo;
GLuint Geometry::nbo;
GLuint Geometry::nlocation;
GLuint Geometry::uModelLocation;
GLuint Geometry::uSelected;

Geometry::Geometry()
{
   // needs to be set by derived classes
   height = 0;
   setColor(Color::WHITE);
   timesSubdivided = 0;
   canSubdivide = false;
   selected = false;
}


Geometry::~Geometry()
{

}

float Geometry::getHeight()
{
   return height;
}

void Geometry::setHeight(float height)
{
   this->height = height;
}

void Geometry::setColor(Color::Color color)
{
   this->color = color;
}

Color::Color Geometry::getColor()
{
   return color;
}

void Geometry::setVBO(GLuint vbo)
{
   Geometry::vbo = vbo;
}

GLuint Geometry::getVBO()
{
   return Geometry::vbo;
}

void Geometry::setVLocation(GLuint vlocation)
{
   Geometry::vlocation = vlocation;
}

void Geometry::setCBO(GLuint cbo)
{
   Geometry::cbo = cbo;
}

GLuint Geometry::getCBO()
{
   return Geometry::cbo;
}

void Geometry::setCLocation(GLuint clocation)
{
   Geometry::clocation = clocation;
}

void Geometry::setIBO(GLuint ibo)
{
   Geometry::ibo = ibo;
}

GLuint Geometry::getIBO()
{
   return Geometry::ibo;
}

void Geometry::setNBO(GLuint nbo)
{
   Geometry::nbo = nbo;
}

GLuint Geometry::getNBO()
{
   return Geometry::nbo;
}

void Geometry::setNLocation(GLuint nlocation)
{
   Geometry::nlocation = nlocation;
}

void Geometry::setUModelLocation(GLuint uModelLocation)
{
   Geometry::uModelLocation = uModelLocation;
}

void Geometry::setUSelectedLocation(GLuint uSelected)
{
   Geometry::uSelected = uSelected;
}

void Geometry::setSelected(bool selected)
{
   this->selected = selected;
}

void Geometry::setColorOffset(int offset)
{
   cOffset = offset;
}
void Geometry::setIndexOffset(int offset)
{
   iOffset = offset;
}

void Geometry::setVertexAndNormalOffset(int offset)
{
   vnOffset = offset;
}

void Geometry::setNumberOfIndicies(int indicies)
{
   this->indicies = indicies;
}

void Geometry::setNumberOfVerticies(int verticies)
{
   this->verticies = verticies;
}

int Geometry::getTimesSubdivided()
{
   return timesSubdivided;
}

void Geometry::setTimesSubdivided(int times)
{
   timesSubdivided = times;
   if (timesSubdivided > 3) canSubdivide = false;
}

bool Geometry::isAbleToSubdivide()
{
   return canSubdivide;
}

void Geometry::basicDraw(glm::mat4 model)
{
   // check if it should be drawn brightly
   (selected) ? glUniform1f(uSelected, 1.0f) : glUniform1f(uSelected, 0.0f);

   // setup the color attribute pointer for the desired color  
   glBindBuffer(GL_ARRAY_BUFFER, Geometry::cbo);
	glVertexAttribPointer(Geometry::clocation, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(glm::vec3)*cOffset + sizeof(glm::vec3)*color*verticies));
   glBindBuffer(GL_ARRAY_BUFFER, Geometry::nbo);
   glVertexAttribPointer(Geometry::nlocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(glm::vec4)*vnOffset));
   glBindBuffer(GL_ARRAY_BUFFER, Geometry::vbo);
   glVertexAttribPointer(Geometry::vlocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(glm::vec4)*vnOffset));

   // draw itself
   glUniformMatrix4fv(Geometry::uModelLocation, 1, GL_FALSE, glm::value_ptr(model));
   glDrawElements(GL_TRIANGLES, indicies, GL_UNSIGNED_INT, (GLvoid*)(sizeof(unsigned int)*iOffset));

	glFlush();
}