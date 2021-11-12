/*
 * LinkedList.h
 *
 *  Created on: Sep 19, 2021
 *      Author: wildg
 *
 *      NOTE: This Code was originally written by Ben Kresge (with who I was partnered) for Homework #4. With permission, I modified it to
 *      work with my implementation for Homework #5. I changed all of the variables for the data subclass and added the function
 *      complicatedDequeue. I also edited the print to wrote with checkers rather than room searching. Ben was not consulted at all during
 *      this project.
 *
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdbool.h>

class LinkedList {
public:
	LinkedList();
	virtual ~LinkedList();
	int size;
	class Data{
	public:
		Data(int pMRow, int pMCol, int pFRow, int pFCol){
			mRow = pMRow;
			mCol = pMCol;
			fRow = pFRow;
			fCol = pFCol;
			red = false;
			king = false;
		};

		Data(int pRow, int pCol, bool isRed, bool isKing){
			mRow = pRow;
			mCol = pCol;
			fRow = -1;
			fCol = -1;
			red = isRed;
			king = isKing;
		};

		int mRow;
		int mCol;
		int fRow;
		int fCol;
		bool red;
		bool king;
	};

	void enqueue(Data *data);
	Data* dequeue();
	Data* complicatedDequeue(int rRow, int rCol);
	void printSimpleList();
	class Node{
	public:
		Data* dataP;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
};


#endif /* LINKEDLIST_H_ */
