/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
#include "pieceRook.h"
#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 6       p p p         6
  * 5       p(k)p         5
  * 4       p p p         4
  * King at d5, all 8 neighbors friendly - 0 moves
  **************************************/
void TestKing::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	King king(3, 4, true);
	king.fWhite = true;
	king.position.colRow = 0x34;   // d5
	board.board[3][4] = &king;
	White w1(PAWN); board.board[2][3] = &w1;  // c4
	White w2(PAWN); board.board[3][3] = &w2;  // d4
	White w3(PAWN); board.board[4][3] = &w3;  // e4
	White w4(PAWN); board.board[2][4] = &w4;  // c5
	White w5(PAWN); board.board[4][4] = &w5;  // e5
	White w6(PAWN); board.board[2][5] = &w6;  // c6
	White w7(PAWN); board.board[3][5] = &w7;  // d6
	White w8(PAWN); board.board[4][5] = &w8;  // e6
	set<Move> moves;

	// EXERCISE
	king.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 0);

	// TEARDOWN
	board.board[3][4] = nullptr;
	board.board[2][3] = board.board[3][3] = board.board[4][3] = nullptr;
	board.board[2][4] = board.board[4][4] = nullptr;
	board.board[2][5] = board.board[3][5] = board.board[4][5] = nullptr;
}

/*************************************
 * King at d5, all 8 neighbors enemy - 8 captures
 **************************************/
void TestKing::getMoves_capture()
{
	// SETUP
	BoardEmpty board;
	King king(3, 4, true);
	king.fWhite = true;
	king.position.colRow = 0x34;   // d5
	board.board[3][4] = &king;
	Black e1(PAWN); board.board[2][3] = &e1;
	Black e2(PAWN); board.board[3][3] = &e2;
	Black e3(PAWN); board.board[4][3] = &e3;
	Black e4(PAWN); board.board[2][4] = &e4;
	Black e5(PAWN); board.board[4][4] = &e5;
	Black e6(PAWN); board.board[2][5] = &e6;
	Black e7(PAWN); board.board[3][5] = &e7;
	Black e8(PAWN); board.board[4][5] = &e8;
	set<Move> moves;

	// EXERCISE
	king.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 8);

	// TEARDOWN
	board.board[3][4] = nullptr;
	board.board[2][3] = board.board[3][3] = board.board[4][3] = nullptr;
	board.board[2][4] = board.board[4][4] = nullptr;
	board.board[2][5] = board.board[3][5] = board.board[4][5] = nullptr;
}

/*************************************
 * King at d5, empty board - 8 moves
 **************************************/
void TestKing::getMoves_free()
{
	// SETUP
	BoardEmpty board;
	King king(3, 4, true);
	king.fWhite = true;
	king.position.colRow = 0x34;   // d5
	board.board[3][4] = &king;
	set<Move> moves;

	// EXERCISE
	king.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 8);

	// TEARDOWN
	board.board[3][4] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * 2   . .               2
 * 1  (k).               1
 * King at a1 corner - 3 moves (b1, a2, b2)
 **************************************/
void TestKing::getMoves_end()
{
	// SETUP
	BoardEmpty board;
	King king(0, 0, true);
	king.fWhite = true;
	king.nMoves = 1;               // already moved, no castling
	king.position.colRow = 0x00;   // a1
	board.board[0][0] = &king;
	set<Move> moves;

	// EXERCISE
	king.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 3);
	Move a1b1; a1b1.dest.colRow = 0x10;
	Move a1a2; a1a2.dest.colRow = 0x01;
	Move a1b2; a1b2.dest.colRow = 0x11;
	assertUnit(moves.find(a1b1) != moves.end());
	assertUnit(moves.find(a1a2) != moves.end());
	assertUnit(moves.find(a1b2) != moves.end());

	// TEARDOWN
	board.board[0][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * White king at e1, unmoved rooks at a1 and h1,
 * friendly pawns at d2,e2,f2 blocking forward
 * Available: d1, f1, castle queenside (c1), castle kingside (g1) = 4
 **************************************/
void TestKing::getMoves_whiteCastle()
{
	// SETUP
	BoardEmpty board;
	board.moveNumber = 0;
	King king(4, 0, true);
	king.fWhite = true;
	king.nMoves = 0;
	king.position.colRow = 0x40;   // e1
	board.board[4][0] = &king;
	Rook rookQ(0, 0, true); rookQ.fWhite = true;  rookQ.nMoves = 0;
	Rook rookK(7, 0, true); rookK.fWhite = true;  rookK.nMoves = 0;
	board.board[0][0] = &rookQ;    // a1
	board.board[7][0] = &rookK;    // h1
	White pD(PAWN); board.board[3][1] = &pD;  // d2
	White pE(PAWN); board.board[4][1] = &pE;  // e2
	White pF(PAWN); board.board[5][1] = &pF;  // f2
	set<Move> moves;

	// EXERCISE
	king.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 4);
	Move e1g1; e1g1.dest.colRow = 0x60; e1g1.moveType = Move::CASTLE_KING;
	Move e1c1; e1c1.dest.colRow = 0x20; e1c1.moveType = Move::CASTLE_QUEEN;
	Move e1d1; e1d1.dest.colRow = 0x30;
	Move e1f1; e1f1.dest.colRow = 0x50;
	assertUnit(moves.find(e1g1) != moves.end());
	assertUnit(moves.find(e1c1) != moves.end());
	assertUnit(moves.find(e1d1) != moves.end());
	assertUnit(moves.find(e1f1) != moves.end());

	// TEARDOWN
	board.board[4][0] = board.board[0][0] = board.board[7][0] = nullptr;
	board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * Black king at e8, unmoved rooks at a8 and h8,
 * enemy pawns at d7,e7,f7 blocking forward
 * Available: d8, f8, castle queenside (c8), castle kingside (g8) = 4
 **************************************/
void TestKing::getMoves_blackCastle()
{
	// SETUP
	BoardEmpty board;
	board.moveNumber = 0;
	King king(4, 7, false);
	king.fWhite = false;
	king.nMoves = 0;
	king.position.colRow = 0x47;   // e8
	board.board[4][7] = &king;
	Rook rookQ(0, 7, false); rookQ.fWhite = false; rookQ.nMoves = 0;
	Rook rookK(7, 7, false); rookK.fWhite = false; rookK.nMoves = 0;
	board.board[0][7] = &rookQ;    // a8
	board.board[7][7] = &rookK;    // h8
	Black pD(PAWN); board.board[3][6] = &pD;  // d7 (friendly black)
	Black pE(PAWN); board.board[4][6] = &pE;  // e7
	Black pF(PAWN); board.board[5][6] = &pF;  // f7
	set<Move> moves;

	// EXERCISE
	king.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 4);
	Move e8g8; e8g8.dest.colRow = 0x67; e8g8.moveType = Move::CASTLE_KING;
	Move e8c8; e8c8.dest.colRow = 0x27; e8c8.moveType = Move::CASTLE_QUEEN;
	Move e8d8; e8d8.dest.colRow = 0x37;
	Move e8f8; e8f8.dest.colRow = 0x57;
	assertUnit(moves.find(e8g8) != moves.end());
	assertUnit(moves.find(e8c8) != moves.end());
	assertUnit(moves.find(e8d8) != moves.end());
	assertUnit(moves.find(e8f8) != moves.end());

	// TEARDOWN
	board.board[4][7] = board.board[0][7] = board.board[7][7] = nullptr;
	board.board[3][6] = board.board[4][6] = board.board[5][6] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * King already moved - no castling
 * Available: d1, f1 = 2
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
	// SETUP
	BoardEmpty board;
	King king(4, 0, true);
	king.fWhite = true;
	king.nMoves = 1;               // king already moved
	king.position.colRow = 0x40;   // e1
	board.board[4][0] = &king;
	Rook rookQ(0, 0, true); rookQ.fWhite = true; rookQ.nMoves = 0;
	Rook rookK(7, 0, true); rookK.fWhite = true; rookK.nMoves = 0;
	board.board[0][0] = &rookQ;
	board.board[7][0] = &rookK;
	White pD(PAWN); board.board[3][1] = &pD;
	White pE(PAWN); board.board[4][1] = &pE;
	White pF(PAWN); board.board[5][1] = &pF;
	set<Move> moves;

	// EXERCISE
	king.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);
	Move e1d1; e1d1.dest.colRow = 0x30;
	Move e1f1; e1f1.dest.colRow = 0x50;
	assertUnit(moves.find(e1d1) != moves.end());
	assertUnit(moves.find(e1f1) != moves.end());
	// no castling
	Move e1g1; e1g1.dest.colRow = 0x60; e1g1.moveType = Move::CASTLE_KING;
	Move e1c1; e1c1.dest.colRow = 0x20; e1c1.moveType = Move::CASTLE_QUEEN;
	assertUnit(moves.find(e1g1) == moves.end());
	assertUnit(moves.find(e1c1) == moves.end());

	// TEARDOWN
	board.board[4][0] = board.board[0][0] = board.board[7][0] = nullptr;
	board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * Rooks already moved - no castling
 * Available: d1, f1 = 2
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
	// SETUP
	BoardEmpty board;
	King king(4, 0, true);
	king.fWhite = true;
	king.nMoves = 0;               // king unmoved
	king.position.colRow = 0x40;   // e1
	board.board[4][0] = &king;
	Rook rookQ(0, 0, true); rookQ.fWhite = true; rookQ.nMoves = 1; // rook moved
	Rook rookK(7, 0, true); rookK.fWhite = true; rookK.nMoves = 1; // rook moved
	board.board[0][0] = &rookQ;
	board.board[7][0] = &rookK;
	White pD(PAWN); board.board[3][1] = &pD;
	White pE(PAWN); board.board[4][1] = &pE;
	White pF(PAWN); board.board[5][1] = &pF;
	set<Move> moves;

	// EXERCISE
	king.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 2);
	Move e1d1; e1d1.dest.colRow = 0x30;
	Move e1f1; e1f1.dest.colRow = 0x50;
	assertUnit(moves.find(e1d1) != moves.end());
	assertUnit(moves.find(e1f1) != moves.end());
	// no castling
	Move e1g1; e1g1.dest.colRow = 0x60; e1g1.moveType = Move::CASTLE_KING;
	Move e1c1; e1c1.dest.colRow = 0x20; e1c1.moveType = Move::CASTLE_QUEEN;
	assertUnit(moves.find(e1g1) == moves.end());
	assertUnit(moves.find(e1c1) == moves.end());

	// TEARDOWN
	board.board[4][0] = board.board[0][0] = board.board[7][0] = nullptr;
	board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{
	// SETUP
	const King king(4, 0, true);
	PieceType pt = SPACE;

	// EXERCISE
	pt = king.getType();

	// VERIFY
	assertUnit(pt == KING);
}