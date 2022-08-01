#include "Cube.hpp"
#include "Cubelet.hpp"
#include "glm/gtc/matrix_transform.hpp"

Cube::Cube() {
	for (int i = -1; i <= 1; i++) {
		std::vector<std::vector<Cubelet>> cc;
		for (int j = -1; j <= 1; j++) {
			std::vector<Cubelet> c;
			for (int k = -1; k <= 1; k++) {
				Cubelet clet(i, j, k);
				c.push_back(clet);
			}
			cc.push_back(c);
		}
		cubes.push_back(cc);
	}
}
void Cube::draw() {
	for (auto &cc : cubes) {
		for (auto &c : cc) {
			for (auto &cube : c) {
				cube.draw();
			}
		}
	}
}
void Cube::f() {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			glm::mat4 &oldModel = cubes[i + 1][j + 1][1 + 1].model;
			cubes[i + 1][j + 1][1 + 1].model = glm::rotate(
			    oldModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
}
