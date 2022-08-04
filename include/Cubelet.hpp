#pragma once
#include "glm/ext/vector_float3.hpp"
#include <vector>

enum class Type { CORNER, EDGE, MIDDLE };

class Cubelet {
  public:
	Cubelet(int x, int y, int z);
	int x, y, z;
	Type type;
	glm::vec3 xColor, yColor, zColor;
};
