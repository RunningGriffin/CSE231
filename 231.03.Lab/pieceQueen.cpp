/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The queen class
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"

 /***************************************************
  * QUEEN : DISPLAY
  ***************************************************/
void Queen::display(ogstream* pgout) const
{
    pgout->drawQueen(position, !fWhite);
}

/***************************************************
 * QUEEN : GET MOVES
 * Slides in all 8 directions (rook + bishop combined)
 ***************************************************/
void Queen::getMoves(set<Move>& moves, const Board& board) const
{
    const Delta deltas[] =
    {
       {1,0}, {-1,0}, {0,1}, {0,-1},    // rook directions
       {1,1}, {1,-1}, {-1,1}, {-1,-1}   // bishop directions
    };

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