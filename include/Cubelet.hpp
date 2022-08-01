#pragma once
#include <vector>
#include "VertexArray.hpp"

#include "glm/glm.hpp"

enum class Type { CORNER, EDGE, MIDDLE };

class Cubelet {
  public:
	Cubelet();
	Cubelet(int x, int y, int z);
	void setModel(const glm::mat4 &model);
	void draw();
	glm::mat4 model;
	static glm::mat4 view;
	static glm::mat4 projection;

  private:
	Type m_type;
	int m_x, m_y, m_z;

	std::vector<float> m_vertices;
	glm::vec3 m_xcolor, m_ycolor, m_zcolor;
	unsigned int m_vao;
};
