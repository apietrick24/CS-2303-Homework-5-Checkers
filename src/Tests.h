/*
 * Tests.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#ifndef TESTS_H_
#define TESTS_H_
#include "Production.h"
#include <stdio.h>


class Tests {
public:
	Tests();
	virtual ~Tests();
	bool tests();

private:
	//Game Piece Tests
	bool testGamePieceStructure();
	bool testGamePieceToChar();

	//Board Test
	bool testBoardInit(); //Reading File
	bool testBoardDisplay();
	bool testBoardFileWriting();
	bool testComputeMoves();
	bool testIsMoveValid();
	bool testExecuteGivenMove();
	bool testPromote();
	bool testHasWon();
	bool testGetGamePiece();

	//LinkedList Test
	bool testLinkedListInit();
	bool testEnqueue();
	bool testDequeue();
	bool testComplicatedDequeue();
	bool testPrintSimpleList();

	//Test helper
	bool getYesNo(char* query);
};

#endif /* TESTS_H_ */
