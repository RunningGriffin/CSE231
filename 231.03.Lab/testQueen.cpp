/***********************************************************************
 * Source File:
 *    TEST QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the queen
 ************************************************************************/

#include "testQueen.h"
#include "pieceQueen.h"
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
  * 3     p p p           3
  * 2     p(q)p           2
  * 1     p p p           1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  * Queen at c2, all 8 neighbors are friendly pawns
  **************************************/
void TestQueen::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	Queen queen(2, 1, true);
	queen.fWhite = true;
	queen.position.colRow = 0x21;   // c2
	board.board[2][1] = &queen;
	White wN(PAWN);  board.board[2][2] = &wN;  // c3
	White wS(PAWN);  board.board[2][0] = &wS;  // c1
	White wE(PAWN);  board.board[3][1] = &wE;  // d2
	White wW(PAWN);  board.board[1][1] = &wW;  // b2
	White wNE(PAWN); board.board[3][2] = &wNE; // d3
	White wSE(PAWN); board.board[3][0] = &wSE; // d1
	White wNW(PAWN); board.board[1][2] = &wNW; // b3
	White wSW(PAWN); board.board[1][0] = &wSW; // b1
	set<Move> moves;

	// EXERCISE
	queen.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 0);

	// TEARDOWN
	board.board[2][1] = nullptr;
	board.board[2][2] = board.board[2][0] = nullptr;
	board.board[3][1] = board.board[1][1] = nullptr;
	board.board[3][2] = board.board[3][0] = nullptr;
	board.board[1][2] = board.board[1][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .         .   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   .   .   .         4
 * 3     . . .           3
 * 2   . .(q). . . . .   2
 * 1     . . .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Queen at c2, empty board
 * N=6, S=1, E=5, W=2, NE=5, SE=1, NW=2, SW=1 = 23 moves
 **************************************/
void TestQueen::getMoves_slideToEnd()
{
	// SETUP
	BoardEmpty board;
	Queen queen(2, 1, true);
	queen.fWhite = true;
	queen.position.colRow = 0x21;   // c2
	board.board[2][1] = &queen;
	set<Move> moves;

	// EXERCISE
	queen.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 23);
	Move c2c8; c2c8.dest.colRow = 0x27;   // N end
	Move c2h7; c2h7.dest.colRow = 0x76;   // NE end
	Move c2a4; c2a4.dest.colRow = 0x03;   // NW end
	Move c2h2; c2h2.dest.colRow = 0x71;   // E end
	Move c2a2; c2a2.dest.colRow = 0x01;   // W end
	Move c2c1; c2c1.dest.colRow = 0x20;   // S end
	Move c2d1; c2d1.dest.colRow = 0x30;   // SE end
	Move c2b1; c2b1.dest.colRow = 0x10;   // SW end
	assertUnit(moves.find(c2c8) != moves.end());
	assertUnit(moves.find(c2h7) != moves.end());
	assertUnit(moves.find(c2a4) != moves.end());
	assertUnit(moves.find(c2h2) != moves.end());
	assertUnit(moves.find(c2a2) != moves.end());
	assertUnit(moves.find(c2c1) != moves.end());
	assertUnit(moves.find(c2d1) != moves.end());
	assertUnit(moves.find(c2b1) != moves.end());

	// TEARDOWN
	board.board[2][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .         p   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   p   .   .         4
 * 3     . . .           3
 * 2   p .(q). . . . p   2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Queen at c2, friendly blocks at endpoints of each direction
 * N:c3..c7=5(c8 blocked), NE:d3..g6=4(h7 blocked)
 * NW:b3=1(a4 blocked), W:b2=1(a2 blocked)
 * E:d2..g2=4(h2 blocked), S:0(c1 blocked)
 * SW:0(b1 blocked), SE:0(d1 blocked)
 * Total = 15
 **************************************/
void TestQueen::getMoves_slideToBlock()
{
	// SETUP
	BoardEmpty board;
	Queen queen(2, 1, true);
	queen.fWhite = true;
	queen.position.colRow = 0x21;   // c2
	board.board[2][1] = &queen;
	White wN(PAWN);  board.board[2][7] = &wN;  // c8
	White wNE(PAWN); board.board[7][6] = &wNE; // h7
	White wNW(PAWN); board.board[0][3] = &wNW; // a4
	White wW(PAWN);  board.board[0][1] = &wW;  // a2
	White wE(PAWN);  board.board[7][1] = &wE;  // h2
	White wS(PAWN);  board.board[2][0] = &wS;  // c1
	White wSW(PAWN); board.board[1][0] = &wSW; // b1
	White wSE(PAWN); board.board[3][0] = &wSE; // d1
	set<Move> moves;

	// EXERCISE
	queen.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 15);
	Move c2c7; c2c7.dest.colRow = 0x26;   // last N square
	Move c2g6; c2g6.dest.colRow = 0x65;   // last NE square
	Move c2b3; c2b3.dest.colRow = 0x12;   // last NW square
	Move c2b2; c2b2.dest.colRow = 0x11;   // only W square
	assertUnit(moves.find(c2c7) != moves.end());
	assertUnit(moves.find(c2g6) != moves.end());
	assertUnit(moves.find(c2b3) != moves.end());
	assertUnit(moves.find(c2b2) != moves.end());

	// TEARDOWN
	board.board[2][1] = nullptr;
	board.board[2][7] = board.board[7][6] = nullptr;
	board.board[0][3] = board.board[0][1] = nullptr;
	board.board[7][1] = board.board[2][0] = nullptr;
	board.board[1][0] = board.board[3][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .         P   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   P   .   .         4
 * 3     . . .           3
 * 2   P .(q). . . . P   2
 * 1     P P P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Queen at c2, enemy pieces at same endpoints
 * All directions reach the enemy and capture = 23 moves
 **************************************/
void TestQueen::getMoves_slideToCapture()
{
	// SETUP
	BoardEmpty board;
	Queen queen(2, 1, true);
	queen.fWhite = true;
	queen.position.colRow = 0x21;   // c2
	board.board[2][1] = &queen;
	Black eN(PAWN);  board.board[2][7] = &eN;  // c8
	Black eNE(PAWN); board.board[7][6] = &eNE; // h7
	Black eNW(PAWN); board.board[0][3] = &eNW; // a4
	Black eW(PAWN);  board.board[0][1] = &eW;  // a2
	Black eE(PAWN);  board.board[7][1] = &eE;  // h2
	Black eS(PAWN);  board.board[2][0] = &eS;  // c1
	Black eSW(PAWN); board.board[1][0] = &eSW; // b1
	Black eSE(PAWN); board.board[3][0] = &eSE; // d1
	set<Move> moves;

	// EXERCISE
	queen.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 23);
	Move c2c8; c2c8.dest.colRow = 0x27; c2c8.capture = PAWN;
	Move c2h7; c2h7.dest.colRow = 0x76; c2h7.capture = PAWN;
	Move c2a2; c2a2.dest.colRow = 0x01; c2a2.capture = PAWN;
	Move c2b1; c2b1.dest.colRow = 0x10; c2b1.capture = PAWN;
	assertUnit(moves.find(c2c8) != moves.end());
	assertUnit(moves.find(c2h7) != moves.end());
	assertUnit(moves.find(c2a2) != moves.end());
	assertUnit(moves.find(c2b1) != moves.end());

	// TEARDOWN
	board.board[2][1] = nullptr;
	board.board[2][7] = board.board[7][6] = nullptr;
	board.board[0][3] = board.board[0][1] = nullptr;
	board.board[7][1] = board.board[2][0] = nullptr;
	board.board[1][0] = board.board[3][0] = nullptr;
}

/*************************************
 * GET TYPE : queen
 * Input:
 * Output: QUEEN
 **************************************/
void TestQueen::getType()
{
	// SETUP
	const Queen queen(3, 3, true);
	PieceType pt = SPACE;

	// EXERCISE
	pt = queen.getType();

	// VERIFY
	assertUnit(pt == QUEEN);
}