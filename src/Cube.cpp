#include "Cube.hpp"
#include "Cubelet.hpp"

#include "glad/glad.h"

#include "ResourceManager.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

Cube::Cube() : running(false), animate(false) {

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
	ResourceManager::LoadShader("cubelet/vertex.glsl", "cubelet/fragment.glsl",
	                            "cube");
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
						c.zColor = glm::vec3(1.0f, 0.64f, 1.0f);
					}
					m_cubelets.push_back(c);
				}
			}
		}
	}

	view = glm::lookAt(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
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
		glm::mat4 model(1.0f);
		model = glm::rotate(model, glm::radians(-30.0f),
		                    glm::vec3(1.0f, 1.0f, 0.0f));
		model = glm::translate(
		    model, 0.5f * glm::vec3(cubelet.x, cubelet.y, cubelet.z));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

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

void Cube::resume() {}
