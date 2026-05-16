/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move() : promote(INVALID), capture(INVALID), moveType(MOVE), isWhite(true)
{
    source.setInvalid();
    dest.setInvalid();
}

void Move::read(const string& s)
{
    *this = Move();
    if (s.size() < 4) { moveType = MOVE_ERROR; return; }
    source = s.substr(0, 2);
    dest = s.substr(2, 2);
    if (source.isInvalid() || dest.isInvalid()) { moveType = MOVE_ERROR; return; }
    if (s.size() >= 5)
    {
        char extra = s[4];
        switch (extra)
        {
        case 'E': moveType = ENPASSANT;    capture = PAWN; break;
        case 'c': moveType = CASTLE_KING;                  break;
        case 'C': moveType = CASTLE_QUEEN;                 break;
        default:  capture = pieceTypeFromLetter(extra);    break;
        }
    }
    text = s;
}

string Move::getText() const
{
    string s;
    s += (char)('a' + source.getCol());
    s += (char)('1' + source.getRow());
    s += (char)('a' + dest.getCol());
    s += (char)('1' + dest.getRow());
    switch (moveType)
    {
    case ENPASSANT:    s += 'E'; break;
    case CASTLE_KING:  s += 'c'; break;
    case CASTLE_QUEEN: s += 'C'; break;
    default:
        if (capture != INVALID && capture != SPACE)
            s += letterFromPieceType(capture);
        break;
    }
    return s;
}

char Move::letterFromPieceType(PieceType pt) const
{
    switch (pt)
    {
    case SPACE:  return ' ';
    case PAWN:   return 'p';
    case BISHOP: return 'b';
    case KNIGHT: return 'n';
    case ROOK:   return 'r';
    case QUEEN:  return 'q';
    case KING:   return 'k';
    default:     return '?';
    }
}

PieceType Move::pieceTypeFromLetter(char letter) const
{
    switch (letter)
    {
    case 'p': return PAWN;
    case 'b': return BISHOP;
    case 'n': return KNIGHT;
    case 'r': return ROOK;
    case 'q': return QUEEN;
    case 'k': return KING;
    default:  return INVALID;
    }
}