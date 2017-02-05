//
//  main.cpp
//  mutli_dimensional_tic_tac_toe
//
//  Created by Tyree Stevenson on 1/28/17.
//  Copyright © 2017 Tyree Stevenson. All rights reserved.
//
//TODO {
//    5. who comes next after game conclusion.
//    6. ALLOW USER TO END OR CONTINUE GAME.
//    7. DOCUMENTATION.
//}

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
    bool turn;
};

bool validate_name(string full_name);
void get_board_dimesions(int &rows, int &columns);
void get_player_move(Board &board, string firstname, char piece);
int get_players(Player players[5]);
int get_next_game_starter(int next_player, int amount_of_turns, int number_of_players);
void play_game(Player players[5], int number_of_players, int &draws, int &next_player);
void update_loses(Player player[5], int winning_index, int amount_players);
void display_stats(Player player[5], int amount_of_players, int draws, int total_games_played);
string set_display_space(Player player[5], int amount_of_players, int current_player_name_length);
void standardize_names(Player &player, string user_entered_name);

using namespace std;
int main(int argc, const char * argv[]) {
    
    Player players[5];
    int number_of_players = get_players(players);
    int draws = 0;
    int total_games_played = 0;
    int index_of_next_player = 0;
    
    do {
        play_game(players, number_of_players, draws, index_of_next_player);
        total_games_played += 1;
        cout << "index of player: " << index_of_next_player << endl;
        display_stats(players, number_of_players, draws, total_games_played);
        
    } while (true);
    return 0;
}

//============================================================================================
// Takes an array of Player objects by which is used to update players stats.
// Creates a board object
// Then allows the players to play a tic-tac_toe game which displays, updates, and checks for win/draw after every // move
//============================================================================================

void play_game(Player players[5], int number_of_players, int &draws, int &next_player) {
    
    int rows;
    int columns;
    int amount_of_turns = next_player;
    int player_turn = 0;
    bool game_won = false;
    
    get_board_dimesions(rows, columns);
    Board board(rows, columns);
    
    while (player_turn != (rows * columns) && !game_won) {
        
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
            player_turn += 1;

        }
        
        else {
            
            amount_of_turns += 1;
            player_turn += 1;
        }
    }
    
    if (board.search_for_tie_game(amount_of_turns)) {
        
        board.display_board();
        draws += 1;
        next_player = get_next_game_starter(next_player, amount_of_turns, number_of_players);
        cout << "The game ended in a draw" << endl;
        
    }
    
}

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
                    
                     if(!(int(move[counter]) >= 49 && int(move[counter]) <= 59)) {
                     
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
                 if (columns + 1 > board.check_columns_size() || !valid_move) {
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
            
            cout << "Enter Player " << i + 1 << " full name: ";
            getline(cin, user_entered_name);
            validated_name = validate_name(user_entered_name);
            
            
            if (!validated_name) {
                cout << "Invalid Input" << endl;
            }
        
            else {
                
                standardize_names(players[i], user_entered_name);
                validated_name = players[i].lastname != " " && players[i].firstname != " ";
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

void update_loses(Player player[5], int winning_index, int amount_players) {
    for (int i = 0; i < amount_players; i++) {
        
        if (i == winning_index) {
            
            player[i].loses += 0;
            
        }
        
        else {
            
            player[i].loses += 1;
            
        }
    }
}

void display_stats(Player player[5], int amount_of_players, int draws, int total_games_played) {
    
    string spaces = set_display_space(player, amount_of_players, 0);
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

string set_display_space(Player player[5], int amount_of_players, int current_player_name_length) {
    
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

bool validate_name(string full_name) {
    
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

void get_board_dimesions(int &rows, int &columns) {
    
    string user_generated_dimesions;
    string temp;
    bool valid_input;
    
    do {
        
        int counter = 0;
        valid_input = true;
        temp = "";
        rows = 0;
        columns = 0;
        string user_generated_rows;
        string user_generted_columns;

        
        cout << "Enter amount of rows: ";
        getline(cin, user_generated_rows);
        cout << "Enter amount of columns: ";
        getline(cin, user_generted_columns);
        user_generated_dimesions = user_generated_rows + " " + user_generted_columns;
    
        if (user_generated_rows.length() > 3 || user_generted_columns.length() > 3 ||
            user_generated_rows[1] == ' ' || user_generted_columns[1] == ' ') {
            
            cout << "Invalid input " << endl;
            valid_input = false;
            
        }
        
        else if (user_generated_dimesions[0] == ' ' || user_generated_dimesions.length() > 5 ||
                 user_generated_dimesions[user_generated_dimesions.length() - 1] == ' ') {
        
                cout << "Invalid input " << endl;
                valid_input = false;
        
        }
        
    
    else {
        user_generated_dimesions += " ";
        while (valid_input && counter < user_generated_dimesions.length()) {

        if (user_generated_dimesions[counter] == ' ') {
        
            
            if (!rows) {
                
                rows = stoi(temp);
                
            }
            
            else {
                
                columns = stoi(temp);
                
            }
            
            temp = "";
        }
        
        else if (int(user_generated_dimesions[counter]) >= 49 &&
                 int(user_generated_dimesions[counter]) <= 57  ){
            temp += user_generated_dimesions[counter];
            
        }
            
        else {
            valid_input = false;
        }
            
        counter += 1;
            
        }
        
        if (!((rows >= 3 && rows <= 13)  && (columns >= 3 && columns <= 16))) {
            
            cout << "invalid input" << endl;
            valid_input = false;
            
        }
    }
    
        
    }while(!valid_input);
}

int get_next_game_starter(int next_player, int amount_of_turns, int number_of_players) {
    next_player = amount_of_turns + 1;
    if (next_player >= number_of_players) {
        next_player = 0;
    }
    return next_player;
}





