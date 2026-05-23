/***********************************************************************
 * Source File:
 *    TEST ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the rook
 ************************************************************************/

#include "testRook.h"
#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5                     5
  * 4                     4
  * 3       p             3
  * 2     p(r)p           2
  * 1       p             1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  * Rook at c2, friendly pawns on all 4 sides
  **************************************/
void TestRook::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	Rook rook(2, 1, true);
	rook.fWhite = true;
	rook.position.colRow = 0x21;   // c2
	board.board[2][1] = &rook;
	White wN(PAWN); board.board[2][2] = &wN;   // c3
	White wS(PAWN); board.board[2][0] = &wS;   // c1
	White wE(PAWN); board.board[3][1] = &wE;   // d2
	White wW(PAWN); board.board[1][1] = &wW;   // b2
	set<Move> moves;

	// EXERCISE
	rook.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 0);

	// TEARDOWN
	board.board[2][1] = nullptr;
	board.board[2][2] = board.board[2][0] = nullptr;
	board.board[3][1] = board.board[1][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   . .(r). . . . .   2
 * 1       .             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Rook at c2, empty board
 * N=6, S=1, E=5, W=2 = 14 moves
 **************************************/
void TestRook::getMoves_slideToEnd()
{
	// SETUP
	BoardEmpty board;
	Rook rook(2, 1, true);
	rook.fWhite = true;
	rook.position.colRow = 0x21;   // c2
	board.board[2][1] = &rook;
	set<Move> moves;

	// EXERCISE
	rook.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 14);
	Move c2c8; c2c8.dest.colRow = 0x27;
	Move c2c1; c2c1.dest.colRow = 0x20;
	Move c2a2; c2a2.dest.colRow = 0x01;
	Move c2h2; c2h2.dest.colRow = 0x71;
	assertUnit(moves.find(c2c8) != moves.end());
	assertUnit(moves.find(c2c1) != moves.end());
	assertUnit(moves.find(c2a2) != moves.end());
	assertUnit(moves.find(c2h2) != moves.end());

	// TEARDOWN
	board.board[2][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   p .(r). . . . p   2
 * 1       p             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Rook at c2, friendly blocks at c8, a2, h2, c1
 * N=c3..c7=5, S=0, E=d2..g2=4, W=b2=1 = 10 moves
 **************************************/
void TestRook::getMoves_slideToBlock()
{
	// SETUP
	BoardEmpty board;
	Rook rook(2, 1, true);
	rook.fWhite = true;
	rook.position.colRow = 0x21;   // c2
	board.board[2][1] = &rook;
	White wN(PAWN); board.board[2][7] = &wN;   // c8 blocks N
	White wS(PAWN); board.board[2][0] = &wS;   // c1 blocks S
	White wE(PAWN); board.board[7][1] = &wE;   // h2 blocks E
	White wW(PAWN); board.board[0][1] = &wW;   // a2 blocks W
	set<Move> moves;

	// EXERCISE
	rook.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 10);
	Move c2c7; c2c7.dest.colRow = 0x26;   // last N square before block
	Move c2b2; c2b2.dest.colRow = 0x11;   // only W square
	assertUnit(moves.find(c2c7) != moves.end());
	assertUnit(moves.find(c2b2) != moves.end());

	// TEARDOWN
	board.board[2][1] = nullptr;
	board.board[2][7] = board.board[2][0] = nullptr;
	board.board[7][1] = board.board[0][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   P .(r). . . . P   2
 * 1       P             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Rook at c2, enemy pieces at c8, a2, h2, c1
 * N=c3..c8(cap)=6, S=c1(cap)=1, E=d2..h2(cap)=5, W=b2+a2(cap)=2 = 14
 **************************************/
void TestRook::getMoves_slideToCapture()
{
	// SETUP
	BoardEmpty board;
	Rook rook(2, 1, true);
	rook.fWhite = true;
	rook.position.colRow = 0x21;   // c2
	board.board[2][1] = &rook;
	Black eN(PAWN); board.board[2][7] = &eN;   // c8 enemy
	Black eS(PAWN); board.board[2][0] = &eS;   // c1 enemy
	Black eE(PAWN); board.board[7][1] = &eE;   // h2 enemy
	Black eW(PAWN); board.board[0][1] = &eW;   // a2 enemy
	set<Move> moves;

	// EXERCISE
	rook.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 14);
	Move c2c8; c2c8.dest.colRow = 0x27; c2c8.capture = PAWN;
	Move c2c1; c2c1.dest.colRow = 0x20; c2c1.capture = PAWN;
	Move c2h2; c2h2.dest.colRow = 0x71; c2h2.capture = PAWN;
	Move c2a2; c2a2.dest.colRow = 0x01; c2a2.capture = PAWN;
	assertUnit(moves.find(c2c8) != moves.end());
	assertUnit(moves.find(c2c1) != moves.end());
	assertUnit(moves.find(c2h2) != moves.end());
	assertUnit(moves.find(c2a2) != moves.end());

	// TEARDOWN
	board.board[2][1] = nullptr;
	board.board[2][7] = board.board[2][0] = nullptr;
	board.board[7][1] = board.board[0][1] = nullptr;
}

/*************************************
 * GET TYPE : rook
 * Input:
 * Output: ROOK
 **************************************/
void TestRook::getType()
{
	// SETUP
	const Rook rook(0, 0, true);
	PieceType pt = SPACE;

	// EXERCISE
	pt = rook.getType();

	// VERIFY
	assertUnit(pt == ROOK);
}