/***********************************************************************
 * Header File:
 *    QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The queen class
 ************************************************************************/

#pragma once

#include "piece.h"

class TestQueen;

/***************************************************
 * QUEEN
 * The queen, slides in all 8 directions
 ***************************************************/
class Queen : public Piece
{
	friend TestQueen;
public:
	Queen(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
	Queen(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
	~Queen() {}
	PieceType getType()                         const { return QUEEN; }
	void getMoves(set<Move>& moves, const Board& board) const;
	void display(ogstream* pgout)               const;
};