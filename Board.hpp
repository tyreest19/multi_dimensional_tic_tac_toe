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
    bool edit_board(string user_input,char player_piece);
    void display_board();
    bool search_for_win(char piece);
    bool search_for_tie_game(int turns_completed);
    
private:
    int rows;
    int columns;
    bool check_avaiblity(int row, int column);
    char board[13][16];
    void generate_board();
    bool search_for_diagonal_win(char piece);
    bool search_for_horizontal_win(char piece);
    bool search_for_vertical_win(char piece);
};
    

#endif /* Board_hpp */
