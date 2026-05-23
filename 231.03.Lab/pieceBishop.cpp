/***********************************************************************
 * Source File:
 *    BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The bishop class
 ************************************************************************/

#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"

 /***************************************************
  * BISHOP : DISPLAY
  ***************************************************/
void Bishop::display(ogstream* pgout) const
{
    pgout->drawBishop(position, !fWhite);
}

/***************************************************
 * BISHOP : GET MOVES
 * Slide diagonally in all 4 directions
 ***************************************************/
void Bishop::getMoves(set<Move>& moves, const Board& board) const
{
    const Delta deltas[] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };

    for (auto& delta : deltas)
    {
        Position dest(position, delta);
        while (dest.isValid())
        {
            const Piece& target = board[dest];

            // blocked by friendly piece - stop, don't add
            if (target.getType() != SPACE && target.isWhite() == fWhite)
                break;

            // add the move
            Move move;
            move.source = position;
            move.dest = dest;
            move.capture = target.getType();
            move.isWhite = fWhite;
            moves.insert(move);

            // captured an enemy - stop after adding
            if (target.getType() != SPACE)
                break;

            dest += delta;
        }
    }
}