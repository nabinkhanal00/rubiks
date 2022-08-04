#include "Cubelet.hpp"

#include <cmath>
#include <iostream>
Cubelet::Cubelet(int x, int y, int z) : x(x), y(y), z(z) {
	int sum = std::abs(x) + std::abs(y) + std::abs(z);
	if (sum == 3) {
		type = Type::CORNER;
	} else if (sum == 2) {
		type = Type::EDGE;
	} else {
		type = Type::MIDDLE;
	}
	xColor = glm::vec3(1.0f, 1.0f, 1.0f);
	yColor = glm::vec3(1.0f, 1.0f, 1.0f);
	zColor = glm::vec3(1.0f, 1.0f, 1.0f);
}
