//
//  Board.cpp
//  mutli_dimensional_tic_tac_toe
//
//  Created by Tyree Stevenson on 1/28/17.
//  Copyright © 2017 Tyree Stevenson. All rights reserved.
//

#include "Board.hpp"

#include "Board.hpp"
#include <iostream>
#include "Board.hpp"
#include <string>

using namespace std;

Board::Board(int user_choosen_rows, int user_choosen_columns) {
    
    rows = user_choosen_rows;
    columns = user_choosen_columns;
    Generate_Board();
    
}

//============================================================================================
// Generates the game board.
//============================================================================================

void Board:: Generate_Board() {
    
    for (int i = 0; i < 13; i++) {
        
        for (int j = 0; j < 16; j++) {
            
            board[i][j] = ' ';
            
        }
    }
}

//============================================================================================
// Allows user to edit the board.
//============================================================================================

void Board:: Edit_Board(int row, int column, char players_piece) {
    
        board[row][column] = players_piece;
    
}

//============================================================================================
// Displays the board.
//============================================================================================

void Board:: Display_Board() {
    
    int amount_of_interations = rows;

    do {
        
        if (rows - amount_of_interations == 0) {
            
            for (int i = 0; i < columns; i++) {
                
                if(i + 1 == 1) {
                    
                    cout <<"    "<< i + 1;
                    
                }
                
                else if (i  + 1 < 9) {
                    
                    cout <<"   "<< i + 1;
                    
                }
                
                else  if( i + 1 == 9) {
                    
                    cout << "   "<<i + 1;
                    
                }
                
                else if(i + 1 == 10) {
                    
                    cout << "   " << i + 1;
                    
                }
                
                 else {
                     
                    cout << "  " << i + 1;
                     
                }
            }
        }
        
        cout << endl;
        
        for (int i = 0; i < columns; i++) {
            
            if (i == 0) {
                
                cout << "   ---";
            }
            
            else if (i % 2 != 0) {
                
                cout << " --- ";
            }
            
            else {
                
                cout << "---";
            }
        }
        
        cout << endl << char('A' + (rows - amount_of_interations)) << " ";
        
        for (int j = 0; j < columns; j++) {
            
            cout << "|  "<< board[rows - amount_of_interations][j];
            
        }
        
        cout << "|"<<char('A' + (rows - amount_of_interations));

        if (amount_of_interations - 1 == 0) {
            
            cout << endl;
            
            for (int i = 0; i < columns; i++) {
                   
                    if (i == 0) {
                        
                        cout << "   ---";
                        
                    }
                    
                    else if (i % 2 != 0) {
                        
                        cout << " --- ";
                        
                    }
                    
                    else {
                        
                        cout << "---";
                        
                    }
                }
            
                if (amount_of_interations - 1 == 0) {
                    
                    cout << endl;
                    
                    for (int i = 0; i < columns; i++) {
                        
                        if(i + 1 == 1) {
                            
                            cout <<"    "<< i + 1;
                            
                        }
                        
                        else if (i  + 1 < 9) {
                            
                            cout <<"   "<< i + 1;
                            
                        }
                        
                        else  if( i + 1 == 9) {
                            
                            cout << "   "<<i + 1;
                            
                        }
                        else if(i + 1 == 10) {
                            
                            cout << "   " << i + 1;
                            
                        }
                        
                        else {
                            
                            cout << "  " << i + 1;
                            
                        }
                    }
                    
                }
            }
        amount_of_interations -= 1;
        
    }while (amount_of_interations);
};

//============================================================================================
// Searches for win by checking all of the possible winning methods.
//============================================================================================

bool Board:: Search_For_Win(char piece) {
    
    bool diagonal_win = Board:: Search_For_Diagonal_Win(piece);
    
    bool horizontal_win = Board:: Search_For_Horizontal_Win(piece);
    
    bool vertical_win = Board:: Search_For_Vertical_Win(piece);
    
    if (diagonal_win || horizontal_win || vertical_win) {
        
        return true;
        
    }
    
    return false;
    
}

//============================================================================================
// Searches the board for a winning diagnol combination and if combination found it is capitalized and returns true.
//============================================================================================

bool Board:: Search_For_Diagonal_Win(char piece) {
    
    for (int i = 0; i < rows; i++) {
        
        for (int j = 0; j < columns; j++) {
            
            if(board[i][j] == piece && ((i + 1 < rows && j + 1 < columns) || (i + 1 <= rows && j - 1 >= 0))) {
                
                if((board[i + 1][j + 1] == piece || board[i + 1][j - 1] == piece) && ((i + 2 <= rows && j + 2 <= columns) || (i + 2 <= rows && j - 2 >= 0))) {
                   
                    if(board[i + 2][j + 2] == piece)    {
                        
                        board[i + 2][j + 2] = toupper(piece);
                        board[i + 1][j + 1] = toupper(piece);
                        board[i][j] =  toupper(piece);
                        
                        cout << "DIAGONAL WIN FOUND" <<endl;
                        
                        return true;
                  
                    }
                    
                    else if (board[i + 2][j - 2] == piece) {
                        
                        board[i + 2][j - 2] = toupper(piece);
                        board[i + 1][j - 1] = toupper(piece);
                        board[i][j] = toupper(piece);
                        
                        cout << "DIAGONAL WIN FOUND" <<endl;
                        
                        return true;
                        
                    }
                }
            }
        }
    }
    return false;
}

//============================================================================================
// Searches the board for a winning horizontal combination if combination found it is capitalized and returns true.
//============================================================================================

bool Board:: Search_For_Horizontal_Win(char piece) {
    
    for (int i = 0; i < rows; i++) {
        
        for (int j = 0; j < columns; j++) {
            
            if(board[i][j] == piece && board[i][j + 1] == piece && board[i][j + 2] == piece ) {
                    
                    board[i][j + 2] = toupper(piece);
                    board[i][j + 1] = toupper(piece);
                    board[i][j] = toupper(piece);
                    cout << endl;
                
                    return true;
                
                }
            }
        }
    
    return false;
}

//============================================================================================
// Searches the board for a winning vertical combination if combination found it is capitalized and  returns true.
//============================================================================================

bool Board:: Search_For_Vertical_Win(char piece) {
    
    for (int i = 0; i < rows; i++) {
        
        for (int j = 0; j < columns; j++) {
            
            if(board[i][j] == piece && board[i + 1][j] == piece && board[i + 2][j] == piece ) {
                
                board[i][j] = toupper(piece);
                board[i + 1][j] = toupper(piece);
                board[i + 2][j] = toupper(piece);
                cout << endl;
                
                return true;
            }
        }
    }
    
    return false;
}

//============================================================================================
// Searches for tie game.
//============================================================================================

bool Board:: Search_For_Tie_Game(int turns_completed) {
    
    return turns_completed == rows * columns;
    
}

//============================================================================================
// Checks the game board for aviable spaces.
//============================================================================================

bool Board:: Check_Avaiblity(int row, int column) {
    
    return board[row][column] == ' ';
    
}

//============================================================================================
// Check if a choosen board dimension is out of bounds.
//============================================================================================

bool Board:: Check_Bounds(int user_enter_row, int user_enter_column) {
    
    return (rows >= user_enter_row) && (columns >= user_enter_column);
    
}

//============================================================================================
// Returns column size of the board.
//============================================================================================

int Board:: Check_Columns_Size() {
    
    return columns;
    
}
