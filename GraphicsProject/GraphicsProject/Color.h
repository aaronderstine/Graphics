/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   March 15, 2014                          */
/* Name:   Color.h                                 */
/* Description: This file defines various colors   */
/*         that can be used for rendering.         */
/***************************************************/

#pragma once
#include "glm/glm.hpp"

namespace Color
{
   static glm::vec3 Test = glm::vec3(1, 1, 1);

   static glm::vec3 Blue = glm::vec3(0, 0, 1);
   static glm::vec3 Brown = glm::vec3(0.545, 0.271, 0.075);
   static glm::vec3 Crimson = glm::vec3(0.863, 0.078, 0.235);
   static glm::vec3 Cyan = glm::vec3(0, 1, 1);
   static glm::vec3 Gray = glm::vec3(0.5, 0.5, 0.5);
   static glm::vec3 Green = glm::vec3(0, 0.5, 0);
   static glm::vec3 Lime = glm::vec3(0, 1, 0);
   static glm::vec3 Magenta = glm::vec3(1, 0, 1);
   static glm::vec3 Orange = glm::vec3(1, 0.647, 0);
   static glm::vec3 Red = glm::vec3(1, 0, 0);
   static glm::vec3 White = glm::vec3(1, 1, 1);
   static glm::vec3 Yellow = glm::vec3(1, 1, 0);

   enum Color
   {
      TEST = 0,
      BLUE,
      BROWN,
      CRIMSON,
      CYAN,
      GRAY,
      GREEN,
      LIME,
      MAGENTA,
      ORANGE,
      RED,
      WHITE,
      YELLOW
   };

   const int NUM_OF_COLORS = 13;
}