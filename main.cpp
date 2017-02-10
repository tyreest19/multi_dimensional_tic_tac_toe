//
//  main.cpp
//  mutli_dimensional_tic_tac_toe
//
//  Created by Tyree Stevenson on 1/28/17.
//  Copyright © 2017 Tyree Stevenson. All rights reserved.
//


#include <string>
#include <iostream>
#include "Board.hpp"
using namespace std;

struct Player {
    string firstname = " ";
    string lastname = " ";
    int wins = 0;
    int loses = 0;
    char piece;
};

bool validate_name(string full_name);
int get_user_choosen_dimension(string name_of_dimension, int min, int max);
void get_player_move(Board &board, string firstname, char piece);
int get_players(Player players[]);
int get_next_game_starter(int next_player, int amount_of_turns, int number_of_players);
void play_game(Player players[], int number_of_players, int &draws, int &next_player);
void update_loses(Player player[], int winning_index, int amount_players);
void display_stats(Player player[], int amount_of_players, int draws, int total_games_played);
string set_display_space(Player player[], int amount_of_players, int current_player_name_length);
void standardize_names(Player &player, string user_entered_name);

using namespace std;
int main(int argc, const char * argv[]) {
    
    Player players[5];
    int number_of_players = get_players(players);
    int draws = 0;
    int total_games_played = 0;
    int index_of_next_player = 0;
    string user_choice;
    
    do {
        
        user_choice = " ";
        
        play_game(players, number_of_players, draws, index_of_next_player);
        total_games_played += 1;
        display_stats(players, number_of_players, draws, total_games_played);
        
        while (user_choice != "y" && user_choice != "n") {
           
            cout << "If you wish to continue enter y and if you want to quit enter n: ";
            getline(cin, user_choice);
            user_choice = tolower(user_choice[0]);
            
            if (user_choice != "y" && user_choice != "n") {
                
               cout << "Invalid input" << endl;
                
            }
        }
        
    } while (user_choice == "y");
    
    return 0;
}

//============================================================================================
// Takes an array of Player objects by which is used to update players stats.
// Creates a board object
// Then allows the players to play a tic-tac_toe game which displays, updates, and checks for win/draw after every // move
//============================================================================================

void play_game(Player players[], int number_of_players, int &draws, int &next_player) {
    
    int rows = get_user_choosen_dimension("row", 3, 13);
    int columns = get_user_choosen_dimension("columns", 3, 16);
    int amount_of_turns = next_player;
    int total_moves = 0;
    int starting_player = next_player;
    bool game_won = false;
    
    Board board(rows, columns);
    
    while (total_moves != (rows * columns) && !game_won) {
        
        board.display_board();
        get_player_move(board, players[amount_of_turns].firstname, players[amount_of_turns].piece);
        
        if (board.search_for_win(players[amount_of_turns].piece)) {
            
            board.display_board();
            
            cout << endl << "Congrats " << players[amount_of_turns].firstname << ", you won"<< endl;
            
            players[amount_of_turns].wins += 1;
            game_won = true;
            next_player = get_next_game_starter(next_player, amount_of_turns, number_of_players);
            update_loses(players, amount_of_turns, number_of_players);
            
        }
        
        else if (amount_of_turns >= number_of_players - 1) {
            
            amount_of_turns = 0;
            total_moves += 1;

        }
        
        else {
            
            amount_of_turns += 1;
            total_moves += 1;
        }
    }
    
    if (board.search_for_tie_game(total_moves)) {
        
        board.display_board();
        draws += 1;
        next_player = get_next_game_starter(starting_player, amount_of_turns, number_of_players);
        cout << endl <<"The game ended in a draw" << endl;
        
    }
    
}

//============================================================================================
// Gets player move and places piece on the board.
// Parameters: The Game Board, Player's firstname, and Player's piece
// also valdiates the player move and prompts player to enter correct move.
//============================================================================================

void get_player_move(Board &board, string firstname, char piece) {
    
    string move;
    int rows;
    int columns;
    bool valid_move;
    int counter;
    
     do {
         
         rows = 0;
         columns = 0;
         counter = 0;
         valid_move = true;
         string temporary_columns = "";
         
         cout << endl << firstname << ", enter the number on the board where you want to move: ";
         getline(cin,move);
         move[0] = toupper(move[0]);
         
         if (move.length() < 2 || move.length() > 3) {
             
             cout << "invalid input";
             valid_move = false;
             
         }
         
         else {
             
             if(!(int(move[0]) >= 65 && int(move[0]) <= 77)) {
                 cout << "Invalid Input";
                 valid_move = false;
             }
             
             while (valid_move && counter < move.length()) {
                 
                 if (counter == 0) {
                     rows += (move[0] - 65);
                 }

                 else if(!(int(move[counter]) >= 65 && int(move[counter]) <= 77)){
                    
                     if(!(int(move[counter]) >= 48 && int(move[counter]) <= 59)) {
                     
                     cout << "invalid input";
                     valid_move = false;
                         
                    }
                     
                     else {
                         
                         temporary_columns += move[counter];
                         
                     }
                 }
                 
                 counter += 1;
             }
             
             if (valid_move) {
                 columns += stoi(temporary_columns) - 1;
                 valid_move = (board.check_avaiblity(rows, columns)) && (board.check_bounds(rows, columns));
                 if (columns + 1 > board.check_columns_size() || !valid_move || columns + 1 < 1) {
                     cout << "Invalid input" ;
                     valid_move = false;
                    }
                  }
             }
         
     }while(!valid_move);
    
    board.edit_board(rows, columns, piece);
    
}

//============================================================================================
// Allows the user to enter in the number of players.
// Uses the number of players to load players first and lastname into an array of player objects.
// Returns number of players.
//============================================================================================

int get_players(Player players[]) {
    
    string number_of_players;
    bool validated_amount_of_players_choosen;
    
    do {

        cout << "How many Players are playing must be between 2 to 5 players and must be a number: ";
        getline(cin, number_of_players);
        
        validated_amount_of_players_choosen = (number_of_players[0] <= 49) || (number_of_players[0] > 53)
        || (number_of_players.length() != 1);
        
        if (validated_amount_of_players_choosen) {
            
            cout << "Invalid Input" << endl;
            
        }
        
    }  while(validated_amount_of_players_choosen);
    
    int amount_of_players_playing = stoi(number_of_players);
    
    for (int i = 0; i < amount_of_players_playing; i++) {
        
        string user_entered_name;
        bool validated_name;
        
        do {
            
            cout << "Player " << i + 1 << " enter your full name: ";
            getline(cin, user_entered_name);
            validated_name = validate_name(user_entered_name);
            
            
            if (!validated_name) {
                
                cout << "Invalid Input" << endl;
                
            }
        
            else {
                
                standardize_names(players[i], user_entered_name);
                validated_name = !(players[i].lastname != " ") || !players[i].lastname.empty();
                
                if (!validated_name) {
                    
                    cout << "Invalid Input" << endl;
                    
                }
                
            }
            
        } while (!validated_name);
        
        players[i].piece = 'a' + i;
       
        
    }
    
    return amount_of_players_playing;
}

//============================================================================================
// This function Standardizes names by making the first name capitalized capital and the follwing lowercased.
//============================================================================================

void standardize_names(Player &player, string user_entered_name) {
    
    int spaces = 0;
    player.firstname[0] = toupper(user_entered_name[0]);
    
    for (int i = 1; i < user_entered_name.length(); i++) {
        
        if (user_entered_name[i] == ' ') {
            
            spaces += 1;
            player.lastname += user_entered_name[i];
            player.lastname += toupper(user_entered_name[i + 1]);
            i += 1;
            
        }
        
        else if (spaces >= 1) {
            
            player.lastname += tolower(user_entered_name[i]);
            
        }
        
        else {
            
            player.firstname += user_entered_name[i];
            
        }
    }
    
    player.lastname.erase(0,1);
}

//==================================
// Updates players loses
//==================================

void update_loses(Player player[], int winning_index, int amount_players) {
    
    for (int i = 0; i < amount_players; i++) {
        
        if (i == winning_index) {
            
            player[i].loses += 0;
            
        }
        
        else {
            
            player[i].loses += 1;
            
        }
    }
}

//============================================================================================
// This function displays players stats and total games played.
//============================================================================================


void display_stats(Player player[], int amount_of_players, int draws, int total_games_played) {
    
    string spaces = set_display_space(player, amount_of_players, 0);
    cout << endl;
    cout <<"Total game played = " << total_games_played << endl << endl;
    cout << spaces <<"   WIN   LOSS  DRAWS    " << endl;
    cout << spaces <<"  ------ ----- ---- " << endl;
    
    for (int i = 0; i < amount_of_players; i++) {
        
        int length_of_current_name = int(player[i].firstname.length() + player[i].lastname.length());
        
        if (length_of_current_name < 3) {
            
            length_of_current_name = 3;
            
        }
        
        string spaces = set_display_space(player, amount_of_players, length_of_current_name);
        cout << player[i].firstname <<player[i].lastname << ' ' << spaces;
        cout << "|  " << player[i].wins;
        cout << "   |  " << player[i].loses;
        cout << "  |  " << draws << " |" << endl;
        
        spaces = set_display_space(player, amount_of_players, 0);
        
        cout << spaces << "  ------ ----- ---- " << endl;
        
    }
}

//============================================================================================
// This function creates the spacing for "display_stats" function
//============================================================================================

string set_display_space(Player player[], int amount_of_players, int current_player_name_length) {
    
    int longest_name = 0;
    
    for (int i = 0; i < amount_of_players; i++) {
        
        int length_of_full_name = int(player[i].firstname.length() + 1 + player[i].lastname.length());
        
        if (length_of_full_name > longest_name) {
            
            longest_name = length_of_full_name;
    
        }
    }
    
    string empty_string = "";
    
    for (int i = 0; i < (longest_name + 2) - current_player_name_length; i++) {
        
        empty_string += " ";
        
    }
    
        return empty_string;
    
}

//======================================================================================
// Validates users name.
//======================================================================================

bool validate_name(string full_name) {
    
    if (full_name[0] == ' ') {
        
        return false;
        
    }
    
    for (int i = 0; i < full_name.length(); i++) {
    
        char valdiating_char = toupper(full_name[i]);
        
        if ((int(valdiating_char) < 65 || int(valdiating_char) > 90) && valdiating_char != ' ') {
            
            return false;
            
        }
    }
    
        return full_name[full_name.length() - 1] != ' ';
}

//======================================================================================
// Gets boards dimesions and stores them into a rows and columns reference variable.
// also validates the input.
//======================================================================================

int get_user_choosen_dimension(string name_of_dimension, int min, int max) {
    
    string dimension;
    int numeric_value_of_dimnesion;
    
    do {
        
        numeric_value_of_dimnesion = 0;
        
        cout << "Enter a number of " << name_of_dimension  << " between from "<< min << " to "  << max << ": ";
        getline(cin, dimension);
        
        if (dimension.length() <= 2) {
            
            if (int(dimension[0]) >= 48 && int(dimension[0]) <= 57 && dimension.length() == 1) {
                    
                    numeric_value_of_dimnesion = stoi(dimension);
                
                    if (!(numeric_value_of_dimnesion >= min && numeric_value_of_dimnesion <= max)) {
                    
                    cout << "Invalid input" << endl;
                    
                    }
                }
                
                else if (dimension.length() == 2 && int(dimension[1]) >= 48 && int(dimension[1]) <= 57) {
                    
                    numeric_value_of_dimnesion = stoi(dimension);
                    
                    if (!(numeric_value_of_dimnesion >= min && numeric_value_of_dimnesion <= max)) {
                        
                        cout << "Invalid input" << endl;

                    }
                    
                }
                
                else {
                    
                    cout << "Invalid input" << endl;
                }
            }
        
        else {
            
            cout << "Invalid Input" << endl;
            
        }
        
    } while (!(numeric_value_of_dimnesion >= min && numeric_value_of_dimnesion <= max));
    
    
    return numeric_value_of_dimnesion;
}

//======================================================================================
// Returns the index of the next player to start the game.
//======================================================================================

int get_next_game_starter(int next_player, int amount_of_turns, int number_of_players) {
    
    next_player = amount_of_turns + 1;
    
    if (next_player >= number_of_players) {
        
        next_player = 0;
        
    }
    
    return next_player;
}
