/***********************************************************************
 * Header File:
 *    TEST MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    test the Move class
 ************************************************************************/

#include "testMove.h"
#include "move.h"
#include <cassert>

/*************************************
 * Constructor : default
 * Input:
 * Output: source=INVALID
 *         dest  =INVALID
 **************************************/
void TestMove::constructor_default()
{
    // SETUP & EXERCISE
    Move move;
    // VERIFY
    assertUnit(move.source.isInvalid());
    assertUnit(move.dest.isInvalid());
    assertUnit(move.promote == INVALID);
    assertUnit(move.capture == INVALID);
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.isWhite == true);
    // TEARDOWN
}

/*************************************
 * CONSTRUCTOR : standard string move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::constructString_simple()
{
    // SETUP & EXERCISE
    Move move("e5e6");
    // VERIFY
    assertUnit(move.source == Position(4, 4));
    assertUnit(move.dest == Position(4, 5));
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.capture == INVALID);
    // TEARDOWN
}

/*************************************
 * CONSTRUCTOR : promotion move
 * Input:  a7a8q
 * Output: source=0,6
 *         dest  =0,7
 *         type  =MOVE
 *         promote=QUEEN
 **************************************/
void TestMove::constructString_promotion()
{
    // SETUP & EXERCISE
    Move move("a7a8q");
    // VERIFY
    assertUnit(move.source == Position(0, 6));
    assertUnit(move.dest == Position(0, 7));
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.promote == QUEEN);
    assertUnit(move.capture == INVALID);
    // TEARDOWN
}

/*************************************
 * READ simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::read_simple()
{
    // SETUP
    Move move;
    // EXERCISE
    move.read("e5e6");
    // VERIFY
    assertUnit(move.source == Position(4, 4));
    assertUnit(move.dest == Position(4, 5));
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.capture == INVALID);
    // TEARDOWN
}

/*************************************
 * READ capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::read_capture()
{
    // SETUP
    Move move;
    // EXERCISE
    move.read("e5d6r");
    // VERIFY
    assertUnit(move.source == Position(4, 4));
    assertUnit(move.dest == Position(3, 5));
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.capture == ROOK);
    // TEARDOWN
}

/*************************************
 * READ enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::read_enpassant()
{
    // SETUP
    Move move;
    // EXERCISE
    move.read("e5f6E");
    // VERIFY
    assertUnit(move.source == Position(4, 4));
    assertUnit(move.dest == Position(5, 5));
    assertUnit(move.moveType == Move::ENPASSANT);
    assertUnit(move.capture == PAWN);
    // TEARDOWN
}

/*************************************
 * READ king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::read_castleKing()
{
    // SETUP
    Move move;
    // EXERCISE
    move.read("e1g1c");
    // VERIFY
    assertUnit(move.source == Position(4, 0));
    assertUnit(move.dest == Position(6, 0));
    assertUnit(move.moveType == Move::CASTLE_KING);
    assertUnit(move.capture == INVALID);
    assertUnit(move.promote == INVALID);
    // TEARDOWN
}

/*************************************
 * READ queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::read_castleQueen()
{
    // SETUP
    Move move;
    // EXERCISE
    move.read("e1c1C");
    // VERIFY
    assertUnit(move.source == Position(4, 0));
    assertUnit(move.dest == Position(2, 0));
    assertUnit(move.moveType == Move::CASTLE_QUEEN);
    assertUnit(move.capture == INVALID);
    assertUnit(move.promote == INVALID);
    // TEARDOWN
}

/*************************************
 * READ promotion move
 * Input:  a7a8q
 * Output: source=0,6
 *         dest  =0,7
 *         type  =MOVE
 *         promote=QUEEN
 **************************************/
void TestMove::read_promotion()
{
    // SETUP
    Move move;
    // EXERCISE
    move.read("a7a8q");
    // VERIFY
    assertUnit(move.source == Position(0, 6));
    assertUnit(move.dest == Position(0, 7));
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.promote == QUEEN);
    assertUnit(move.capture == INVALID);
    // TEARDOWN
}

/*************************************
 * READ promotion with capture
 * Input:  b7c8n
 * Output: source=1,6
 *         dest  =2,7
 *         type  =MOVE
 *         promote=KNIGHT
 **************************************/
void TestMove::read_promotionCapture()
{
    // SETUP
    Move move;
    // EXERCISE
    move.read("b7c8n");
    // VERIFY
    assertUnit(move.source == Position(1, 6));
    assertUnit(move.dest == Position(2, 7));
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.promote == KNIGHT);
    // TEARDOWN
}

/*************************************
 * ASSIGN simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::assign_simple()
{
    // SETUP
    Move move;
    // EXERCISE
    move = "e5e6";
    // VERIFY
    assertUnit(move.source == Position(4, 4));
    assertUnit(move.dest == Position(4, 5));
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.capture == INVALID);
    // TEARDOWN
}

/*************************************
 * ASSIGN capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::assign_capture()
{
    // SETUP
    Move move;
    // EXERCISE
    move = "e5d6r";
    // VERIFY
    assertUnit(move.source == Position(4, 4));
    assertUnit(move.dest == Position(3, 5));
    assertUnit(move.moveType == Move::MOVE);
    assertUnit(move.capture == ROOK);
    // TEARDOWN
}

/*************************************
 * ASSIGN enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::assign_enpassant()
{
    // SETUP
    Move move;
    // EXERCISE
    move = "e5f6E";
    // VERIFY
    assertUnit(move.source == Position(4, 4));
    assertUnit(move.dest == Position(5, 5));
    assertUnit(move.moveType == Move::ENPASSANT);
    assertUnit(move.capture == PAWN);
    // TEARDOWN
}

/*************************************
 * ASSIGN king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::assign_castleKing()
{
    // SETUP
    Move move;
    // EXERCISE
    move = "e1g1c";
    // VERIFY
    assertUnit(move.source == Position(4, 0));
    assertUnit(move.dest == Position(6, 0));
    assertUnit(move.moveType == Move::CASTLE_KING);
    // TEARDOWN
}

/*************************************
 * ASSIGN queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::assign_castleQueen()
{
    // SETUP
    Move move;
    // EXERCISE
    move = "e1c1C";
    // VERIFY
    assertUnit(move.source == Position(4, 0));
    assertUnit(move.dest == Position(2, 0));
    assertUnit(move.moveType == Move::CASTLE_QUEEN);
    // TEARDOWN
}

/*************************************
 * GET TEXT simple move
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 * Output:  e5e6
 **************************************/
void TestMove::getText_simple()
{
    // SETUP
    Move move;
    move.source = Position(4, 4);
    move.dest = Position(4, 5);
    move.moveType = Move::MOVE;
    // EXERCISE
    string text = move.getText();
    // VERIFY
    assertUnit(text == "e5e6");
    // TEARDOWN
}

/*************************************
 * GET TEXT capture
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 *         capture=ROOK
 * Output:  e5e6r
 **************************************/
void TestMove::getText_capture()
{
    // SETUP
    Move move;
    move.source = Position(4, 4);
    move.dest = Position(4, 5);
    move.moveType = Move::MOVE;
    move.capture = ROOK;
    // EXERCISE
    string text = move.getText();
    // VERIFY
    assertUnit(text == "e5e6r");
    // TEARDOWN
}

/*************************************
 * GET TEXT en passant
 * Input : source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 *         capture=PAWN
 * Output:  e5f6E
 **************************************/
void TestMove::getText_enpassant()
{
    // SETUP
    Move move;
    move.source = Position(4, 4);
    move.dest = Position(5, 5);
    move.moveType = Move::ENPASSANT;
    move.capture = PAWN;
    // EXERCISE
    string text = move.getText();
    // VERIFY
    assertUnit(text == "e5f6E");
    // TEARDOWN
}

/*************************************
 * GET TEXT king side castle
 * Input : source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 * Output:  e1g1c
 **************************************/
void TestMove::getText_castleKing()
{
    // SETUP
    Move move;
    move.source = Position(4, 0);
    move.dest = Position(6, 0);
    move.moveType = Move::CASTLE_KING;
    // EXERCISE
    string text = move.getText();
    // VERIFY
    assertUnit(text == "e1g1c");
    // TEARDOWN
}

/*************************************
 * GET TEXT queen side castle
 * Input : source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 * Output:  e1c1C
 **************************************/
void TestMove::getText_castleQueen()
{
    // SETUP
    Move move;
    move.source = Position(4, 0);
    move.dest = Position(2, 0);
    move.moveType = Move::CASTLE_QUEEN;
    // EXERCISE
    string text = move.getText();
    // VERIFY
    assertUnit(text == "e1c1C");
    // TEARDOWN
}

/*************************************
 * GET TEXT promotion
 * Input : source=0,6
 *         dest  =0,7
 *         type  =MOVE
 *         promote=QUEEN
 * Output:  a7a8q
 **************************************/
void TestMove::getText_promotion()
{
    // SETUP
    Move move;
    move.source = Position(0, 6);
    move.dest = Position(0, 7);
    move.moveType = Move::MOVE;
    move.promote = QUEEN;
    // EXERCISE
    string text = move.getText();
    // VERIFY
    assertUnit(text == "a7a8q");
    // TEARDOWN
}

/*************************************
 * LETTER FROM PIECE TYPE space
 * Input :  SPACE
 * Output:  ' '
 **************************************/
void TestMove::letterFromPieceType_space()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.letterFromPieceType(SPACE) == ' ');
    // TEARDOWN
}

/*************************************
 * LETTER FROM PIECE TYPE pawn
 * Input : PAWN
 * Output:  'p'
 **************************************/
void TestMove::letterFromPieceType_pawn()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.letterFromPieceType(PAWN) == 'p');
    // TEARDOWN
}

/*************************************
 * LETTER FROM PIECE TYPE bishop
 * Input : BISHOP
 * Output:  'b'
 **************************************/
void TestMove::letterFromPieceType_bishop()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.letterFromPieceType(BISHOP) == 'b');
    // TEARDOWN
}

/*************************************
 * LETTER FROM PIECE TYPE knight
 * Input : KNIGHT
 * Output:  'n'
 **************************************/
void TestMove::letterFromPieceType_knight()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.letterFromPieceType(KNIGHT) == 'n');
    // TEARDOWN
}

/*************************************
 * LETTER FROM PIECE TYPE rook
 * Input : ROOK
 * Output:  'r'
 **************************************/
void TestMove::letterFromPieceType_rook()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.letterFromPieceType(ROOK) == 'r');
    // TEARDOWN
}

/*************************************
 * LETTER FROM PIECE TYPE queen
 * Input : QUEEN
 * Output:  'q'
 **************************************/
void TestMove::letterFromPieceType_queen()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.letterFromPieceType(QUEEN) == 'q');
    // TEARDOWN
}

/*************************************
 * LETTER FROM PIECE TYPE king
 * Input : KING
 * Output:  'k'
 **************************************/
void TestMove::letterFromPieceType_king()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.letterFromPieceType(KING) == 'k');
    // TEARDOWN
}

/*************************************
 * PIECE TYPE FROM LETTER pawn
 * Input : 'p'
 * Output:  PAWN
 **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.pieceTypeFromLetter('p') == PAWN);
    // TEARDOWN
}

/*************************************
 * PIECE TYPE FROM LETTER bishop
 * Input : 'b'
 * Output:  BISHOP
 **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.pieceTypeFromLetter('b') == BISHOP);
    // TEARDOWN
}

/*************************************
 * PIECE TYPE FROM LETTER knight
 * Input : 'n'
 * Output:  KNIGHT
 **************************************/
void TestMove::pieceTypeFromLetter_knight()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.pieceTypeFromLetter('n') == KNIGHT);
    // TEARDOWN
}

/*************************************
 * PIECE TYPE FROM LETTER rook
 * Input : 'r'
 * Output:  ROOK
 **************************************/
void TestMove::pieceTypeFromLetter_rook()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.pieceTypeFromLetter('r') == ROOK);
    // TEARDOWN
}

/*************************************
 * PIECE TYPE FROM LETTER queen
 * Input : 'q'
 * Output:  QUEEN
 **************************************/
void TestMove::pieceTypeFromLetter_queen()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.pieceTypeFromLetter('q') == QUEEN);
    // TEARDOWN
}

/*************************************
 * PIECE TYPE FROM LETTER king
 * Input : 'k'
 * Output:  KING
 **************************************/
void TestMove::pieceTypeFromLetter_king()
{
    // SETUP
    Move move;
    // EXERCISE & VERIFY
    assertUnit(move.pieceTypeFromLetter('k') == KING);
    // TEARDOWN
}

/*************************************
 * EQUAL - NOT
 * Input : b2b4 == b2b5
 * Output: false
 **************************************/
void TestMove::equal_not()
{
    // SETUP
    Move lhs; lhs.dest = Position(1, 3);  // b4
    Move rhs; rhs.dest = Position(1, 4);  // b5
    // EXERCISE & VERIFY
    assertUnit(!(lhs == rhs));
    // TEARDOWN
}

/*************************************
 * EQUAL - EQUALS
 * Input : b2b4 == b2b4
 * Output: true
 **************************************/
void TestMove::equal_equals()
{
    // SETUP
    Move lhs; lhs.dest = Position(1, 3);  // b4
    Move rhs; rhs.dest = Position(1, 3);  // b4
    // EXERCISE & VERIFY
    assertUnit(lhs == rhs);
    // TEARDOWN
}

/*************************************
 * LESS THAN - LESS THAN
 * Input : b2b2 < b2b4
 * Output: true (according to test implementation)
 *    Note that the less-than operator is needed
 *    so std::set<T> can sort the elements. Thus,
 *    any T in a set must define less-than. In this
 *    case, I defined it according to the
 *     destination's Position's location.
 **************************************/
void TestMove::lessthan_lessthan()
{
    // SETUP
    Move lhs; lhs.dest = Position(1, 1);  // b2
    Move rhs; rhs.dest = Position(1, 3);  // b4
    // EXERCISE & VERIFY
    assertUnit(lhs < rhs);
    // TEARDOWN
}

/*************************************
 * LESS THAN - EQUALS
 * Input : b2b4 < b2b4
 * Output: false
 **************************************/
void TestMove::lessthan_equals()
{
    // SETUP
    Move lhs; lhs.dest = Position(1, 3);  // b4
    Move rhs; rhs.dest = Position(1, 3);  // b4
    // EXERCISE & VERIFY
    assertUnit(!(lhs < rhs));
    // TEARDOWN
}

/*************************************
 * LESS THAN - GREATER THAN
 * Input : b2b4 < b2b2
 * Output: false
 **************************************/
void TestMove::lessthan_greaterthan()
{
    // SETUP
    Move lhs; lhs.dest = Position(1, 3);  // b4
    Move rhs; rhs.dest = Position(1, 1);  // b2
    // EXERCISE & VERIFY
    assertUnit(!(lhs < rhs));
    // TEARDOWN
}
