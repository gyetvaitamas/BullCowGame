/*
This is the console executable, that makes use of the BullCow class
This acts as the view in MVC pattern, and is responsible for all user action.
For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


// Make syntax UE4 friendly
using FText = std::string;
using int32 = int;

// Function prototypes as outside a class
void PrintIntro();
void PlayGame(const int& NUMBER_OF_TURN);
FText GetValidGuess();
void PrintGuess(FText PlayerGuess);
bool AskToPlayAgain();
void PrintGameSummary();

// Instanciate a new game, re-use across plays
FBullCowGame BCGame;


// The entry point for our game
int main()
{
	constexpr int32 NUMBER_OF_TURN = 5;

	PrintIntro();

	do
	{
		PlayGame(NUMBER_OF_TURN);
	} while (AskToPlayAgain());
	
	return 0;
}

// Starts a new game play
void PlayGame(const int& NUMBER_OF_TURN)
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Looping for NUMBER_OF_TURN number
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText PlayerGuess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(PlayerGuess);

		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();

	return;
}

// Print the intro message when the game starts
void PrintIntro()
{
	const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << std::endl;
	std::cout << "	   __n__n__\n";
	std::cout << "    .------`-\\00/-'\n";
	std::cout << "   /  ##  ## (oo)\n";
	std::cout << "  / \## __   ./\n";
	std::cout << "     |//YY \|/\n";
	std::cout << "     |||   |||\n";
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows!\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

// Get a guess from the player, loop continually until gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl << CurrentTry << ". try of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// Assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

// Repeat the guess back to them
void PrintGuess(FText PlayerGuess)
{
	std::cout << "Your guess was " << PlayerGuess << std::endl << std::endl;
	return;
}

bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again?: ";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You win!" << std::endl;
	}
	else
	{
		std::cout << "You lose!" << std::endl;
	}
}
