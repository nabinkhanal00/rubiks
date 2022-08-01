#include "Application.hpp"
#include <iostream>
void Application::keyCallback(GLFWwindow *window, int key, int scanCode,
                              int action, int mods) {
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		c->f();
	}
}
Application::Application(unsigned int width, unsigned int height,
                         std::string title)
    : m_width(width), m_height(height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window =
	    glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr);
	if (!m_window) {
		throw "Cannot create window!!";
	} else {
		std::cout << "Created Window!!" << std::endl;
	}

	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw "Cannot initialize window!!";
	}
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);

	c = new Cube();
}
void Application::run() {
	while (!glfwWindowShouldClose(m_window)) {
		// processEvents();
		update();
		render();
		listenEvents();
	}
}

void Application::processEvents() {}

void Application::listenEvents() { glfwPollEvents(); }

void Application::update() {}

void Application::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	c->draw();
	glfwSwapBuffers(m_window);
}

Application::~Application() { delete c; }
