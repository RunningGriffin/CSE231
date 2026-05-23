/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The rook class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"

 /***************************************************
  * ROOK : DISPLAY
  ***************************************************/
void Rook::display(ogstream* pgout) const
{
    pgout->drawRook(position, !fWhite);
}

/***************************************************
 * ROOK : GET MOVES
 * Slide horizontally and vertically
 ***************************************************/
void Rook::getMoves(set<Move>& moves, const Board& board) const
{
    const Delta deltas[] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

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