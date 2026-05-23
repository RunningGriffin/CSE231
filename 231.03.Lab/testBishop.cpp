/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the bishop
 ************************************************************************/

#include "testBishop.h"
#include "pieceBishop.h"
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
  * 3     p   p           3
  * 2      (b)            2
  * 1     p   p           1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  * Bishop at b2, friendly pawns on all 4 diagonals immediately adjacent
  **************************************/
void TestBishop::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	Bishop bishop(1, 1, true);
	bishop.fWhite = true;
	bishop.position.colRow = 0x11;   // b2
	board.board[1][1] = &bishop;
	White w1(PAWN); board.board[0][0] = &w1;   // a1 (SW)
	White w2(PAWN); board.board[2][0] = &w2;   // c1 (SE)
	White w3(PAWN); board.board[0][2] = &w3;   // a3 (NW)
	White w4(PAWN); board.board[2][2] = &w4;   // c3 (NE)
	set<Move> moves;

	// EXERCISE
	bishop.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 0);

	// TEARDOWN
	board.board[1][1] = nullptr;
	board.board[0][0] = board.board[2][0] = nullptr;
	board.board[0][2] = board.board[2][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Bishop at b2, empty board
 * NE: c3,d4,e5,f6,g7,h8 = 6
 * NW: a3 = 1
 * SE: c1 = 1
 * SW: a1 = 1
 * Total = 9
 **************************************/
void TestBishop::getMoves_slideToEnd()
{
	// SETUP
	BoardEmpty board;
	Bishop bishop(1, 1, true);
	bishop.fWhite = true;
	bishop.position.colRow = 0x11;   // b2
	board.board[1][1] = &bishop;
	set<Move> moves;

	// EXERCISE
	bishop.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 9);
	Move b2h8; b2h8.dest.colRow = 0x77;
	Move b2a3; b2a3.dest.colRow = 0x02;
	Move b2c1; b2c1.dest.colRow = 0x20;
	Move b2a1; b2a1.dest.colRow = 0x00;
	assertUnit(moves.find(b2h8) != moves.end());
	assertUnit(moves.find(b2a3) != moves.end());
	assertUnit(moves.find(b2c1) != moves.end());
	assertUnit(moves.find(b2a1) != moves.end());

	// TEARDOWN
	board.board[1][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Bishop at b2, friendly blocks on h7(NE), a4(NW? No - not on diag),
 * a1(SW), c1(SE)
 * NE: c3,d4,e5,f6,g7 = 5 (h7 is not on NE diagonal - h8 reachable)
 * Actually h7 = col=7,row=6. NE from b2: col+1,row+1 each step.
 * b2->c3->d4->e5->f6->g7->h8. g7=col6,row6. h7=col7,row6 NOT on path.
 * The diagram p at row7-col h must mean col=7 = h, which is h7 not h8.
 * But NE reaches h8(col7,row7) not h7(col7,row6). So NE = 6.
 * NW: a3 = 1 (a4 at col0,row3 is not on NW diagonal from b2)
 * SE: blocked at c1 = 0
 * SW: blocked at a1 = 0
 * Total = 7
 **************************************/
void TestBishop::getMoves_slideToBlock()
{
	// SETUP
	BoardEmpty board;
	Bishop bishop(1, 1, true);
	bishop.fWhite = true;
	bishop.position.colRow = 0x11;   // b2
	board.board[1][1] = &bishop;
	White wNE(PAWN); board.board[7][6] = &wNE;  // h7 - NOT on NE diag, irrelevant
	White wNW(PAWN); board.board[0][3] = &wNW;  // a4 - NOT on NW diag, irrelevant
	White wSW(PAWN); board.board[0][0] = &wSW;  // a1 (SW) - blocks immediately
	White wSE(PAWN); board.board[2][0] = &wSE;  // c1 (SE) - blocks immediately
	set<Move> moves;

	// EXERCISE
	bishop.getMoves(moves, board);

	// VERIFY
	// NE: c3,d4,e5,f6,g7,h8 = 6 (h7 not on NE diagonal)
	// NW: a3 = 1 (a4 not on NW diagonal)
	// SE: 0 (c1 friendly blocks)
	// SW: 0 (a1 friendly blocks)
	assertUnit(moves.size() == 7);
	Move b2h8; b2h8.dest.colRow = 0x77;
	Move b2a3; b2a3.dest.colRow = 0x02;
	assertUnit(moves.find(b2h8) != moves.end());
	assertUnit(moves.find(b2a3) != moves.end());

	// TEARDOWN
	board.board[1][1] = nullptr;
	board.board[7][6] = board.board[0][3] = nullptr;
	board.board[0][0] = board.board[2][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Bishop at b2, enemy pieces (uppercase P) at same spots
 * SE: c1 capture = 1
 * SW: a1 capture = 1
 * NE: c3,d4,e5,f6,g7,h8 = 6 (h7 not on diagonal)
 * NW: a3 = 1
 * Total = 9
 **************************************/
void TestBishop::getMoves_slideToCapture()
{
	// SETUP
	BoardEmpty board;
	Bishop bishop(1, 1, true);
	bishop.fWhite = true;
	bishop.position.colRow = 0x11;   // b2
	board.board[1][1] = &bishop;
	Black eNE(PAWN); board.board[7][6] = &eNE;  // h7 - NOT on NE diagonal
	Black eNW(PAWN); board.board[0][3] = &eNW;  // a4 - NOT on NW diagonal
	Black eSW(PAWN); board.board[0][0] = &eSW;  // a1 (SW)
	Black eSE(PAWN); board.board[2][0] = &eSE;  // c1 (SE)
	set<Move> moves;

	// EXERCISE
	bishop.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 9);
	Move b2a1; b2a1.dest.colRow = 0x00; b2a1.capture = PAWN;
	Move b2c1; b2c1.dest.colRow = 0x20; b2c1.capture = PAWN;
	assertUnit(moves.find(b2a1) != moves.end());
	assertUnit(moves.find(b2c1) != moves.end());

	// TEARDOWN
	board.board[1][1] = nullptr;
	board.board[7][6] = board.board[0][3] = nullptr;
	board.board[0][0] = board.board[2][0] = nullptr;
}

/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
	// SETUP
	const Bishop bishop(3, 3, true);
	PieceType pt = SPACE;

	// EXERCISE
	pt = bishop.getType();

	// VERIFY
	assertUnit(pt == BISHOP);
}