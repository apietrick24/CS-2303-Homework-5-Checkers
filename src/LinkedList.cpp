/*
 * LinkedList.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: wildg
 *
 *      NOTE: This Code was originally written by Ben Kresge (with who I was partnered) for Homework #4. With permission, I modified it to
 *      work with my implementation for Homework #5. I changed all of the variables for the data subclass and added the function
 *      complicatedDequeue. I also edited the print to wrote with checkers rather than room searching. Ben was not consulted at all during
 *      this project.
 */

#include "LinkedList.h"
#include <cstdio>

LinkedList::LinkedList() {
	head = (Node*)0;
	tail = head;
	size = 0;
}

LinkedList::~LinkedList() {
	// TODO Auto-generated destructor stub
}


void LinkedList::enqueue(Data *d){
	Node *n = new Node();
	n->dataP = d;
	if(size == 0){
		head = tail = n;
	}else{
		tail->next = n;
		n->prev = tail;
		tail = n;
	}
	size++;
}

LinkedList::Data* LinkedList::dequeue(){
	Data *returnP = (Data*)0;
	if(size == 0){
		//printf("attempted to dequeue from an empty list, returning %p\n",(void*)returnP);
	}else{
		returnP = head->dataP;
		delete(head);
		head = head->next;
		if(size-- == 0){
			head = (Node*)0;
			tail=head;
		}


	}
	return returnP;
}

LinkedList::Data* LinkedList::complicatedDequeue(int rRow, int rCol){
	Data *returnP = (Data*)0;

	if(size == 0){
		//printf("attempted to dequeue from an empty list, returning %p\n",(void*)returnP);
	}else{
		Node* curNode = head;

		int i = 0;
		for (i; i < size && !(curNode->dataP->mRow == rRow && curNode->dataP->mCol == rCol); i++){
			curNode = curNode->next;
		}

		if (curNode->dataP->mRow == rRow && curNode->dataP->mCol == rCol){
			if (i == 0){
				//dequeue head just use normal dequeue
				return dequeue();
			} else if (i != (size-1)) {
				//dequeue non tail
				returnP = curNode->dataP;

				Node* prevNode = head;

				for (int j = 0; j < (i-1); j++){
					prevNode = prevNode->next;
				}


				//curNode->prev->next = curNode->next;
				prevNode->next = curNode->next;
				//curNode = curNode->next;

				if(size-- == 0){
					head = (Node*)0;
					tail=head;
				}

				delete(curNode);
			} else {
				//dequeue tail
				//printf("fired please work i begg of ityou\n");
				returnP = curNode->dataP;

				Node* prevNode = head;

				for (int j = 0; j < (size-2); j++){
					prevNode = prevNode->next;
				}

				//printf("prev node: (%d, %d)\n", prevNode->dataP->mRow, prevNode->dataP->mCol);

				prevNode->next = head;
				tail = prevNode;

				if(size-- == 0){
					head = (Node*)0;
					tail=head;
				}

				delete(curNode);
			}
		}

	}

	//printf("head: (%d, %d) | tail: (%d, %d)\n", head->dataP->mRow, head->dataP->mCol, tail->dataP->mRow, tail->dataP->mCol);

	return returnP;
}


void LinkedList::printSimpleList(){
	if(size == 0){
		printf("Empty List\n");
	}else{
		printf("There are %d Game Pieces Left\n\t", size);
		Node* curNode = head;

		for(int i = 0; i < size; i++){
			printf("(%d, %d) %s %s, ", curNode->dataP->mRow, curNode->dataP->mCol, curNode->dataP->red ? "Red" : "Black",  curNode->dataP->king ? "King Checker" : "Checker");
			curNode = curNode -> next;
		}

		printf("\n");

	}
}

