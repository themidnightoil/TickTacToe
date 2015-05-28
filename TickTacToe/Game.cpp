#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include "string"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
bool turn = true;
bool isAIOn = false;


void gameMessages(int x){
	// This Method Stores all the messages for the game, this design pattern allows for a centralized place for the editting of in game messages
	// leaving the possibility for lighter weight code
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
		cout << "It's a tie." << endl;
		break;
	case 6:
		cout << "You are the winner!" << endl;
		break;
	case 7:
		cout << "move has already been taken please try again." << endl;
		break;

	}

}

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
				gameMessages(7);
			}
			if (!isAIOn){
				gameMessages(7);
			}
			return false;
		}
	}


	void setMove(int player_move, string symbol){
		moves[player_move] = symbol;
	}

	bool isFull(){
		//test that returns true if the all possible move have been taken and
		//that it the board is indeed full
		for (int x = 0; x < moves.size(); x++){
			if (moves[x] != "X" && moves[x] != "O"){
				return false;
			}
		}
		return true;
	}

};// end board class
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
	for (int x = 0; x<=b.moves.size()/3; x++){
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
	while (true && !b.isFull()){
		int random = rand() % 8;
		if (b.isFree(random)){
			go(random, B);
			return;
		}
	}//end while



}//end function





///AI End


void Game::start(){


	Board B;

	gameMessages(1);
	setIsAIOn();

	while (true){
		B.display();
		getTurn();

		int console_input;
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


		if (isTie(B)){
			B.display();
			gameMessages(5);
			break;
		}
		if (isWinner(B)){
			B.display();
			string winner = turn ? "O" : "X";
			cout <<"Player"<<winner;
			gameMessages(6);
			break;
		}

	}
	

}
