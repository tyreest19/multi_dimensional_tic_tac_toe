//
//  Board.hpp
//  mutli_dimensional_tic_tac_toe
//
//  Created by Tyree Stevenson on 1/28/17.
//  Copyright © 2017 Tyree Stevenson. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp
#include <stdio.h>
#include <string>

using namespace std;

class Board {
    
public:
    
    Board(int rows, int columns);
    void edit_board(int row, int column, char players_piece);
    void display_board();
    bool search_for_win(char piece);
    bool search_for_tie_game(int turns_completed);
    bool check_avaiblity(int row, int column);
    bool check_bounds(int user_enter_row, int user_enter_column);
    int check_columns_size();

private:
    
    int rows;
    int columns;
    char board[13][16];
    void generate_board();
    bool search_for_diagonal_win(char piece);
    bool search_for_horizontal_win(char piece);
    bool search_for_vertical_win(char piece);
    
};
    

#endif /* Board_hpp */
