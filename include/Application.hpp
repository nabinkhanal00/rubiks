#pragma once
#include "GLFW/glfw3.h"
#include "Cube.hpp"
#include <string>
#include <unordered_set>
class Application {
  public:
	Application(const Application &) = delete;
	Application &operator=(const Application &) = delete;
	Application(unsigned int width, unsigned int height,
	            std::string title = "opengl-rubiks");
	Application() = delete;
	~Application();
	void run();

  private:
	void keyCallback(GLFWwindow *window, int key, int scanCode, int action,
	                 int mods);
	void processEvents();
	void listenEvents();
	void update();
	void render();

	static void framebufferSizeCallback(GLFWwindow *window, int width,
	                                    int height);
	unsigned int m_width;
	unsigned int m_height;
	GLFWwindow *m_window;
	std::unordered_set<char> m_key_set;
	Cube *c;
};
