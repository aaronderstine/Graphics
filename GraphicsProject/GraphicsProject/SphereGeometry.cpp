#include "SphereGeometry.h"
#include "glm/gtc/type_ptr.hpp"

SphereGeometry::SphereGeometry()
{
   height = 1.0;
}


SphereGeometry::~SphereGeometry()
{
}

void SphereGeometry::draw(glm::mat4 model)
{
   basicDraw(model);
}
