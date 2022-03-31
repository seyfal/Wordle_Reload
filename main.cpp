#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <vector>     // Input file is stored in a vector
#include <cassert>    // For the assert statement used to validate file open
#include <cctype>     // Allows using the tolower() function
#include <ctime>      // Timer functions
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
using namespace std;

// Display welcome message, introducing the user to the program and describing the instructions for the game
void displayWelcomeMessage()
{
    cout << "Program 3: Wordle Reload \n"
        << "CS 141, Spring 2022, UIC \n"
        << " \n"
        << "The objective of this game is to guess the randomly selected \n"
        << "word within a given number of attempts. You can select either \n"
        << "a three or five word board. \n"
        << "At the conlusion of the game, stats will be displayed.  \n"
        << "Indicators will be given if characters of the user entered \n"
        << "word are reflected in the guessed word. \n"
        << "  - If the character is in the correct position, the character \n"
        << "    will display as an uppercase value.\n"
        << "  - If the character is within the random word, the character \n"
        << "    will display as a lowercase value.\n"
        << "  - If you enter a character that is not in the word, an asterisk '*' \n"
        << "    will display."
        << " \n"
        << endl;
}//end displayWelcomeMessage()

// Read words into Wordle vector.
void readWordsIntoWordle( vector <string> & wordle)
{
   // Read in dictionary into dictionary vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "wordlewords.txt");       // Open dictionary file
    assert( inStream.fail() == false );     // Ensure file open worked
    
    // If you had previously used vector dictionary, then you might want to clear it
    // before continuing to use it, though that is not the case here.
    wordle.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while( inStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        wordle.push_back( newWord);
    }
    
    // Close the dictionary file
    inStream.close();
}//end readWordsIntoWordle

// function that choses the random word from wordle.txt 
string randomWord(vector < string > wordle, int n) {

  // vector that holds all words of lenght n 
  vector < string > wordleB;

  // loop thru wordle and choose a word 
  for (int i = 0; i < wordle.size(); ++i) {

    if (wordle[i].length() % n == 0) {
      wordleB.push_back(wordle[i]);
    }
  }

  // return the word 
  return wordleB[rand() % wordleB.size()];;
} //end randomWord

// function that executes the game for the 3 word 
// takes the user input, checks it, and puts it in the brackets 
void displayBoard3(char board[3], string InputWord, string RandWord, int & NumWins, int &Time, vector < string > wordle, int & currentStreak) {
  time_t startTime = time( NULL);
  vector < string > inputAll; // vector that holds all the input 
  int attempts = 0; // attempt counter 

  for (int i = 0; i < 4; i++) { // for loop that gives 4 attempts 
    attempts += 1; // attempt + 1 
    if (i <= 4) { // if loop that executes only if less than 4 attempts has been done
      cout << "Please enter word -->  "; // ask for the input
      cin >> InputWord; // store the input 

      // check inputWord for length and execute error if not 3 lenght 
      while (InputWord.size() != 3) {
        cout << "Invalid word entry - please enter a word that is 3 characters long." << endl; // print the error 
        cout << endl;
        cout << "Please enter word -->  "; // ask for the input
        cin >> InputWord; // store the input 
      }

      // lowercase input 
      int i = 0;
      while (InputWord[i]) {
        InputWord[i] = tolower(InputWord[i]);
        i++;
      }

      while (true) {
        if (std::count(wordle.begin(), wordle.end(), InputWord)) {
          break;
        } else {
          cout << "Not a playable word, please select another word." << endl; // print the error 
          cout << endl;
          cout << "Please enter word -->  "; // ask for the input
          cin >> InputWord; // store the input 
        }
      }

      cout << endl; // whitespace 

      int elapsedSeconds = difftime( time( NULL), startTime);
      
      string out = "***"; // empty string of 3 stars 

      // iterate for 3 charecters of input
      for (int i = 0; i < 3; i++) {
        // if input charecter is equal to random word charecter it is made uppercase
        if (RandWord[i] == InputWord[i]) {
          out.at(i) = toupper(InputWord[i]); //toupper function is used to upppercase the letter
        }
        //find function is used find if the character is present in the string or not
        else if (RandWord.find(InputWord[i]) != std::string::npos) {
          out.at(i) = InputWord[i]; //toupper function is used to upppercase the letter, index = i;
        }
      }
      // push the answer without brackets to the old vector 
      inputAll.push_back(out);
      // nested for loop to create the bracket board 
      for (int s = 0; s < inputAll.size(); s++) {
        for (int d = 0; d < inputAll[s].size(); d++) {
          board[d] = inputAll[s].at(d);
        }
        for (int j = 0; j < 3; j++) // encapsulate the chars in the brackets
        {
          cout << " [ ";
          cout << board[j];
          cout << " ]  ";
        }
        cout << endl; // double end line 
        cout << endl; // double end line 
      }
      // If loop that finishes the round if won 
      if (InputWord == RandWord) {
        NumWins = NumWins + 1;
        cout << "Nice Work!  You guessed the correct word " << endl;
        cout << "  - You completed the board in: " << Time << " seconds. " << endl;
        cout << "  - It took you " << attempts << "/4 attempts." << endl;

        // add to the streak 
        currentStreak = true;
        break; // break out of the round 
      }
      if (attempts >= 4 || elapsedSeconds > 20) // if more than 4 attempts or time more 20 sec 
      {
        currentStreak = false; // reset streak 
        cout << "Maximum amount of attempts have been reached. Try again." << endl; // print the approaching of max attempts 
        cout << endl; // whitespace 
        break; // break out of the game 
      } else {
        continue;
      } // if didn't win, then continue 
    }
  }
  inputAll.clear();
} //end displayBoard3

// function that executes the game for the 5 word
// takes the user input, checks it, and puts it in the brackets 
void displayBoard5(char board[5], string InputWord, string RandWord, int & NumWins, int &Time, vector < string > wordle, int & currentStreak) {

  time_t startTime = time( NULL); 
  // vector that holds all the input 
  vector < string > inputAll;

  // attempt counter 
  int attempts = 0;
  int streak = 0;

  // for loop that gives 6 attempts 
  for (int i = 0; i < 6; i++) {

    // attempt + 1 
    attempts += 1;

    // if loop that executes only if less than 6 attempts has been done 
    if (i <= 6) {
      cout << "Please enter word -->  "; // ask for the input
      cin >> InputWord; // store the input 

      // check inputWord for length and execute error if not 3 lenght 
      while (InputWord.size() != 5) {
        cout << "Invalid word entry - please enter a word that is 5 characters long." << endl; // print the error 
        cout << endl;
        cout << "Please enter word -->  "; // ask for the input
        cin >> InputWord; // store the input 
      }

      // lowercase input 
      int i = 0;
      while (InputWord[i]) {
        InputWord[i] = tolower(InputWord[i]);
        i++;
      }

      while (true) {
        if (std::count(wordle.begin(), wordle.end(), InputWord)) {
          break;
        } else {
          cout << "Not a playable word, please select another word." << endl; // print the error 
          cout << endl;
          cout << "Please enter word -->  "; // ask for the input
          cin >> InputWord; // store the input 
        }
      }

      int elapsedSeconds = difftime( time( NULL), startTime);

      cout << endl; // whitespace 
      string out = "*****"; // empty string of 5 stars 

      // iterate for 5 charecters of input
      for (int i = 0; i < 5; i++) {
        // if input charecter is equal to random word charecter it is made uppercase
        if (RandWord[i] == InputWord[i]) {
          //toupper function is used to upppercase the letter
          out.at(i) = toupper(InputWord[i]);
        }
        //find function is used find if the character is present in the string or not
        else if (RandWord.find(InputWord[i]) != std::string::npos) {
          //toupper function is used to upppercase the letter
          out.at(i) = InputWord[i];
        }
      }
      // push the answer without brackets to the old vector 
      inputAll.push_back(out);
      // nested for loop to create the bracket board 
      for (int s = 0; s < inputAll.size(); s++) {
        for (int d = 0; d < inputAll[s].size(); d++) {
          board[d] = inputAll[s].at(d);
        }
        for (int j = 0; j < 5; j++) // encapsulate the chars in the brackets
        {
          cout << " [ ";
          cout << board[j];
          cout << " ]  ";
        }
        cout << endl; // double end line 
        cout << endl; // double end line 
      }
      // If loop that finishes the round if won 
      if (InputWord == RandWord) {
        NumWins = NumWins + 1;
        //old.clear();
        cout << "Nice Work!  You guessed the correct word " << endl;
        cout << "  - You completed the board in: " << Time << " seconds. " << endl;
        cout << "  - It took you " << attempts << "/6 attempts." << endl;

        // add to the streak 
        currentStreak = true;
        break; // break out of the round 
      }

      if (attempts >= 6 || elapsedSeconds > 40) // if more than 4 attempts or 40 seconds 
      {
        currentStreak = false; // reset streak 
        cout << "Maximum amount of attempts have been reached. Try again." << endl; // print the approaching of max attempts 
        cout << endl; // whitespace 
        break; // break out of the game 
      } else {
        continue;
      } // if didn't win, then continue 
    }
  }
  inputAll.clear();
} //end displayBoard5


int binarySearch(vector <string>wordle, string InputWord);

int binarySearch(vector <string>wordle, string InputWord)
{
    int size = wordle.size(); 
    int first = 0,             // First array element
        last = size - 1,       // Last array element
        middle,                // Mid point of search
        position = -1;         // Position of search value
    bool found = false;        // Flag

    while (!found && first <= last)
    {
        middle = (first + last) / 2;     // Calculate mid point
        if (wordle[middle] == InputWord)      // If input is found at mid
        {
            found = true;
            position = middle;
        }
        else if (wordle[middle] > InputWord)  // If input is in lower half
            last = middle - 1; 
        else
            first = middle + 1;      // If input is in upper half
    }
    return found;
}


// initialize main
int main() {
  srand(1); // make it predictable for now

  int currentStreak = 0; // current streak
  string InputWord; 
  string RandWord;
  string out; // string that contains the OUTput of the code that goes into brackets 
  int menuOptions;
  int Time = 0; // Will store number of elapsed seconds
  int LongestStreak = 0; // longest streak
  int NumWins = 0;
  int addStreak = 0;
  vector < string > wordle; // Stores words from input file into dictionary vector

  readWordsIntoWordle(wordle); // Read the wordlewords.txt 
  displayWelcomeMessage(); // display the welcome message

  time_t startTime = time( NULL);

  while (menuOptions != 3) {

    // if streak is zero don't add to longest streak
    if (currentStreak == 0) {
      addStreak = 0;
    }
    if (currentStreak == 1) {
      addStreak++;
      if (addStreak > LongestStreak) {
        LongestStreak = addStreak;
      }
    }
    // display the main menu
    cout << "Select a menu option: \n" <<
      "   1. To play Wordle Reload 3 letter play \n" <<
      "   2. To play Wordle Reload 5 letter play \n" <<
      "   3. Exit the program\n" <<
      "Your choice --> ";

    cin >> menuOptions; //request the input for the menu 

    // if input is 3, exit the program and show overall stats
    if (menuOptions == 3) {
      // show the overall stats
      cout << endl;
      cout << "Overall Stats: " << endl;
      cout << "  - You guessed: " << NumWins << endl;
      cout << "  - Your longest streak is: " << LongestStreak << endl;
      if (LongestStreak > 0) {
        cout << "  - Average word completion time: " << Time << endl;
      } else {
        cout << "  - Average word completion time: N/A" << endl;
      }
      cout << "Exiting program" << endl; // display the "exiting the program"
      break; // break the loop to exit the program
    } //end if input is 3

    // play the 3 letter game by ... 
    if (menuOptions == 1) {
      char board3[3] = {
        ' ',
        ' ',
        ' '
      };
      // assign random word from wordle.txt to RandWord 
      RandWord = randomWord(wordle, 3);
      // display the get started message without the "Please enter the word -->" part 
      cout << "To get started, enter your first 3 letter word.\n" <<
        "You have 4 attempts to guess the random word.\n" <<
        "The timer will start after your first word entry.\n" <<
        "Try to guess the word within 20 seconds.\n" <<
        "\n" <<
        endl;
      // call game driver 
      displayBoard3(board3, InputWord, RandWord, NumWins, Time, wordle, currentStreak);

    } //end if input is 2

    if (menuOptions == 2) {
      char board5[5] = {
        ' ',
        ' ',
        ' ',
        ' ',
        ' '
      };
      // assign random word from wordle.txt to RandWord 
      RandWord = randomWord(wordle, 5);
      // display the get started message without the "Please enter the word -->" part 
      cout << "To get started, enter your first 5 letter word.\n" <<
        "You have 6 attempts to guess the random word.\n" <<
        "The timer will start after your first word entry.\n" <<
        "Try to guess the word within 40 seconds.\n" <<
        "\n" <<
        endl;
      // call game driver 
      displayBoard5(board5, InputWord, RandWord, NumWins, Time, wordle, currentStreak);
    } //end if input is 3
  }
  return 0;
} //end main 