#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <array>
#include "string"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <windows.h>
using namespace std;
bool turn = true;
bool isAIOn = false;


void gameMessages(int x){
	/******************************************************************************************************************************************
	 This Method Stores all the messages for the game. 
	 This design pattern allows for a centralized place for the editting of in game messages.
	 ******************************************************************************************************************************************/
	switch (x){

	case 1:
		cout << "Tick Tack Toe" << endl;
		cout << "First player to get 3 spaces in a row wins the game!" << endl;
		break;
	case 2:
		cout << "Would you like to play with a computer?" << endl;
		cout << "Type 1 for yes or type 0 for no and press enter" << endl;
		break;
	case 3:
		cout << "Player X please make a move and press enter." << endl;
		break;
	case 4:
		cout << "Player O please make a move and press enter." << endl;
		break;
	case 5:
		cout << "move has already been taken please try again." << endl;
		break;
	case 6:
		cout << "It's a tie." << endl;
		break;
	case 7:
	
		for (int x = 0; x < 8; x++){
			cout << "!";
			Sleep(50);
			cout << " * ";
			Sleep(50);
		}
		cout << "Y ";
		Sleep(50);
		cout << "O ";
		Sleep(50);
		cout << "U ";
		Sleep(50);
		cout << "  W ";
		Sleep(50);
		cout << "I ";
		Sleep(50);
		cout << "N ";
		Sleep(50);
		for (int x = 0; x < 8; x++){
			cout << "!";
			Sleep(50);
			cout << " * ";
			Sleep(50);
		}
		cout<< endl;

		break;

	}

}
/*************************************************************************************************
This is the board class which simulates the physical board.The board class has only methods that
display itself for the user and has tests to describe its "physical" form.
**************************************************************************************************/
class Board{
public:
	vector<string> moves;
	Board(){

	
		moves.push_back("0");
		moves.push_back("1");
		moves.push_back("2");
		moves.push_back("3");
		moves.push_back("4");
		moves.push_back("5");
		moves.push_back("6");
		moves.push_back("7");
		moves.push_back("8");
		
	}


	void display(){
		system("CLS");
		cout << "\n";
		cout << " " << moves[0] << "|" << " " << moves[1] << " |" << " " << moves[2] << endl;
		cout << "----------" << endl;
		cout << " " << moves[3] << "|" << " " << moves[4] << " |" << " " << moves[5] << endl;
		cout << "----------" << endl;
		cout << " " << moves[6] << "|" << " " << moves[7] << " |" << " " << moves[8] << endl;
		cout << "\n";
	}


	

	bool isFree(int x){
		if (moves[x] != "X" && moves[x] != "O"){
			return true;

		}
		else{
			if (turn && isAIOn){
				//only prints out message if its users turn
				gameMessages(5);
			}
			if (!isAIOn){
				gameMessages(5);
			}
			return false;
		}
	}


	void setMove(int player_move, string symbol){
		moves[player_move] = symbol;
	}

	bool isFull(){
		//test that returns true if the all possible move have been taken and the board is indeed full
		for (int x = 0; x < moves.size(); x++){
			if (moves[x] != "X" && moves[x] != "O"){
				return false;
			}
		}
		return true;
	}

};// end board class

/****************************************************************************************
Internal methods used only by the game class
****************************************************************************************/
void getTurn(){
	//prompts a player X or O to make a move
	if (turn){
		gameMessages(3);
	}
	if (!turn && !isAIOn){
		gameMessages(4);
	}

}
void switchTurn(){
	turn = !turn;

}

bool isWinner(Board b){
	//diagonal 0/4/8
	if (b.moves[0] == b.moves[4] && b.moves[0] == b.moves[8]){
		return true;
	}
	//diagonal 2/4/6
	if (b.moves[2] == b.moves[4] && b.moves[2] == b.moves[6]){
		return true;
	}
	//horizontal cases
	for (int x = 0; x < b.moves.size(); x += 3){
		if (b.moves[x] == b.moves[x + 1] && b.moves[x] == b.moves[x + 2]){
			return true;
		}
	}
	//column cases
	for (int x = 0; x<b.moves.size()/3; x++){
		if (b.moves[x] == b.moves[x + 3] && b.moves[x] == b.moves[x + 6]){
			return true;
		}

	}

	return false;
}

bool isTie(Board b){
	if (b.isFull()){
		return true;
	}
	else{
		return false;
	}

}

void go(int input, Board& b){
	if (b.isFree(input)){
		if (turn){
			b.setMove(input, "X");
		}
		else{
			b.setMove(input, "O");
		}
		switchTurn();
	}


}

/***********************************************************************************************************************************************************
*********************************This is the CODE for the AI************************************************************************************************
************************************************************************************************************************************************************/
void setIsAIOn(){
	gameMessages(2);
	cin >> isAIOn;

}
bool testIfNextMoveIsWinForTheHumanPlayer(int n, Board b){
	if (b.isFree(n)){
		b.setMove(n, "X");
	}
	return (isWinner(b) || isTie(b)) ? true : false;
}
bool testIfNextMoveIsWinForTheAI(int n, Board b){
	if (b.isFree(n)){
		b.setMove(n, "O");
	}
	return(isWinner(b) || isTie(b)) ? true : false;

}

/***************************************************************************************************************************************************************
**** NOTE TO MY TEAMATES for the function AIMoveDecision(b, B) *lower case b is a copy of the board *Capital B is the actual Board were using's memory address
**** When b[oard] copy is finished being used by the method the compiler will throw it off the stack and no actual changes to the flow of the game is made
**** This is done so the computer may simulate a series of moves by a human and therefore decide a course of action.
***************************************************************************************************************************************************************/
void AIMoveDecision(Board b, Board &B){

	/*
	If the middle position hasnt been taken then
	the AI will take middle position.
		  | |
		--------
		  |O|
		--------
		  | |
	*/
	if (b.isFree(4)){
		go(4, B);
		return;
	}//end if


	/*

	Brute Force Attempts to see if the next move will allow for a win for the computer and/or
	block a winning move for the player.
	*/

	for (int x = 0; x<9; x++){
		if (testIfNextMoveIsWinForTheAI(x, b)){
			go(x, B);
			return;
		}
	}

	for (int z = 0; z<9; z++){

		if (testIfNextMoveIsWinForTheHumanPlayer(z, b)){
			go(z, B);
			return;
		}
	}
	//****end brute force technique.******

	
	
	
	/*
		 T| |T
		--------
		  |X|
		--------
		 T| |T

	If human player takes center piece the AI takes a corner piece

	*/


	if (b.moves[4] == "X" && (b.isFree(0))){
		go(0, B);
		return;
	}
	if (b.moves[4] == "X" && (b.isFree(2))){
		go(2, B);
		return;
	}
	if (b.moves[4] == "X" && (b.isFree(6))){
		go(6, B);
		return;
	}
	if (b.moves[4] == "X" && (b.isFree(8))){
		go(8, B);
		return;
	}




	//If no other conditions are fufilled a random position will be drawn


	srand(time(NULL));
	while (!b.isFull()){
		int random = rand() % 8;
		if (b.isFree(random)){
			go(random, B);
			return;
		}
	}



}//AI End


void Game::start(){
	Board B;
	
	gameMessages(1);
	
	setIsAIOn();
	while (true){
		B.display();
		getTurn();

		int console_input;
		// The following if else statement splits the computer onto two different paths depending if the AI is on
		if (!isAIOn){
			cin >> console_input;
			go(console_input, B);
		}
		else{
			if (turn){
				cin >> console_input;
				go(console_input, B);
			}
			else{
				AIMoveDecision(B, B);
			}
		}

		if (isWinner(B)){
			B.display();
			string winner = turn ? "O" : "X";
			cout <<"                                   Player "<<winner<<""<<endl;
			gameMessages(7);
			break;
		}
		if (isTie(B)){
			B.display();
			gameMessages(6);
			break;
		}
		

	}	
}
