/***********************************************************************
 * Header File:
 *    BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The BISHOP class
 ************************************************************************/

#pragma once

#include "piece.h"

class TestBishop;

/***************************************************
 * BISHOP
 * The bishop, moves diagonally any number of squares
 ***************************************************/
class Bishop : public Piece
{
	friend TestBishop;
public:
	Bishop(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
	Bishop(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
	~Bishop() {}
	PieceType getType()                         const { return BISHOP; }
	void getMoves(set<Move>& moves, const Board& board) const;
	void display(ogstream* pgout)               const;
};