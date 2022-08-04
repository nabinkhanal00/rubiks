#pragma once

#include "Cubelet.hpp"
#include "glm/glm.hpp"

enum class Move { f = 0, r, u, b, l, d, F, R, U, B, L, D, NONE };

#include <vector>
class Cube {
  public:
	bool running;
	bool animate;
	bool ss;
	glm::mat4 view;
	glm::mat4 projection;
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

	void F();
	void R();
	void U();
	void L();
	void B();
	void D();

	void FAnimate();
	void RAnimate();
	void UAnimate();
	void LAnimate();
	void BAnimate();
	void DAnimate();

	void shuffle();
	void shuffle(std::vector<Move> &moves);
	void solve();
	void shuffleAndSolve();

  private:
	void applyMove(Move m);
	void animateMove(Move m);

  private:
	unsigned int m_vao;
	std::vector<Cubelet> m_cubelets;
	Move m_move;
};
