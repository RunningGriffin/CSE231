/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default
const int OFFSET_BOARD = 50;   // boarder between the board and the edge of screen

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
    int dRow;
    int dCol;
};

const Delta ADD_R = { 1,  0 };
const Delta ADD_C = { 0,  1 };
const Delta SUB_R = { -1,  0 };
const Delta SUB_C = { 0, -1 };


class PositionTest;
class TestKnight;
class TestBoard;
class TestMove;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
    friend class PositionTest;
    friend class TestKnight;
    friend class TestBoard;
    friend class TestMove;
    friend class TestBishop;
    friend class TestRook;
    friend class TestQueen;
    friend class TestKing;
    friend class TestPawn;
    friend class TestSpace;
public:

    // Position :    The Position class can work with other positions,
    //               Allowing for comparisions, copying, etc.
    Position(const Position& rhs) : colRow(rhs.colRow) {}
    Position() : colRow(0xff) {}
    bool isInvalid() const { return (colRow & 0x88) != 0; }
    bool isValid()   const { return !isInvalid(); }
    void setValid() { if (isInvalid()) colRow = 0x00; }
    void setInvalid() { colRow = 0xff; }
    bool operator <  (const Position& rhs) const { return colRow < rhs.colRow; }
    bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
    bool operator != (const Position& rhs) const { return colRow != rhs.colRow; }
    const Position& operator = (const Position& rhs) { colRow = rhs.colRow; return *this; }

    // Location : The Position class can work with locations, which
    //            are 0...63 where we start in row 0, then row 1, etc.
    Position(int location) : colRow(0xff)
    {
        if (location >= 0 && location <= 63)
            colRow = (uint8_t)(((location % 8) << 4) | (location / 8));
    }
    int getLocation() const
    {
        if (isInvalid()) return -1;
        return getRow() * 8 + getCol();
    }
    void setLocation(int location)
    {
        if (location >= 0 && location <= 63)
            colRow = (uint8_t)(((location % 8) << 4) | (location / 8));
        else
            colRow = 0xff;
    }

    // Row/Col : The position class can work with row/column,
    //           which are 0..7 and 0...7
    Position(int c, int r) : colRow(0xff)
    {
        if (c >= 0 && c <= 7 && r >= 0 && r <= 7)
            colRow = (uint8_t)((c << 4) | r);
    }
    virtual int getCol() const { return isInvalid() ? -1 : (int)((colRow & 0xf0) >> 4); }
    virtual int getRow() const { return isInvalid() ? -1 : (int)((colRow & 0x0f) >> 0); }
    void setRow(int r)
    {
        if (r >= 0 && r <= 7)
            colRow = (colRow & 0xf0) | (uint8_t)r;
    }
    void setCol(int c)
    {
        if (c >= 0 && c <= 7)
            colRow = (colRow & 0x0f) | (uint8_t)(c << 4);
    }
    void set(int c, int r)
    {
        if (c >= 0 && c <= 7 && r >= 0 && r <= 7)
            colRow = (uint8_t)((c << 4) | r);
        else
            colRow = 0xff;
    }

    // Text:    The Position class can work with textual coordinates,
    //          such as "d4"
    Position(const char* s) : colRow(0xff)
    {
        if (s && s[0] >= 'a' && s[0] <= 'h' && s[1] >= '1' && s[1] <= '8')
            colRow = (uint8_t)(((s[0] - 'a') << 4) | (s[1] - '1'));
    }
    const Position& operator = (const char* rhs)
    {
        if (rhs && rhs[0] >= 'a' && rhs[0] <= 'h' && rhs[1] >= '1' && rhs[1] <= '8')
            colRow = (uint8_t)(((rhs[0] - 'a') << 4) | (rhs[1] - '1'));
        else
            colRow = 0xff;
        return *this;
    }
    const Position& operator = (const string& rhs)
    {
        if (rhs.size() >= 2 && rhs[0] >= 'a' && rhs[0] <= 'h' && rhs[1] >= '1' && rhs[1] <= '8')
            colRow = (uint8_t)(((rhs[0] - 'a') << 4) | (rhs[1] - '1'));
        else
            colRow = 0xff;
        return *this;
    }


    // Pixels:    The Position class can work with screen coordinates,
    //            a.k.a. Pixels, these are X and Y coordinates. Note that
    //            we need to scale them according to the size of the board.

    int getX()   const
    {
        return (int)((double)getCol() * getSquareWidth() + getSquareWidth());
    }
    int getY()   const
    {
        return (int)((double)getRow() * getSquareHeight() + getSquareHeight());
    }
    void setXY(double x, double y)
    {
        int c = (int)(x / getSquareWidth()) - 1;
        int r = 8 - (int)(y / getSquareHeight());
        bool validC = (c >= 0 && c <= 7);
        bool validR = (r >= 0 && r <= 7);
        if (validC && validR)
            colRow = (uint8_t)((c << 4) | r);
        else if (validC)
            colRow = (uint8_t)((c << 4) | 0x0f);
        else
            colRow = 0xff;
    }
    double getSquareWidth()  const { return squareWidth; }
    double getSquareHeight() const { return squareHeight; }
    void setBoardWidthHeight(int widthBoard, int heightBoard)
    {
        if (widthBoard < 0 || heightBoard < 0)
            return;
        squareWidth = (double)widthBoard / 10.0; // 8 squares + 2 spaces
        squareHeight = (double)heightBoard / 10.0;
    }

    // Delta:    The Position class can work with deltas, which are
    //           offsets from a given location. This helps pieces move
    //           on the chess board.
    Position(const Position& rhs, const Delta& delta) : colRow(0xff)
    {
        if (rhs.isValid())
        {
            int c = rhs.getCol() + delta.dCol;
            int r = rhs.getRow() + delta.dRow;
            if (c >= 0 && c <= 7 && r >= 0 && r <= 7)
                colRow = (uint8_t)((c << 4) | r);
        }
    }
    void adjustRow(int dRow)
    {
        if (isInvalid()) return;
        int r = getRow() + dRow;
        if (r < 0 || r > 7) colRow = 0xff;
        else colRow = (colRow & 0xf0) | (uint8_t)r;
    }
    void adjustCol(int dCol)
    {
        if (isInvalid()) return;
        int c = getCol() + dCol;
        if (c < 0 || c > 7) colRow = 0xff;
        else colRow = (colRow & 0x0f) | (uint8_t)(c << 4);
    }
    const Position& operator += (const Delta& rhs)
    {
        if (isInvalid()) return *this;
        int c = getCol() + rhs.dCol;
        int r = getRow() + rhs.dRow;
        if (c < 0 || c > 7 || r < 0 || r > 7) colRow = 0xff;
        else colRow = (uint8_t)((c << 4) | r);
        return *this;
    }
    Position operator + (const Delta& rhs) const { return Position(*this, rhs); }

private:
    void set(uint8_t colRowNew) { colRow = colRowNew; }

    uint8_t colRow;
    static double squareWidth;
    static double squareHeight;
};


ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);