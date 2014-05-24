/* Lawrence Lew - TicTacToe.cpp - CS 110A
   Starting point for Programming Lab 7
   Tic Tac Toe game program
   5/20/2014
*/

#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;

// Intialize the board for the beginning of a game.
void clear(char b[][3]) {
/*
//      char temp[3][3] = {"  ", "  ", "  "};
  char *ptr = NULL;
  cout << "The ptr was set to null" << endl;
  ptr = strstr(b[0], "   \0");
//  cout << *ptr;
  cout << "Derp you are an idiot" << endl;
*/

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      b[i][j] = ' ';
  }
}

// Display the current status of the board on the
// screen, using hyphens (-) for horizontal lines
// and pipes (|) for vertical lines.
void display(const char b[][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << b[i][j];
      if (j < 2)
        cout << "|";
    }
    if (i < 2)
      cout << endl << "-----" << endl;
  }
  cout << endl << endl;
}

// Allow and displays the nextPlayer to take a turn and format of input.
// Read input and verify valid move.
// If it's invalid, re-enter it put it on the board.
void takeTurn(char b[][3], char& nextPlayer) {
  bool valid = false;
  int row = 0;
  int col = 0;
// While valid == false, the loop will keep repeating
  while (!valid) {
    cout << "It is now " << nextPlayer << "'s turn.\n";
    cout << "Please enter your move in the form row column.\n";
    cout << "So 0 0 would be the top left, and 0 2 would be the top right.\n";
    cin >> row >> col;
    cout << endl;
// Same as setting else {valid = true;} later
    valid = true;
    if (row < 0 || row > 2 || col < 0 || col > 2) {
//    if (row >=0 && row <=2 && column >= 0 && column <= 2) {
      cout << "Invalid entry: row and column must both be between 0 and 2 (inclusive).\n";
      cout << "Please try again.\n";
      valid = false;
    }
    if (b[row][col] == 'X' || b[row][col] == 'O') {
      cout << "Invalid entry: Row 0 at Column 0 already contains: " << b[row][col] << "\n";
      cout << "Please try again.\n";
      valid = false;
    }
  }
  b[row][col] = nextPlayer;
  if (nextPlayer == 'X')
    nextPlayer = 'O';
  else
    nextPlayer = 'X';
}

// Examines the board and returns one of the following:
// ' ' (a space) meaning the game is not yet over
// 'X' meaning that player X has won
// 'O' meaning that player O has won
// '?' meaning that the game is over because the board
//     is full, but no one won.
//char winner(char board[][3]) {
char winner(char b[][3]) {
// Check columns, rows, and then diagonals for winners
// we'll have 3 counters for horizontal and vertical and diagonal
  int rowCount = 0,colCount = 0,diagCount1 = 0,diagCount2 = 0,drawCount = 0;
  bool winner = false;

  char player[3] = "XO";
// Loops through both X and O player
// Alternative way is to increment player via *player++, since player is a pointer
//   for (char player[3] = "XO"; *ch [while not pointing to null]; ch++)
for (int h = 0; h < 2; h++) {
// Check rows first
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      if(b[i][j] == player[h]) {
        rowCount++;
      }
    if(rowCount == 3) {
      return player[h];   // Note, we don't need to end loop by setting false loop condition
      i = 3;              // Ends loops by setting false loop conditions
    }
    rowCount = 0;
  }

// Check columns (up to down)
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++)
      if(b[i][j] == player[h]) {
        colCount++;
      }
    if(colCount == 3) {
      return player[h];
      j = 3;     // Ends loops by setting false loop conditions
    }
    colCount = 0;
  }
// Check diagonals (2 of them)
  for (int i = 0; i < 3; i++) {
    if(b[i][i] == player[h]) {
      diagCount1++;
    }
    if(b[i][2-i] == player[h]) {
      diagCount2++;
    }
    if(diagCount1 == 3 || diagCount2 == 3) {
      i = 3;     // Ends loops by setting false loop conditions
      return player[h];
    }
  }
    diagCount1 = 0;
    diagCount2 = 0;
}
// Check to see if game has ended in a draw
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      if(b[i][j] == 'X' || b[i][j] == 'O') {
        drawCount++;
      }
  }
  if (drawCount == 9)
    return '?';
  return ' ';
}

// Pass in the character the ai is playing as along with the board.
void ai(char b[][3], char& aiPlayer) {
// First is to copy one array into another
  char copy[3][3];
  int tempXRow = -1, tempXCol = -1;
  int tempORow = -1, tempOCol = -1;
  int row = -1, col = -1;
  char player[3] = "XO";
  bool aiPlaced = false;    //Checks if AI has made a move yet

// Creates a copy of the board to use a brute force algorithm on
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      copy[i][j] = b[i][j];
  }

// ' ' (a space) meaning the game is not yet over
// 'X' meaning that player X has won
// 'O' meaning that player O has won
// '?' meaning that the game is over because the board
//     is full, but no one won.

// Brute force check "X" and "O" victory conditions
// Need to remember to "reset" or recopy the board each time ________
  for(int h = 0; h < 2; h++) {
    for(int l = 0; l < 3; l++) {
      for(int m = 0; m < 3; m++) {
        if (b[l][m] != 'X' && b[l][m] != 'O') {   //Makes sure the space isn't filled before 
          copy[l][m] = player[h];
          if(player[h] == 'X' && winner(copy) == player[h]) {     //Check if X has an endgame location and move onto O
//            cout << "Found critical block location " << l << m << endl;
            tempXRow = l;
            tempXCol = m;
            h = 1; l = 0; m = 0;                      //Proceed to check next character if end game found
          }
          for (int i = 0; i < 3; i++)       //Resets the copied matrix
            for (int j = 0; j < 3; j++)
              copy[i][j] = b[i][j];
 
//          cout << player[h] << ": " << l << ", " << m << endl;

          copy[l][m] = player[h];
 
          if(player[h] == 'O' && winner(copy) == player[h]) {
//            cout << "Found winning location " << l << m << endl;
            tempORow = l;
            tempOCol = m;
            h = 2; l = 3; m = 3;
          }
          for (int i = 0; i < 3; i++)     //Reset the copied matrix
            for (int j = 0; j < 3; j++)
              copy[i][j] = b[i][j];

        }
      }
    }
  }
//Assuming AI will be 'O' "Next 2 lines are debugging mode"
//  cout << "This board is before the AI Goes " << endl << endl;
//  display(b);

//  cout << "AI is preparing to go" << endl;
//  cout << tempORow << ", " << tempOCol << "  " << tempXRow << ", " << tempXCol << endl;
  if(tempORow != -1 && tempOCol != -1) {  //Will preference winning over blocking
    if(b[tempORow][tempOCol] != 'X' && b[tempORow][tempOCol] != 'O') {
//      cout << "Winning move executed " << tempORow << ", " << tempOCol << endl;
      b[tempORow][tempOCol] = aiPlayer;
//      cout << tempORow << ", " << tempOCol << endl;
      aiPlaced = true;
    }
  }
//  cout << "Progress of the AI after the winning move: " << aiPlaced << tempXRow << tempXCol << endl;
//-------------- Always check aiPlaced at this location
  if(aiPlaced == false && tempXRow != -1 && tempXCol != -1) { //Will block opponent if can't win
    if(b[tempXRow][tempXCol] != 'X' && b[tempXRow][tempXCol] != 'O') {
//      cout << "Critical block move executed " << tempXRow << ", " << tempXCol << endl;
      b[tempXRow][tempXCol] = aiPlayer;
//      cout << tempXRow << ", " << tempXCol << endl;
      aiPlaced = true;
    }
  }
// AI will execute random move if there is none better
  if(aiPlaced == false) {
    do {
//      cout << "Random Strategy Executed" << endl;
      row = (int)(rand() % 3);
      col = (int)(rand() % 3);
//      cout << "Row,Col " << row << ", " << col << endl;
      if (b[row][col] != 'X' && b[row][col] != 'O') {
        b[row][col] = aiPlayer;
        aiPlaced = true;
      }
    } while (aiPlaced == false);
  }

  if (aiPlayer == 'X')
    aiPlayer = 'O';
  else
    aiPlayer = 'X';

//takeTurn(board,nextPlayer);

// Employ strategy =(, 1 for going first, 1 for going second
};

// No changes needed in this function.
// It declares the variables, initializes the game,
// and plays until someone wins or the game becomes unwinnable.
int main()
{
  char board[3][3];
  char nextPlayer;
  char winningPlayer;
  char aiRecord;
  char first;

  srand(time(NULL));

  cout << "Would you like to play with the AI? (y/n): ";
  cin >> aiRecord;

// Set Tic-Tac-Toe for AI
  if (aiRecord == 'y') {
//    cout << "Alright! AI will go second so you have to advantage.\n\n";
    cout << "Alright! Do you want AI to go first?(y/n): ";
    cin >> first;

    clear(board);
// Rotate first/second player/AI, 
    if(first == 'y')
      nextPlayer = 'O';
    else
      nextPlayer = 'X';

    display(board);

    do {
      if (nextPlayer == 'X')
        takeTurn(board, nextPlayer);
      else            //if (nextPlayer == 'O')
        ai(board, nextPlayer);

      display(board);

      winningPlayer = winner(board);
    }while(winningPlayer == ' ');
  }

// Set Tic-Tac-Toe Board for players
  if (aiRecord == 'n') {
    clear(board);
    display(board);
    nextPlayer = 'X';

    do {
      takeTurn(board, nextPlayer);

      display(board);

      winningPlayer = winner(board);
    }while(winningPlayer == ' ');
  }

  if (winningPlayer == '?')
    cout << "Nobody won. Please play again.\n";
  else
    cout << "Congratulations, " << winningPlayer << " YOU WON!\n";

  return 0;
}
