//Group Project: Hangman
//Team Members: Anusha Nandam, Truc Phan, Briana Sze
//Created on April 10, 2020
//CS 113 Group Project
/*
 We are making a Hangman game in C++. In the game, there will be 2 players. Player 1 will be
 typing in a word for the other player to guess. After Player 1 types the word, the number of
 characters in the word would be visible to Player 2. The objective of the game is for Player 2
 to guess Player 1's word. If player 2 guesses wrong, a graphic of the Hangman will appear. If
 the complete graphic of the Hangman appears, then Player 2 has lost. Otherwise, if player 2
 guessed the word, it would be their turn to challenge player 1. This game is in a continuous
 loop until the players decide to quit. In addition to this, a 1 player mode has been added
 so that player 1 can play against the computer. We will implement a truth table to check
 player 2’s answer.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <vector>

using namespace std;

string KEY_WORD; // Player 1 types this word for Player 2 to guess
int incorrect;
string letters_guessed; //current letters guessed
string chosen_letters;// compilation of the letters guessed in the past
const int MAX_INCORRECT = 6;  // there is a max of 6 wrong guesses allowed

//function prototypes
int mainMenu();
void askInfo(string a, string b);
bool game(char character, string p1_word);
void printGuess(string p, string des, int max, int incorr, string chosen, string guessed);
int* assignTruthValues(string a);
char progressGuess(string a);
bool repeatGame();
void printHangman(int a);

int main()
{
  //declare variables
    string p1, p2, description;
    int choice;
    vector <string> list;
    int *val;

 //start of loop
    bool done = false;
    do
    {
        choice = mainMenu();


      //one player mode - play with computer
        if(choice==1) {
          incorrect=0;
            cout << "Please enter your name:\n";
            cin.ignore();
            getline(cin,p2);

            srand(time(0));
            list.push_back("ASPARAGUS");
            list.push_back("HIPPOCAMPUS");
            list.push_back("INCUMBENT");
            list.push_back("ARRAY");
            list.push_back("KOMBUCHA");
            list.push_back("ONTO");
          	list.push_back("TRIOXYGEN");
          	list.push_back("REGGAETON");

            random_shuffle(list.begin(), list.end());
            KEY_WORD = list[0];
            val = assignTruthValues(KEY_WORD);

            if (val[0]==0 && val[1]==0 && val[2]==0) {
                description="A common vegetable used to serve with steak.\n";
            }
            else if (val[0]==0 && val[1]==0 && val[2]==1) {
                description="A brain structure whose major function is learning and memorizing.\n";
            }
            else if (val[0]==0 && val[1]==1 && val[2]==0) {
                description="An official who is currently holding office (usually referred in the govenrment).\n";
            }
            else if (val[0]==0 && val[1]==1 && val[2]==1) {
                description="A data structure which is efficient to access random data.\n";
            }
            else if (val[0]==1 && val[1]==0 && val[2]==0) {
                description="A drink made popular by Millenials and Gen Z.\n";
            }
            else if (val[0]==1 && val[1]==0 && val[2]==1) {
                description="A function is called ____ if every element of set B is mapped to by some element of set A.\n";
            }
            else if (val[0]==1 && val[1]==1 && val[2]==0) {
                description="Another word for ozone.\n";
            }
            else if (val[0]==1 && val[1]==1 && val[2]==1) {
                description="A music genre which combines Jamaican and urban Latin music.\n";
            }

            askInfo(p2, description);
        }

      	//two players mode
        else if(choice==2) {
          incorrect=0;
            cout << "Player 1. Please enter your name:\n";
            cin.ignore();
            getline(cin, p1);
            cout << "Player 2. Please enter your name:\n";
            getline(cin, p2);

            cout << "Hello " << p1 << "! Please enter the word for "
            << p2 << " to guess.\n";
            getline(cin, KEY_WORD);
            for (int i=0; i<KEY_WORD.size(); i++)
            {
                KEY_WORD[i]=toupper(KEY_WORD[i]);
            }
            cout << "Now, please enter some words to describe the word for "
            << p2 <<".\n";
            getline(cin, description);

            askInfo(p2, description);
        }

    } while(repeatGame());

    return 0;
}

int mainMenu()
{
    int c;
    cout << "\nWelcome to Hangman! Please select 1 or 2:\n"
         << "1. One player mode\n"
         << "2. Two players mode\n";
    cin >> c;
    while (cin.fail() || (c!=1 && c!=2)) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid input. Please enter again:\n";
        cin >> c;
    }
    return c;
}

void askInfo(string a, string b)
{
    letters_guessed = string(KEY_WORD.size(), '-'); // progress of the word being guessed
    chosen_letters = "";                            // letters that player 2 has already chosen

    // loop for the word that player 2 is guessing
    while ((incorrect < MAX_INCORRECT) && (letters_guessed != KEY_WORD))
    {
        printGuess(a, b, MAX_INCORRECT, incorrect, chosen_letters, letters_guessed);

        chosen_letters += progressGuess(chosen_letters);
    }

    if (incorrect == MAX_INCORRECT) {
        cout << "\nYou have no more guesses!\n";
        cout<< "   -------   " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "   -------   " << endl
            << "   \\  |  /  " << endl
            << "    \\ | /   " << endl
            << "     \\|/    " << endl
            << "      |      " << endl
            << "      |      " << endl
            << "     / \\    " << endl
            << "    /   \\   " << endl
            << "   /     \\  " << endl;
    }

    cout << "\nCorrect Word: " << KEY_WORD << endl;
}

inline bool game(char character, string p1_word)
{
       return ( p1_word.find(character) != string::npos );
}

void printGuess(string p, string des, int max, int incorr, string chosen, string guessed)
{
	cout << "\n\nHello " << p << "! The description for the word you"
		<< " are going to guess is: " << des << ".\n";
	cout << "\nYou have " << (max - incorr) << " guesses left! \n";
	cout << "\nThese are the letters that you have already chosen: \n" << chosen << endl;
	cout << "\nThis is the progress of the word you are trying to guess: \n" << guessed << endl;
}

int* assignTruthValues(string a)
{
    static int b[3];
    bool truthTable[8][3] = {
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1},
    }; //the truth table presented by the array
    if (a=="ASPARAGUS") {for(int i=0; i<3; i++) {b[i]=truthTable[0][i];}}
    else if (a=="HIPPOCAMPUS") {for(int i=0; i<3; i++) {b[i]=truthTable[1][i];}}
    else if (a=="INCUMBENT") {for(int i=0; i<3; i++) {b[i]=truthTable[2][i];}}
    else if (a=="ARRAY") {for(int i=0; i<3; i++) {b[i]=truthTable[3][i];}}
    else if (a=="KOMBUCHA") {for(int i=0; i<3; i++) {b[i]=truthTable[4][i];}}
    else if (a=="ONTO") {for(int i=0; i<3; i++) {b[i]=truthTable[5][i];}}
    else if (a=="TRIOXYGEN") {for(int i=0; i<3; i++) {b[i]=truthTable[6][i];}}
    else if (a=="REGGAETON") {for(int i=0; i<3; i++) {b[i]=truthTable[7][i];}}

    return b;
}

char progressGuess(string a)
{
    char p2_guess;
    cout << "\n\nWhat letter do you want to guess? ";
    cin >> p2_guess;
    p2_guess = toupper(p2_guess);

    while (game(p2_guess, chosen_letters))
    {
        cout << "\nThat letter has already been guessed! " << p2_guess << endl;
        cout << "What letter do you want to guess? ";
        cin >> p2_guess;
        p2_guess = toupper(p2_guess);
    }


//if Player 2 guesses a letter in Player 1's word correctly
    if (game(p2_guess, KEY_WORD))
    {
        cout << "Good guess! " << p2_guess << " is one of the letters in the secret word.\n";

        // letters_guessed news to be updated every time O=Player 2 guesses a new letter
        for (int i = 0; i < KEY_WORD.length(); ++i)
            if (KEY_WORD[i] == p2_guess)
                letters_guessed[i] = p2_guess;
    }
    //if Player 2 guesses a letter in Player 1's word incorrectly
    else
    {
        cout << "That was a good attempt, but " << p2_guess << " is not one of the letters in the secret word.\n";
        incorrect++;
        printHangman(incorrect);
    }
    return p2_guess;
}

bool repeatGame() ///repeat the game until user decides to stop
{
    char rounds;
    cout << "\n\nAre you ready for the next round? (Y/N): ";
    cin >> rounds;
    rounds = toupper(rounds);

    cin.clear();
    cin.ignore();

    if (rounds=='Y')
        return true;
    else
        return false;
}

void printHangman(int a)
{
    if (a==1)
    {
      cout << "   -------   " << endl
             << "  |       |  " << endl
             << "  |       |  " << endl
             << "  |       |  " << endl
             << "   -------   " << endl;
    }
    if (a==2)
    {
      cout<< "   -------   " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "   -------   " << endl
            << "      |    " << endl
            << "      |    " << endl
            << "      |    " << endl
            << "      |      " << endl
            << "      |      " << endl;

    }
    if (a==3)
    {
      cout << "   -------   " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "   -------   " << endl
            << "   \\  |    " << endl
            << "    \\ |    " << endl
            << "     \\|    " << endl
            << "      |      " << endl
            << "      |      " << endl;
    }
    if (a==4)
    {
        cout<< "   -------   " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "   -------   " << endl
            << "   \\  |  /  " << endl
            << "    \\ | /   " << endl
            << "     \\|/    " << endl
            << "      |      " << endl
            << "      |      " << endl;
    }
    if (a==5)
    {
        cout<< "   -------   " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "  |       |  " << endl
            << "   -------   " << endl
            << "   \\  |  /  " << endl
            << "    \\ | /   " << endl
            << "     \\|/    " << endl
            << "      |      " << endl
            << "      |      " << endl
            << "     /     " << endl
            << "    /      " << endl
            << "   /       " << endl;
    }
}
