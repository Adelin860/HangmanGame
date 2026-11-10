
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// Display the hangman based on remaining attempts
void displayHangman(int attempts)
{
    switch (attempts)
    {
        case 6:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << "     |\n";
            cout << "     |\n";
            cout << "     |\n";
            cout << "     |\n";
            break;

        case 5:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "     |\n";
            cout << "     |\n";
            cout << "     |\n";
            break;

        case 4:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << " |   |\n";
            cout << "     |\n";
            cout << "     |\n";
            break;

        case 3:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "/|   |\n";
            cout << "     |\n";
            cout << "     |\n";
            break;

        case 2:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "/|\\  |\n";
            cout << "     |\n";
            cout << "     |\n";
            break;

        case 1:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "/|\\  |\n";
            cout << "/    |\n";
            cout << "     |\n";
            break;

        case 0:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "/|\\  |\n";
            cout << "/ \\  |\n";
            cout << "     |\n";
            break;
    }
}

// Select difficulty level
int selectDifficulty()
{
    int choice;

    cout << "\nSelect Difficulty:\n";
    cout << "1. Easy   (8 attempts)\n";
    cout << "2. Medium (6 attempts)\n";
    cout << "3. Hard   (4 attempts)\n";

    while (true)
    {
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3)
            break;

        cout << "Choose between 1 and 3.\n";
    }

    switch (choice)
    {
        case 1: return 8;
        case 2: return 6;
        case 3: return 4;
    }

    return 6;
}

// Display incorrect guesses
void displayIncorrectGuesses(const vector<char>& guesses)
{
    cout << "Incorrect Guesses: ";

    if (guesses.empty())
    {
        cout << "None";
    }
    else
    {
        for (char letter : guesses)
        {
            cout << letter << " ";
        }
    }

    cout << endl;
}

// Display the current word
void displayWord(const string& word)
{
    cout << "Word: ";

    for (char letter : word)
    {
        cout << letter << " ";
    }

    cout << endl;
}

// Run one round of Hangman
bool playGame(const vector<string>& words)
{
    string secretWord = words[rand() % words.size()];

    string guessedWord(secretWord.length(), '_');

    vector<char> guessedLetters;
    vector<char> incorrectGuesses;

    int attempts = selectDifficulty();

    // Save the original number of attempts
    int maxAttempts = attempts;

    while (attempts > 0 && guessedWord != secretWord)
    {
        cout << "\n================================\n";

        displayHangman(attempts);

        displayWord(guessedWord);

        displayIncorrectGuesses(incorrectGuesses);

        cout << "Guesses Left: " << attempts << "/" 
             << maxAttempts << endl;

        string input;

        cout << "Guess a letter: ";
        cin >> input;

        // Validate input length
        if (input.length() != 1)
        {
            cout << "Please enter exactly one letter.\n";
            continue;
        }

        char guess = tolower(static_cast<unsigned char>(input[0]));

        // Validate alphabetical character
        if (!isalpha(static_cast<unsigned char>(guess)))
        {
            cout << "Invalid input. Enter an alphabetic letter.\n";
            continue;
        }

        // Check whether the letter was already guessed
        bool alreadyGuessed = false;

        for (char letter : guessedLetters)
        {
            if (letter == guess)
            {
                alreadyGuessed = true;
                break;
            }
        }

        if (alreadyGuessed)
        {
            cout << "You already guessed that letter!\n";
            continue;
        }

        guessedLetters.push_back(guess);

        // Check whether the guessed letter exists
        bool correctGuess = false;

        for (int i = 0; i < secretWord.length(); i++)
        {
            if (secretWord[i] == guess)
            {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }

        if (correctGuess)
        {
            cout << "Correct guess!\n";
        }
        else
        {
            incorrectGuesses.push_back(guess);

            attempts--;

            cout << "Incorrect guess!\n";
        }
    }

    cout << "\n================================\n";

    displayHangman(attempts);

    if (guessedWord == secretWord)
    {
        cout << "\nCongratulations!\n";
        cout << "You guessed the word \""
             << secretWord << "\" correctly!\n";

        return true;
    }
    else
    {
        cout << "\nGAME OVER!\n";
        cout << "The correct word was: "
             << secretWord << endl;

        return false;
    }
}

// Main function
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    vector<string> words = {
        "teacher",
        "computer",
        "programming",
        "engineer",
        "keyboard",
        "software",
        "science",
        "university",
        "technology",
        "development"
    };

    int wins = 0;
    int losses = 0;

    char playAgain;

    cout << "================================\n";
    cout << "       WELCOME TO HANGMAN       \n";
    cout << "================================\n";

    do
    {
        bool won = playGame(words);

        if (won)
            wins++;
        else
            losses++;

        cout << "\n========== SCOREBOARD ==========\n";
        cout << "Wins:   " << wins << endl;
        cout << "Losses: " << losses << endl;

        cout << "\nWould you like to play again? (y/n): ";
        cin >> playAgain;

        playAgain = tolower(static_cast<unsigned char>(playAgain));

        while (playAgain != 'y' && playAgain != 'n')
        {
            cout << "Please enter y or n: ";
            cin >> playAgain;

            playAgain = tolower(static_cast<unsigned char>(playAgain));
        }

    } while (playAgain == 'y');

    cout << "\nThanks for playing Hangman!\n";
    cout << "Final Score: " << wins << " wins, "
         << losses << " losses.\n";

    return 0;
}
