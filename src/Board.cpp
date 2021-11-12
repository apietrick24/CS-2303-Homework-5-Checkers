/*
 * Board.cpp
 *
 *  Created on: Aug 2, 2021
 *      Author: theresesmith
 */

#include "Board.h"
#include <fstream>
#include <string>
#include "GamePiece.h"
#include "LinkedList.h"
#include <cmath>
#include <iostream>

Board::Board(char* filename, char* writeFileName) {
	// TODO Auto-generated constructor stub

	writeFile.open(writeFileName);

	bool createdBoard = false;

	redPieces = new LinkedList;
	blackPieces = new LinkedList;

	std::ifstream file(filename);
	std::string str;

	for (int row = 0; std::getline(file, str); row++){
		//Character rep of the current piece
		char *cstr = new char[str.length() + 1];
		strcpy(cstr, str.c_str());

		if (!createdBoard){
			size = (unsigned)strlen(cstr);
			gameBoard = (GamePiece**) malloc(size*size*sizeof(GamePiece*));
			createdBoard = true;
			//printf("Malloced the memory for the Game Board\n");
		}

		for (int col = 0; col < size; col++){

			GamePiece* hold = (GamePiece*) malloc(sizeof(GamePiece));

			switch(cstr[col]){
			default:
			case '-':
				hold = new GamePiece(true, false, false, row, col);
				break;

			case 'r':

				hold = new GamePiece(false, true, false, row, col);
				redPieces->enqueue(new LinkedList::Data(row, col, true, false));


				break;

			case 'R':
				hold = new GamePiece(false, true, true, row, col);
				redPieces->enqueue(new LinkedList::Data(row, col, true, true));
				break;

			case 'b':

				hold = new GamePiece(false, false, false, row, col);
				blackPieces->enqueue(new LinkedList::Data(row, col, false, false));

				break;

			case 'B':
				hold = new GamePiece(false, false, true, row, col);
				blackPieces->enqueue(new LinkedList::Data(row, col, false, true));
				break;
			}

			GamePiece** currentGamePiecePointerStorage = gameBoard + (row * size) + col;

			*currentGamePiecePointerStorage = hold;

			//printf("%c (%d, %d) ", (*(gameBoard + row*size + col))->toChar(), row, col);
		}

		//printf("\n");
	}
}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

void Board::displayBoard(){
	printf("Current Status of the Game Board:\n");
	for(int row = 0; row < size; row++){
		for (int col = 0; col < size; col++){
			printf("(%d, %d): %c ", row, col, (*(gameBoard + row*size + col))->toChar());
			//printf("%c", (*(gameBoard + row*size + col))->toChar());
		}
		printf("\n");
	}

	printf("\nGame Pieces List in the Game:\nRed Piece's: ");
	redPieces->printSimpleList();
	printf("\nBlack Piece's: ");
	blackPieces->printSimpleList();

	printf("\n");
}
void Board::printToFile(){
	writeFile << "\n";
	for(int row = 0; row < size; row++){
		for (int col = 0; col < size; col++){
			writeFile << (*(gameBoard + row*size + col))->toChar();
		}
		writeFile << "\n";
	}
}

bool Board::computerMove(bool isComputerRed, bool write, bool execute){
	bool returnVar = false;
	LinkedList* computerPieces = isComputerRed ? redPieces : blackPieces;
	LinkedList* computerPossibleJumpMoves = new LinkedList;
	LinkedList* computerPossibleNonJumpMoves = new LinkedList;

	LinkedList::Node* currentNode = computerPieces->head;

	for (int i = 0; i < computerPieces->size; i++){
		int sRow = currentNode->dataP->mRow;
		int sCol = currentNode->dataP->mCol;

		computerPossibleNonJumpMoves->enqueue(new LinkedList::Data(sRow, sCol, sRow + 1, sCol + 1));
		computerPossibleNonJumpMoves->enqueue(new LinkedList::Data(sRow, sCol, sRow + 1, sCol - 1));
		computerPossibleNonJumpMoves->enqueue(new LinkedList::Data(sRow, sCol, sRow - 1, sCol - 1));
		computerPossibleNonJumpMoves->enqueue(new LinkedList::Data(sRow, sCol, sRow - 1, sCol + 1));

		computerPossibleJumpMoves->enqueue(new LinkedList::Data(sRow, sCol, sRow + 2, sCol + 2));
		computerPossibleJumpMoves->enqueue(new LinkedList::Data(sRow, sCol, sRow + 2, sCol - 2));
		computerPossibleJumpMoves->enqueue(new LinkedList::Data(sRow, sCol, sRow - 2, sCol - 2));
		computerPossibleJumpMoves->enqueue(new LinkedList::Data(sRow, sCol, sRow - 2, sCol + 2));

		currentNode=currentNode->next;
	}

	LinkedList* validComputerMoves = new LinkedList;

	while (computerPossibleJumpMoves->size != 0 || computerPossibleNonJumpMoves->size != 0){
		LinkedList::Data* currentMove = computerPossibleJumpMoves->size != 0 ? computerPossibleJumpMoves->dequeue() : computerPossibleNonJumpMoves->dequeue();

		if(isMoveValid(currentMove->mRow, currentMove->mCol, currentMove->fRow, currentMove->fCol)){
			validComputerMoves->enqueue(new LinkedList::Data(currentMove->mRow, currentMove->mCol, currentMove->fRow, currentMove->fCol));
		}
	}


	LinkedList::Node* currentNodeValid = validComputerMoves->head;

	writeFile << "Possible Moves: ";


	while (currentNodeValid){
		LinkedList::Data* currentValidMode = currentNodeValid->dataP;

		writeFile << "(" << std::to_string(currentValidMode->mRow) << ", " << std::to_string(currentValidMode->mCol) << ") -> (" << std::to_string(currentValidMode->fRow) << ", " << std::to_string(currentValidMode->fCol) << "), ";

		currentNodeValid=currentNodeValid->next;
	}

	writeFile << "\n";

	if (validComputerMoves->size != 0){
		if (execute){
			LinkedList::Data* currentMove = validComputerMoves->dequeue();
			executeGivenMove(currentMove->mRow, currentMove->mCol, currentMove->fRow, currentMove->fCol);
			printf("Computer successful made a legal move\n");
		}

		returnVar = true;

	} else {
		if (execute){
			printf("Computer didn't move; there are no possible moves\n");
		}

		returnVar = false;
	}

	delete validComputerMoves;
	delete computerPossibleJumpMoves;
	delete computerPossibleNonJumpMoves;

	return returnVar;
}
bool Board::isMoveValid(int row1, int col1, int row2, int col2){
	GamePiece* movePiece = getGamePiece(row1, col1);
	GamePiece* finishedPiece = getGamePiece(row2, col2);

	//printf("%d %d - now in isMOve valid -> %d %d\n", row1, col1, row2, col2);

	if (movePiece->isEmpty() || row1 >= size || row2 >= size || col1 >= size || col2 >= size || row1 < 0 || row2 < 0 || col1 < 0 || col2 < 0){
		//printf("\tnot even valid move due to size of board\n");
		return false;
	}

	bool redPieceIsMoving = movePiece->isRed();
	bool movingPieceIsKing = movePiece->isKing();

	bool isJumpMove = (abs(movePiece->getCol() - finishedPiece->getCol()) == 2 && abs(movePiece->getRow() - finishedPiece->getRow()) == 2);

	//printf("\tthe move is %s a jump moving\n", isJumpMove ? "indeed" : "not");
	//printf("\tthe moving piece is %s a king\n", movingPieceIsKing ? "indeed" : "not");

	if (!isJumpMove){
		bool validColorMove = false;

		if (movingPieceIsKing){
			validColorMove = ((movePiece->getRow() + 1 == finishedPiece->getRow()) || (movePiece->getRow() - 1 == finishedPiece->getRow()));
		} else {
			validColorMove = redPieceIsMoving ? (movePiece->getRow() - 1 == finishedPiece->getRow()) : (movePiece->getRow() + 1 == finishedPiece->getRow());
		}

		//printf("\tthe move is %s a valid move for the color\n", validColorMove ? "indeed" : "not");

		bool validMove = (abs(movePiece->getCol() - finishedPiece->getCol())) == 1;
		//printf("\tthe move is %s a valid move\n", validMove ? "indeed" : "not");
		//printf("\tthe moving piece is %s going to an empty space\n", finishedPiece->isEmpty() ? "indeed" : "not");

		if (finishedPiece->isEmpty() && validMove && validColorMove){
			return true;
		}

	} else {
		bool validColorMove = false;

		if (movingPieceIsKing){
			validColorMove = ((movePiece->getRow() + 2 == finishedPiece->getRow()) || (movePiece->getRow() - 2 == finishedPiece->getRow()));
		} else {
			validColorMove = redPieceIsMoving ? (movePiece->getRow() - 2 == finishedPiece->getRow()) : (movePiece->getRow() + 2 == finishedPiece->getRow());
		}

		//printf("\tthe move is %s a valid move for the color\n", validColorMove ? "indeed" : "not");

		bool validMove = (abs(movePiece->getCol() - finishedPiece->getCol())) == 2;
		//printf("\tthe move is %s a valid move\n", validMove ? "indeed" : "not");

		GamePiece* jumpedPiece = getGamePiece(row1 + ((row2 - row1)/2), col1 + ((col2 - col1)/2));
		bool jumpedPieceOtherColor = jumpedPiece->isRed() != redPieceIsMoving;
		//printf("\tthe piece potentially going to be jumped, the piece %c at (%d, %d), is %s the same color as the moving piece\n", jumpedPiece->toChar(), row1 + ((row2 - row1)/2), row1 + ((row2 - row1)/2), jumpedPieceOtherColor ? "not" : "INDEED");

		if (finishedPiece->isEmpty() && jumpedPieceOtherColor && !jumpedPiece->isEmpty() && validMove && validColorMove){
			return true;
		}

	}

	return false;

}

bool Board::executeGivenMove(int row1, int col1, int row2, int col2){
	printf("Attempting to make the move (%d, %d) -> (%d, %d)\n", row1, col1, row2, col2);
	//non-jump move

	GamePiece* movePiece = getGamePiece(row1, col1);
	GamePiece* finishedPiece = getGamePiece(row2, col2);

	bool redPieceIsMoving = movePiece->isRed();
	bool movingPieceIsKing = movePiece->isKing();

	bool isJumpMove = (abs(movePiece->getCol() - finishedPiece->getCol()) == 2 && abs(movePiece->getRow() - finishedPiece->getRow()) == 2);

	if (!isJumpMove){
		char movedChar = movePiece->toChar();
		char finishedChar = finishedPiece->toChar();
		//Set the new position for the moved piece
		finishedPiece->setEmpty(false);
		finishedPiece->setKing(movingPieceIsKing);
		finishedPiece->setRed(redPieceIsMoving);

		//Set the new posistion for the empty space
		movePiece->setEmpty(true);
		movePiece->setKing(false);
		movePiece->setRed(false);

		if (redPieceIsMoving){
			redPieces->complicatedDequeue(row1, col1);
			redPieces->enqueue(new LinkedList::Data(row2, col2, redPieceIsMoving, movingPieceIsKing));
		} else {
			blackPieces->complicatedDequeue(row1, col1);
			blackPieces->enqueue(new LinkedList::Data(row2, col2, redPieceIsMoving, movingPieceIsKing));
		}

		printf("\nThe move %c (%d, %d) -> %c (%d, %d) has been executed. The board and lists has been updated.\n",
				movedChar, row1, col1, finishedChar, row2, col2);

		writeFile << "Move: " << movedChar << " (" << std::to_string(row1) << ", " << std::to_string(col1) << ") -> " << finishedChar << " (" << std::to_string(row2) << ", " << std::to_string(col2) << ")\n";
	} else {
		//jump move

		GamePiece* jumpedPiece = getGamePiece(row1 + ((row2 - row1)/2), col1 + ((col2 - col1)/2));

		char movedChar = movePiece->toChar();
		char jumpedChar = jumpedPiece->toChar();
		char finishedChar = finishedPiece->toChar();

		//Set the new position for the moved piece
		finishedPiece->setEmpty(false);
		finishedPiece->setKing(movingPieceIsKing);
		finishedPiece->setRed(redPieceIsMoving);

		//Set the new posistion for the empty space
		movePiece->setEmpty(true);
		movePiece->setKing(false);
		movePiece->setRed(false);

		jumpedPiece->setEmpty(true);
		jumpedPiece->setKing(false);
		jumpedPiece->setRed(false);

		if (redPieceIsMoving){
			redPieces->complicatedDequeue(row1, col1);
			blackPieces->complicatedDequeue(jumpedPiece->getRow(), jumpedPiece->getCol());
			redPieces->enqueue(new LinkedList::Data(row2, col2, redPieceIsMoving, movingPieceIsKing));
		} else {
			blackPieces->complicatedDequeue(row1, col1);
			redPieces->complicatedDequeue(jumpedPiece->getRow(), jumpedPiece->getCol());
			blackPieces->enqueue(new LinkedList::Data(row2, col2, redPieceIsMoving, movingPieceIsKing));
		}

		printf("\nThe move %c (%d, %d) -- %c (%d, %d) -> %c (%d, %d) has been executed. The board and lists has been updated.\n",
				movedChar, row1, col1, jumpedChar, jumpedPiece->getRow(), jumpedPiece->getCol(), finishedChar, row2, col2);

		writeFile << "Move: " << movedChar << " (" << std::to_string(row1) << ", " << std::to_string(col1) << ") -- " << jumpedChar << " (" << std::to_string(jumpedPiece->getRow()) << ", " << std::to_string(jumpedPiece->getCol()) << ") -> " << finishedChar << " (" << std::to_string(row2) << ", " << std::to_string(col2) << ")\n";
	}

	return true;

}

void Board::promote(){
	for(int row = 0; row < size; row++){
		for (int col = 0; col < size; col++){
			GamePiece* current = getGamePiece(row, col);

			if (current->isRed() && row == 0){
				current->setKing(true);
			} else if (!current->isRed() && row == (size-1)){
				current->setKing(true);
			}
		}
	}
}

bool Board::hasRedWon(){
	return blackPieces->size == 0;
}
bool Board::hasBlackWon(){
	return redPieces->size == 0;
}

GamePiece* Board::getGamePiece(int row, int col){
	return (*(gameBoard + row*size + col));
}
