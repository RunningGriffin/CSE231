/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The knight class
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Knight::display(ogstream* pgout) const
{
    pgout->drawKnight(position, !fWhite);
}


/**********************************************
 * KNIGHT : GET MOVES
 * All 8 possible L-shaped moves
 *********************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
{
    // all 8 knight deltas {dRow, dCol}
    const Delta deltas[] =
    {
       {-2, -1}, {-2,  1},
       {-1, -2}, {-1,  2},
       { 1, -2}, { 1,  2},
       { 2, -1}, { 2,  1}
    };

    for (const Delta& delta : deltas)
    {
        Position dest(position, delta);

        // skip off-board squares
        if (dest.isInvalid())
            continue;

        // get what's on the dest square
        const Piece& target = board[dest];

        // skip only if occupied by a friendly non-space piece
        if (target.getType() != SPACE && target.isWhite() == fWhite)
            continue;

        // build the move
        Move move;
        move.source = position;
        move.dest = dest;
        move.capture = target.getType();
        move.isWhite = fWhite;

        moves.insert(move);
    }
}