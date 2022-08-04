#include "Cube.hpp"
#include "Cubelet.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

Cube::Cube() : running(false), animate(false) {
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

void Cube::resume() {
	if (c.x == -1) {
		rAnimate();
	} else if (c.x == 1) {
		RAnimate();
	} else if (c.y == -1) {
		// uAnimate();
	} else if (c.y == 1) {
		// UAnimate();
	} else if (c.z == -1) {
		fAnimate();
	} else if (c.z == 1) {
		FAnimate();
	}
}

void Cube::fAnimate() {
	c.z = -1;
	static int sum = 0;
	if (sum == 0)
		std::cout << "f pressed" << std::endl;
	int degree = 2;
	running = true;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].z == 1) {
					glm::mat4 &oldModel = cubes[i + 1][j + 1][k + 1].model;
					cubes[i + 1][j + 1][k + 1].model =
					    glm::rotate(oldModel, glm::radians(float(-degree)),
					                glm::vec3(0.0f, 0.0f, 1.0f));
				}
			}
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					if (cubes[i + 1][j + 1][k + 1].z == 1) {
						Cubelet &clet = cubes[i + 1][j + 1][k + 1];
						int newX = clet.x * round(cos(-M_PI_2)) -
						           clet.y * round(sin(-M_PI_2));
						int newY = clet.x * round(sin(-M_PI_2)) +
						           clet.y * round(cos(-M_PI_2));
						clet.x = newX;
						clet.y = newY;
					}
				}
			}
		}
		running = false;
		sum = 0;
		c.z = 0;
	}
}

void Cube::uAnimate() {}
void Cube::UAnimate() {}
void Cube::FAnimate() {
	c.z = 1;
	static int sum = 0;
	if (sum == 0)
		std::cout << "F pressed" << std::endl;
	int degree = 2;
	running = true;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].z == 1) {
					glm::mat4 &oldModel = cubes[i + 1][j + 1][k + 1].model;
					cubes[i + 1][j + 1][k + 1].model =
					    glm::rotate(oldModel, glm::radians(float(degree)),
					                glm::vec3(0.0f, 0.0f, 1.0f));
				}
			}
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					if (cubes[i + 1][j + 1][k + 1].z == 1) {
						Cubelet &clet = cubes[i + 1][j + 1][k + 1];
						int newX = clet.x * round(cos(M_PI_2)) -
						           clet.y * round(sin(M_PI_2));
						int newY = clet.x * round(sin(M_PI_2)) +
						           clet.y * round(cos(M_PI_2));
						clet.x = newX;
						clet.y = newY;
					}
				}
			}
		}
		running = false;
		sum = 0;
		c.z = 0;
	}
}

void Cube::RAnimate() {
	c.x = 1;
	static int sum = 0;
	if (sum == 0)
		std::cout << "R pressed" << std::endl;
	int degree = 2;
	running = true;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].x == 1) {
					glm::mat4 &oldModel = cubes[i + 1][j + 1][k + 1].model;
					cubes[i + 1][j + 1][k + 1].model =
					    glm::rotate(oldModel, glm::radians(float(degree)),
					                glm::vec3(1.0f, 0.0f, 0.0f));
				}
			}
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					if (cubes[i + 1][j + 1][k + 1].x == 1) {
						Cubelet &clet = cubes[i + 1][j + 1][k + 1];
						int newY = clet.y * round(cos(M_PI_2)) -
						           clet.z * round(sin(M_PI_2));
						int newZ = clet.y * round(sin(M_PI_2)) +
						           clet.z * round(cos(M_PI_2));
						clet.y = newY;
						clet.z = newZ;
					}
				}
			}
		}
		running = false;
		sum = 0;
		c.x = 0;
	}
}
void Cube::rAnimate() {
	c.x = -1;
	static int sum = 0;
	if (sum == 0)
		std::cout << "r pressed" << std::endl;
	int degree = 2;
	running = true;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].x == 1) {
					glm::mat4 &oldModel = cubes[i + 1][j + 1][k + 1].model;
					cubes[i + 1][j + 1][k + 1].model =
					    glm::rotate(oldModel, glm::radians(float(-degree)),
					                glm::vec3(1.0f, 0.0f, 0.0f));
				}
			}
		}
	}

	sum += degree;
	if (sum >= 90) {

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					if (cubes[i + 1][j + 1][k + 1].x == 1) {
						Cubelet &clet = cubes[i + 1][j + 1][k + 1];
						int newY = clet.y * round(cos(-M_PI_2)) -
						           clet.z * round(sin(-M_PI_2));
						int newZ = clet.y * round(sin(-M_PI_2)) +
						           clet.z * round(cos(-M_PI_2));
						clet.y = newY;
						clet.z = newZ;
					}
				}
			}
		}
		running = false;
		sum = 0;
		c.x = 0;
	}
}

void Cube::F() {
	std::cout << "F pressed" << std::endl;
	int degree = 90;
	std::vector<std::vector<glm::mat4>> tempModel(
	    3, std::vector<glm::mat4>(3, glm::mat4(1.0f)));

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].z == 1) {

					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.tempModel =
					    glm::rotate(c.model, glm::radians(float(degree)),
					                glm::vec3(0.0f, 0.0f, 1.0f));
				}
			}
		}
	}

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].z == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.model = c.tempModel;
					int newX =
					    c.x * round(cos(M_PI_2)) - c.y * round(sin(M_PI_2));
					int newY =
					    c.x * round(sin(M_PI_2)) + c.y * round(cos(M_PI_2));

					c.x = newX;
					c.y = newY;
				}
			}
		}
	}
}

void Cube::f() {
	std::cout << "f pressed" << std::endl;
	int degree = 90;
	std::vector<std::vector<glm::mat4>> tempModel(
	    3, std::vector<glm::mat4>(3, glm::mat4(1.0f)));

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].z == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.tempModel =
					    glm::rotate(c.model, glm::radians(float(-degree)),
					                glm::vec3(0.0f, 0.0f, 1.0f));
				}
			}
		}
	}

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].z == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.model = c.tempModel;
					int newX =
					    c.x * round(cos(-M_PI_2)) - c.y * round(sin(-M_PI_2));
					int newY =
					    c.x * round(sin(-M_PI_2)) + c.y * round(cos(-M_PI_2));
					c.x = newX;
					c.y = newY;
				}
			}
		}
	}
}

void Cube::r() {
	std::cout << "r pressed" << std::endl;
	int degree = 90;
	std::vector<std::vector<glm::mat4>> tempModel(
	    3, std::vector<glm::mat4>(3, glm::mat4(1.0f)));

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].x == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.tempModel =
					    glm::rotate(c.model, glm::radians(float(-degree)),
					                glm::vec3(1.0f, 0.0f, 0.0f));
				}
			}
		}
	}

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].x == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.model = c.tempModel;

					int newY =
					    c.y * round(cos(-M_PI_2)) - c.z * round(sin(-M_PI_2));
					int newZ =
					    c.y * round(sin(-M_PI_2)) + c.z * round(cos(-M_PI_2));
					c.y = newY;
					c.z = newZ;
				}
			}
		}
	}
}

void Cube::R() {
	std::cout << "R pressed" << std::endl;
	int degree = 90;
	std::vector<std::vector<glm::mat4>> tempModel(
	    3, std::vector<glm::mat4>(3, glm::mat4(1.0f)));

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].x == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.tempModel =
					    glm::rotate(c.model, glm::radians(float(degree)),
					                glm::vec3(1.0f, 0.0f, 0.0f));
				}
			}
		}
	}

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].x == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.model = c.tempModel;

					int newY =
					    c.y * round(cos(M_PI_2)) - c.z * round(sin(M_PI_2));
					int newZ =
					    c.y * round(sin(M_PI_2)) + c.z * round(cos(M_PI_2));
					c.y = newY;
					c.z = newZ;
				}
			}
		}
	}
}
void Cube::U() {
	std::cout << "U pressed" << std::endl;
	int degree = 90;
	std::vector<std::vector<glm::mat4>> tempModel(
	    3, std::vector<glm::mat4>(3, glm::mat4(1.0f)));

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].y == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.tempModel =
					    glm::rotate(c.model, glm::radians(float(degree)),
					                glm::vec3(0.0f, 1.0f, 0.0f));
				}
			}
		}
	}

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].y == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.model = c.tempModel;

					int newZ =
					    c.z * round(cos(M_PI_2)) - c.x * round(sin(M_PI_2));
					int newX =
					    c.z * round(sin(M_PI_2)) + c.x * round(cos(M_PI_2));
					c.z = newZ;
					c.x = newX;
				}
			}
		}
	}
}
void Cube::u() {
	std::cout << "u pressed" << std::endl;
	int degree = 90;
	std::vector<std::vector<glm::mat4>> tempModel(
	    3, std::vector<glm::mat4>(3, glm::mat4(1.0f)));

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].y == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.tempModel =
					    glm::rotate(c.model, glm::radians(float(-degree)),
					                glm::vec3(0.0f, 1.0f, 0.0f));
				}
			}
		}
	}

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (cubes[i + 1][j + 1][k + 1].y == 1) {
					Cubelet &c = cubes[i + 1][j + 1][k + 1];
					c.model = c.tempModel;

					int newZ =
					    c.z * round(cos(-M_PI_2)) - c.x * round(sin(-M_PI_2));
					int newX =
					    c.z * round(sin(-M_PI_2)) + c.x * round(cos(-M_PI_2));
					c.z = newZ;
					c.x = newX;
				}
			}
		}
	}
}
