#include <iostream>
#include <algorithm>
#include "Numerical_Tic_Tac.h"
#include <cstdlib>
#include <ctime>
using namespace std;
Numerical_Board::Numerical_Board() : Board<int>(3, 3) {
    // Initialize board with zeros (empty cells)
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_value;
        }
    }

    // Initialize available numbers
    player1_numbers = {1, 3, 5, 7, 9};
    player2_numbers = {2, 4, 6, 8};
}

bool Numerical_Board::is_valid_number(int number, Player<int>* player) {
    // Check if number was already used
    if (used_numbers.count(number) > 0) {
        return false;
    }

    // Check if number belongs to this player
    int player_id = player->get_symbol();  // 1 for player1 (odd), 2 for player2 (even)

    if (player_id == 1) {
        return player1_numbers.count(number) > 0;
    } else {
        return player2_numbers.count(number) > 0;
    }
}

set<int> Numerical_Board::get_available_numbers(Player<int>* player) {
    int player_id = player->get_symbol();
    set<int> available;

    if (player_id == 1) {
        for (int num : player1_numbers) {
            if (used_numbers.count(num) == 0) {
                available.insert(num);
            }
        }
    } else {
        for (int num : player2_numbers) {
            if (used_numbers.count(num) == 0) {
                available.insert(num);
            }
        }
    }

    return available;
}

bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    // Validate position
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    // Check if cell is empty
    if (board[x][y] != blank_value) {
        return false;
    }

    // For undo move (number == 0)
    if (number == 0) {
        n_moves--;
        board[x][y] = blank_value;
        return true;
    }

    // Check if number is valid (not used and belongs to player)
    if (used_numbers.count(number) > 0) {
        return false;
    }

    // Apply move
    board[x][y] = number;
    used_numbers.insert(number);
    n_moves++;

    return true;
}

bool Numerical_Board::is_win(Player<int>* player) {
    // Check all rows
    for (int i = 0; i < rows; i++) {
        int sum = board[i][0] + board[i][1] + board[i][2];
        if (sum == 15 && board[i][0] != blank_value &&
            board[i][1] != blank_value && board[i][2] != blank_value) {
            return true;
        }
    }

    // Check all columns
    for (int j = 0; j < columns; j++) {
        int sum = board[0][j] + board[1][j] + board[2][j];
        if (sum == 15 && board[0][j] != blank_value &&
            board[1][j] != blank_value && board[2][j] != blank_value) {
            return true;
        }
    }

    // Check main diagonal (top-left to bottom-right)
    int sum_diag1 = board[0][0] + board[1][1] + board[2][2];
    if (sum_diag1 == 15 && board[0][0] != blank_value &&
        board[1][1] != blank_value && board[2][2] != blank_value) {
        return true;
    }

    // Check anti-diagonal (top-right to bottom-left)
    int sum_diag2 = board[0][2] + board[1][1] + board[2][0];
    if (sum_diag2 == 15 && board[0][2] != blank_value &&
        board[1][1] != blank_value && board[2][0] != blank_value) {
        return true;
    }

    return false;
}

bool Numerical_Board::is_draw(Player<int>* player) {
    // Draw if board is full (9 moves) and no winner
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

Numerical_UI::Numerical_UI()
    : UI<int>("Welcome to FCAI Numerical Tic-Tac-Toe Game!", 3) {
    cout << "\nGame Rules:\n";
    cout << "- Player 1 uses ODD numbers: 1, 3, 5, 7, 9\n";
    cout << "- Player 2 uses EVEN numbers: 2, 4, 6, 8\n";
    cout << "- Each number can only be used once\n";
    cout << "- Win by getting three numbers that sum to 15\n";
    cout << "  (in a row, column, or diagonal)\n\n";
}

Player<int>** Numerical_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = {"Human", "Computer"};

    // Player 1 (Odd numbers)
    string name1 = get_player_name("Player 1 (Odd numbers)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1);  // symbol = 1 for odd

    // Player 2 (Even numbers)
    string name2 = get_player_name("Player 2 (Even numbers)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2);  // symbol = 2 for even

    return players;
}

Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (Uses "
         << (symbol == 1 ? "ODD" : "EVEN") << " numbers)\n";

    return new Player<int>(name, symbol, type);
}

Move<int>* Numerical_UI::get_move(Player<int>* player) {
    Numerical_Board* board = dynamic_cast<Numerical_Board*>(player->get_board_ptr());

    if (!board) {
        cerr << "Error: Invalid board type!\n";
        return nullptr;
    }

    int x, y, number;

    if (player->get_type() == PlayerType::HUMAN) {
        // Get available numbers
        set<int> available = board->get_available_numbers(player);

        cout << "\n" << player->get_name() << "'s turn\n";
        cout << "Available numbers: ";
        for (int num : available) {
            cout << num << " ";
        }
        cout << endl;

        // Get number input
        do {
            cout << "Enter the number you want to place: ";
            cin >> number;

            if (available.count(number) == 0) {
                cout << "Invalid number! Choose from available numbers.\n";
            }
        } while (available.count(number) == 0);

        // Get position input
        cout << "Enter position (row and column, 0-2): ";
        cin >> x >> y;

    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Computer plays randomly
        set<int> available = board->get_available_numbers(player);

        if (available.empty()) {
            return nullptr;
        }

        // Pick random number from available
        auto it = available.begin();
        advance(it, rand() % available.size());
        number = *it;

        // Pick random empty position
        do {
            x = rand() % board->get_rows();
            y = rand() % board->get_columns();
        } while (board->get_board_matrix()[x][y] != 0);

        cout << "\nComputer " << player->get_name() << " plays: "
             << number << " at position (" << x << ", " << y << ")\n";
    }

    return new Move<int>(x, y, number);
}