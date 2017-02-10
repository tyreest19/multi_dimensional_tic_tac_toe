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
    void Edit_Board(int row, int column, char players_piece);
    void Display_Board();
    bool Search_For_Win(char piece);
    bool Search_For_Tie_Game(int turns_completed);
    bool Check_Avaiblity(int row, int column);
    bool Check_Bounds(int user_enter_row, int user_enter_column);
    int Check_Columns_Size();

private:
    
    int rows;
    int columns;
    char board[13][16];
    void Generate_Board();
    bool Search_For_Diagonal_Win(char piece);
    bool Search_For_Horizontal_Win(char piece);
    bool Search_For_Vertical_Win(char piece);
    
};
    

#endif /* Board_hpp */
