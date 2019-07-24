// Simple guess the numbers game
//
// TODO: 
// 	- Clean up output
// 	- Print messages based on user performance (e.g. total guesses)
// 		- Print messages during game 
// 

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <climits>

const int EASY = 10;
const int REGULAR = 50;
const int HARD = 100;

void play(int maxNumber);
int setRandomNumber(int max);
int getIntInput(std::string message); 
std::string getStringInput();
int menuChoice(); 
int setDifficulty();

int main() {

	bool exit = false;	
	// Default difficulty is regular
	int maxNumber = REGULAR;
	// Seed random number
	srand(time(NULL));

	do {
		switch(menuChoice()) {
			case 1: 
				play(maxNumber);
				break;
			case 2:
				maxNumber = setDifficulty();
				break;
			case 3:
				exit = true;
				break;
		}
	} while(!exit);

	return 0;

}

// Plays one game of guess the number
void play(int maxNumber) {
	int guessCount = 0;
	int randomNumber, userGuess, menuChoice;
	// Set random number
	randomNumber = setRandomNumber(maxNumber);
	do {
		std::cout << "I am thinking of a number between 1 and " << maxNumber << ".\nCan you guess what my number is?" << std::endl;	
		userGuess = getIntInput("Enter your guess\n>");
		if(userGuess < 1 || userGuess > maxNumber) {
			std::cout << "Your guess is out of range" << std::endl;
			continue;
		}
		if(userGuess == randomNumber) {
			std::cout << "Good job! " << userGuess << " is the number!\nYou guessed it in " << ++guessCount << " tries." << std::endl;
		}
		else if(userGuess > randomNumber) {
			++guessCount;
			std::cout << "Nice try, but my number is lower than " << userGuess << std::endl;
		}
		else if(userGuess < randomNumber) {
			++guessCount;
			std::cout << "Nice try, but my number is higher than " << userGuess << std::endl;
		}
	} while(userGuess != randomNumber);
}

// Generates a random number
int setRandomNumber(int max) {
	int randomNumber = rand() % max + 1;
	return randomNumber;
}

// Gets integer input
int getIntInput(std::string message) {
	std::string rawInput;
	while(true) {
		std::cout << message;
		rawInput = getStringInput();
		std::stringstream stream(rawInput);

		int value;
		char temp;
		stream >> value;
		if(stream && !(stream >> temp) && value >= 0 && value <= INT_MAX) {
			return value;
		}
		else {
			std::cout << "Invalid input" << std::endl;
		}
	}
}

// Gets string input
std::string getStringInput() {
	std::string input;
	std::getline(std::cin,input);
	return input;
}

// Gets users choice for main menu
int menuChoice() {
	std::string menuMessage = "\nMain Menu\n1. Start\n2. Difficulty\n3. Quit\n>";
	while(true) {
		int selection = getIntInput(menuMessage);
		if(selection > 0 && selection <= 3) {
			return selection;
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
}

// Allows user to set difficulty
int setDifficulty() {
	std::string difficultyMessage = "Set difficulty level\n1. Easy (1-10)\n2. Regular (1-50)\n3. Hard (1-100)\n>";
	while(true) {
		int selection = getIntInput(difficultyMessage);
		switch(selection) {
			case 1:
				return EASY;
			case 2:
				return REGULAR;
			case 3:
				return HARD;
			default:
				std::cout << "Invalid Input" << std::endl;
				break;
		}
	}
}

