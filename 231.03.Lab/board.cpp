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
#include <cassert>
using namespace std;


/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
    // free everything if requested
    if (fFree)
        free();

    // initialize all squares to nullptr
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;

    // place white knights at b1 (col=1,row=0) and g1 (col=6,row=0)
    board[1][0] = new Knight(1, 0, true  /*white*/);
    board[6][0] = new Knight(6, 0, true  /*white*/);

    // place black knights at b8 (col=1,row=7) and g8 (col=6,row=7)
    board[1][7] = new Knight(1, 7, false /*black*/);
    board[6][7] = new Knight(6, 7, false /*black*/);
}

// we really REALLY need to delete this.
Space space(0, 0);

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
    return space;
}
Piece& Board::operator [] (const Position& pos)
{
    return space;
}

/***********************************************
* BOARD : DISPLAY
*         Display the board
***********************************************/
void Board::display(const Position& posHover, const Position& posSelect) const
{
    // draw the board itself
    pgout->drawBoard();

    // draw hover and select highlights if valid
    if (posHover.isValid())
        pgout->drawHover(posHover);
    if (posSelect.isValid())
        pgout->drawSelected(posSelect);

    // draw each piece on the board
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[c][r] != nullptr)
                board[c][r]->display(pgout);
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
    // initialize all squares to nullptr first
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;

    if (!noreset)
        reset(false /*fFree - already null*/);
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
        {
            delete board[c][r];
            board[c][r] = nullptr;
        }
}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{

}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move& move)
{
    // get source and dest positions
    int sc = move.source.getCol();
    int sr = move.source.getRow();
    int dc = move.dest.getCol();
    int dr = move.dest.getRow();

    assert(board[sc][sr] != nullptr);

    // update the moving piece's position and move count
    board[sc][sr]->position = move.dest;
    board[sc][sr]->setLastMove(numMoves);

    // move the pointer: dest gets the piece, source gets a new space
    board[dc][dr] = board[sc][sr];
    board[sc][sr] = new Space(sc, sr);

    // advance the move counter
    numMoves++;
}



/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
    pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty()
{
    delete pSpace;
}