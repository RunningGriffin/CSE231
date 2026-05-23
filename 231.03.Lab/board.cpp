/***********************************************************************
 * Source File:
 *    BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "pieceBishop.h"
#include "pieceRook.h"
#include "pieceQueen.h"
#include "pieceKing.h"
#include "piecePawn.h"
#include <cassert>
using namespace std;

/***********************************************
 * BOARD : RESET
 *         Place all 32 pieces in starting positions
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8   R N B Q K B N R   8
 *   7   P P P P P P P P   7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2   p p p p p p p p   2
 *   1   r n b q k b n r   1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
    if (fFree)
        free();

    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;

    // white pieces (row 0 = rank 1)
    board[0][0] = new Rook(0, 0, true);
    board[1][0] = new Knight(1, 0, true);
    board[2][0] = new Bishop(2, 0, true);
    board[3][0] = new Queen(3, 0, true);
    board[4][0] = new King(4, 0, true);
    board[5][0] = new Bishop(5, 0, true);
    board[6][0] = new Knight(6, 0, true);
    board[7][0] = new Rook(7, 0, true);
    for (int c = 0; c < 8; c++)
        board[c][1] = new Pawn(c, 1, true);

    // empty middle rows
    for (int r = 2; r <= 5; r++)
        for (int c = 0; c < 8; c++)
            board[c][r] = new Space(c, r);

    // black pieces (row 7 = rank 8)
    board[0][7] = new Rook(0, 7, false);
    board[1][7] = new Knight(1, 7, false);
    board[2][7] = new Bishop(2, 7, false);
    board[3][7] = new Queen(3, 7, false);
    board[4][7] = new King(4, 7, false);
    board[5][7] = new Bishop(5, 7, false);
    board[6][7] = new Knight(6, 7, false);
    board[7][7] = new Rook(7, 7, false);
    for (int c = 0; c < 8; c++)
        board[c][6] = new Pawn(c, 6, false);
}

/***********************************************
 * BOARD : OPERATOR []
 ***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
    return *(board[pos.getCol()][pos.getRow()]);
}
Piece& Board::operator [] (const Position& pos)
{
    return *(board[pos.getCol()][pos.getRow()]);
}

/***********************************************
 * BOARD : DISPLAY
 ***********************************************/
void Board::display(const Position& posHover, const Position& posSelect) const
{
    pgout->drawBoard();
    if (posHover.isValid())  pgout->drawHover(posHover);
    if (posSelect.isValid()) pgout->drawSelected(posSelect);
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[c][r] != nullptr)
                board[c][r]->display(pgout);
}

/***********************************************
 * BOARD : CONSTRUCT
 ***********************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;
    if (!noreset)
        reset(false);
}

/***********************************************
 * BOARD : FREE
 ***********************************************/
void Board::free()
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
        {
            delete board[c][r];
            board[c][r] = nullptr;
        }
}

/***********************************************
 * BOARD : ASSERT BOARD
 ***********************************************/
void Board::assertBoard() {}

/***********************************************
 * BOARD : MOVE
 *         Execute a move according to the instructions.
 *         Handles: normal, capture, en passant, castling, promotion
 ***********************************************/
void Board::move(const Move& move)
{
    int sc = move.source.getCol();
    int sr = move.source.getRow();
    int dc = move.dest.getCol();
    int dr = move.dest.getRow();

    assert(board[sc][sr] != nullptr);

    // update moving piece state
    board[sc][sr]->position = move.dest;
    board[sc][sr]->setLastMove(numMoves);

    switch (move.moveType)
    {
    case Move::CASTLE_KING:
    {
        // king moves sc->dc (e->g), rook moves h->f
        board[dc][dr] = board[sc][sr];
        board[sc][sr] = new Space(sc, sr);
        // move rook from h to f (same row)
        board[7][sr]->position = Position(5, sr);
        board[7][sr]->setLastMove(numMoves);
        board[5][sr] = board[7][sr];
        board[7][sr] = new Space(7, sr);
        break;
    }
    case Move::CASTLE_QUEEN:
    {
        // king moves sc->dc (e->c), rook moves a->d
        board[dc][dr] = board[sc][sr];
        board[sc][sr] = new Space(sc, sr);
        // move rook from a to d (same row)
        board[0][sr]->position = Position(3, sr);
        board[0][sr]->setLastMove(numMoves);
        board[3][sr] = board[0][sr];
        board[0][sr] = new Space(0, sr);
        break;
    }
    case Move::ENPASSANT:
    {
        // pawn moves diagonally to empty square, captured pawn beside source
        board[dc][dr] = board[sc][sr];
        board[sc][sr] = new Space(sc, sr);
        // captured pawn is at same row as source, dest column
        board[dc][sr] = new Space(dc, sr);
        break;
    }
    default:
    {
        // promotion: replace pawn with new piece at dest
        if (move.promote != INVALID && move.promote != SPACE)
        {
            bool white = board[sc][sr]->isWhite();
            board[sc][sr] = new Space(sc, sr);
            switch (move.promote)
            {
            case QUEEN:  board[dc][dr] = new Queen(dc, dr, white); break;
            case ROOK:   board[dc][dr] = new Rook(dc, dr, white); break;
            case BISHOP: board[dc][dr] = new Bishop(dc, dr, white); break;
            case KNIGHT: board[dc][dr] = new Knight(dc, dr, white); break;
            default:     board[dc][dr] = new Space(dc, dr);        break;
            }
        }
        else
        {
            // normal move or capture — just move the pointer
            board[dc][dr] = board[sc][sr];
            board[sc][sr] = new Space(sc, sr);
        }
        break;
    }
    }

    numMoves++;
}

/***********************************************
 * BOARD EMPTY : CONSTRUCT / DESTRUCT
 ***********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
    pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty()
{
    delete pSpace;
}