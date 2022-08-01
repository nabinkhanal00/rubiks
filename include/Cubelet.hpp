#pragma once
#include <vector>
#include "VertexArray.hpp"

#include "glm/glm.hpp"

enum class Type { CORNER, EDGE, MIDDLE };

class Cubelet {
  public:
	Cubelet();
	Cubelet(int x, int y, int z);
	void adjustVertices();
	void setModel(const glm::mat4 &model);
	void draw();
	glm::mat4 model;
	static glm::mat4 view;
	static glm::mat4 projection;

	int x, y, z;
	glm::mat4 tempModel;

  private:
	Type m_type;

	std::vector<float> m_vertices;
	glm::vec3 m_xcolor, m_ycolor, m_zcolor;
	int d_x, d_y, d_z;
	unsigned int m_vao;
};
