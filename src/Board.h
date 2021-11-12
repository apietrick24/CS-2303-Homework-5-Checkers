 /*
 * Board.h
 *
 *  Created on: Aug 2, 2021
 *      Author: theresesmith
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <stdio.h>
#include "GamePiece.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>

class Board {
public:
	Board(char* filename, char* writeFileName);
	virtual ~Board();
	void displayBoard();
	void printToFile ();
	bool computerMove(bool isComputerRed, bool write, bool execute);
	bool hasRedWon();
	bool hasBlackWon();
	bool isMoveValid(int row1, int col1, int row2, int col2);
	bool executeGivenMove(int row1, int col1, int row2, int col2);
	GamePiece* getGamePiece(int row, int col);
	void promote();
	std::ofstream writeFile;

private:
	int size;
	GamePiece** gameBoard;
	LinkedList* redPieces;
	LinkedList* blackPieces;
};

#endif /* BOARD_H_ */
