/*
 * Tests.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Tests.h"
#include <stdbool.h>
#include "GamePiece.h"
#include "LinkedList.h"
#include "Board.h"

Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::tests(){
	printf("Starting Tests\n\n");
	bool answer = true;

	/*bool ok1 = testReadFile();
	bool ok2 = testFileOutput();
	bool ok3 = testMakeLList();
	bool ok4 = testEnqueue();
	//pedagogical bool ok5 = testRemoveFromList();
	bool ok6 = testPrintHistory();
	answer = ok1 && ok3 && ok4  && ok6;*/

	bool test1 = testGamePieceStructure();
	bool test2 = testGamePieceToChar();
	bool test3 = testBoardInit();
	bool test4 = testBoardDisplay();
	bool test5 = testBoardFileWriting();
	bool test6 = testComputeMoves();
	bool test7 = testIsMoveValid();
	bool test8 = testExecuteGivenMove();
	bool test9 = testPromote();
	bool test10 = testHasWon();
	bool test11 = testGetGamePiece();
	bool test12 = testLinkedListInit();
	bool test13 = testEnqueue();
	bool test14 = testDequeue();
	bool test15 = testComplicatedDequeue();
	bool test16 = testPrintSimpleList();
	answer = test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8 && test9 && test10 && test11 && test12 && test13 && test14 && test15 && test16;

	if (answer){
		printf("All Tests Passed: program is ready to be run\n\n");
	} else {
		printf("At least one test didn't pass: program will not be run\n\n");
	}
	return answer;
}

//Game Piece Tests
bool Tests::testGamePieceStructure(){
	printf("Starting testGamePieceStructure (testing Game Piece's Setters and Getters)\n");
	bool testPasses = true;
	GamePiece* testPiece = new GamePiece(false, true, true, 0, 0);

	//Testing Getters
	if (testPiece->isEmpty() != false || testPiece->isRed() != true || testPiece->isKing() != true || testPiece->getCol() != 0 || testPiece->getRow() != 0){
		testPasses = false;
		printf("\tfailed testGamePieceGetters subtest\n");
	} else {
		printf("\tpassed testGamePieceGetters subtest\n");
	}

	testPiece->setEmpty(true);
	testPiece->setRed(false);
	testPiece->setKing(false);
	testPiece->setRow(3);
	testPiece->setCol(3);

	if (testPiece->isEmpty() == false || testPiece->isRed() == true || testPiece->isKing() == true || testPiece->getCol() == 0 || testPiece->getRow() == 0){
		testPasses = false;
		printf("\tfailed testGamePieceSetters subtest\n");
	} else {
		printf("\tpassed testGamePieceSetters subtest\n");
	}

	if (testPasses){
		printf("testGamePieceStructure Passed: successful passed all subtests\n");
	} else {
		printf("testGamePieceStructure Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}

bool Tests::testGamePieceToChar(){
	printf("Starting testGamePieceToChar\n");
	bool testPasses = true;

	if ((new GamePiece(true, true, false, 0, 0))->toChar() != '-'){
		testPasses = false;
		printf("\tfailed testGamePieceToCharEmptyRed subtest\n");
	} else {
		printf("\tpassed testGamePieceToCharEmptyRed subtest\n");
	}

	if ((new GamePiece(true, false, false, 0, 0))->toChar() != '-'){
		testPasses = false;
		printf("\tfailed testGamePieceToCharEmptyBlack subtest\n");
	} else {
		printf("\tpassed testGamePieceToCharEmptyBlack subtest\n");
	}

	if ((new GamePiece(false, true, false, 0, 0))->toChar() != 'r'){
		testPasses = false;
		printf("\tfailed testGamePieceToCharRedChecker subtest\n");
	} else {
		printf("\tpassed testGamePieceToCharRedChecker subtest\n");
	}

	if ((new GamePiece(false, true, true, 0, 0))->toChar() != 'R'){
		testPasses = false;
		printf("\tfailed testGamePieceToCharRedKingChecker subtest\n");
	} else {
		printf("\tpassed testGamePieceToCharRedKingChecker subtest\n");
	}

	if ((new GamePiece(false, false, false, 0, 0))->toChar() != 'b'){
		testPasses = false;
		printf("\tfailed testGamePieceToCharBlackChecker subtest\n");
	} else {
		printf("\tpassed testGamePieceToCharBlackChecker subtest\n");
	}

	if ((new GamePiece(false, false, true, 0, 0))->toChar() != 'B'){
		testPasses = false;
		printf("\tfailed testGamePieceToCharBlackKingChecker subtest\n");
	} else {
		printf("\tpassed testGamePieceToCharBlackKingChecker subtest\n");
	}

	if (testPasses){
		printf("testGamePieceToChar Passed: successful passed all subtests\n");
	} else {
		printf("testGamePieceToChar Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;

}

//Board Test
bool Tests::testBoardInit(){
	printf("Starting testBoardInit (testing Reading File and Board Init)\n");
	bool testPasses = true;
	Board* theBoard = new Board("testingGame1.txt", "testGame1WriteFile.txt");
	theBoard->displayBoard();

	if (theBoard->getGamePiece(0, 4)->toChar() != 'b' && theBoard->getGamePiece(1, 1)->toChar() != 'b' && theBoard->getGamePiece(2, 2)->toChar() != 'b'){
		testPasses = false;
		printf("\tfailed testBoardInitBlack subtest\n");
	} else {
		printf("\tpassed testBoardInitBlack subtest\n");
	}

	if (theBoard->getGamePiece(3, 1)->toChar() != 'R' && theBoard->getGamePiece(4, 2)->toChar() != 'r' && theBoard->getGamePiece(4, 4)->toChar() != 'r'){
		testPasses = false;
		printf("\tfailed testBoardInitRed subtest\n");
	} else {
		printf("\tpassed testBoardInitRed subtest\n");
	}

	if (testPasses){
		printf("testBoardInit Passed: successful passed all subtests\n");
	} else {
		printf("testBoardInit Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;


} //Reading File
bool Tests::testBoardDisplay(){
	printf("Starting testBoardDisplay\n");
	bool testPasses = true;

	Board* theBoard = new Board("testingGame1.txt", "testGame1WriteFile.txt");

	theBoard->displayBoard();

	if(!getYesNo("Given the board in the file \"testingGame1.txt\", is the lines above an accurate representation of it?")){
		testPasses = false;
		printf("\tfailed testBoardDisplay1 subtest\n");
	} else {
		printf("\tpassed testBoardDisplay1 subtest\n");
	}

	printf("\n");

	Board* theBoard2 = new Board("testingGame2.txt", "testGame1WriteFile.txt");

	theBoard2->displayBoard();

	if(!getYesNo("Given the board in the file \"testingGame2.txt\", is the lines above an accurate representation of it?")){
		testPasses = false;
		printf("\tfailed testBoardDisplay1 subtest\n");
	} else {
		printf("\tpassed testBoardDisplay1 subtest\n");
	}

	printf("\n");

	if (testPasses){
		printf("testBoardDisplay Passed: successful passed all subtests\n");
	} else {
		printf("testBoardDisplay Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}
bool Tests::testBoardFileWriting(){
	printf("Starting testBoardFileWriting\n");
	bool pass = true;

	std::ofstream fp;
	fp.open ("testOutputFile.txt", std::ios::out | std::ios::trunc);
	fp.clear();
	fp << "Write";
	fp.close();

	char store [15];

	FILE* fp2 = fopen("testOutputFile.txt", "r"); //read the file
	fscanf(fp2, "%s", store);

	if (strcmp("Write", store) != 0){

		pass = false;
		printf("\tfailed testBoardFileWritingBasic subtest\n");
	} else {
		printf("\tpassed testBoardFileWritingBasic subtest\n");
	}

	fclose(fp2);

	std::ofstream fp3;
	fp3.open ("testOutputFile.txt", std::ios::out | std::ios::trunc);
	fp3.clear();
	fp3.close();

	FILE* fp4 = fopen("testOutputFile.txt", "r"); //read the file
	fscanf(fp4, "%s", store);

	if (strcmp("Write", store) != 0){

		pass = false;
		printf("\tfailed testBoardFileWritingAdvance subtest\n");
	} else {
		printf("\tpassed testBoardFileWritingAdvance subtest\n");
	}

	fclose(fp4);

	if (!pass){
		printf("testBoardFileWriting Failed: not all subtests passed\n");
	} else {
		printf("testBoardFileWriting Passed: successful passed all subtests\n");
	}

	printf("\n");

	return pass;
}
bool Tests::testComputeMoves(){
	printf("Starting testComputeMoves\n");
	bool testPasses = true;

	Board* theBoard = new Board("testingGame1.txt", "testGame1WriteFile.txt");

	if(!theBoard->computerMove(true, false, false)){
		testPasses = false;
		printf("\tfailed testComputeMoves1Red(Move) subtest\n");
	} else {
		printf("\tpassed testComputeMoves1Red(Move) subtest\n");
	}


	if(!theBoard->computerMove(false, false, false)){
		testPasses = false;
		printf("\tfailed testComputeMoves1Black(Move) subtest\n");
	} else {
		printf("\tpassed testComputeMoves1Black(Move) subtest\n");
	}

	Board* theBoard2 = new Board("testingGame2.txt", "testGame1WriteFile.txt");

	if(theBoard2->computerMove(true, false, false)){
		testPasses = false;
		printf("\tfailed testComputeMoves2Red(No Move) subtest\n");
	} else {
		printf("\tpassed testComputeMoves2Red(No Move) subtest\n");
	}

	if(theBoard2->computerMove(false, false, false)){
		testPasses = false;
		printf("\tfailed testComputeMoves2Black(No Move) subtest\n");
	} else {
		printf("\tpassed testComputeMoves2Black(No Move) subtest\n");
	}

	if (testPasses){
		printf("testComputeMoves Passed: successful passed all subtests\n");
	} else {
		printf("testComputeMoves Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;

}
bool Tests::testIsMoveValid(){
	printf("Starting testIsMoveValid\n");

	Board* theBoard = new Board("testingGame1.txt", "testGame1WriteFile.txt");

	bool testPasses = true;


	if(!theBoard->isMoveValid(2, 2, 4, 0)){
		testPasses = false;
		printf("\tfailed testValidJump subtest\n");
	} else {
		printf("\tpassed testValidJump subtest\n");
	}

	if(theBoard->isMoveValid(2, 2, 4, 4)){
		testPasses = false;
		printf("\tfailed testNonValidJump subtest\n");
	} else {
		printf("\tpassed testNonValidJump subtest\n");
	}

	if(!theBoard->isMoveValid(3, 1, 2, 0)){
		testPasses = false;
		printf("\tfailed testValidNonJump subtest\n");
	} else {
		printf("\tpassed testValidNonJump subtest\n");
	}

	if(theBoard->isMoveValid(2, 2, 3, 1)){
		testPasses = false;
		printf("\tfailed testNonValidNonJump subtest\n");
	} else {
		printf("\tpassed testNonValidNonJump subtest\n");
	}

	if (testPasses){
		printf("testIsMoveValid Passed: successful passed all subtests\n");
	} else {
		printf("testIsMoveValid Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}

bool Tests::testExecuteGivenMove(){
	printf("Starting testExecuteGivenMove\n");

	Board* theBoard = new Board("testingGame1.txt", "testGame1WriteFile.txt");

	bool testPasses = true;

	theBoard->executeGivenMove(3, 1, 1, 3);

	if (theBoard->getGamePiece(3, 1)->toChar() != '-' || theBoard->getGamePiece(2, 2)->toChar() != '-' || theBoard->getGamePiece(1, 3)->toChar() != 'R'){
		testPasses = false;
		printf("\tfailed testExecuteGivenJumpMove subtest\n");
	} else {
		printf("\tpassed testExecuteGivenJumpMove subtest\n");
	}

	theBoard->executeGivenMove(1, 1, 2, 0);

	if (theBoard->getGamePiece(1, 1)->toChar() != '-' || theBoard->getGamePiece(2, 0)->toChar() != 'b'){
		testPasses = false;
		printf("\tfailed testExecuteGivenNonJumpMove subtest\n");
	} else {
		printf("\tpassed testExecuteGivenNonJumpMove subtest\n");
	}

	if (testPasses){
		printf("testExecuteGivenMove Passed: successful passed all subtests\n");
	} else {
		printf("testExecuteGivenMove Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}

bool Tests::testPromote(){
	printf("Starting testPromote\n");

	Board* theBoard = new Board("testingGame2.txt", "testGame1WriteFile.txt");

	bool testPasses = true;

	theBoard->promote();

	if (theBoard->getGamePiece(2, 0)->toChar() != 'B' || theBoard->getGamePiece(2, 2)->toChar() != 'B'){
		testPasses = false;
		printf("\tfailed testPromoteBlack subtest\n");
	} else {
		printf("\tpassed testPromoteBlack subtest\n");
	}

	if (theBoard->getGamePiece(1, 1)->toChar() != 'r'){
		testPasses = false;
		printf("\tfailed testPromoteRed subtest\n");
	} else {
		printf("\tpassed testPromoteRed subtest\n");
	}

	if (testPasses){
		printf("testPromote Passed: successful passed all subtests\n");
	} else {
		printf("testPromote Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}
bool Tests::testHasWon(){
	printf("Starting testHasWon\n");

	Board* theBoard = new Board("gameState.txt", "testGame1WriteFile.txt");

	bool testPasses = true;

	if (theBoard->hasBlackWon()){
		testPasses = false;
		printf("\tfailed testHasBlackWonNo subtest\n");
	} else {
		printf("\tpassed testHasBlackWonNo subtest\n");
	}

	if (theBoard->hasRedWon()){
		testPasses = false;
		printf("\tfailed testHasRedWonNo subtest\n");
	} else {
		printf("\tpassed testHasRedWonNo subtest\n");
	}

	theBoard->executeGivenMove(7, 5, 5, 7);

	if (!theBoard->hasBlackWon()){
		testPasses = false;
		printf("\tfailed testHasBlackWonYes subtest\n");
	} else {
		printf("\tpassed testHasBlackWonYes subtest\n");
	}

	if (theBoard->hasRedWon()){
		testPasses = false;
		printf("\tfailed testHasRedWonStillNo subtest\n");
	} else {
		printf("\tpassed testHasRedWonStillNo subtest\n");
	}

	if (testPasses){
		printf("testHasWon Passed: successful passed all subtests\n");
	} else {
		printf("testHasWon Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}
bool Tests::testGetGamePiece(){
	printf("Starting testGetGamePiece\n");

	Board* theBoard = new Board("testingGame2.txt", "testGame1WriteFile.txt");

	bool testPasses = true;

	theBoard->promote();

	GamePiece* currentPiece = theBoard->getGamePiece(1, 1);

	if (currentPiece->isEmpty() || !currentPiece->isRed() || currentPiece->isKing()){
		testPasses = false;
		printf("\tfailed testGetGamePieceRedNonKing subtest\n");
	} else {
		printf("\tpassed testGetGamePieceRedNonKing subtest\n");
	}

	currentPiece->setKing(true);

	currentPiece = theBoard->getGamePiece(0,0);

	if (currentPiece->isEmpty() || currentPiece->isRed() || currentPiece->isKing()){
		testPasses = false;
		printf("\tfailed testGetGamePieceBlackNonKing subtest\n");
	} else {
		printf("\tpassed testGetGamePieceBlackNonKing subtest\n");
	}

	currentPiece = theBoard->getGamePiece(1, 1);

	if (currentPiece->isEmpty() || !currentPiece->isRed() || !currentPiece->isKing()){
		testPasses = false;
		printf("\tfailed testGetGamePieceRedKing subtest\n");
	} else {
		printf("\tpassed testGetGamePieceRedKing subtest\n");
	}

	currentPiece = theBoard->getGamePiece(2,0);

	if (currentPiece->isEmpty() || currentPiece->isRed() || !currentPiece->isKing()){
		testPasses = false;
		printf("\tfailed testGetGamePieceBlackKing subtest\n");
	} else {
		printf("\tpassed testGetGamePieceBlackKing subtest\n");
	}

	currentPiece = theBoard->getGamePiece(1,0);

	if (!currentPiece->isEmpty()){
		testPasses = false;
		printf("\tfailed testGetGamePieceEmpty subtest\n");
	} else {
		printf("\tpassed testGetGamePieceEmpty subtest\n");
	}

	if (testPasses){
		printf("testGetGamePiece Passed: successful passed all subtests\n");
	} else {
		printf("testGetGamePiece Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}

//LinkedList Test
bool Tests::testLinkedListInit(){
	printf("Starting testLinkedListInit\n");

	bool testPasses = true;

	LinkedList* linkedListPointer = new LinkedList();

	if(linkedListPointer->size != 0){
		testPasses = false;
		printf("\tfailed testLinkedListInitSize subtest\n");
	} else {
		printf("\tpassed testLinkedListInitSize subtest\n");
	}

	if(linkedListPointer->head != (LinkedList::Node*)0){
		testPasses = false;
		printf("\tfailed testLinkedListInitNullHead subtest\n");
	} else {
		printf("\tpassed testLinkedListInitNullHead subtest\n");
	}

	if(linkedListPointer->tail != (LinkedList::Node*)0){
		testPasses = false;
		printf("\tfailed testLinkedListInitNullTail subtest\n");
	} else {
		printf("\tpassed testLinkedListInitNullTail subtest\n");
	}

	if (testPasses){
		printf("testLinkedListInit Passed: successful passed all subtests\n");
	} else {
		printf("testLinkedListInit Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}
bool Tests::testEnqueue(){
	printf("Starting testEnqueue\n");

	bool testPasses = true;

	LinkedList* linkedListPointer = new LinkedList();

	LinkedList::Data* dataPointer1 = new LinkedList::Data(1, 1, true, false);
	LinkedList::Data* dataPointer2 = new LinkedList::Data(2, 2, true, false);

	linkedListPointer->enqueue(dataPointer1);

	if(linkedListPointer->size != 1){
		testPasses = false;
		printf("\tfailed testEnqueueSizeIncrease1 subtest\n");
	} else {
		printf("\tpassed testEnqueueSizeIncrease1 subtest\n");
	}

	linkedListPointer->enqueue(dataPointer2);

	if(linkedListPointer->size != 2){
		testPasses = false;
		printf("\tfailed testEnqueueSizeIncrease2 subtest\n");
	} else {
		printf("\tpassed testEnqueueSizeIncrease2 subtest\n");
	}

	LinkedList::Data* firstDataPointer = linkedListPointer->head->dataP;
	LinkedList::Data* secondDataPointer = linkedListPointer->head->next->dataP;

	if(firstDataPointer != dataPointer1){
		testPasses = false;
		printf("\tfailed testEnqueueCorrectDataPointer1 subtest\n");
	} else {
		printf("\tpassed testEnqueueCorrectDataPointer1 subtest\n");
	}

	if(secondDataPointer != dataPointer2){
		testPasses = false;
		printf("\tfailed testEnqueueCorrectDataPointer2 subtest\n");
	} else {
		printf("\tpassed testEnqueueCorrectDataPointer2 subtest\n");
	}

	if (testPasses){
		printf("testEnqueue Passed: successful passed all subtests\n");
	} else {
		printf("testEnqueue Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}

bool Tests::testDequeue(){
	printf("Starting testDequeue\n");

	bool testPasses = true;

	LinkedList* linkedListPointer = new LinkedList();

	LinkedList::Data* dataPointer1 = new LinkedList::Data(1, 1, true, false);
	LinkedList::Data* dataPointer2 = new LinkedList::Data(2, 2, true, false);
	LinkedList::Data* dataPointer3 = new LinkedList::Data(3, 2, true, true);

	LinkedList::Data* removedDataPointer = linkedListPointer->dequeue();

	linkedListPointer->enqueue(dataPointer1);
	removedDataPointer = linkedListPointer->dequeue();

	if (removedDataPointer != dataPointer1){
		testPasses = false;
		printf("\tfailed testDequeueCorrectRemovedDataPointer1 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectRemovedDataPointer1 subtest\n");
	}

	if (linkedListPointer->size != 0){
		testPasses = false;
		printf("\tfailed testDequeueCorrectSize1 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectSize1 subtest\n");
	}

	if (linkedListPointer->head != (LinkedList::Node*)0){
		testPasses = false;
		printf("\tfailed testDequeueHeadNull1 subtest\n");
	} else {
		printf("\tpassed testDequeueHeadNull1 subtest\n");
	}

	linkedListPointer->enqueue(dataPointer1);
	linkedListPointer->enqueue(dataPointer2);
	linkedListPointer->enqueue(dataPointer3);
	removedDataPointer = linkedListPointer->dequeue();

	if (removedDataPointer != dataPointer1){
		testPasses = false;
		printf("\tfailed testDequeueCorrectRemovedDataPointer2 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectRemovedDataPointer2 subtest\n");
	}

	if (linkedListPointer->size != 2){
		testPasses = false;
		printf("\tfailed testDequeueCorrectSize2 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectSize2 subtest\n");
	}

	if (linkedListPointer->head->dataP != dataPointer2){
		testPasses = false;
		printf("\tfailed testDequeueNewHead1 subtest\n");
	} else {
		printf("\tpassed testDequeueNewHead1 subtest\n");
	}

	removedDataPointer = linkedListPointer->dequeue();

	if (removedDataPointer != dataPointer2){
		testPasses = false;
		printf("\tfailed testDequeueCorrectRemovedDataPointer3 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectRemovedDataPointer3 subtest\n");
	}

	if (linkedListPointer->size != 1){
		testPasses = false;
		printf("\tfailed testDequeueCorrectSize3 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectSize3 subtest\n");
	}

	if (linkedListPointer->head->dataP != dataPointer3){
		testPasses = false;
		printf("\tfailed testDequeueNewHead2 subtest\n");
	} else {
		printf("\tpassed testDequeueNewHead2 subtest\n");
	}

	removedDataPointer = linkedListPointer->dequeue();

	if (removedDataPointer != dataPointer3){
		testPasses = false;
		printf("\tfailed testDequeueCorrectRemovedDataPointer4 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectRemovedDataPointer4 subtest\n");
	}

	if (linkedListPointer->size != 0){
		testPasses = false;
		printf("\tfailed testDequeueCorrectSize4 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectSize4 subtest\n");
	}

	if (linkedListPointer->head != (LinkedList::Node*)0){
		testPasses = false;
		printf("\tfailed testDequeueHeadNull2 subtest\n");
	} else {
		printf("\tpassed testDequeueHeadNull2 subtest\n");
	}

	linkedListPointer->enqueue(dataPointer1);
	linkedListPointer->enqueue(dataPointer2);
	removedDataPointer = linkedListPointer->dequeue();
	linkedListPointer->enqueue(dataPointer3);

	LinkedList::Data* firstPointer = linkedListPointer->head->dataP;
	LinkedList::Data* secondPointer = linkedListPointer->head->next->dataP;

	if (firstPointer != dataPointer2){
		testPasses = false;
		printf("\tfailed testDequeueCorrectOrder1 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectOrder1  subtest\n");
	}

	if (secondPointer != dataPointer3){
		testPasses = false;
		printf("\tfailed testDequeueCorrectOrder2 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectOrder2  subtest\n");
	}

	if (linkedListPointer->size != 2){
		testPasses = false;
		printf("\tfailed testDequeueCorrectSize5 subtest\n");
	} else {
		printf("\tpassed testDequeueCorrectSize5 subtest\n");
	}


	if (testPasses){
		printf("testDequeue Passed: successful passed all subtests\n");
	} else {
		printf("testDequeue Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}
bool Tests::testComplicatedDequeue(){
	printf("Starting testComplicatedDequeue\n");

	bool testPasses = true;

	LinkedList* linkedListPointer = new LinkedList();

	LinkedList::Data* dataPointer1 = new LinkedList::Data(1, 1, true, false);
	LinkedList::Data* dataPointer2 = new LinkedList::Data(2, 2, true, false);
	LinkedList::Data* dataPointer3 = new LinkedList::Data(3, 2, true, true);

	LinkedList::Data* removedDataPointer = linkedListPointer->dequeue();

	linkedListPointer->enqueue(dataPointer1);
	removedDataPointer = linkedListPointer->complicatedDequeue(1, 1);

	if (removedDataPointer != dataPointer1){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueHead subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueHead subtest\n");
	}

	if (linkedListPointer->size != 0){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectSize1 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectSize1 subtest\n");
	}

	if (linkedListPointer->head != (LinkedList::Node*)0){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueHeadNull1 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueHeadNull1 subtest\n");
	}

	linkedListPointer->enqueue(dataPointer1);
	linkedListPointer->enqueue(dataPointer2);
	linkedListPointer->enqueue(dataPointer3);

	removedDataPointer = linkedListPointer->complicatedDequeue(2, 2);

	if (removedDataPointer != dataPointer2){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectRemovedDataPointer1 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectRemovedDataPointer1 subtest\n");
	}

	if (linkedListPointer->size != 2){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectSize2 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectSize2 subtest\n");
	}

	if (linkedListPointer->head->dataP != dataPointer1){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectHead1 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectHead1  subtest\n");
	}

	if (linkedListPointer->tail->dataP != dataPointer3){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectTail1 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectTail1 subtest\n");
	}

	//linkedListPointer->printSimpleList();

	removedDataPointer = linkedListPointer->complicatedDequeue(3, 2);

	//linkedListPointer->printSimpleList();

	if (removedDataPointer != dataPointer3){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectRemovedDataPointer2 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectRemovedDataPointer2 subtest\n");
	}

	if (linkedListPointer->size != 1){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectSize3 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectSize3 subtest\n");
	}

	if (linkedListPointer->head->dataP != dataPointer1){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectHead2 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectHead2  subtest\n");
	}

	//printf("tail is (%d, %d)\n", linkedListPointer->tail->dataP->mRow, linkedListPointer->tail->dataP->mCol);

	if (linkedListPointer->tail->dataP != dataPointer1){
		testPasses = false;
		printf("\tfailed testComplicatedDequeueCorrectTail2 subtest\n");
	} else {
		printf("\tpassed testComplicatedDequeueCorrectTail2 subtest\n");
	}

	if (testPasses){
		printf("testComplicatedDequeue Passed: successful passed all subtests\n");
	} else {
		printf("testComplicatedDequeue Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}
bool Tests::testPrintSimpleList(){
	printf("Starting testPrintSimpleList\n");

	bool testPasses = true;

	LinkedList* linkedListPointer = new LinkedList();

	LinkedList::Data* dataPointer1 = new LinkedList::Data(1, 1, true, false);
	LinkedList::Data* dataPointer2 = new LinkedList::Data(2, 2, false, true);
	LinkedList::Data* dataPointer3 = new LinkedList::Data(3, 2, true, true);
	LinkedList::Data* dataPointer4 = new LinkedList::Data(3, 3, false, false);

	linkedListPointer->printSimpleList();

	printf("\n");

	if(!getYesNo("Was an empty linked list printed in the console?")){
		testPasses = false;
		printf("\tfailed testPrintSimpleListEmpty subtest\n");
	} else {
		printf("\tpassed testPrintSimpleListEmpty subtest\n");
	}

	printf("\n");

	linkedListPointer->enqueue(dataPointer1);
	linkedListPointer->printSimpleList();

	printf("\n");

	if(!getYesNo("Was a linked list of length 1 printed to the console with the following piece:\n\t(1, 1) Red Checker?")){
		testPasses = false;
		printf("\tfailed testPrintSimpleList1 subtest\n");
	} else {
		printf("\tpassed testPrintSimpleList1 subtest\n");
	}

	printf("\n");

	linkedListPointer->enqueue(dataPointer2);
	linkedListPointer->printSimpleList();

	printf("\n");

	if(!getYesNo("Was a linked list of length 2 printed to the console with the following pieces:\n\t(1, 1) Red Checker, (2, 2) Black King Checker?")){
		testPasses = false;
		printf("\tfailed testPrintSimpleList2 subtest\n");
	} else {
		printf("\tpassed testPrintSimpleList2 subtest\n");
	}

	printf("\n");


	linkedListPointer->enqueue(dataPointer3);
	linkedListPointer->printSimpleList();

	printf("\n");

	if(!getYesNo("Was a linked list of length 3 printed to the console with the following pieces:\n\t(1, 1) Red Checker, (2, 2) Black King Checker, (3, 2) Red King Checker?")){
		testPasses = false;
		printf("\tfailed testPrintSimpleList3 subtest\n");
	} else {
		printf("\tpassed testPrintSimpleList3 subtest\n");
	}

	printf("\n");


	linkedListPointer->enqueue(dataPointer4);
	linkedListPointer->printSimpleList();

	printf("\n");

	if(!getYesNo("Was a linked list of length 4 printed to the console with the following pieces:\n\t(1, 1) Red Checker, (2, 2) Black King Checker, (3, 2) Red King Checker, (3, 3) Black Checker?")){
		testPasses = false;
		printf("\tfailed testPrintSimpleList4 subtest\n");
	} else {
		printf("\tpassed testPrintSimpleList4 subtest\n");
	}

	printf("\n");

	if (testPasses){
		printf("testPrintSimpleList Passed: successful passed all subtests\n");
	} else {
		printf("testPrintSimpleList Failed: not all subtests passed\n");
	}

	printf("\n");

	return testPasses;
}

bool Tests::getYesNo(char* query)
{
	bool answer = true; //so far
	char said = 'x';
	do
	{
		printf("%s (y/n):",query);
		fflush(stdout);
		fflush(stdin);
		scanf("%c",&said);
	}while((said!= 'y')&&(said!='n'));
	if(said=='n')
	{
		answer=false;
	}


	return answer;
}


