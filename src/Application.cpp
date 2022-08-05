#include "glad/glad.h"
#include "Application.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

void Application::framebufferSizeCallback(GLFWwindow *window, int width,
                                          int height) {
	glViewport(0, 0, width, height);
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

	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

	c = new Cube();
	c->view =
	    glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
	                glm::vec3(0.0f, 1.0f, 0.0f));
	c->projection = glm::perspective(glm::radians(90.0f),
	                                 m_height / (float)m_height, 0.1f, 100.0f);
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
	} else if (c->ss) {
		c->shuffleAndSolve();
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
		if (glfwGetKey(m_window, GLFW_KEY_B) == GLFW_PRESS &&
		    m_key_set.find('B') == m_key_set.end()) {
			if (c->animate)
				c->BAnimate();
			else
				c->B();
			m_key_set.insert('B');
		}

		if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS &&
		    m_key_set.find('L') == m_key_set.end()) {
			if (c->animate)
				c->LAnimate();
			else
				c->L();
			m_key_set.insert('L');
		}
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS &&
		    m_key_set.find('D') == m_key_set.end()) {
			if (c->animate)
				c->DAnimate();
			else
				c->D();
			m_key_set.insert('D');
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
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_RELEASE) {
			m_key_set.erase('D');
		}
		if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_RELEASE) {
			m_key_set.erase('L');
		}

		if (glfwGetKey(m_window, GLFW_KEY_B) == GLFW_RELEASE) {
			m_key_set.erase('B');
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
		if (glfwGetKey(m_window, GLFW_KEY_B) == GLFW_PRESS &&
		    m_key_set.find('b') == m_key_set.end()) {
			if (c->animate)
				c->bAnimate();
			else
				c->b();
			m_key_set.insert('b');
		}
		if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS &&
		    m_key_set.find('l') == m_key_set.end()) {
			if (c->animate)
				c->lAnimate();
			else
				c->l();
			m_key_set.insert('l');
		}
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS &&
		    m_key_set.find('d') == m_key_set.end()) {
			if (c->animate)
				c->dAnimate();
			else
				c->d();
			m_key_set.insert('d');
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
		if (glfwGetKey(m_window, GLFW_KEY_B) == GLFW_RELEASE) {
			m_key_set.erase('b');
		}
		if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_RELEASE) {
			m_key_set.erase('l');
		}
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_RELEASE) {
			m_key_set.erase('d');
		}

		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS &&
		    m_key_set.find('s') == m_key_set.end()) {
			c->shuffleAndSolve();
			m_key_set.insert('s');
		}

		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_RELEASE) {
			m_key_set.erase('s');
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
