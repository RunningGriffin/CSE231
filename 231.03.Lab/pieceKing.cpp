/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    <your name here>
 * Summary:
 *    The king class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"

 /***************************************************
  * KING : DISPLAY
  ***************************************************/
void King::display(ogstream* pgout) const
{
    pgout->drawKing(position, !fWhite);
}

/***************************************************
 * KING : GET MOVES
 * One step in any direction, plus castling if eligible
 ***************************************************/
void King::getMoves(set<Move>& moves, const Board& board) const
{
    // 8 one-step directions
    const Delta deltas[] =
    {
       {1,0}, {-1,0}, {0,1}, {0,-1},
       {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    for (auto& delta : deltas)
    {
        Position dest(position, delta);
        if (!dest.isValid())
            continue;

        const Piece& target = board[dest];

        // skip squares occupied by a friendly non-space piece
        if (target.getType() != SPACE && target.isWhite() == fWhite)
            continue;

        Move move;
        move.source = position;
        move.dest = dest;
        move.capture = target.getType();
        move.isWhite = fWhite;
        moves.insert(move);
    }

    // castling: king must not have moved
    if (nMoves != 0)
        return;

    int row = fWhite ? 0 : 7;

    // kingside castle: f and g must be empty, rook at h unmoved
    {
        Position f(5, row), g(6, row), h(7, row);
        const Piece& rook = board[h];
        if (rook.getType() == ROOK &&
            rook.isWhite() == fWhite &&
            rook.getNMoves() == 0 &&
            board[f].getType() == SPACE &&
            board[g].getType() == SPACE)
        {
            Move move;
            move.source = position;
            move.dest = g;
            move.capture = SPACE;
            move.isWhite = fWhite;
            move.moveType = Move::CASTLE_KING;
            moves.insert(move);
        }
    }

    // queenside castle: b, c, d must be empty, rook at a unmoved
    {
        Position b(1, row), c(2, row), d(3, row), a(0, row);
        const Piece& rook = board[a];
        if (rook.getType() == ROOK &&
            rook.isWhite() == fWhite &&
            rook.getNMoves() == 0 &&
            board[b].getType() == SPACE &&
            board[c].getType() == SPACE &&
            board[d].getType() == SPACE)
        {
            Move move;
            move.source = position;
            move.dest = c;
            move.capture = SPACE;
            move.isWhite = fWhite;
            move.moveType = Move::CASTLE_QUEEN;
            moves.insert(move);
        }
    }
}