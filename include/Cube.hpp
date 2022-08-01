#pragma once

#include "Cubelet.hpp"
#include <vector>
class Cube {
  private:
	std::vector<std::vector<std::vector<Cubelet>>> cubes;
	struct current {
		int x, y, z;
	} c;

  public:
	bool running;
	bool animate;
	Cube();
	void draw();

	void resume();

	void f();
	void r();
	void u();
	void l();
	void b();
	void d();

	void fAnimate();
	void rAnimate();
	void uAnimate();
	void lAnimate();
	void bAnimate();
	void dAnimate();

	void f2();
	void r2();
	void u2();
	void l2();
	void b2();
	void d2();

	void f2Animate();
	void r2Animate();
	void u2Animate();
	void l2Animate();
	void b2Animate();
	void d2Animate();

	void FAnimate();
	void RAnimate();
	void UAnimate();
	void LAnimate();
	void BAnimate();
	void DAnimate();

	void F();
	void R();
	void U();
	void L();
	void B();
	void D();
};
