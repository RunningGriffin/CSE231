/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "testPawn.h"
#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>

 /*************************************
  * GET MOVES Simple White
  * White pawn at b4, one move forward: b4b5
  **************************************/
void TestPawn::getMoves_simpleWhite()
{
	// SETUP
	BoardEmpty board;
	Pawn pawn(1, 3, true);
	pawn.fWhite = true;
	pawn.nMoves = 1;                     // not on starting row
	pawn.position.colRow = 0x13;         // b4
	board.board[1][3] = &pawn;
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 1);
	Move b4b5;
	b4b5.dest.colRow = 0x14;
	assertUnit(moves.find(b4b5) != moves.end());

	// TEARDOWN
	board.board[1][3] = nullptr;
}

/*************************************
 * GET MOVES Simple Black
 * Black pawn at b4, one move forward: b4b3
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
	// SETUP
	BoardEmpty board;
	Pawn pawn(1, 3, false);
	pawn.fWhite = false;
	pawn.nMoves = 1;
	pawn.position.colRow = 0x13;         // b4
	board.board[1][3] = &pawn;
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 1);
	Move b4b3;
	b4b3.dest.colRow = 0x12;
	assertUnit(moves.find(b4b3) != moves.end());

	// TEARDOWN
	board.board[1][3] = nullptr;
}

/*************************************
 * GET MOVES Initial Advance White
 * White pawn at b2, two moves: b2b3, b2b4
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
	// SETUP
	BoardEmpty board;
	Pawn pawn(1, 1, true);
	pawn.fWhite = true;
	pawn.nMoves = 0;                     // starting position
	pawn.position.colRow = 0x11;         // b2
	board.board[1][1] = &pawn;
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);
	Move b2b3; b2b3.dest.colRow = 0x12;
	Move b2b4; b2b4.dest.colRow = 0x13;
	assertUnit(moves.find(b2b3) != moves.end());
	assertUnit(moves.find(b2b4) != moves.end());

	// TEARDOWN
	board.board[1][1] = nullptr;
}

/*************************************
 * GET MOVES Initial Advance Black
 * Black pawn at c7, two moves: c7c6, c7c5
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
	// SETUP
	BoardEmpty board;
	Pawn pawn(2, 6, false);
	pawn.fWhite = false;
	pawn.nMoves = 0;
	pawn.position.colRow = 0x26;         // c7
	board.board[2][6] = &pawn;
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);
	Move c7c6; c7c6.dest.colRow = 0x25;
	Move c7c5; c7c5.dest.colRow = 0x24;
	assertUnit(moves.find(c7c6) != moves.end());
	assertUnit(moves.find(c7c5) != moves.end());

	// TEARDOWN
	board.board[2][6] = nullptr;
}

/*************************************
 * GET MOVES Capture White
 * White pawn at b6, b7 blocked by friendly, enemy at a7 and c7
 * Only captures: b6a7, b6c7
 **************************************/
void TestPawn::getMoves_captureWhite()
{
	// SETUP
	BoardEmpty board;
	Pawn pawn(1, 5, true);
	pawn.fWhite = true;
	pawn.nMoves = 1;
	pawn.position.colRow = 0x15;         // b6
	board.board[1][5] = &pawn;
	White blocker(PAWN); board.board[1][6] = &blocker; // b7 friendly blocks
	Black eA7(PAWN);     board.board[0][6] = &eA7;     // a7 enemy
	Black eC7(PAWN);     board.board[2][6] = &eC7;     // c7 enemy
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);
	Move b6a7; b6a7.dest.colRow = 0x06; b6a7.capture = PAWN;
	Move b6c7; b6c7.dest.colRow = 0x26; b6c7.capture = PAWN;
	assertUnit(moves.find(b6a7) != moves.end());
	assertUnit(moves.find(b6c7) != moves.end());

	// TEARDOWN
	board.board[1][5] = nullptr;
	board.board[1][6] = board.board[0][6] = board.board[2][6] = nullptr;
}

/*************************************
 * GET MOVES Capture Black
 * Black pawn at b6, b5 blocked by friendly, enemy at a5 and c5
 * Only captures: b6a5, b6c5
 **************************************/
void TestPawn::getMoves_captureBlack()
{
	// SETUP
	BoardEmpty board;
	Pawn pawn(1, 5, false);
	pawn.fWhite = false;
	pawn.nMoves = 1;
	pawn.position.colRow = 0x15;         // b6
	board.board[1][5] = &pawn;
	Black blocker(PAWN); board.board[1][4] = &blocker; // b5 friendly blocks
	White eA5(PAWN);     board.board[0][4] = &eA5;     // a5 enemy
	White eC5(PAWN);     board.board[2][4] = &eC5;     // c5 enemy
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);
	Move b6a5; b6a5.dest.colRow = 0x04; b6a5.capture = PAWN;
	Move b6c5; b6c5.dest.colRow = 0x24; b6c5.capture = PAWN;
	assertUnit(moves.find(b6a5) != moves.end());
	assertUnit(moves.find(b6c5) != moves.end());

	// TEARDOWN
	board.board[1][5] = nullptr;
	board.board[1][4] = board.board[0][4] = board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES Enpassant White
 * White pawn at b5, b6 blocked by friendly,
 * enemy pawns at a5 and c5 that just moved (justMoved=true)
 * En passant: b5a6E, b5c6E
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{
	// SETUP
	BoardEmpty board;
	board.moveNumber = 4;
	Pawn pawn(1, 4, true);
	pawn.fWhite = true;
	pawn.nMoves = 1;
	pawn.position.colRow = 0x14;         // b5
	board.board[1][4] = &pawn;
	White blocker(PAWN); board.board[1][5] = &blocker;  // b6 friendly blocks

	// Enemy pawns that just moved (lastMove = moveNumber - 1 = 3)
	Pawn adjL(0, 4, false); adjL.fWhite = false; adjL.lastMove = 3;
	Pawn adjR(2, 4, false); adjR.fWhite = false; adjR.lastMove = 3;
	board.board[0][4] = &adjL;  // a5
	board.board[2][4] = &adjR;  // c5
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);
	Move b5a6; b5a6.dest.colRow = 0x05; b5a6.moveType = Move::ENPASSANT;
	Move b5c6; b5c6.dest.colRow = 0x25; b5c6.moveType = Move::ENPASSANT;
	assertUnit(moves.find(b5a6) != moves.end());
	assertUnit(moves.find(b5c6) != moves.end());

	// TEARDOWN
	board.board[1][4] = nullptr;
	board.board[1][5] = board.board[0][4] = board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES Enpassant Black
 * Black pawn at f4, f3 blocked by friendly,
 * enemy pawns at e4 and g4 that just moved
 * En passant: f4e3E, f4g3E
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{
	// SETUP
	BoardEmpty board;
	board.moveNumber = 7;
	Pawn pawn(5, 3, false);
	pawn.fWhite = false;
	pawn.nMoves = 1;
	pawn.position.colRow = 0x53;         // f4
	board.board[5][3] = &pawn;
	Black blocker(PAWN); board.board[5][2] = &blocker;  // f3 friendly blocks

	// Enemy pawns that just moved (lastMove = moveNumber - 1 = 6)
	Pawn adjL(4, 3, true); adjL.fWhite = true; adjL.lastMove = 6;
	Pawn adjR(6, 3, true); adjR.fWhite = true; adjR.lastMove = 6;
	board.board[4][3] = &adjL;  // e4
	board.board[6][3] = &adjR;  // g4
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);
	Move f4e3; f4e3.dest.colRow = 0x42; f4e3.moveType = Move::ENPASSANT;
	Move f4g3; f4g3.dest.colRow = 0x62; f4g3.moveType = Move::ENPASSANT;
	assertUnit(moves.find(f4e3) != moves.end());
	assertUnit(moves.find(f4g3) != moves.end());

	// TEARDOWN
	board.board[5][3] = nullptr;
	board.board[5][2] = board.board[4][3] = board.board[6][3] = nullptr;
}

/*************************************
 * GET MOVES Enpassant Denied
 * White pawn at b5, b6 blocked by friendly Black pawn,
 * a5 has enemy that just moved (valid ep),
 * c5 has enemy that moved two turns ago (denied),
 * Result: 0 moves (b6 blocked, c5 denied, a5 valid but b6 blocked)
 * Wait - a5 is valid en passant (dest a6), b6 blocked doesn't affect a6
 * So result: 1 move (b5a6E only)
 **************************************/
void TestPawn::getMoves_enpassantDenied()
{
	// SETUP
	BoardEmpty board;
	board.moveNumber = 10;
	Pawn pawn(1, 4, true);
	pawn.fWhite = true;
	pawn.nMoves = 1;
	pawn.position.colRow = 0x14;         // b5
	board.board[1][4] = &pawn;
	Black blocker(PAWN); board.board[1][5] = &blocker;  // b6 friendly Black blocks

	// a5: enemy that just moved - en passant IS valid
	Pawn adjL(0, 4, false); adjL.fWhite = false; adjL.lastMove = 9;
	board.board[0][4] = &adjL;

	// c5: enemy that moved two turns ago - en passant DENIED
	Pawn adjR(2, 4, false); adjR.fWhite = false; adjR.lastMove = 8;
	board.board[2][4] = &adjR;
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 1);
	Move b5a6; b5a6.dest.colRow = 0x05; b5a6.moveType = Move::ENPASSANT;
	assertUnit(moves.find(b5a6) != moves.end());

	// TEARDOWN
	board.board[1][4] = nullptr;
	board.board[1][5] = board.board[0][4] = board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES Promotion White
 * White pawn at b7, b8 empty, enemy at a8 and c8
 * Three promotion moves: b7b8Q, b7a8pQ, b7c8pQ
 **************************************/
void TestPawn::getMoves_promotionWhite()
{
	// SETUP
	BoardEmpty board;
	Pawn pawn(1, 6, true);
	pawn.fWhite = true;
	pawn.nMoves = 1;
	pawn.position.colRow = 0x16;         // b7
	board.board[1][6] = &pawn;
	Black eA8(PAWN); board.board[0][7] = &eA8;  // a8 enemy
	Black eC8(PAWN); board.board[2][7] = &eC8;  // c8 enemy
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 3);
	Move b7b8; b7b8.dest.colRow = 0x17; b7b8.promote = QUEEN;
	Move b7a8; b7a8.dest.colRow = 0x07; b7a8.capture = PAWN; b7a8.promote = QUEEN;
	Move b7c8; b7c8.dest.colRow = 0x27; b7c8.capture = PAWN; b7c8.promote = QUEEN;
	assertUnit(moves.find(b7b8) != moves.end());
	assertUnit(moves.find(b7a8) != moves.end());
	assertUnit(moves.find(b7c8) != moves.end());

	// TEARDOWN
	board.board[1][6] = nullptr;
	board.board[0][7] = board.board[2][7] = nullptr;
}

/*************************************
 * GET MOVES Promotion Black
 * Black pawn at e2, e1 empty, enemy rooks at d1 and f1
 * Three promotion moves: e2e1Q, e2d1rQ, e2f1rQ
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
	// SETUP
	BoardEmpty board;
	Pawn pawn(4, 1, false);
	pawn.fWhite = false;
	pawn.nMoves = 1;
	pawn.position.colRow = 0x41;         // e2
	board.board[4][1] = &pawn;
	White eD1(ROOK); board.board[3][0] = &eD1;  // d1 enemy rook
	White eF1(ROOK); board.board[5][0] = &eF1;  // f1 enemy rook
	set<Move> moves;

	// EXERCISE
	pawn.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 3);
	Move e2e1; e2e1.dest.colRow = 0x40; e2e1.promote = QUEEN;
	Move e2d1; e2d1.dest.colRow = 0x30; e2d1.capture = ROOK; e2d1.promote = QUEEN;
	Move e2f1; e2f1.dest.colRow = 0x50; e2f1.capture = ROOK; e2f1.promote = QUEEN;
	assertUnit(moves.find(e2e1) != moves.end());
	assertUnit(moves.find(e2d1) != moves.end());
	assertUnit(moves.find(e2f1) != moves.end());

	// TEARDOWN
	board.board[4][1] = nullptr;
	board.board[3][0] = board.board[5][0] = nullptr;
}

/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{
	// SETUP
	const Pawn pawn(1, 1, true);
	PieceType pt = SPACE;

	// EXERCISE
	pt = pawn.getType();

	// VERIFY
	assertUnit(pt == PAWN);
}