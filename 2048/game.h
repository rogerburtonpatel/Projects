// Roger Burtonpatel
// 2020/07/20
#ifndef GAME_H
#define GAME_H

#include <string>

class Game {
    public:
        Game();
        ~Game();
        void play();
    private:

      // Mem vars

        int score;
        int** board; // Currently Phase 1

        int board_size;
        bool gameOver;
        bool somethingChanged;

      // Mem Funcs

        int get_board_size();

        void generate_new_tile();

        void print_board();

        void get_input();

        void shift_left();
        void shift_right();
        void shift_up();
        void shift_down();

        void print_score();

        void game_over();

        bool end_game();

        void print_number(std::string num);
};

#endif
