/*
 * Production.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Production.h"
#include <iostream>
#include <fstream>

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[])
{
	printf("Starting Production\n");
	printf("Arguments:\n");
	printf("\tprogram file - read file - write file - computer's color - whose turn - max number of turns\n\n");
	bool answer = false;

	if(argc <=1) //no interesting information
	{
		puts("Didn't find any arguments.");
		fflush(stdout);
		answer = false;
	}
	else //there is interesting information
	{
		printf("Found %d interesting arguments.\n\n", argc-1);
		fflush(stdout);

		char gameStateReadFile[FILENAMELENGTHALLOWANCE];
		char gameStateWriteFile[FILENAMELENGTHALLOWANCE];
		char* eptr=(char*) malloc(sizeof(char*));
		long aL=-1L;

		bool isRedTurn = false;
		bool isRedTurnSet = false;
		bool isComputerRed = false;
		bool isComputerRedSet = false;
		int maxNumOfTurns = 0;

		for(int i = 1; ((i<argc && (argc-1) == 5) || i <= 2); i++) //don't want to read argv[0]
		{//argv[i] is a string

			switch(i)
			{
			case 1:
				printf("Reading Game State Reading File Name:\n");

				printf("\tThe proposed filename is %s.\n", argv[i]);
				if(strlen(argv[i])>=FILENAMELENGTHALLOWANCE)
				{
					puts("\tFilename is too long.");
					fflush(stdout);
					answer = false;
				}
				else
				{
					strcpy(gameStateReadFile, argv[i]);
					printf("\tFilename was %s.\n", gameStateReadFile);
					fflush(stdout);
				}

				printf("\n");
				break;

			case 2:
				printf("Reading Game State Writing File Name:\n");

				printf("\tThe proposed filename is %s.\n", argv[i]);
				if(strlen(argv[i])>=FILENAMELENGTHALLOWANCE)
				{
					puts("\tFilename is too long.");
					fflush(stdout);
					answer = false;
				}
				else
				{
					strcpy(gameStateWriteFile, argv[i]);
					printf("\tFilename was %s.\n", gameStateWriteFile);
					fflush(stdout);
				}
				printf("\n");
				break;

			case 5:
				printf("Reading Max Number of Turns:\n");
				aL = strtol(argv[i], &eptr, 10);
				maxNumOfTurns = (int) aL;
				printf("\tMax Number of Turns: %d\n\n", maxNumOfTurns);fflush(stdout);
				break;

			case 4:
				printf("Reading Which Player's Turn is it:\n");
				if (strcmp(argv[i], "red") == 0){
					isRedTurn = true;
					isRedTurnSet = true;
					printf("\tIt is the Red Player's turn\n");
				} else if (strcmp(argv[i], "black") == 0){
					isRedTurn = false;
					isRedTurnSet = true;
					printf("\tIt is the Black Player's turn\n");
				} else {
					printf("\tunexpected string found\n");
				}
				printf("\n");
				break;

			case 3:
				printf("Reading Which Player the Computer is:\n");
				if (strcmp(argv[i], "red") == 0){
					isComputerRed = true;
					isComputerRedSet = true;
					printf("\tThe Computer is the Red Player\n");
				} else if (strcmp(argv[i], "black") == 0){
					isComputerRed = false;
					isComputerRedSet = true;
					printf("\tThe Computer is the Black Player\n");
				} else {
					printf("\tunexpected string found\n");
				}
				printf("\n");
				break;

			default:
				puts("Unexpected argument count."); fflush(stdout);
				answer = false;
				break;
			}//end of switch
		}//end of for loop on argument count

		while(maxNumOfTurns <= 0 || !isRedTurnSet || !isComputerRedSet){
			if (maxNumOfTurns <= 0){
				int num = 0;
				printf("%d is an incorrect input for maxNumOfTurns. Please give a integer greater than zero:\n", maxNumOfTurns);
				fflush(stdout);
				fflush(stdin);
				scanf("%d",&num);
				printf("The program has read the integer %d\n\n", num);

				maxNumOfTurns = num;
			}

			if (!isComputerRed){
				isComputerRed = getYesNo("Is the computer the Red Player?\n");
				isComputerRedSet = true;
				printf("\n");

			}

			if (!isRedTurnSet){
				isRedTurn = getYesNo("Is it the Red Player's Turn?\n");
				isRedTurnSet = true;
				printf("\n");
			}
		}

		printf("Quick Summary of Passed Arguments:\n");
		printf("\tGame State is being read from: %s\n", gameStateReadFile);
		printf("\tGame State is being written to: %s\n", gameStateWriteFile);
		printf("\tMax Number of turns left: %d\n", maxNumOfTurns);
		printf("\tComputer is the color: %s\n", isComputerRed ? "red" : "black");
		printf("\tWhose turn is it: %s\n\n", isRedTurn ? "red" : "black");

		puts("Before read file"); fflush(stdout);
		//Reading File to Create Board
		Board* theBoard = new Board(gameStateReadFile, gameStateWriteFile);
		puts("Back from read file\nReady to start the game up again\n"); fflush(stdout);

		theBoard->promote();

		bool gameOver = false;

		for (int currentTurn = 0; (currentTurn < maxNumOfTurns) && !theBoard->hasBlackWon() && !theBoard->hasRedWon() && !gameOver; currentTurn++){
			theBoard->displayBoard();
			theBoard->printToFile();
			if ((!isRedTurn && !isComputerRed) || (isRedTurn && isComputerRed)){
				printf("It's the computer's (%s) turn\n", isComputerRed ? "red" : "black");
				theBoard->writeFile << "It's the computer's " << (isComputerRed ? "red " : "black ") << "turn\n";
				bool computableMove = theBoard->computerMove(isComputerRed, true, true);

				//printf("back from computableMove\n");
				if (!computableMove){
					gameOver = true;
				}

				printf("\n");
			} else {
				printf("It's the player's (%s) turn\n", !isComputerRed ? "red" : "black");
				theBoard->writeFile << "It's the player's " << (!isComputerRed ? "red " : "black ") << "turn\n";
				int mRow = -1;
				int mCol = -1;
				int fRow = -1;
				int fCol = -1;

				if (!theBoard->computerMove(isComputerRed, false, false)){
					gameOver = true;
				}

				do{
					bool validInput = true;

					do{
						printf("Please enter a valid move for yours pieces. You are the color %s\n\n", !isComputerRed ? "red" : "black");

						printf("Which Row is the piece that you want to move in?\n");
						fflush(stdout);
						fflush(stdin);
						scanf("%d", &mRow);

						printf("\nWhich Col is the piece that you want to move in?\n");
						fflush(stdout);
						fflush(stdin);
						scanf("%d", &mCol);

						printf("\nWhat is the Row of the place where you want to move the piece?\n");
						fflush(stdout);
						fflush(stdin);
						scanf("%d", &fRow);

						printf("\nWhat is the Col of the place where you want to move the piece?\n");
						fflush(stdout) ;
						fflush(stdin);
						scanf("%d", &fCol);

						if (0 <= mRow && 0 <=mCol && 0 <= fRow && 0<= fCol){
							printf("\nThe move: (%d, %d) -> (%d, %d) has been received and will be processed\n", mRow, mCol, fRow, fCol);
							validInput = true;
						} else {
							printf("Improper input: all numbers must be great than or equal to zero\n");
						}

					}while(!validInput);
				} while(!theBoard->isMoveValid(mRow, mCol, fRow, fCol));

				theBoard->executeGivenMove(mRow, mCol, fRow, fCol);

				printf("\n");
			}

			theBoard->promote();

			if (!isRedTurn){
				isRedTurn = true;
				currentTurn-=1;
			} else {
				isRedTurn = false;
			}
			printf("End of the Turn\n\n");
		}

		theBoard->writeFile << "\nEnd of the Game";
		theBoard->printToFile();

		if (!theBoard->hasBlackWon() && !theBoard->hasRedWon()){
			printf("The game is a draw\n");
			theBoard->writeFile << "The game ended in a draw";
		} else if (theBoard->hasBlackWon()){
			printf("Black has won the game!\n");
			theBoard->writeFile << "Black has won the game";
		} else {
			printf("Red has won the game!\n");
			theBoard->writeFile << "Red has won the game";
		}

		theBoard->writeFile.close();

		theBoard->displayBoard();

	}
	return answer;
}

bool Production::getYesNo(char* query)
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

