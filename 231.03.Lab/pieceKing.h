/***********************************************************************
 * Header File:
 *    KING
 * Author:
 *    <your name here>
 * Summary:
 *    The king class
 ************************************************************************/

#pragma once

#include "piece.h"

class TestKing;

/***************************************************
 * KING
 * The king, moves one square in any direction + castling
 ***************************************************/
class King : public Piece
{
	friend TestKing;
public:
	King(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
	King(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
	~King() {}
	PieceType getType()                         const { return KING; }
	void getMoves(set<Move>& moves, const Board& board) const;
	void display(ogstream* pgout)               const;
};