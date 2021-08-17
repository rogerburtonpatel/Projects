// Roger Burtonpatel
// 2020/07/20

//Extra Credit 1 complete using boolean somethingChanged

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "game.h"
#include "int-string.h"


using namespace std;

const string UP = "w";
const string LEFT = "a";
const string DOWN = "s";
const string RIGHT = "d";
const string QUIT = "q";
const string BLANK = "-";


//Game Class
Game::Game()
{
    board_size = get_board_size(); // Gets a board size from the user
    score = 0;
    gameOver = false;
    board = new int*[board_size]; // Allocates a new board on the heap
    for (int i = 0; i < board_size; i++) {
       board[i] = new int[board_size];
    }
    for (int i = 0; i < board_size; i++) { // Fills the board with zeroes
       board[i][i] = 0;
    }

    cout << "Starting game!" << endl;
}

Game::~Game()
{
    delete [] board;
}

void Game::play() // Play function. Generates 2 new tiles on the empty board, then loops.
{
    generate_new_tile();
    generate_new_tile();
    do {
       print_board();
       cout << endl;
       get_input();
       game_over();
       print_score();
  } while (gameOver != true);
}

void Game::print_number(string num) {
    printf("%-6s", num.c_str());
}

int Game::get_board_size()
{
  int board_size;
  cout << "Enter desired dimension of board:" << endl;
  cin >> board_size;
  if (board_size < 2) {
    cout << "Must input an integer board dimension greater than 2." << endl;
    exit(1);
  }
  return board_size;
}

void Game::generate_new_tile() //Generates a new random tile
{
  srand(time(NULL));
    int num_blank = 0;
    int randomize_tile;
    int randomize_4_or_2;
    int count;
    bool tile_generated = false;
    for (int i = 0; i < board_size; i++) {
      for (int j = 0; j < board_size; j++) {
       if (board[i][j] == 0) {
         num_blank++;
       }
    }
  }

  randomize_tile = rand() % num_blank + 1;
  randomize_4_or_2 = rand() % 10;
  count = 0;
  for (int i = 0; i < board_size; i++) {
    for (int j = 0; j < board_size; j++) { // ***reads through board, finds all blank spots***
     if (board[i][j] == 0) {
        count++;
        if (count == randomize_tile) {
             if (randomize_4_or_2 == 0) { // ***picks 4 based on 1/10 chance***
               board[i][j] = 4;
               tile_generated = true;
               return;
             }
            else {
                board[i][j] = 2;
                tile_generated = true;
                return;
             }
         }
        }
     }
   }
 }

void Game::print_board() // prints the board
{
   for (int i = 0; i < board_size; i++) {
     for (int j = 0; j < board_size; j++) {
      if (board[i][j] == 0) {
        print_number(BLANK);
      }
      else {
      print_number(int2string(board[i][j]));
      }
   }
   cout << endl;
 }
}



void Game::get_input() // gets an input; rejects invalid inputs
{
   string input;
   cin >> input;
   if (input == QUIT) {
      gameOver = end_game();
   }

      // ***this first block determines if 2 identical numbers are contiguous and/or only have zeroes in between them,
      // ***and sums them if the conditions are met. This is acheived using nested for loops, ifs, and break.***
   else if (input == UP) {
       somethingChanged = false; // ***initialized as false; changes to true if board changes***
       for (int i = 0; i < board_size; i++) {
         for (int j = 0; j < board_size; j++) {
           if (board[i][j] != 0) {
               for (int k = i + 1; k < board_size; k++) {
                  if (board[k][j] != 0) {
                     if (board[k][j] == board[i][j]) {
                        board[i][j] = (board[i][j] + board[k][j]);
                        score += board[i][j];
                        board[k][j] = 0;
                        somethingChanged = true;
                        break;
                     }
                break;
                }
              }
          }
       }
     }
    shift_up();
   }

   else if (input == DOWN) {
     somethingChanged = false;
          for (int i = board_size - 1; i >= 0; i--) {
            for (int j = board_size - 1; j >= 0; j--) {
              if (board[i][j] != 0) {
                  for (int k = i - 1; k >= 0; k--) {
                     if (board[k][j] != 0) {
                     if (board[k][j] == board[i][j]) {
                       board[i][j] = (board[k][j] + board [i][j]);
                       score += board[i][j];
                       board[k][j] = 0;
                       somethingChanged = true;
                       break;
                   }
                   break;
                 }
               }
            }
         }
       }
   shift_down();

   }

   else if (input == LEFT) {
     somethingChanged = false;
     for (int i = 0; i < board_size; i++) {
       for (int j = 0; j < board_size; j++) {
         if (board[i][j] != 0) {
             for (int k = j + 1; k < board_size; k++) {
                if (board[i][k] != 0) {
                   if (board[i][k] == board[i][j]) {
                      board[i][j] = (board[i][j] + board[i][k]);
                      score += board[i][j];
                      board[i][k] = 0;
                      somethingChanged = true;
                      break;
                   }
              break;
              }
            }
        }
     }
   }
   shift_left();
}
   else if (input == RIGHT) {
     somethingChanged = false;
          for (int i = board_size - 1; i >= 0; i--) {
            for (int j = board_size - 1; j >= 0; j--) {
              if (board[i][j] != 0) {
                  for (int k = j - 1; k >= 0; k--) {
                     if (board[i][k] != 0) {
                     if (board[i][k] == board[i][j]) {
                       board[i][j] = (board[i][k] + board [i][j]);
                       score += board[i][j];
                       board[i][k] = 0;
                       somethingChanged = true;
                       break;
                   }
                   break;
                 }
               }
            }
         }
       }
   shift_right();

 }

 else {
    cout << "Command not recognized. Please try again." << endl;
 }
}



void Game::shift_left()
{
  // ***this second block moves tiles after all addition has been performed.
  // ***again, nested for loops, if, and break are used.***
  for (int i = 0; i < board_size; i++) {
     for (int j = 0; j < board_size; j++) {
       if (board[i][j] != 0) {
         for (int k = j - 1; k >= 0; k--) {
            if (board[i][k] != 0 && board[i][k + 1] == 0) {
               board[i][k + 1] = board[i][j];
               if ((k + 1) != j) {
                  board[i][j] = 0;
                  somethingChanged = true;
                }
            }
             if (k == 0 && board[i][k] == 0) {
               board[i][k] = board[i][j];
               board[i][j] = 0;
               somethingChanged = true;
               break;
            }
         }
       }
     }
    }
   if (somethingChanged == true) {
     generate_new_tile();
   }
}

void Game::shift_right()
{
  for (int i = board_size - 1; i >= 0; i--) {
    for (int j = board_size - 1; j >= 0; j--) {
       if (board[i][j] != 0) {
         for (int k = j + 1; k < board_size; k++) {
            if (board[i][k] != 0 && board[i][k - 1] == 0) {
               board[i][k - 1] = board[i][j];
               if ((k + 1) != j) {
                  board[i][j] = 0;
                  somethingChanged = true;
                }
            }
             if (k == board_size - 1 && board[i][board_size - 1] == 0) {
               board[i][k] = board[i][j];
               board[i][j] = 0;
               somethingChanged = true;
               break;
            }
         }
       }
    }
  }
   if (somethingChanged == true) {
      generate_new_tile();
   }
}

void Game::shift_up(){
  for (int i = 1; i < board_size; i++) {
     for (int j = 0; j < board_size; j++) {
       if (board[i][j] != 0) {
         for (int k = i - 1; k >= 0; k--) {
            if (board[k][j] != 0 && board[k + 1][j] == 0) {
               board[k + 1][j] = board[i][j];
               if ((k + 1) != i) {
                  board[i][j] = 0;
                  somethingChanged = true;
                }
            }
             if (k == 0 && board[k][j] == 0) {
               board[k][j] = board[i][j];
               board[i][j] = 0;
               somethingChanged = true;
               break;
            }
         }
       }
     }
    }
   if (somethingChanged == true) {
     generate_new_tile();
   }
}


void Game::shift_down() {
  for (int i = board_size - 2; i >= 0; i--) {
    for (int j = board_size - 1; j >= 0; j--) {
       if (board[i][j] != 0) {
         for (int k = i + 1; k < board_size; k++) {
            if (board[k][j] != 0 && board[k - 1][j] == 0) {
               board[k - 1][j] = board[i][j];
               if ((k - 1) != i) {
                  board[i][j] = 0;
                  somethingChanged = true;
                }
            }
             if (k == board_size - 1 && board[board_size - 1][j] == 0) {
               board[k][j] = board[i][j];
               board[i][j] = 0;
               somethingChanged = true;
               break;
            }
         }
       }
    }
  }
   if (somethingChanged == true) {
      generate_new_tile();
   }
}

void Game::print_score() // prints score
{
  cout << "\n\nCurrent Score\n: " << score << endl;
}

void Game::game_over() // checks for a) no zeroes on board and b) no adjacent matching tiles. If both are true, ends game.
{
   bool no_zeroes;
   bool no_matches;
   for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
      if (board[i][j] == 0) {
        no_zeroes = false;
        return;
      }
      else {
        no_zeroes = true;
      }
    }
  }
    for (int i = 0; i < board_size - 1; i++) {
        for (int j = 0; j < board_size; j++) {
       if (board[i][j] == board[i + 1][j]) {
          no_matches = false;
          return;
       }
       else {
          no_matches = true;
       }
    }
  }

  for (int i = 0; i < board_size; i++) {
      for (int j = 0; j < board_size - 1; j++) {
     if (board[i][j] == board[i][j + 1]) {
        no_matches = false;
        return;
     }
     else {
        no_matches = true;
     }
  }
}

   if (no_zeroes == true && no_matches == true) {
      cout << endl;
      print_board();
      gameOver = end_game();
   }

}

bool Game::end_game() // cute endgame function. 
{
cout << "\nGame over!" << endl;
return true;
}
