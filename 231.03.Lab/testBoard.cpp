/***********************************************************************
 * Source File:
 *    TEST BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for board
 ************************************************************************/

#include "testBoard.h"
#include "position.h"
#include "piece.h"
#include "board.h"
#include <cassert>

 /********************************************************
  * KNIGHT MOVE: e5c6
  ********************************************************/
void TestBoard::move_knightMove()
{
	// SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x25;
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][4] = new PieceSpy(4, 4, true, KNIGHT);
	board.board[2][5] = new PieceSpy(2, 5, false, SPACE);
	board.board[4][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][4]->getType());
	assertUnit(KNIGHT == board.board[2][5]->getType());
	assertUnit(18 == board.board[2][5]->nMoves);
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[2][5];
	delete board.board[4][4];
	board.board[2][5] = board.board[4][4] = nullptr;
}

/********************************************************
 * KNIGHT ATTACK: e5c6r
 ********************************************************/
void TestBoard::move_knightAttack()
{
	// SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x25;
	move.capture = ROOK;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][4] = new PieceSpy(4, 4, true, KNIGHT);
	board.board[2][5] = new PieceSpy(2, 5, false, ROOK);
	board.board[4][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][4]->getType());
	assertUnit(KNIGHT == board.board[2][5]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[2][5];
	delete board.board[4][4];
	board.board[2][5] = board.board[4][4] = nullptr;
}

/********************************************************
 * PAWN SIMPLE: a2a3
 ********************************************************/
void TestBoard::move_pawnSimple()
{
	// SETUP
	Move move;
	move.source.colRow = 0x01;
	move.dest.colRow = 0x02;
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[0][1] = new PieceSpy(0, 1, true, PAWN);
	board.board[0][2] = new PieceSpy(0, 2, false, SPACE);
	board.board[0][1]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[0][1]->getType());
	assertUnit(PAWN == board.board[0][2]->getType());
	assertUnit(18 == board.board[0][2]->nMoves);
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][1];
	delete board.board[0][2];
	board.board[0][1] = board.board[0][2] = nullptr;
}

/********************************************************
 * PAWN CAPTURE: a6b7r
 ********************************************************/
void TestBoard::move_pawnCapture()
{
	// SETUP
	Move move;
	move.source.colRow = 0x05;
	move.dest.colRow = 0x16;
	move.capture = ROOK;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[0][5] = new PieceSpy(0, 5, true, PAWN);
	board.board[1][6] = new PieceSpy(1, 6, false, ROOK);
	board.board[0][5]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[0][5]->getType());
	assertUnit(PAWN == board.board[1][6]->getType());
	assertUnit(18 == board.board[1][6]->nMoves);
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][5];
	delete board.board[1][6];
	board.board[0][5] = board.board[1][6] = nullptr;
}

/********************************************************
 * PAWN DOUBLE: e2e4
 ********************************************************/
void TestBoard::move_pawnDouble()
{
	// SETUP
	Move move;
	move.source.colRow = 0x41;
	move.dest.colRow = 0x43;
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][1] = new PieceSpy(4, 1, true, PAWN);
	board.board[4][3] = new PieceSpy(4, 3, false, SPACE);
	board.board[4][1]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][1]->getType());
	assertUnit(PAWN == board.board[4][3]->getType());
	assertUnit(18 == board.board[4][3]->nMoves);
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][1];
	delete board.board[4][3];
	board.board[4][1] = board.board[4][3] = nullptr;
}

/********************************************************
 * PAWN EN PASSANT: a5b6E
 ********************************************************/
void TestBoard::move_pawnEnpassant()
{
	// SETUP
	Move move;
	move.source.colRow = 0x04;   // a5
	move.dest.colRow = 0x15;   // b6
	move.capture = PAWN;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::ENPASSANT;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[0][4] = new PieceSpy(0, 4, true, PAWN);   // white pawn a5
	board.board[1][4] = new PieceSpy(1, 4, false, PAWN);   // black pawn b5 (captured)
	board.board[1][5] = new PieceSpy(1, 5, false, SPACE);  // b6 destination
	board.board[0][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[0][4]->getType());  // a5 now space
	assertUnit(PAWN == board.board[1][5]->getType());  // b6 has pawn
	assertUnit(SPACE == board.board[1][4]->getType());  // b5 captured pawn removed
	assertUnit(18 == board.board[1][5]->nMoves);
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][4];
	delete board.board[1][4];
	delete board.board[1][5];
	board.board[0][4] = board.board[1][4] = board.board[1][5] = nullptr;
}

/********************************************************
 * PAWN PROMOTION: a7a8Q
 ********************************************************/
void TestBoard::move_pawnPromotion()
{
	// SETUP
	Move move;
	move.source.colRow = 0x06;   // a7
	move.dest.colRow = 0x07;   // a8
	move.capture = SPACE;
	move.promote = QUEEN;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[0][6] = new PieceSpy(0, 6, true, PAWN);
	board.board[0][7] = new PieceSpy(0, 7, false, SPACE);
	board.board[0][6]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[0][6]->getType());  // a7 now space
	assertUnit(QUEEN == board.board[0][7]->getType());  // a8 has queen
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][6];
	delete board.board[0][7];
	board.board[0][6] = board.board[0][7] = nullptr;
}

/********************************************************
 * ROOK SLIDE: e5a5
 ********************************************************/
void TestBoard::move_rookSlide()
{
	// SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x04;
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][4] = new PieceSpy(4, 4, true, ROOK);
	board.board[0][4] = new PieceSpy(0, 4, false, SPACE);
	board.board[4][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][4]->getType());
	assertUnit(ROOK == board.board[0][4]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][4];
	delete board.board[4][4];
	board.board[0][4] = board.board[4][4] = nullptr;
}

/********************************************************
 * ROOK ATTACK: e5a5b
 ********************************************************/
void TestBoard::move_rookAttack()
{
	// SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x04;
	move.capture = BISHOP;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][4] = new PieceSpy(4, 4, true, ROOK);
	board.board[0][4] = new PieceSpy(0, 4, false, BISHOP);
	board.board[4][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][4]->getType());
	assertUnit(ROOK == board.board[0][4]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][4];
	delete board.board[4][4];
	board.board[0][4] = board.board[4][4] = nullptr;
}

/********************************************************
 * BISHOP SLIDE: e5g3
 ********************************************************/
void TestBoard::move_bishopSlide()
{
	// SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x62;
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][4] = new PieceSpy(4, 4, true, BISHOP);
	board.board[6][2] = new PieceSpy(6, 2, false, SPACE);
	board.board[4][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][4]->getType());
	assertUnit(BISHOP == board.board[6][2]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][4];
	delete board.board[6][2];
	board.board[4][4] = board.board[6][2] = nullptr;
}

/********************************************************
 * BISHOP ATTACK: e5g3q
 ********************************************************/
void TestBoard::move_bishopAttack()
{
	// SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x62;
	move.capture = QUEEN;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][4] = new PieceSpy(4, 4, true, BISHOP);
	board.board[6][2] = new PieceSpy(6, 2, false, QUEEN);
	board.board[4][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][4]->getType());
	assertUnit(BISHOP == board.board[6][2]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][4];
	delete board.board[6][2];
	board.board[4][4] = board.board[6][2] = nullptr;
}

/********************************************************
 * QUEEN SLIDE: e5g3
 ********************************************************/
void TestBoard::move_queenSlide()
{
	// SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x62;
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][4] = new PieceSpy(4, 4, true, QUEEN);
	board.board[6][2] = new PieceSpy(6, 2, false, SPACE);
	board.board[4][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][4]->getType());
	assertUnit(QUEEN == board.board[6][2]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][4];
	delete board.board[6][2];
	board.board[4][4] = board.board[6][2] = nullptr;
}

/********************************************************
 * QUEEN ATTACK: e5a5b
 ********************************************************/
void TestBoard::move_queenAttack()
{
	// SETUP
	Move move;
	move.source.colRow = 0x44;
	move.dest.colRow = 0x04;
	move.capture = BISHOP;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][4] = new PieceSpy(4, 4, true, QUEEN);
	board.board[0][4] = new PieceSpy(0, 4, false, BISHOP);
	board.board[4][4]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][4]->getType());
	assertUnit(QUEEN == board.board[0][4]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][4];
	delete board.board[4][4];
	board.board[0][4] = board.board[4][4] = nullptr;
}

/********************************************************
 * KING MOVE: e1f1
 ********************************************************/
void TestBoard::move_kingMove()
{
	// SETUP
	Move move;
	move.source.colRow = 0x40;
	move.dest.colRow = 0x50;
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][0] = new PieceSpy(4, 0, true, KING);
	board.board[5][0] = new PieceSpy(5, 0, false, SPACE);
	board.board[4][0]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][0]->getType());
	assertUnit(KING == board.board[5][0]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][0];
	delete board.board[5][0];
	board.board[4][0] = board.board[5][0] = nullptr;
}

/********************************************************
 * KING ATTACK: e1f1r
 ********************************************************/
void TestBoard::move_kingAttack()
{
	// SETUP
	Move move;
	move.source.colRow = 0x40;
	move.dest.colRow = 0x50;
	move.capture = ROOK;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::MOVE;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][0] = new PieceSpy(4, 0, true, KING);
	board.board[5][0] = new PieceSpy(5, 0, false, ROOK);
	board.board[4][0]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][0]->getType());
	assertUnit(KING == board.board[5][0]->getType());
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][0];
	delete board.board[5][0];
	board.board[4][0] = board.board[5][0] = nullptr;
}

/********************************************************
 * KING SHORT CASTLE: e1g1c
 * Before: king at e1, rook at h1, f1 and g1 empty
 * After:  king at g1, rook at f1
 ********************************************************/
void TestBoard::move_kingShortCastle()
{
	// SETUP
	Move move;
	move.source.colRow = 0x40;   // e1
	move.dest.colRow = 0x60;   // g1
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::CASTLE_KING;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][0] = new PieceSpy(4, 0, true, KING);
	board.board[5][0] = new PieceSpy(5, 0, false, SPACE);  // f1
	board.board[6][0] = new PieceSpy(6, 0, false, SPACE);  // g1
	board.board[7][0] = new PieceSpy(7, 0, true, ROOK);   // h1
	board.board[4][0]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][0]->getType());  // e1 empty
	assertUnit(ROOK == board.board[5][0]->getType());  // f1 has rook
	assertUnit(KING == board.board[6][0]->getType());  // g1 has king
	assertUnit(SPACE == board.board[7][0]->getType());  // h1 empty
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][0];
	delete board.board[5][0];
	delete board.board[6][0];
	delete board.board[7][0];
	board.board[4][0] = board.board[5][0] = nullptr;
	board.board[6][0] = board.board[7][0] = nullptr;
}

/********************************************************
 * KING LONG CASTLE: e1c1C
 * Before: king at e1, rook at a1, b1/c1/d1 empty
 * After:  king at c1, rook at d1
 ********************************************************/
void TestBoard::move_kingLongCastle()
{
	// SETUP
	Move move;
	move.source.colRow = 0x40;   // e1
	move.dest.colRow = 0x20;   // c1
	move.capture = SPACE;
	move.promote = SPACE;
	move.isWhite = true;
	move.moveType = Move::CASTLE_QUEEN;
	Board board(nullptr, true /*noreset*/);
	board.numMoves = 17;
	board.board[4][0] = new PieceSpy(4, 0, true, KING);   // e1
	board.board[3][0] = new PieceSpy(3, 0, false, SPACE);  // d1
	board.board[2][0] = new PieceSpy(2, 0, false, SPACE);  // c1
	board.board[1][0] = new PieceSpy(1, 0, false, SPACE);  // b1
	board.board[0][0] = new PieceSpy(0, 0, true, ROOK);   // a1
	board.board[4][0]->nMoves = 17;
	PieceSpy::reset();

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(18 == board.numMoves);
	assertUnit(SPACE == board.board[4][0]->getType());  // e1 empty
	assertUnit(ROOK == board.board[3][0]->getType());  // d1 has rook
	assertUnit(KING == board.board[2][0]->getType());  // c1 has king
	assertUnit(SPACE == board.board[1][0]->getType());  // b1 empty
	assertUnit(SPACE == board.board[0][0]->getType());  // a1 empty
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][0];
	delete board.board[3][0];
	delete board.board[2][0];
	delete board.board[1][0];
	delete board.board[0][0];
	board.board[4][0] = board.board[3][0] = board.board[2][0] = nullptr;
	board.board[1][0] = board.board[0][0] = nullptr;
}