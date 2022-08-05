#include "Cube.hpp"
#include "Cubelet.hpp"

#include "glad/glad.h"

#include "ResourceManager.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

Cube::Cube() : running(false), animate(true), ss(false) {

	std::vector<float> vertices{

	    //  ╭──────────────────────────────────────────────────────────╮
	    //  │ 		right                                             │
	    //  ╰──────────────────────────────────────────────────────────╯

	    0.5f, -0.5f, 0.5f,  //
	    0.5f, -0.5f, -0.5f, //
	    0.5f, 0.5f, -0.5f,  //
	    0.5f, 0.5f, -0.5f,  //
	    0.5f, 0.5f, 0.5f,   //
	    0.5f, -0.5f, 0.5f,  //

	    //  ╭──────────────────────────────────────────────────────────╮
	    //  │ 		left                                              │
	    //  ╰──────────────────────────────────────────────────────────╯

	    -0.5f, -0.5f, 0.5f,  //
	    -0.5f, -0.5f, -0.5f, //
	    -0.5f, 0.5f, -0.5f,  //
	    -0.5f, 0.5f, -0.5f,  //
	    -0.5f, 0.5f, 0.5f,   //
	    -0.5f, -0.5f, 0.5f,  //

	    //  ╭──────────────────────────────────────────────────────────╮
	    //  │ 		top                                               │
	    //  ╰──────────────────────────────────────────────────────────╯

	    0.5f, 0.5f, 0.5f,   //
	    0.5f, 0.5f, -0.5f,  //
	    -0.5f, 0.5f, -0.5f, //
	    -0.5f, 0.5f, -0.5f, //
	    -0.5f, 0.5f, 0.5f,  //
	    0.5f, 0.5f, 0.5f,   //

	    //  ╭──────────────────────────────────────────────────────────╮
	    //  │ 		bottom                                            │
	    //  ╰──────────────────────────────────────────────────────────╯

	    0.5f, -0.5f, 0.5f,   //
	    0.5f, -0.5f, -0.5f,  //
	    -0.5f, -0.5f, -0.5f, //
	    -0.5f, -0.5f, -0.5f, //
	    -0.5f, -0.5f, 0.5f,  //
	    0.5f, -0.5f, 0.5f,   //

	    //  ╭──────────────────────────────────────────────────────────╮
	    //  │ 		front                                             │
	    //  ╰──────────────────────────────────────────────────────────╯

	    -0.5f, -0.5f, 0.5f, //
	    0.5f, -0.5f, 0.5f,  //
	    0.5f, 0.5f, 0.5f,   //
	    0.5f, 0.5f, 0.5f,   //
	    -0.5f, 0.5f, 0.5f,  //
	    -0.5f, -0.5f, 0.5f, //

	    //  ╭──────────────────────────────────────────────────────────╮
	    //  │ 		back                                              │
	    //  ╰──────────────────────────────────────────────────────────╯

	    -0.5f, -0.5f, -0.5f, //
	    0.5f, -0.5f, -0.5f,  //
	    0.5f, 0.5f, -0.5f,   //
	    0.5f, 0.5f, -0.5f,   //
	    -0.5f, 0.5f, -0.5f,  //
	    -0.5f, -0.5f, -0.5f, //
	};

	glGenVertexArrays(1, &m_vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0],
	             GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
	                      (void *)0);
	ResourceManager::LoadShader("shaders/cubelet/vertex.glsl",
	                            "shaders/cubelet/fragment.glsl", "cube");
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (!(i == 0 && j == 0 && k == 0)) {
					Cubelet c(i, j, k);
					if (c.x == 1) {
						c.xColor = glm::vec3(0.0f, 0.0f, 1.0f);
					} else if (c.x == -1) {
						c.xColor = glm::vec3(0.0f, 1.0f, 0.0f);
					}
					if (c.y == 1) {
						c.yColor = glm::vec3(1.0f, 1.0f, 1.0f);
					} else if (c.y == -1) {
						c.yColor = glm::vec3(1.0f, 1.0f, 0.0f);
					}
					if (c.z == 1) {
						c.zColor = glm::vec3(1.0f, 0.0f, 0.0f);
					} else if (c.z == -1) {
						c.zColor = glm::vec3(1.0f, 0.64f, 0.0f);
					}
					m_cubelets.push_back(c);
				}
			}
		}
	}

	view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
	                   glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
}

void Cube::draw() {

	glBindVertexArray(m_vao);

	Shader &shader = ResourceManager::GetShader("cube");
	shader.Use();
	shader.SetMat4("view", glm::mat4(view));
	shader.SetMat4("projection", glm::mat4(projection));

	for (Cubelet &cubelet : m_cubelets) {
		int position = 0;
		glm::mat4 model = cubelet.model;
		model = glm::translate(
		    model, 0.7f * glm::vec3(cubelet.x, cubelet.y, cubelet.z));
		model = glm::scale(model, 0.6f * glm::vec3(1.0f, 1.0f, 1.0f));

		shader.SetMat4("model", model);
		shader.SetVec3("color", cubelet.xColor);

		if (cubelet.x == 1) {
			glDrawArrays(GL_TRIANGLES, position, 6);
		}
		position += 6;
		if (cubelet.x == -1) {
			glDrawArrays(GL_TRIANGLES, position, 6);
		}
		position += 6;

		shader.SetVec3("color", cubelet.yColor);
		if (cubelet.y == 1) {
			glDrawArrays(GL_TRIANGLES, position, 6);
		}

		position += 6;
		if (cubelet.y == -1) {
			glDrawArrays(GL_TRIANGLES, position, 6);
		}

		position += 6;
		shader.SetVec3("color", cubelet.zColor);
		if (cubelet.z == 1) {
			glDrawArrays(GL_TRIANGLES, position, 6);
		}

		position += 6;
		if (cubelet.z == -1) {
			glDrawArrays(GL_TRIANGLES, position, 6);
		}
	}
}

void Cube::resume() {
	switch (m_move) {
	case Move::r:
		rAnimate();
		break;
	case Move::l:
		lAnimate();
		break;
	case Move::f:
		fAnimate();
		break;
	case Move::b:
		bAnimate();
		break;
	case Move::u:
		uAnimate();
		break;
	case Move::d:
		dAnimate();
		break;

	case Move::R:
		RAnimate();
		break;
	case Move::L:
		LAnimate();
		break;
	case Move::F:
		FAnimate();
		break;
	case Move::B:
		BAnimate();
		break;
	case Move::U:
		UAnimate();
		break;
	case Move::D:
		DAnimate();
		break;
	case Move::NONE:
		break;
	}
}

void Cube::animateMove(Move m) {
	switch (m) {
	case Move::r:
		rAnimate();
		break;
	case Move::l:
		lAnimate();
		break;
	case Move::f:
		fAnimate();
		break;
	case Move::b:
		bAnimate();
		break;
	case Move::u:
		uAnimate();
		break;
	case Move::d:
		dAnimate();
		break;

	case Move::R:
		RAnimate();
		break;
	case Move::L:
		LAnimate();
		break;
	case Move::F:
		FAnimate();
		break;
	case Move::B:
		BAnimate();
		break;
	case Move::U:
		UAnimate();
		break;
	case Move::D:
		DAnimate();
		break;
	case Move::NONE:
		break;
	}
}

void Cube::applyMove(Move m) {
	switch (m) {
	case Move::r:
		// std::cout << "r"
		//           << ":" << static_cast<int>(m) << " ";
		r();
		break;
	case Move::l:
		// std::cout << "l"
		//           << ":" << static_cast<int>(m) << " ";
		l();
		break;
	case Move::f:
		// std::cout << "f"
		//           << ":" << static_cast<int>(m) << " ";
		f();
		break;
	case Move::b:
		// std::cout << "b"
		//           << ":" << static_cast<int>(m) << " ";
		b();
		break;
	case Move::u:
		// std::cout << "u"
		//           << ":" << static_cast<int>(m) << " ";
		u();
		break;
	case Move::d:
		// std::cout << "d"
		//           << ":" << static_cast<int>(m) << " ";
		d();
		break;

	case Move::R:
		// std::cout << "R"
		//           << ":" << static_cast<int>(m) << " ";
		R();
		break;
	case Move::L:
		// std::cout << "L"
		//           << ":" << static_cast<int>(m) << " ";
		L();
		break;
	case Move::F:
		// std::cout << "F"
		//           << ":" << static_cast<int>(m) << " ";
		F();
		break;
	case Move::B:
		// std::cout << "B"
		//           << ":" << static_cast<int>(m) << " ";
		B();
		break;
	case Move::U:
		// std::cout << "U"
		//           << ":" << static_cast<int>(m) << " ";
		U();
		break;
	case Move::D:
		// std::cout << "D"
		//           << ":" << static_cast<int>(m) << " ";
		D();
		break;
	case Move::NONE:
		break;
	}
}

void Cube::f() {

	for (Cubelet &c : m_cubelets) {
		if (c.z == 1) {
			int newX = c.x * round(cos(-M_PI_2)) - c.y * round(sin(-M_PI_2));
			int newY = c.x * round(sin(-M_PI_2)) + c.y * round(cos(-M_PI_2));
			c.x = newX;
			c.y = newY;
			glm::vec3 tempColor = c.xColor;
			c.xColor = c.yColor;
			c.yColor = tempColor;
		}
	}
}

void Cube::r() {

	for (Cubelet &c : m_cubelets) {
		if (c.x == 1) {
			int newY = c.y * round(cos(-M_PI_2)) - c.z * round(sin(-M_PI_2));
			int newZ = c.y * round(sin(-M_PI_2)) + c.z * round(cos(-M_PI_2));
			c.y = newY;
			c.z = newZ;
			glm::vec3 tempColor = c.yColor;
			c.yColor = c.zColor;
			c.zColor = tempColor;
		}
	}
}

void Cube::u() {

	for (Cubelet &c : m_cubelets) {
		if (c.y == 1) {
			int newZ = c.z * round(cos(-M_PI_2)) - c.x * round(sin(-M_PI_2));
			int newX = c.z * round(sin(-M_PI_2)) + c.x * round(cos(-M_PI_2));
			c.z = newZ;
			c.x = newX;
			glm::vec3 tempColor = c.xColor;
			c.xColor = c.zColor;
			c.zColor = tempColor;
		}
	}
}

void Cube::l() {

	for (Cubelet &c : m_cubelets) {
		if (c.x == -1) {
			int newY = c.y * round(cos(-M_PI_2)) - c.z * round(sin(-M_PI_2));
			int newZ = c.y * round(sin(-M_PI_2)) + c.z * round(cos(-M_PI_2));
			c.y = newY;
			c.z = newZ;
			glm::vec3 tempColor = c.yColor;
			c.yColor = c.zColor;
			c.zColor = tempColor;
		}
	}
}
void Cube::b() {

	for (Cubelet &c : m_cubelets) {
		if (c.z == -1) {
			int newX = c.x * round(cos(-M_PI_2)) - c.y * round(sin(-M_PI_2));
			int newY = c.x * round(sin(-M_PI_2)) + c.y * round(cos(-M_PI_2));
			c.x = newX;
			c.y = newY;
			glm::vec3 tempColor = c.xColor;
			c.xColor = c.yColor;
			c.yColor = tempColor;
		}
	}
}
void Cube::d() {

	for (Cubelet &c : m_cubelets) {
		if (c.y == -1) {
			int newZ = c.z * round(cos(-M_PI_2)) - c.x * round(sin(-M_PI_2));
			int newX = c.z * round(sin(-M_PI_2)) + c.x * round(cos(-M_PI_2));
			c.z = newZ;
			c.x = newX;
			glm::vec3 tempColor = c.xColor;
			c.xColor = c.zColor;
			c.zColor = tempColor;
		}
	}
}

void Cube::F() {

	for (Cubelet &c : m_cubelets) {
		if (c.z == 1) {
			int newX = c.x * round(cos(M_PI_2)) - c.y * round(sin(M_PI_2));
			int newY = c.x * round(sin(M_PI_2)) + c.y * round(cos(M_PI_2));
			c.x = newX;
			c.y = newY;
			glm::vec3 tempColor = c.xColor;
			c.xColor = c.yColor;
			c.yColor = tempColor;
		}
	}
}

void Cube::R() {

	for (Cubelet &c : m_cubelets) {
		if (c.x == 1) {
			int newY = c.y * round(cos(M_PI_2)) - c.z * round(sin(M_PI_2));
			int newZ = c.y * round(sin(M_PI_2)) + c.z * round(cos(M_PI_2));
			c.y = newY;
			c.z = newZ;
			glm::vec3 tempColor = c.yColor;
			c.yColor = c.zColor;
			c.zColor = tempColor;
		}
	}
}

void Cube::U() {

	for (Cubelet &c : m_cubelets) {
		if (c.y == 1) {
			int newZ = c.z * round(cos(M_PI_2)) - c.x * round(sin(M_PI_2));
			int newX = c.z * round(sin(M_PI_2)) + c.x * round(cos(M_PI_2));
			c.z = newZ;
			c.x = newX;
			glm::vec3 tempColor = c.xColor;
			c.xColor = c.zColor;
			c.zColor = tempColor;
		}
	}
}

void Cube::L() {

	for (Cubelet &c : m_cubelets) {
		if (c.x == -1) {
			int newY = c.y * round(cos(M_PI_2)) - c.z * round(sin(M_PI_2));
			int newZ = c.y * round(sin(M_PI_2)) + c.z * round(cos(M_PI_2));
			c.y = newY;
			c.z = newZ;
			glm::vec3 tempColor = c.yColor;
			c.yColor = c.zColor;
			c.zColor = tempColor;
		}
	}
}
void Cube::B() {

	for (Cubelet &c : m_cubelets) {
		if (c.z == -1) {
			int newX = c.x * round(cos(M_PI_2)) - c.y * round(sin(M_PI_2));
			int newY = c.x * round(sin(M_PI_2)) + c.y * round(cos(M_PI_2));
			c.x = newX;
			c.y = newY;
			glm::vec3 tempColor = c.xColor;
			c.xColor = c.yColor;
			c.yColor = tempColor;
		}
	}
}

void Cube::D() {

	for (Cubelet &c : m_cubelets) {
		if (c.y == -1) {
			int newZ = c.z * round(cos(M_PI_2)) - c.x * round(sin(M_PI_2));
			int newX = c.z * round(sin(M_PI_2)) + c.x * round(cos(M_PI_2));
			c.z = newZ;
			c.x = newX;
			glm::vec3 tempColor = c.xColor;
			c.xColor = c.zColor;
			c.zColor = tempColor;
		}
	}
}

void Cube::fAnimate() {
	static int sum = 0;
	m_move = Move::f;
	// if (sum == 0)
	// 	std::cout << "f pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.z == 1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(-degree)),
			                      glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.z == 1) {
				int newX =
				    c.x * round(cos(-M_PI_2)) - c.y * round(sin(-M_PI_2));
				int newY =
				    c.x * round(sin(-M_PI_2)) + c.y * round(cos(-M_PI_2));
				c.x = newX;
				c.y = newY;
				glm::vec3 tempColor = c.xColor;
				c.xColor = c.yColor;
				c.yColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::rAnimate() {

	static int sum = 0;
	m_move = Move::r;
	// if (sum == 0)
	// 	std::cout << "r pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.x == 1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(-degree)),
			                      glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.x == 1) {
				int newY =
				    c.y * round(cos(-M_PI_2)) - c.z * round(sin(-M_PI_2));
				int newZ =
				    c.y * round(sin(-M_PI_2)) + c.z * round(cos(-M_PI_2));
				c.y = newY;
				c.z = newZ;
				glm::vec3 tempColor = c.yColor;
				c.yColor = c.zColor;
				c.zColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::uAnimate() {

	static int sum = 0;
	m_move = Move::u;
	// if (sum == 0)
	// 	std::cout << "u pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.y == 1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(-degree)),
			                      glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.y == 1) {
				int newZ =
				    c.z * round(cos(-M_PI_2)) - c.x * round(sin(-M_PI_2));
				int newX =
				    c.z * round(sin(-M_PI_2)) + c.x * round(cos(-M_PI_2));
				c.z = newZ;
				c.x = newX;
				glm::vec3 tempColor = c.xColor;
				c.xColor = c.zColor;
				c.zColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::bAnimate() {
	static int sum = 0;
	m_move = Move::b;
	// if (sum == 0)
	// 	std::cout << "b pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.z == -1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(-degree)),
			                      glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.z == -1) {
				int newX =
				    c.x * round(cos(-M_PI_2)) - c.y * round(sin(-M_PI_2));
				int newY =
				    c.x * round(sin(-M_PI_2)) + c.y * round(cos(-M_PI_2));
				c.x = newX;
				c.y = newY;
				glm::vec3 tempColor = c.xColor;
				c.xColor = c.yColor;
				c.yColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::lAnimate() {

	static int sum = 0;
	m_move = Move::l;
	// if (sum == 0)
	// 	std::cout << "l pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.x == -1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(-degree)),
			                      glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.x == -1) {
				int newY =
				    c.y * round(cos(-M_PI_2)) - c.z * round(sin(-M_PI_2));
				int newZ =
				    c.y * round(sin(-M_PI_2)) + c.z * round(cos(-M_PI_2));
				c.y = newY;
				c.z = newZ;
				glm::vec3 tempColor = c.yColor;
				c.yColor = c.zColor;
				c.zColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::dAnimate() {

	static int sum = 0;
	m_move = Move::d;
	// if (sum == 0)
	// 	std::cout << "d pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.y == -1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(-degree)),
			                      glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.y == -1) {
				int newZ =
				    c.z * round(cos(-M_PI_2)) - c.x * round(sin(-M_PI_2));
				int newX =
				    c.z * round(sin(-M_PI_2)) + c.x * round(cos(-M_PI_2));
				c.z = newZ;
				c.x = newX;
				glm::vec3 tempColor = c.xColor;
				c.xColor = c.zColor;
				c.zColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}

void Cube::FAnimate() {
	static int sum = 0;
	m_move = Move::F;
	// if (sum == 0)
	// 	std::cout << "F pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.z == 1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(degree)),
			                      glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.z == 1) {
				int newX = c.x * round(cos(M_PI_2)) - c.y * round(sin(M_PI_2));
				int newY = c.x * round(sin(M_PI_2)) + c.y * round(cos(M_PI_2));
				c.x = newX;
				c.y = newY;
				glm::vec3 tempColor = c.xColor;
				c.xColor = c.yColor;
				c.yColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::RAnimate() {

	static int sum = 0;
	m_move = Move::R;
	// if (sum == 0)
	// 	std::cout << "R pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.x == 1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(degree)),
			                      glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.x == 1) {
				int newY = c.y * round(cos(M_PI_2)) - c.z * round(sin(M_PI_2));
				int newZ = c.y * round(sin(M_PI_2)) + c.z * round(cos(M_PI_2));
				c.y = newY;
				c.z = newZ;
				glm::vec3 tempColor = c.yColor;
				c.yColor = c.zColor;
				c.zColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::UAnimate() {

	static int sum = 0;
	m_move = Move::U;
	// if (sum == 0)
	// 	std::cout << "U pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.y == 1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(degree)),
			                      glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.y == 1) {
				int newZ = c.z * round(cos(M_PI_2)) - c.x * round(sin(M_PI_2));
				int newX = c.z * round(sin(M_PI_2)) + c.x * round(cos(M_PI_2));
				c.z = newZ;
				c.x = newX;
				glm::vec3 tempColor = c.xColor;
				c.xColor = c.zColor;
				c.zColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::BAnimate() {
	static int sum = 0;
	m_move = Move::B;
	// if (sum == 0)
	// 	std::cout << "B pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.z == -1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(degree)),
			                      glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.z == -1) {
				int newX = c.x * round(cos(M_PI_2)) - c.y * round(sin(M_PI_2));
				int newY = c.x * round(sin(M_PI_2)) + c.y * round(cos(M_PI_2));
				c.x = newX;
				c.y = newY;
				glm::vec3 tempColor = c.xColor;
				c.xColor = c.yColor;
				c.yColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::LAnimate() {

	static int sum = 0;
	m_move = Move::L;
	// if (sum == 0)
	// 	std::cout << "L pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.x == -1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(degree)),
			                      glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.x == -1) {
				int newY = c.y * round(cos(M_PI_2)) - c.z * round(sin(M_PI_2));
				int newZ = c.y * round(sin(M_PI_2)) + c.z * round(cos(M_PI_2));
				c.y = newY;
				c.z = newZ;
				glm::vec3 tempColor = c.yColor;
				c.yColor = c.zColor;
				c.zColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}
void Cube::DAnimate() {

	static int sum = 0;
	m_move = Move::D;
	// if (sum == 0)
	// 	std::cout << "D pressed" << std::endl;
	int degree = 2;
	running = true;
	for (Cubelet &c : m_cubelets) {
		if (c.y == -1) {
			glm::mat4 &oldModel = c.model;
			c.model = glm::rotate(oldModel, glm::radians(float(degree)),
			                      glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}
	sum += degree;
	if (sum >= 90) {

		for (Cubelet &c : m_cubelets) {
			if (c.y == -1) {
				int newZ = c.z * round(cos(M_PI_2)) - c.x * round(sin(M_PI_2));
				int newX = c.z * round(sin(M_PI_2)) + c.x * round(cos(M_PI_2));
				c.z = newZ;
				c.x = newX;
				glm::vec3 tempColor = c.xColor;
				c.xColor = c.zColor;
				c.zColor = tempColor;
				c.model = glm::mat4(1.0f);
			}
		}
		running = false;
		sum = 0;
		m_move = Move::NONE;
	}
}

void Cube::shuffle() {
	for (int i = 0; i < 10; i++) {
		int pos = random() % 12;
		applyMove(static_cast<Move>(pos));
	}
}
void Cube::shuffle(std::vector<Move> &moves) {
	int prev = -1;
	srand(time(0));
	while (moves.size() < 20) {
		int pos = rand() % 12;

		if (pos == prev ||
		    (pos >= 6 ? ((pos + 7) % 13 == prev) : ((pos + 6) % 12 == prev)))
			continue;
		Move m = static_cast<Move>(pos);
		applyMove(m);
		if (pos >= 6) {
			moves.push_back(static_cast<Move>((pos + 7) % 13));
		} else {
			moves.push_back(static_cast<Move>((pos + 6) % 12));
		}
		prev = pos;
	}
}

void Cube::shuffleAndSolve() {
	ss = true;
	static int count = -100;
	static std::vector<Move> moves;
	if (count == -100) {
		shuffle(moves);
	} else if (count < 0) {
	} else if (count < (int)moves.size()) {
		animateMove(moves[moves.size() - 1 - count]);
	} else {
		ss = false;
		moves.clear();
		count = -101;
	}
	count++;
}
