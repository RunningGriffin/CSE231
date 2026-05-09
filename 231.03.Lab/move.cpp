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

/***************************************************
 * MOVE : LETTER FROM PIECE TYPE
 ***************************************************/
char Move::letterFromPieceType(PieceType pt) const
{
    switch (pt)
    {
    case SPACE:   return ' ';
    case PAWN:    return 'p';
    case BISHOP:  return 'b';
    case KNIGHT:  return 'n';
    case ROOK:    return 'r';
    case QUEEN:   return 'q';
    case KING:    return 'k';
    default:      return '?';
    }
}

/***************************************************
 * MOVE : READ
 * Parse a move string like "e5e6", "e5d6r", "e5f6E",
 * "e1g1c", "e1c1C", "a7a8q"
 ***************************************************/
void Move::read(const string& s)
{
    // reset to defaults
    *this = Move();

    // need at least 4 characters: source (2) + dest (2)
    if (s.size() < 4)
    {
        moveType = MOVE_ERROR;
        return;
    }

    // parse source and dest positions
    source = s.substr(0, 2);
    dest = s.substr(2, 2);

    if (source.isInvalid() || dest.isInvalid())
    {
        moveType = MOVE_ERROR;
        return;
    }

    // parse optional 5th character for move type / capture / promotion
    if (s.size() >= 5)
    {
        char extra = s[4];
        switch (extra)
        {
        case 'E':                              // en passant
            moveType = ENPASSANT;
            capture = PAWN;
            promote = INVALID;
            break;
        case 'c':                              // castle kingside
            moveType = CASTLE_KING;
            capture = INVALID;
            promote = INVALID;
            break;
        case 'C':                              // castle queenside
            moveType = CASTLE_QUEEN;
            capture = INVALID;
            promote = INVALID;
            break;
        default:                              // capture or promotion
            // Check if this is a promotion (pawn moving to last rank)
            // Rank 7 (row 7) for white? Actually row 0 = rank 1, row 7 = rank 8
            // Promotion happens when moving to rank 8 (row 7) or rank 1 (row 0)
            bool isPromotion = false;
            
            // Check if destination is on the last rank (row 7 or row 0)
            if (dest.getRow() == 7 || dest.getRow() == 0)
            {
                // This could be a promotion
                PieceType promoPiece = pieceTypeFromLetter(extra);
                if (promoPiece != INVALID)
                {
                    promote = promoPiece;
                    isPromotion = true;
                }
            }
            
            if (isPromotion)
            {
                // This is a promotion move, not a capture (unless also a capture)
                moveType = MOVE;
                capture = INVALID;
                // promote already set above
            }
            else
            {
                // This is a capture (lowercase piece letter)
                capture = pieceTypeFromLetter(extra);
                moveType = MOVE;
                promote = INVALID;
            }
            break;
        }
    }
    else
    {
        // No 5th character - ensure capture and promote are INVALID
        capture = INVALID;
        promote = INVALID;
    }

    // store the text
    text = s;
}

/***************************************************
 * MOVE : GET TEXT
 * Build the move string from the current state
 ***************************************************/
string Move::getText() const
{
    // source + dest always
    string s;
    s += (char)('a' + source.getCol());
    s += (char)('1' + source.getRow());
    s += (char)('a' + dest.getCol());
    s += (char)('1' + dest.getRow());

    // optional suffix
    switch (moveType)
    {
    case ENPASSANT:   
        s += 'E';  
        break;
    case CASTLE_KING: 
        s += 'c';  
        break;
    case CASTLE_QUEEN:
        s += 'C';  
        break;
    default:
        // For MOVE type, check if there's a promotion first
        if (promote != INVALID && promote != SPACE)
        {
            s += letterFromPieceType(promote);
        }
        else if (capture != INVALID && capture != SPACE)
        {
            s += letterFromPieceType(capture);
        }
        break;
    }

    return s;
}

/***************************************************
 * MOVE : PIECE TYPE FROM LETTER
 ***************************************************/
PieceType Move::pieceTypeFromLetter(char letter) const
{
    switch (letter)
    {
    case 'p':  return PAWN;
    case 'b':  return BISHOP;
    case 'n':  return KNIGHT;
    case 'r':  return ROOK;
    case 'q':  return QUEEN;
    case 'k':  return KING;
    default:   return INVALID;
    }
}
