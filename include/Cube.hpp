#pragma once

#include "Cubelet.hpp"
#include <vector>
class Cube {
  private:
	std::vector<std::vector<std::vector<Cubelet>>> cubes;

  public:
	Cube();
	void draw();

	void f();
	void r();
	void u();
	void l();
	void b();
	void d();

	void f2();
	void r2();
	void u2();
	void l2();
	void b2();
	void d2();

	void F();
	void R();
	void U();
	void L();
	void B();
	void D();
};
