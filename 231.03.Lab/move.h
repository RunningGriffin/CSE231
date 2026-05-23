/***********************************************************************
 * Header File:
 *    MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#pragma once

#include <string>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type


class TestMove;
class TestBoard;
class TestKnight;
class TestBishop;
class TestRook;
class TestQueen;
class TestKing;
class TestPawn;
class Knight;
class Bishop;
class Rook;
class Queen;
class King;
class Pawn;
class Board;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
public:
	enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

	friend TestMove;
	friend TestBoard;
	friend TestKnight;
	friend TestBishop;
	friend TestRook;
	friend TestQueen;
	friend TestKing;
	friend TestPawn;
	friend Knight;
	friend Bishop;
	friend Rook;
	friend Queen;
	friend King;
	friend Pawn;
	friend Board;

	// constructor
	Move();
	Move(const string& rhs) { read(rhs); }
	bool operator<(const Move& rhs)  const { return dest < rhs.dest; }
	bool operator==(const Move& rhs)  const { return dest == rhs.dest; }
	void read(const string& rhs);
	string getText() const;
	const Move& operator = (const string& rhs) { read(rhs); return *this; }
	const Move& operator = (const char* rhs) { read(string(rhs)); return *this; }


private:
	char letterFromPieceType(PieceType pt)     const;
	PieceType pieceTypeFromLetter(char letter) const;



	Position  source;    // where the move originated from
	Position  dest;      // where the move finished
	PieceType promote;   // piece to be promoted to
	PieceType capture;   // did a capture happen this move?
	MoveType  moveType;  // what type of move is this?
	bool      isWhite;   // whose turn is it anyway?
	string    text;      // what is the textual version of the move?
};