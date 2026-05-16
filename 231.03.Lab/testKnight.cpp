/***********************************************************************
 * Source File:
 *    TEST KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the knight
 ************************************************************************/

#include "testKnight.h"
#include "pieceKnight.h"     
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
  * 3             p   .   3
  * 2           P         2
  * 1              (n)    1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestKnight::getMoves_end()
{
	// SETUP
	BoardEmpty board;
	Knight knight(7, 7, false /*white*/); // we will reset all this.
	knight.fWhite = true;
	knight.position.colRow = 0x60;
	board.board[6][0] = &knight;
	Black black(PAWN);
	board.board[4][1] = &black;
	White white(PAWN);
	board.board[5][2] = &white;
	set <Move> moves;
	Move g1e2p;
	g1e2p.source.colRow = 0x60;
	g1e2p.dest.colRow = 0x41;
	g1e2p.capture = PAWN;
	Move g1h3;
	g1h3.source.colRow = 0x60;
	g1h3.dest.colRow = 0x72;
	g1h3.capture = SPACE;

	// EXERCISE
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);  // many possible moves
	assertUnit(moves.find(g1e2p) != moves.end());
	assertUnit(moves.find(g1h3) != moves.end());

	// TEARDOWN
	board.board[6][0] = nullptr; // white knight
	board.board[4][1] = nullptr; // black pawn
	board.board[5][2] = nullptr; // white pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Knight at d5, all 8 squares blocked by friendly pawns
 **************************************/
void TestKnight::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	Knight knight(0, 0, true);
	knight.fWhite = true;
	knight.position.colRow = 0x34;   // d5
	board.board[3][4] = &knight;
	// all 8 landing squares have friendly (white) pawns
	White w1(PAWN); board.board[2][2] = &w1;  // c3  {-2,-1}
	White w2(PAWN); board.board[4][2] = &w2;  // e3  {-2, 1}
	White w3(PAWN); board.board[1][3] = &w3;  // b4  {-1,-2}
	White w4(PAWN); board.board[5][3] = &w4;  // f4  {-1, 2}
	White w5(PAWN); board.board[1][5] = &w5;  // b6  { 1,-2}
	White w6(PAWN); board.board[5][5] = &w6;  // f6  { 1, 2}
	White w7(PAWN); board.board[2][6] = &w7;  // c7  { 2,-1}
	White w8(PAWN); board.board[4][6] = &w8;  // e7  { 2, 1}
	set<Move> moves;

	// EXERCISE
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 0);

	// TEARDOWN
	board.board[3][4] = nullptr;
	board.board[2][2] = nullptr;
	board.board[4][2] = nullptr;
	board.board[1][3] = nullptr;
	board.board[5][3] = nullptr;
	board.board[1][5] = nullptr;
	board.board[5][5] = nullptr;
	board.board[2][6] = nullptr;
	board.board[4][6] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Knight at d5, all 8 squares occupied by enemy pawns
 **************************************/
void TestKnight::getMoves_capture()
{
	// SETUP
	BoardEmpty board;
	Knight knight(0, 0, true);
	knight.fWhite = true;
	knight.position.colRow = 0x34;   // d5
	board.board[3][4] = &knight;
	// all 8 landing squares have enemy (black) pawns
	Black b1(PAWN); board.board[2][2] = &b1;  // c3
	Black b2(PAWN); board.board[4][2] = &b2;  // e3
	Black b3(PAWN); board.board[1][3] = &b3;  // b4
	Black b4(PAWN); board.board[5][3] = &b4;  // f4
	Black b5(PAWN); board.board[1][5] = &b5;  // b6
	Black b6(PAWN); board.board[5][5] = &b6;  // f6
	Black b7(PAWN); board.board[2][6] = &b7;  // c7
	Black b8(PAWN); board.board[4][6] = &b8;  // e7
	set<Move> moves;

	// EXERCISE
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 8);
	// spot-check a few captures
	Move d5c3; d5c3.dest.colRow = 0x22; d5c3.capture = PAWN;
	Move d5e7; d5e7.dest.colRow = 0x46; d5e7.capture = PAWN;
	assertUnit(moves.find(d5c3) != moves.end());
	assertUnit(moves.find(d5e7) != moves.end());

	// TEARDOWN
	board.board[3][4] = nullptr;
	board.board[2][2] = nullptr;
	board.board[4][2] = nullptr;
	board.board[1][3] = nullptr;
	board.board[5][3] = nullptr;
	board.board[1][5] = nullptr;
	board.board[5][5] = nullptr;
	board.board[2][6] = nullptr;
	board.board[4][6] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       .   .         7
 * 6     .       .       6
 * 5        (n)          5
 * 4     .       .       4
 * 3       .   .         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * Knight at d5, all 8 squares empty
 **************************************/
void TestKnight::getMoves_free()
{
	// SETUP
	BoardEmpty board;
	Knight knight(0, 0, true);
	knight.fWhite = true;
	knight.position.colRow = 0x34;   // d5
	board.board[3][4] = &knight;
	set<Move> moves;

	// EXERCISE
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 8);
	Move d5c3; d5c3.dest.colRow = 0x22;
	Move d5e3; d5e3.dest.colRow = 0x42;
	Move d5b4; d5b4.dest.colRow = 0x13;
	Move d5f4; d5f4.dest.colRow = 0x53;
	Move d5b6; d5b6.dest.colRow = 0x15;
	Move d5f6; d5f6.dest.colRow = 0x55;
	Move d5c7; d5c7.dest.colRow = 0x26;
	Move d5e7; d5e7.dest.colRow = 0x46;
	assertUnit(moves.find(d5c3) != moves.end());
	assertUnit(moves.find(d5e3) != moves.end());
	assertUnit(moves.find(d5b4) != moves.end());
	assertUnit(moves.find(d5f4) != moves.end());
	assertUnit(moves.find(d5b6) != moves.end());
	assertUnit(moves.find(d5f6) != moves.end());
	assertUnit(moves.find(d5c7) != moves.end());
	assertUnit(moves.find(d5e7) != moves.end());

	// TEARDOWN
	board.board[3][4] = nullptr;
}



/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{
	// SETUP  
	const Knight knight(7, 7, false /*white*/);
	PieceType pt = SPACE;

	// EXERCISE
	pt = knight.getType();

	// VERIFY
	assertUnit(pt == KNIGHT);
}  // TEARDOWN