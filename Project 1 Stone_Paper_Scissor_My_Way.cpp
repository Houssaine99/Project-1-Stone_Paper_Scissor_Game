#include <iostream>

using namespace std;

// Inputs:

enum enChoices { Stone = 1, Paper = 2, Scissor = 3 };

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

int ReadNumberInRange(string Message, int From, int To)
{
	int InputValue = 0;
	
	do
	{
		cout << Message;
		cin >> InputValue;

	} while (InputValue < From || InputValue > To);

	return InputValue;
}

int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;

	return RandomNumber;
}

short NumberOfRounds()
{
	short Number_Of_Rounds = ReadNumberInRange("How many Rounds You Want To Play 1 to 10:\n", 1, 10);

	return Number_Of_Rounds;

}

void PrintStartOfRound(int RoundNumber)
{
	cout << "\nRound [" << RoundNumber << "] begins:\n";
}

enChoices GetPlayerChoice()
{
	short Player_Choice = ReadNumberInRange("\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissor? ", 1, 3);

	return (enChoices)Player_Choice;
}

enChoices GenerateComputerChoice()
{
	short Computer_Choice = RandomNumber(1, 3);

	return (enChoices)Computer_Choice;
}

string ToStrChoices(enChoices Choice)
{
	switch (Choice)
	{
	case enChoices::Stone:
		return "Stone";
	case enChoices::Paper:
		return "Paper";
	case enChoices::Scissor:
		return "Scissor";
	default:
		return "Something Wrong!";
	}
}

// Processing:

enWinner CheckWhoWinsTheRound(enChoices Player_Choice, enChoices Computer_Choice)
{
	if (Player_Choice == Computer_Choice)
		return enWinner::Draw;
	else if (Player_Choice == enChoices::Stone)
	{
		if (Computer_Choice == enChoices::Scissor)
			return enWinner::Player;
		else
			return enWinner::Computer;
	}
	else if (Player_Choice == enChoices::Paper)
	{
		if (Computer_Choice == enChoices::Stone)
			return enWinner::Player;
		else
			return enWinner::Computer;
	}
	else if (Player_Choice == enChoices::Scissor)
	{
		if (Computer_Choice == enChoices::Paper)
			return enWinner::Player;
		else
			return enWinner::Computer;
	}
}

void GetScore(enWinner Who_Won, int& Player_Score, int& Computer_Score, int& Draw_Score)
{
	switch (Who_Won)
	{
	case enWinner::Computer:
		Computer_Score++;
		break;
	case enWinner::Player:
		Player_Score++;
		break;
	default:
		Draw_Score++;
		break;
	}
}

enWinner CheckWhoWinsTheGame(int Player_Score, int Computer_Score)
{
	if (Player_Score > Computer_Score)
		return enWinner::Player;
	else if (Player_Score < Computer_Score)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

void ChangeColor(enWinner Who_Won)
{
	switch (Who_Won)
	{
	case enWinner::Computer:
		cout << "\a";
		system("color 4F");
		break;
	case enWinner::Player:
		system("color 2F");
		break;
	default:
		system("color 6F");
		break;
	}
}

string ToStrWhoWins(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Computer:
		return "Computer";
	case enWinner::Player:
		return "Player";
	case enWinner::Draw:
		return "No Winner";
	}
}

// OutPut:

void ShowOneRound(short Round_Number, enChoices Player_Choice, enChoices Computer_Choice, enWinner Winner)
{
	cout << "\n______________Round [" << Round_Number << "]______________\n";
	cout << "\nPlayer Choice  : " << ToStrChoices(Player_Choice) << endl;
	cout << "Computer Choice: " << ToStrChoices(Computer_Choice) << endl;
	cout << "Round Winner   : [" << ToStrWhoWins(Winner) << "]\n";
	cout << "_____________________________________\n";
}

void ShowAllGameRounds(short Number_of_Rounds, int& Player_Score, int& Computer_Score, int& Draw_Score)
{
	enChoices Computer_Choice, Player_Choice;
	enWinner Who_Wins;
	
	for (int i = 1; i <= Number_of_Rounds; i++)
	{
		PrintStartOfRound(i);

		Player_Choice = GetPlayerChoice();
		Computer_Choice = GenerateComputerChoice();
		Who_Wins = CheckWhoWinsTheRound(Player_Choice, Computer_Choice);

		GetScore(Who_Wins, Player_Score, Computer_Score, Draw_Score);

		ChangeColor(Who_Wins);

		ShowOneRound(i, Player_Choice, Computer_Choice, Who_Wins);
	}
}

void ShowFinalResults(short Number_of_Rounds, int Player_Score, int Computer_Score, int Draw_Times)
{
	cout << "\n\t\t------------------------------------------------------------\n";
	cout << "\n\t\t                  +++ G a m e  O v e r +++                  \n";
	cout << "\n\t\t------------------------------------------------------------\n";
	cout << "\t\t_____________________ [Game   Results] _____________________\n";
	cout << "\n\t\tGame Rounds        : " << Number_of_Rounds << endl;
	cout << "\t\tPlayer Won Times   : " << Player_Score << endl;
	cout << "\t\tComputer Won Times : " << Computer_Score << endl;
	cout << "\t\tDraw Times         : " << Draw_Times << endl;
	cout << "\t\tFinal Winner       : " << ToStrWhoWins(CheckWhoWinsTheGame(Player_Score, Computer_Score)) << endl;
	cout << "\t\t____________________________________________________________\n";

}

char PlayAgain()
{
	char Play_Again = 'y';

	do
	{
		cout << "\n\t\tDo you want to play again? Y/N? ";
		cin >> Play_Again;
		cout << endl;

	} while (Play_Again != 'Y' && Play_Again != 'N' && Play_Again != 'n' && Play_Again != 'y');

	return Play_Again;
}

void Game()
{
	short Rounds_Number = 0;
	char Play;

	do
	{
		int Player_Score = 0;
		int Computer_Score = 0;
		int Draw_Times = 0;

		system("color 0F");

		Rounds_Number = NumberOfRounds();

		ShowAllGameRounds(Rounds_Number, Player_Score, Computer_Score, Draw_Times);

		ShowFinalResults(Rounds_Number, Player_Score, Computer_Score, Draw_Times);

		Play = PlayAgain();

	} while (Play == 'y' || Play == 'Y');

}

int main()
{
	srand((unsigned)time(NULL));

	Game();

	return 0;
}