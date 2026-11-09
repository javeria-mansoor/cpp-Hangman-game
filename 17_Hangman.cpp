
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

void Initialise(char board[], char word[], int& state);
void PlayerHints(char board[], char word[], int& hint);
void BoardState(char board[]);
void getPlayersGuess(char board[], char word[], int& Wguess, int& hint);
void Category(char category[]);
int loadWords(const char filename[], char words[][30], char secret[]);
bool checkWin(char board[]);
void playGame();

// size, copy, lower, length

int size(const char word[])
{
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        count++;
    }
    return count;
}

void copy(char to[], const char from[])
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

int length(const char word[])
{
    int count = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        count++;
    }

    return count;
}

// Initialise board

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

// Display board

void BoardState(char board[])
{
    for (int i = 0; board[i] != '\0'; i++)
    {
        cout << board[i] << " ";
    }

    cout << endl;
}

// Hints

void PlayerHints(char board[], char word[], int& hint)
{
    int N = size(word);

    if (hint >= 3)
    {
        cout << "You have used all of your hints.\n";
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (board[i] == '_')
        {
            board[i] = lower(word[i]);
            hint++;

            cout << "Hint used! (" << hint << "/3)\n";
            return;
        }
    }
}

// Get player's guess

void getPlayersGuess(char board[], char word[], int& Wguess, int& hint)
{
    int N = size(word);
    int count = 0;

    char guess = ' ', temp;

    cout << "Enter your guess: ";
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
        return;
    }

    if (guess == '?')
    {
        PlayerHints(board, word, hint);
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (lower(word[i]) == guess)
        {
            board[i] = guess;
            count++;
        }
    }

    if (count == 0)
    {
        Wguess++;
        cout << "Wrong guess! (" << Wguess << "/6)\n";
    }
}

// Category selection

void Category(char category[])
{
    int cat;

    cout << "Which category do you want:\n";
    cout << "1. Animals\n";
    cout << "2. Movies\n";
    cout << "3. Sports\n";
    cout << "4. Food\n";

    cin >> cat;

    if (cat == 1)
    {
        copy(category, "Animals.txt");
    }
    else if (cat == 2)
    {
        copy(category, "Movies.txt");
    }
    else if (cat == 3)
    {
        copy(category, "Sports.txt");
    }
    else if (cat == 4)
    {
        copy(category, "food.txt");
    }
    else
    {
        cout << "Invalid category. Animals selected.\n";
        copy(category, "Animals.txt");
    }
}

// Load words from files

int loadWords(const char filename[], char words[][30], char secret[])
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Could not open file: " << filename << endl;
        return 0;
    }

    int count = 0;

    while (count < 20 && file.getline(words[count], 30))
    {
        if (length(words[count]) > 0)
        {
            count++;
        }
    }

    if (count == 0)
    {
        cout << "No words found in file.\n";
        return 0;
    }

    copy(secret, words[rand() % count]);

    return count;
}

// Check whether player has won

bool checkWin(char board[])
{
    for (int i = 0; board[i] != '\0'; i++)
    {
        if (board[i] == '_')
        {
            return false;
        }
    }

    return true;
}

// Play game

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

        if (checkWin(board))
        {
            cout << "\nYou WIN! The word was: " << secret << "\n";
            return;
        }
    }

    cout << "\nYou LOST! The word was: " << secret << "\n";
}

// Main

int main()
{
    srand(time(0));

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

    return 0;
}
