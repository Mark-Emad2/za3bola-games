#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <set>
#include <algorithm>

class Numerical_Board : public Board<int> {
private:
    set<int> used_numbers;
    set<int> player1_numbers;
    set<int> player2_numbers;
    int blank_value = 0;

public:

    Numerical_Board();
    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override { return false; }
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
    bool is_valid_number(int number, Player<int>* player);
    set<int> get_available_numbers(Player<int>* player);
};


class Numerical_UI : public UI<int> {
public:
    Numerical_UI();
    ~Numerical_UI() {}


    Player<int>* create_player(string& name, int symbol, PlayerType type) override;

    Move<int>* get_move(Player<int>* player) override;

    Player<int>** setup_players() override;
};

#endif // NUMERICAL_TICTACTOE_H