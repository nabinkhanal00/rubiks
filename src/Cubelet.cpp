#include "Cubelet.hpp"
#include "ResourceManager.hpp"
#include "Shader.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <cmath>
#include <iostream>

glm::mat4 Cubelet::view =
    glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
glm::mat4 Cubelet::projection =
    glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
Cubelet::Cubelet(int x, int y, int z)
    : model(glm::mat4(1.0f)), m_x(x), m_y(y), m_z(z) {
	int sum = std::abs(x) + std::abs(y) + std::abs(z);
	if (sum == 3) {
		m_type = Type::CORNER;
	} else if (sum == 2) {
		m_type = Type::EDGE;
	} else {
		m_type = Type::MIDDLE;
	}
	std::vector<float> right{
	    0.5f, -0.5f, 0.5f,  //
	    0.5f, -0.5f, -0.5f, //
	    0.5f, 0.5f,  -0.5f, //
	    0.5f, 0.5f,  -0.5f, //
	    0.5f, 0.5f,  0.5f,  //
	    0.5f, -0.5f, 0.5f,  //
	};

	std::vector<float> left{
	    -0.5f, -0.5f, 0.5f,  //
	    -0.5f, -0.5f, -0.5f, //
	    -0.5f, 0.5f,  -0.5f, //
	    -0.5f, 0.5f,  -0.5f, //
	    -0.5f, 0.5f,  0.5f,  //
	    -0.5f, -0.5f, 0.5f,  //
	};

	std::vector<float> up{
	    0.5f,  0.5f, 0.5f,  //
	    0.5f,  0.5f, -0.5f, //
	    -0.5f, 0.5f, -0.5f, //
	    -0.5f, 0.5f, -0.5f, //
	    -0.5f, 0.5f, 0.5f,  //
	    0.5f,  0.5f, 0.5f,  //
	};

	std::vector<float> down{
	    0.5f,  -0.5f, 0.5f,  //
	    0.5f,  -0.5f, -0.5f, //
	    -0.5f, -0.5f, -0.5f, //
	    -0.5f, -0.5f, -0.5f, //
	    -0.5f, -0.5f, 0.5f,  //
	    0.5f,  -0.5f, 0.5f,  //
	};

	std::vector<float> front = {
	    -0.5f, -0.5f, 0.5f, //
	    0.5f,  -0.5f, 0.5f, //
	    0.5f,  0.5f,  0.5f, //
	    0.5f,  0.5f,  0.5f, //
	    -0.5f, 0.5f,  0.5f, //
	    -0.5f, -0.5f, 0.5f, //
	};

	std::vector<float> back = {
	    -0.5f, -0.5f, -0.5f, //
	    0.5f,  -0.5f, -0.5f, //
	    0.5f,  0.5f,  -0.5f, //
	    0.5f,  0.5f,  -0.5f, //
	    -0.5f, 0.5f,  -0.5f, //
	    -0.5f, -0.5f, -0.5f, //
	};
	if (m_x == 1) {
		m_vertices.insert(m_vertices.end(), right.begin(), right.end());
		m_xcolor = glm::vec3(0.0f, 0.0f, 1.0f);
		// std::cout << "right" << std::endl;
	}
	if (m_x == -1) {
		m_vertices.insert(m_vertices.end(), left.begin(), left.end());
		m_xcolor = glm::vec3(0.0f, 1.0f, 0.0f);
		// std::cout << "left" << std::endl;
	}
	if (m_y == 1) {
		m_vertices.insert(m_vertices.end(), up.begin(), up.end());
		m_ycolor = glm::vec3(1.0f, 1.0f, 1.0f);
		// std::cout << "up" << std::endl;
	}
	if (m_y == -1) {
		m_vertices.insert(m_vertices.end(), down.begin(), down.end());
		m_ycolor = glm::vec3(1.0f, 1.0f, 0.0f);
		// std::cout << "down" << std::endl;
	}
	if (m_z == 1) {
		m_vertices.insert(m_vertices.end(), front.begin(), front.end());
		m_zcolor = glm::vec3(1.0f, 0.0f, 0.0f);
		// std::cout << "front" << std::endl;
	}
	if (m_z == -1) {
		m_vertices.insert(m_vertices.end(), back.begin(), back.end());
		m_zcolor = glm::vec3(1.0f, 0.644f, 0.0f);
		// std::cout << "back" << std::endl;
	}
	// for (int i = 0; i < m_vertices.size(); i += 3) {
	// 	std::cout << m_vertices[i] << " " << m_vertices[i + 1] << " "
	// 	          << m_vertices[i + 2];
	// 	std::cout << std::endl;
	// }
	glGenVertexArrays(1, &m_vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float),
	             &m_vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
	                      (void *)0);
	ResourceManager::LoadShader("cubelet/vertex.glsl", "cubelet/fragment.glsl",
	                            "cubelet");
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Cubelet::setModel(const glm::mat4 &_model) { model = _model; }

void Cubelet::draw() {
	glm::mat4 tempmodel = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

	tempmodel =
	    glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	tempmodel = glm::translate(tempmodel, 1.05f * glm::vec3(m_x, m_y, m_z));
	Shader shader = ResourceManager::GetShader("cubelet");
	shader.Use();
	shader.SetMat4("model", tempmodel);
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);
	glBindVertexArray(m_vao);
	int position = 0;
	if (m_x == 1 || m_x == -1) {
		shader.SetVec3("inColor", m_xcolor);
		glDrawArrays(GL_TRIANGLES, position, 6);
		position += 6;
	}
	if (m_y == 1 || m_y == -1) {
		shader.SetVec3("inColor", m_ycolor);
		glDrawArrays(GL_TRIANGLES, position, 6);
		position += 6;
	}
	if (m_z == 1 || m_z == -1) {
		shader.SetVec3("inColor", m_zcolor);
		glDrawArrays(GL_TRIANGLES, position, 6);
	}
	glBindVertexArray(0);
}
