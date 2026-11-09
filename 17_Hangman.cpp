#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void Initialise(char board[], char word[], int& state);
void PlayerHints(char board[], char word[], int& hint);
void BoardState(char board[]);
void getPlayersGuess(char board[], char word[], int& Wguess, int& hint);
void Category(char category[]);
int loadWords(const char filename[], char words[][30], char secret[]);
void GameResult(char board[], int N, char word[], int& Wguess);
void playGame();

//size, strcpy, tolower, strlen
int size(char word[])
{
	int count = 0;
	for (int i = 0; word[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}

void copy(char to[], char from[])
{
	for (int i = 0; i < size(from); i++)
	{
		to[i] = from[i];
	}
	to[size(from)] = '\0';
}

char lower(char g)
{
	if (g >= 'A' && g <= 'Z')
	{
		g += 32;
	}

	return g;
}
int compare(char board[], char word[])
{
	int i = 0;
	while (word[i] != '\0' && board[i] != '\0')
	{
		if (board[i] != word[i])
		{
			return (word[i] - board[i]);
		}
		i++;
	}

}
int length(char word[])
{
	int count = 0;
	for (int i = 0; word[i] != '\0'; i++)
	{
		count++;
	}

	return count;
}

//boardstate
void Initialise(char board[], char word[], int& state)
{
	int N = size(word);
	for (int i = 0; i < N; i++)
	{
		if (word[i] == ' ')
		{
			board[i] = ' ';
		}
		else
		{
			board[i] = '_';
		}
	}
	board[N] = '\0';
	state = 1;
}

void BoardState(char board[])
{

	for (int i = 0; board[i] != '\0'; i++)
	{
		cout << board[i] << " ";

	}
	cout << endl;
}

//hint
void PlayerHints(char board[], char word[], int& hint)
{
	int N = size(word);

	if (hint >= 3)
	{
		cout << "You have used all of your hints.\n";
		return;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			if (board[i] == '_')
			{
				board[i] = word[i];
				hint++;
				cout << "Hint used! (" << hint << "/3)\n";
				return;
			}
		}
	}
}

//getplayerguess
void getPlayersGuess(char board[], char word[], int& Wguess, int& hint)
{
	int N = size(word);
	int count = 0;
	char guess = ' ', temp;

	cout << "Enter you guess: ";
	cin >> temp;
	if (temp >= 'A' && temp <= 'Z')
	{
		guess = lower(temp);
	}
	else if (temp >= 'a' && temp <= 'z')
	{
		guess = temp;
	}
	else if (temp == '?')
	{
		guess = temp;
	}
	else
	{
		cout << "Wrong input.\n";
	}

	if (guess == '?')
	{
		PlayerHints(board, word, hint);
		return;
	}

	for (int i = 0; i < N; i++)
	{
		if (word[i] == guess)
		{
			board[i] = guess;
			count++;
		}
	}

	if (count == 0)
	{
		Wguess++;
	}

}

//load files
void Category(char category[])
{
	int cat;
	cout << "Which category do you want:\n1. Animals\n2. Movies\n3. Sports\n4. Food\n";
	{
		cin >> cat;
	}

	if (cat == 1)
	{
		copy(category, (char*)"Animals.txt");
	}
	else if (cat == 2)
	{
		copy(category, (char*)"Movies.txt");
	}
	else if (cat == 3)
	{
		copy(category, (char*)"Sports.txt");
	}
	else if (cat == 4)
	{
		copy(category, (char*)"food.txt");
	}
	else
	{
		copy(category, (char*)"Animals.txt");
	}
}

int loadWords(const char filename[], char words[][30], char secret[])
{
	ifstream file(filename);

	if (!file)
	{
		cout << "Could not open file: " << filename << endl;
	}

	int count = 0;

	while (count < 20 && file.getline(words[count], 30))
	{
		if (length(words[count]) > 0)
		{
			count++;
		}
	}


	copy(secret, words[rand() % count]);

	return count;
}

//won or not
void GameResult(char board[], int N, char word[], int& Wguess)
{
	bool flag = false;

	for (int i = 0; i < N; i++)
	{
		if (board[i] == '_')
		{
			flag = false;
			break;
		}
		else
		{
			flag = true;
		}
	}
	if (Wguess < 6 && flag == true)
	{
		cout << "You have Won.\n";
	}
	else
	{
		cout << "You have lost.\n";
	}
}

//playgame
void playGame()
{
	char filename[30], words[100][30], secret[30], board[30];
	int wrong = 0, hints = 0, state = 0;

	Category(filename);

	if (loadWords(filename, words, secret) == 0)
	{
		return;
	}

	Initialise(board, secret, state);

	while (wrong < 6)
	{
		cout << "\nWord: ";
		BoardState(board);

		getPlayersGuess(board, secret, wrong, hints);

		if (compare(board, secret) == 0)
		{
			cout << "\nYou WIN! The word was: " << secret << "\n";
			return;
		}
	}

	cout << "\nYou LOST! The word was: " << secret << "\n";
}


int main()
{
	char again;
	while (true)
	{
		playGame();

		cout << "\nDo you want to play again? (y/n): ";
		cin >> again;

		if (again != 'y' && again != 'Y')
		{
			cout << "Goodbye!\n";
			break;
		}
	}
}
