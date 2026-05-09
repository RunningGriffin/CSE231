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

	// constructors
	Move();
	Move(const char* s) : Move() { read(s); }

	// text
	void        read(const string& s);
	string      getText() const;
	const Move& operator =  (const string& rhs) { read(rhs); return *this; }
	const Move& operator =  (const char* rhs) { read(string(rhs)); return *this; }

	// operators
	bool operator == (const Move& rhs) const { return dest == rhs.dest; }
	bool operator != (const Move& rhs) const { return dest != rhs.dest; }
	bool operator <  (const Move& rhs) const { return dest < rhs.dest; }

private:
	char letterFromPieceType(PieceType pt)     const;
	PieceType pieceTypeFromLetter(char letter) const;

	friend class TestMove;



	Position  source;    // where the move originated from
	Position  dest;      // where the move finished
	PieceType promote;   // piece to be promoted to
	PieceType capture;   // did a capture happen this move?
	MoveType  moveType;  // what type of move is this?
	bool      isWhite;   // whose turn is it anyway?
	string    text;      // what is the textual version of the move?
};