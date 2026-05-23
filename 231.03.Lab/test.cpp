/***********************************************************************
 * Source File:
 *    TEST
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPiece.h"
#include "testSpace.h"
#include "testPawn.h"
#include "testKnight.h"
#include "testBishop.h"
#include "testRook.h"
#include "testQueen.h"
#include "testKing.h"
#include "testPosition.h"
#include "testBoard.h"
#include "testMove.h"

#ifdef _WIN32
#include <windows.h>
#include <iostream>
using namespace std;
#endif

#include "piece.h"        // for PIECE and company


// useful if we want to use the spy double to test our chess class. See Chapter 3.4
int PieceSpy::numConstruct = 0;
int PieceSpy::numCopy = 0;
int PieceSpy::numDelete = 0;
int PieceSpy::numAssign = 0;
int PieceSpy::numMove = 0;

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
#ifdef _WIN32
	AllocConsole();
	FILE* stream;
	errno_t err;
	err = freopen_s(&stream, "CONOUT$", "a", stdout);
#endif // _WIN32

	// Lab 03
	PositionTest().run();
	TestMove().run();
	TestBoard().run();

	// Lab 04
	TestPiece().run();
	TestSpace().run();
	TestKnight().run();

	// Lab 05
	//TestPawn().run();      
	//TestQueen().run();
	//TestRook().run();
	//TestBishop().run();
	//TestKing().run();
}