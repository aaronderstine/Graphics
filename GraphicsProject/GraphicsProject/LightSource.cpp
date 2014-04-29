/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   March 15, 2014                          */
/* Name:   LightSource.cpp                         */
/* Description: This file defines a light source   */
/*         that can be moved about the room.       */
/***************************************************/

#include "LightSource.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLuint LightSource::uLightLocation;

LightSource::LightSource(Geometry *geometry) : geometry(geometry)
{
   // place it initially above the center of room
   x = 0.0;
   y = 3.0;
   z = 0.0;

   updateUniform();
}


LightSource::~LightSource()
{

}

void LightSource::setULightLocation(GLuint uLightLocation)
{
   LightSource::uLightLocation = uLightLocation;
}

void LightSource::changeZ(float delta)
{
   z += delta;
   updateUniform();
}

void LightSource::changeX(float delta)
{
   x += delta;
   updateUniform();
}

void LightSource::changeY(float delta)
{
   y += delta;
   updateUniform();
}

void LightSource::updateUniform()
{
   glm::vec4 light = glm::vec4(x, y, z, 1.0);
   glUniform4fv(uLightLocation, 1, glm::value_ptr(light));
}

void LightSource::render()
{
   if (geometry)
   {
      // draw brightly
      geometry->setSelected(true);
      glm::mat4 model = glm::mat4(1.0);

      // move the little cube into position
      model = glm::translate(model, glm::vec3(x, y, z));
      model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));

      geometry->setColor(Color::YELLOW);
      geometry->draw(model);
   }   
}
