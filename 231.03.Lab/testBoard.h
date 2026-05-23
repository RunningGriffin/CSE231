/***********************************************************************
 * Header File:
 *    TEST BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for Board
 ************************************************************************/

#pragma once

#include "unitTest.h"

class Board;

/***************************************************
 * BOARD TEST
 * Test the Board class
 ***************************************************/
class TestBoard : public UnitTest
{
public:
    void run()
    {
        // move tests
        move_knightMove();
        move_knightAttack();
        move_pawnSimple();
        move_pawnCapture();
        move_pawnDouble();
        move_pawnEnpassant();
        move_pawnPromotion();
        move_rookSlide();
        move_rookAttack();
        move_bishopSlide();
        move_bishopAttack();
        move_queenSlide();
        move_queenAttack();
        move_kingMove();
        move_kingAttack();
        move_kingShortCastle();
        move_kingLongCastle();
        report("Board");
    }
private:
    void move_knightMove();
    void move_knightAttack();
    void move_pawnSimple();
    void move_pawnCapture();
    void move_pawnDouble();
    void move_pawnEnpassant();
    void move_pawnPromotion();
    void move_rookSlide();
    void move_rookAttack();
    void move_bishopSlide();
    void move_bishopAttack();
    void move_queenSlide();
    void move_queenAttack();
    void move_kingMove();
    void move_kingAttack();
    void move_kingShortCastle();
    void move_kingLongCastle();
};