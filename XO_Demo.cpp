#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Numerical_tic_tac.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;

    cout << "=============================================" << endl;
    cout << "  Welcome to FCAI Board Games Center (Team XX)" << endl;
    cout << "=============================================" << endl;
    cout << "Menu:" << endl;
    cout << "  1. Play X-O Game (Demo)" << endl;
    cout << "  2. Play Numerical Tic-Tac-Toe (Game 9)" << endl;
    cout << "  0. Exit" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nLaunching X-O Game..." << endl;

        UI<char>* game_ui = new XO_UI();
        Board<char>* xo_board = new X_O_Board();
        Player<char>** players = game_ui->setup_players();
        GameManager<char> x_o_game(xo_board, players, game_ui);

        x_o_game.run();

        delete xo_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }


    else if (choice == 2) {
        cout << "\nLaunching Numerical Tic-Tac-Toe..." << endl;

        UI<int>* game_ui = new Numerical_UI();
        Board<int>* num_board = new Numerical_Board();
        Player<int>** players = game_ui->setup_players();
        GameManager<int> num_game(num_board, players, game_ui);

        num_game.run();

        delete num_board;
        delete players[0];
        delete players[1];
        delete[] players;
        delete game_ui;
    }
    else if (choice!=0) {
        cout << "Invalid choice. Exiting." << endl;
    }

    cout << "\nThank you for playing!" << endl;
    return 0;
}