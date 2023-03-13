//Made by Kevin Masson
//April 1 2022
//For CPSC3750
//Assignment 2
//This program allows a user to play tictactoe against a computer player
//using a minimax algorithm to find the optimal move
#include<iostream>
#include<limits>

using namespace std;

void setup();
void print();
bool move(int, int, char);
void minimax();
int findMax(int, int);
int findMin(int, int);
int checkWin();

//Allocates the game board, visible to all functions
char board[3][3];


int main(){
  int x,y;
  char again;

//begins the initial game loop
  do {
  int win = 0;
  cout << "You are the 'X' player.\n";
  setup(); //sets up the board

//Begins the main game loop, alternating turns until the game is finished
  while (win == 0) {
    cout << endl;
    cout << "Here is the current board:\n";
    print();
    cout << endl;


//will prompt player for a move, and repeat until a viable move is found
    cout << "Put the coordinate of your next move ('x y' notation):";
    do {
    cin >> x >> y;
  } while (!move(y,x,'h'));

//checks if the player has won
    win = checkWin();

//if the player has not won it will allow the computer to move
    if(win != 1) {
      minimax();
    }
    win = checkWin();
  }
  cout << endl;
  print();


//if there the game is finished it will display the result.
  switch(win){
    case 1:
      cout << "You have won!\n";
      break;
    case 2:
      cout << "The computer has won!\n";
      break;
    case 3:
      cout << "It's a draw!\n";
      break;
  }

//Prompts the user to choose to play again
  cout << "\nPlay again? ('y' or 'Y' for yes)";
  cin >> again;
} while (again == 'y' || again == 'Y');

//If the user does not want to play again, it ends the program
  return 0;
}

//generates the blank board
void setup(){
  for(int i = 0; i<3; i++) {
    for (int j = 0; j<3; j++) {
      board[i][j] = '-';
    }
  }
};

//outputs the current board
void print(){
  cout << "   0 1 2" << endl;
  for (int i = 0; i<3;i++) {
    cout << i << " |";
    for (int j = 0; j<3; j++){
      cout << board[i][j] << " ";
    }
    cout << "|" << endl;
  }
}

//implements the chosen move
bool move(int y, int x, char z){
  if(y>3 || x > 3 || y<0 || x<0) {
    cout << "Not a valid move\n";
    return false;
  }

  if(board[y][x] == '-'){
    if (z=='h')
      board[y][x] = 'X';
    else
      board[y][x] = 'O';

    return true;
  } else {
    cout << "Not a valid move\n";
    return false;
  }
}

//begins the minimax algorithm
void minimax()
{
    int score = numeric_limits<int>::max();
    int x, y, a, b;
    //sets the minimizing player to lowest possible number
    //and vice versa for the maximizing player
    a = numeric_limits<int>::min();
    b = numeric_limits<int>::max();
    for (int i = 0; i<3;i++) {
      for (int j = 0; j<3; j++) {
            if (board[i][j] == '-') {
                board[i][j] = 'O';

                if (checkWin() == 2) //will implement the move if it is a win
                  return;

                //checks the score of the current move
                int temp = findMax(a,b);

                if (temp < score) {
                    score = temp;
                    x = i;
                    y = j;
                }

                //resets the board for the next move
                board[i][j] = '-';
            }
        }
      }
    //implements the optimal move if no immediate win
    move(x,y,'c');
}

//finds the maximizing players best move
int findMax(int a, int b) {
  if (checkWin() == 1)
    return 10;

  if (checkWin() == 2)
    return -10;

  if (checkWin() == 3)
    return 0;

  int score = numeric_limits<int>::min();

  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      if (board[i][j] == '-') {
        board[i][j] = 'X';
        if (findMin(a,b) > score)
          score = findMin(a,b);
        board[i][j] = '-';
        if (score > a)
          a = score; //if better than the previous best, will update it
        if (score >= b)
          return score; //prunes the tree if not a viable move

      }
    }
  }

  return score;
  }

//finds the minimizing players best move
int findMin(int a, int b) {
  if (checkWin() == 1)
   return 10;

 if (checkWin() == 2)
   return -10;

 if (checkWin() == 3)
   return 0;

  int score = numeric_limits<int>::max();

  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      if (board[i][j] == '-') {
        board[i][j] = 'O';
        if (findMax(a,b) < score)
          score = findMax(a,b);
        board[i][j] = '-';
        if (score < b)
          b = score; //if better than the original best, will update it
        if (score <= a)
          return score; //prunes the tree if not a viable move
      }
    }
  }

  return score;
 }

//checks for a win/draw state
//NOTATION: return 1 for player win, return 2 for computer win,
//          return 0 for draw, return 3 for no end game state
 int checkWin(){
   //checks for horizontal win
   for (unsigned int i = 0; i < 3; i++) {
     if (board[i][0] != '-'){
      if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
        if (board[i][0] == 'X')
          return 1;
        else
          return 2;
      }
    }

    //checks for vertical win
    if (board[0][i] != '-'){
      if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
        if (board[0][i] == 'X')
          return 1;
        else
          return 2;
      }
    }

    //checks for top-left -> bottom right diagonal win
    if (board[0][0] != '-'){
      if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        if (board[0][0] == 'X')
          return 1;
        else
          return 2;
      }
    }
  }

    //checks for top right -> bottom left diagonal win
    if (board[0][2] != '-'){
      if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        if (board[0][2] == 'X')
          return 1;
        else
          return 2;
        }
      }

    //check for draw
    for (int i = 0; i<3; i++) {
      for(int j = 0; j<3; j++) {
        if (board[i][j] == '-')
          return 0;
      }
    }

    //if game is not finished it will return that info
    return 3;
 }
