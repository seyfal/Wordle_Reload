# Wordle_Reload
Wordle Reloaded introduces a delightful twist to the classic game. Now, you have the choice to play either a three-letter or five-letter Wordle board game. To make things easy, we have bundled a text file filled with sorted three and five-letter words for your gaming pleasure. 

The game offers various hints based on the user's guesses:
1. If a character in the guessed word is in the correct position, it is displayed in uppercase.
2. If a character in the guessed word is in the incorrect position but exists in the target word, it is displayed in lowercase.
3. Incorrect characters are shown as asterisks ('*').


## How to Play?

When you guess a word, indicators are given to show how close (or far) you are from the mystery word:

### 1. Uppercase Letters:
If a character from your guessed word matches the mystery word and is in the correct position, it will be displayed as an uppercase letter.

Example:
```
Random word:  fan
Guessed word: sad
Output:      [ * ]  [ A ]  [ * ]
```

### 2. Lowercase Letters:
If a character from your guessed word is present in the mystery word but is in the wrong position, it will be displayed as a lowercase letter.

Example:
```
Random word: fan
Guessed word: net
Output:      [ n ]  [ * ]  [ * ]
```

### 3. Asterisk '*':
For any character in your guessed word that does not appear in the mystery word, an asterisk '*' will be displayed.

Example:
```
Random word: fan
Guessed word: tic
Output:      [ * ]  [ * ]  [ * ]
```

## Ready to Play?
Dive in and enjoy Wordle Reloaded. Remember, whether it's three letters or five, the fun remains just as high!

## Requirements
- A C++ compiler to compile and run the program.
- `wordlewords.txt`: A dictionary file containing valid words for the game.

## How to Compile and Execute

1. Ensure the `wordlewords.txt` file is in the same directory as the game source code.
2. Compile the program using the following command:
```bash
g++ <filename>.cpp -o wordleReloadGame
```
Replace `<filename>` with the name of the C++ source file.

3. Execute the game:
```bash
./wordleReloadGame
```

## How the Program Works

1. **Initialization**: 
   - The program starts by displaying a welcome message to the user.
   - The words from `wordlewords.txt` are read into a vector named `wordle`.

2. **Random Word Selection**: 
   - A word of either three or five letters is randomly chosen from the `wordle` vector based on the game mode chosen by the user.

3. **Game Execution**: 
   - The user is prompted to input a word of the specified length.
   - The game checks if the input word is of the correct length and if it exists in the dictionary.
   - The user's input is compared with the random word to give feedback as described above.
   - This process is repeated until the user guesses the word or runs out of attempts.

4. **Binary Search**: 
   - The program also includes a binary search function that searches for a given word in the `wordle` vector. It returns a boolean indicating if the word was found.

5. **Statistics**:
   - At the end of each round, the game provides statistics, such as the time taken and the number of attempts made.

## Notes

- The user has a maximum of 4 attempts for the three-letter word mode and 6 attempts for the five-letter word mode.
- The game also includes time constraints. For the three-letter word mode, the user has a maximum of 20 seconds, and for the five-letter word mode, the user has a maximum of 40 seconds.
- The streak system can be extended to keep track of consecutive successful guesses.

## Enhancements and Modifications
If you wish to add new words or modify the existing word list, simply make changes to the `wordlewords.txt` file.

## License
Ensure to give credit to the original creators or source if you intend to use, distribute or modify this game for non-personal or commercial purposes.
