/*
 * GamePiece.cpp
 *
 *  Created on: Oct 2, 2021
 *      Author: apietrick20
 */

#include "GamePiece.h"
#include <stdio.h>

//Is the piece just an empty space? If so, the rest of its' variables don't matter
bool empty;

//Does the piece belong to the Red Player? If not, then it must belong to the Black player
bool red;

//Is the piece a King? If not, it's just a pawn
bool king;

//Which row is the piece in?
int row;

//WHich col is the piece in?
int col;

GamePiece::GamePiece(bool pEmpty, bool pRed, bool pKing, int pRow, int pCol) {
	empty = pEmpty;
	red = pRed;
	king = pKing;
	row = pRow;
	col = pCol;
}

GamePiece::~GamePiece() {
	// TODO Auto-generated destructor stub
}

bool GamePiece::isEmpty(){
	return empty;
}
bool GamePiece::isKing(){
	return king;
}
bool GamePiece::isRed(){
	return red;
}
int GamePiece::getRow(){
	return row;
}
int GamePiece::getCol(){
	return col;
}

void GamePiece::setRow(int pRow){
	row = pRow;
}
void GamePiece::setCol(int pCol){
	col = pCol;
}
void GamePiece::setKing(bool pKing){
	king = pKing;

}
void GamePiece::setEmpty(bool pEmpty){
	empty = pEmpty;
}
void GamePiece::setRed(bool pRed){
	red = pRed;
}
char GamePiece::toChar(){
	if (empty){
		return '-';
	} else {
		char checker = red ? 'r' : 'b';

		if (king){
			checker-=32;
		}

		return checker;

	}
}


