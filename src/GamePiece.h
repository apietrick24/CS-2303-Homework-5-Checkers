/*
 * GamePiece.h
 *
 *  Created on: Oct 2, 2021
 *      Author: apietrick20
 */

#ifndef GAMEPIECE_H_
#define GAMEPIECE_H_

class GamePiece {
public:
	GamePiece(bool pEmpty, bool pRed, bool pKing, int pRow, int pCol);
	virtual ~GamePiece();
	bool isEmpty();
	bool isKing();
	bool isRed();
	int getRow();
	int getCol();
	void setRow(int pRow);
	void setCol(int pCol);
	void setKing(bool pKing);
	void setEmpty(bool pEmpty);
	void setRed(bool pRed);
	char toChar();

private:
	bool empty;
	bool red;
	bool king;
	int row;
	int col;
};

#endif /* GAMEPIECE_H_ */
