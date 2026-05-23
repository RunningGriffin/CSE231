/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The pawn class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"

 /***************************************************
  * PAWN : DISPLAY
  ***************************************************/
void Pawn::display(ogstream* pgout) const
{
    pgout->drawPawn(position, !fWhite);
}

/***************************************************
 * PAWN : GET MOVES
 ***************************************************/
void Pawn::getMoves(set<Move>& moves, const Board& board) const
{
    int col = position.getCol();
    int row = position.getRow();
    int dir = fWhite ? 1 : -1;       // white moves up, black moves down
    int startRow = fWhite ? 1 : 6;        // row where double-advance is allowed
    int promoRow = fWhite ? 7 : 0;        // back rank after the move

    // --- simple forward move ---
    Position fwd(col, row + dir);
    if (fwd.isValid() && board[fwd].getType() == SPACE)
    {
        if (fwd.getRow() == promoRow)
        {
            // promotion
            Move move;
            move.source = position;
            move.dest = fwd;
            move.capture = SPACE;
            move.isWhite = fWhite;
            move.promote = QUEEN;
            moves.insert(move);
        }
        else
        {
            Move move;
            move.source = position;
            move.dest = fwd;
            move.capture = SPACE;
            move.isWhite = fWhite;
            moves.insert(move);

            // initial double-advance (only if the square beyond is also empty)
            if (row == startRow)
            {
                Position fwd2(col, row + 2 * dir);
                if (fwd2.isValid() && board[fwd2].getType() == SPACE)
                {
                    Move m2;
                    m2.source = position;
                    m2.dest = fwd2;
                    m2.capture = SPACE;
                    m2.isWhite = fWhite;
                    moves.insert(m2);
                }
            }
        }
    }

    // --- diagonal captures ---
    for (int dc : {-1, 1})
    {
        Position diag(col + dc, row + dir);
        if (!diag.isValid())
            continue;

        const Piece& target = board[diag];
        if (target.getType() != SPACE && target.isWhite() != fWhite)
        {
            Move move;
            move.source = position;
            move.dest = diag;
            move.capture = target.getType();
            move.isWhite = fWhite;
            if (diag.getRow() == promoRow)
                move.promote = QUEEN;
            moves.insert(move);
        }
    }

    // --- en passant ---
    // White captures from row 4 (index), black from row 3
    int epRow = fWhite ? 4 : 3;
    if (row == epRow)
    {
        for (int dc : {-1, 1})
        {
            Position adjPos(col + dc, row);
            if (!adjPos.isValid())
                continue;

            const Piece& adj = board[adjPos];
            // adjacent pawn must be enemy and have just moved last turn
            if (adj.getType() == PAWN &&
                adj.isWhite() != fWhite &&
                adj.justMoved(board.getCurrentMove()))
            {
                Position epDest(col + dc, row + dir);
                if (epDest.isValid())
                {
                    Move move;
                    move.source = position;
                    move.dest = epDest;
                    move.capture = PAWN;
                    move.isWhite = fWhite;
                    move.moveType = Move::ENPASSANT;
                    moves.insert(move);
                }
            }
        }
    }
}