// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// #include "BoardGame_Classes.h"
// #include "Numerical_Tic_Tac.h"
// using namespace std;
// int main() {
//     srand(static_cast<unsigned int>(time(0)));
//
//     UI<int>* game_ui = new Numerical_UI();
//
//     Board<int>* game_board = new Numerical_Board();
//
//     Player<int>** players = game_ui->setup_players();
//


//     players[0]->set_board_ptr(game_board);
//     players[1]->set_board_ptr(game_board);
//
//
//     GameManager<int> game(game_board, players, game_ui);
//
//     game.run();
//
//     delete game_board;
//     delete players[0];
//     delete players[1];
//     delete[] players;
//     delete game_ui;
//
//     return 0;
// }