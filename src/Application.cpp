#include "Application.hpp"
#include "glad/glad.h"
#include <iostream>
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
		processEvents();
		update();
		render();
		listenEvents();
	}
}

void Application::processEvents() {
	if (c->running) {
		c->resume();
		return;
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {

		if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS &&
		    m_key_set.find('F') == m_key_set.end()) {
			if (c->animate)
				c->FAnimate();
			else
				c->F();
			m_key_set.insert('F');
		}

		if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS &&
		    m_key_set.find('R') == m_key_set.end()) {
			if (c->animate)
				c->RAnimate();
			else
				c->R();
			m_key_set.insert('R');
		}
		if (glfwGetKey(m_window, GLFW_KEY_U) == GLFW_PRESS &&
		    m_key_set.find('U') == m_key_set.end()) {
			if (c->animate)
				c->UAnimate();
			else
				c->U();
			m_key_set.insert('U');
		}

		if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_RELEASE) {
			m_key_set.erase('R');
		}
		if (glfwGetKey(m_window, GLFW_KEY_U) == GLFW_RELEASE) {
			m_key_set.erase('U');
		}

		if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_RELEASE) {
			m_key_set.erase('F');
		}
	} else {

		if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS &&
		    m_key_set.find('f') == m_key_set.end()) {
			if (c->animate)
				c->fAnimate();
			else
				c->f();
			m_key_set.insert('f');
		}
		if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS &&
		    m_key_set.find('r') == m_key_set.end()) {
			if (c->animate)
				c->rAnimate();
			else
				c->r();
			m_key_set.insert('r');
		}
		if (glfwGetKey(m_window, GLFW_KEY_U) == GLFW_PRESS &&
		    m_key_set.find('u') == m_key_set.end()) {
			if (c->animate)
				c->uAnimate();
			else
				c->u();
			m_key_set.insert('u');
		}

		if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_RELEASE) {
			m_key_set.erase('f');
		}
		if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_RELEASE) {
			m_key_set.erase('r');
		}
		if (glfwGetKey(m_window, GLFW_KEY_U) == GLFW_RELEASE) {
			m_key_set.erase('u');
		}
	}
}

void Application::listenEvents() { glfwPollEvents(); }

void Application::update() {}

void Application::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	c->draw();
	glfwSwapBuffers(m_window);
}

Application::~Application() { delete c; }
