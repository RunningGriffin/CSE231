/***********************************************************************
 * Source File:
 *    TEST MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    test the Move class
 ************************************************************************/

#include "testMove.h"
#include "move.h"
#include <cassert>

void TestMove::constructor_default()
{
	// SETUP & EXERCISE
	Move move;
	// VERIFY
	assertUnit(move.source.isInvalid());
	assertUnit(move.dest.isInvalid());
	assertUnit(move.promote == INVALID);
	assertUnit(move.capture == INVALID);
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.isWhite == true);
}

void TestMove::constructString_simple()
{
	// SETUP & EXERCISE
	Move move("e5e6");
	// VERIFY
	assertUnit(move.source == Position(4, 4));
	assertUnit(move.dest == Position(4, 5));
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == INVALID);
}

void TestMove::read_simple()
{
	// SETUP
	Move move;
	// EXERCISE
	move.read("e5e6");
	// VERIFY
	assertUnit(move.source == Position(4, 4));
	assertUnit(move.dest == Position(4, 5));
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == INVALID);
}

void TestMove::read_capture()
{
	// SETUP
	Move move;
	// EXERCISE
	move.read("e5d6r");
	// VERIFY
	assertUnit(move.source == Position(4, 4));
	assertUnit(move.dest == Position(3, 5));
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);
}

void TestMove::read_enpassant()
{
	// SETUP
	Move move;
	// EXERCISE
	move.read("e5f6E");
	// VERIFY
	assertUnit(move.source == Position(4, 4));
	assertUnit(move.dest == Position(5, 5));
	assertUnit(move.moveType == Move::ENPASSANT);
	assertUnit(move.capture == PAWN);
}

void TestMove::read_castleKing()
{
	// SETUP
	Move move;
	// EXERCISE
	move.read("e1g1c");
	// VERIFY
	assertUnit(move.source == Position(4, 0));
	assertUnit(move.dest == Position(6, 0));
	assertUnit(move.moveType == Move::CASTLE_KING);
}

void TestMove::read_castleQueen()
{
	// SETUP
	Move move;
	// EXERCISE
	move.read("e1c1C");
	// VERIFY
	assertUnit(move.source == Position(4, 0));
	assertUnit(move.dest == Position(2, 0));
	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}

void TestMove::assign_simple()
{
	// SETUP
	Move move;
	// EXERCISE
	move = "e5e6";
	// VERIFY
	assertUnit(move.source == Position(4, 4));
	assertUnit(move.dest == Position(4, 5));
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == INVALID);
}

void TestMove::assign_capture()
{
	// SETUP
	Move move;
	// EXERCISE
	move = "e5d6r";
	// VERIFY
	assertUnit(move.source == Position(4, 4));
	assertUnit(move.dest == Position(3, 5));
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);
}

void TestMove::assign_enpassant()
{
	// SETUP
	Move move;
	// EXERCISE
	move = "e5f6E";
	// VERIFY
	assertUnit(move.source == Position(4, 4));
	assertUnit(move.dest == Position(5, 5));
	assertUnit(move.moveType == Move::ENPASSANT);
	assertUnit(move.capture == PAWN);
}

void TestMove::assign_castleKing()
{
	// SETUP
	Move move;
	// EXERCISE
	move = "e1g1c";
	// VERIFY
	assertUnit(move.source == Position(4, 0));
	assertUnit(move.dest == Position(6, 0));
	assertUnit(move.moveType == Move::CASTLE_KING);
}

void TestMove::assign_castleQueen()
{
	// SETUP
	Move move;
	// EXERCISE
	move = "e1c1C";
	// VERIFY
	assertUnit(move.source == Position(4, 0));
	assertUnit(move.dest == Position(2, 0));
	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}

void TestMove::getText_simple()
{
	// SETUP
	Move move;
	move.source = Position(4, 4);
	move.dest = Position(4, 5);
	move.moveType = Move::MOVE;
	// EXERCISE
	string text = move.getText();
	// VERIFY
	assertUnit(text == "e5e6");
}

void TestMove::getText_capture()
{
	// SETUP
	Move move;
	move.source = Position(4, 4);
	move.dest = Position(4, 5);
	move.moveType = Move::MOVE;
	move.capture = ROOK;
	// EXERCISE
	string text = move.getText();
	// VERIFY
	assertUnit(text == "e5e6r");
}

void TestMove::getText_enpassant()
{
	// SETUP
	Move move;
	move.source = Position(4, 4);
	move.dest = Position(5, 5);
	move.moveType = Move::ENPASSANT;
	move.capture = PAWN;
	// EXERCISE
	string text = move.getText();
	// VERIFY
	assertUnit(text == "e5f6E");
}

void TestMove::getText_castleKing()
{
	// SETUP
	Move move;
	move.source = Position(4, 0);
	move.dest = Position(6, 0);
	move.moveType = Move::CASTLE_KING;
	// EXERCISE
	string text = move.getText();
	// VERIFY
	assertUnit(text == "e1g1c");
}

void TestMove::getText_castleQueen()
{
	// SETUP
	Move move;
	move.source = Position(4, 0);
	move.dest = Position(2, 0);
	move.moveType = Move::CASTLE_QUEEN;
	// EXERCISE
	string text = move.getText();
	// VERIFY
	assertUnit(text == "e1c1C");
}

void TestMove::letterFromPieceType_space()
{
	Move move;
	assertUnit(move.letterFromPieceType(SPACE) == ' ');
}

void TestMove::letterFromPieceType_pawn()
{
	Move move;
	assertUnit(move.letterFromPieceType(PAWN) == 'p');
}

void TestMove::letterFromPieceType_bishop()
{
	Move move;
	assertUnit(move.letterFromPieceType(BISHOP) == 'b');
}

void TestMove::letterFromPieceType_knight()
{
	Move move;
	assertUnit(move.letterFromPieceType(KNIGHT) == 'n');
}

void TestMove::letterFromPieceType_rook()
{
	Move move;
	assertUnit(move.letterFromPieceType(ROOK) == 'r');
}

void TestMove::letterFromPieceType_queen()
{
	Move move;
	assertUnit(move.letterFromPieceType(QUEEN) == 'q');
}

void TestMove::letterFromPieceType_king()
{
	Move move;
	assertUnit(move.letterFromPieceType(KING) == 'k');
}

void TestMove::pieceTypeFromLetter_pawn()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('p') == PAWN);
}

void TestMove::pieceTypeFromLetter_bishop()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('b') == BISHOP);
}

void TestMove::pieceTypeFromLetter_knight()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('n') == KNIGHT);
}

void TestMove::pieceTypeFromLetter_rook()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('r') == ROOK);
}

void TestMove::pieceTypeFromLetter_queen()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('q') == QUEEN);
}

void TestMove::pieceTypeFromLetter_king()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('k') == KING);
}