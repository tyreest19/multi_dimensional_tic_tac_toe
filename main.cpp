//
//  main.cpp
//  mutli_dimensional_tic_tac_toe
//
//  Created by Tyree Stevenson on 1/28/17.
//  Copyright © 2017 Tyree Stevenson. All rights reserved.
//
//TODO {
//    3. SHOW PLAYER STATS.
//    4. INPUT VALADATION.
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
void get_player_move(Board board, string firstname, char piece);
int get_players(Player players[5]);
void play_game(Player players[5], int number_of_players, int &draws);
void update_loses(Player player[5], int winning_index, int amount_players);
void display_stats(Player player[5], int amount_of_players, int draws, int total_games_played);
string set_display_space(Player player[5], int amount_of_players, int current_player_name_length);
void standardize_names(Player &player, string user_entered_name);

using namespace std;
int main(int argc, const char * argv[]) {
//    Player players[5];
//    int number_of_players = get_players(players);
//    int draws = 0;
//    play_game(players, number_of_players, draws);
//    int total_games_played;
//    display_stats(players, number_of_players, draws, total_games_played);
    int rows;
    int columns;
    get_board_dimesions(rows, columns);
    Board board(rows, columns);
    board.display_board();
    return 0;
}

//============================================================================================
// Takes an array of Player objects by which is used to update players stats.
// Creates a board object
// Then allows the players to play a tic-tac_toe game which displays, updates, and checks for win/draw after every // move
//============================================================================================

void play_game(Player players[5], int number_of_players, int &draws) {
    
    int rows;
    int columns;
    int amount_of_turns = 0;
    int player_turn = 0;
    bool game_won = false;
    
    get_board_dimesions(rows, columns);
    Board board(rows, columns);
    
    while (player_turn <= (rows * columns) && !game_won) {
        
        Player current_player = players[amount_of_turns];
        cout << "display board caused this error" << endl;
        board.display_board();
        cout << "after display board" << endl;
        get_player_move(board, players[amount_of_turns].firstname, current_player.piece);
        
        if (board.search_for_win(current_player.piece)) {
            
            board.display_board();

            cout << "Congrats " << current_player.firstname << ", you won"<< endl;
            
            current_player.wins += 1;
            game_won = true;
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
        
        cout << "The game ended in a draw" << endl;
        
    }
    
}

void get_player_move(Board board, string firstname, char piece) {
    
    bool is_space_available;
    string move;
    int row;
    int column;
    
    do {
        
        cout << endl << firstname <<", enter the number on the board where you want to move: ";
        getline(cin,move);
        row = move[0] - 65;
        
        if (move.length() == 2) {
            
            column = int(move[1]);
            
        }
        
        else {
            
            string temporary_column = move.substr(move.length() - 2);
            column = stoi(temporary_column);
            
        }
        
        column -= 1;
        is_space_available = board.check_avaiblity(row, column);
        
        if (!is_space_available) {
            
            cout << "Space has been taken please choose a new move" << endl;
            
        }
        
    } while(!is_space_available);

    board.edit_board(row, column, piece);
    
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
            
        } while (!validated_name);
        
        standardize_names(players[i], user_entered_name);
        players[i].piece = 'a' + i;
       
        
    }
    
    return amount_of_players_playing;
}

//============================================================================================
// This function Standardizes names by making the first name capitalized capital and the follwing lowercased.
//============================================================================================

void standardize_names(Player &player, string user_entered_name) {
    
    int spaces = 0;
    
    for (int i = 1; i < user_entered_name.length(); i++) {
        
        if (i == 0) {
            player.firstname[0] = toupper(user_entered_name[i]);
        }
        
        else if (user_entered_name[i] == ' ') {
            
            spaces += 1;
            player.lastname[0] = toupper(user_entered_name[i + 1]);
            i += 1;
            
        }
        
        else if (spaces == 1) {
            
            player.lastname += tolower(user_entered_name[i]);
            
        }
        
        else {
            
            player.firstname += user_entered_name[i];
            
        }
    }
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
    cout << spaces <<"  WIN   LOSS   DRAWS    " << endl;
    cout << spaces <<" --------------------" << endl;
    
    for (int i = 0; i < amount_of_players; i++) {
        
        int length_of_current_name = int(player[i].firstname.length() + player[i].lastname.length());
        
        if (length_of_current_name < 3) {
            length_of_current_name = 3;
        }
        
        string spaces = set_display_space(player, amount_of_players, length_of_current_name);
        // int spaces_length = int(player[i].firstname.length() + player[i].lastname.length());
        cout << player[i].firstname << " " << player[i].lastname << spaces;
        cout << "|  " << player[i].wins;
        cout << "   |  " << player[i].loses;
        cout << "   |  " << draws << " |" << endl;
        spaces = set_display_space(player, amount_of_players, 0);
        cout << spaces << " --------------------" << endl;
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
    int spaces = 0;
    
    for (int i = 0; i < full_name.length(); i++) {
        
        char valdiating_char = toupper(full_name[i]);
        
        if (valdiating_char == ' ') {
            spaces += 1;
            
            if (spaces > 1) {
                return false;
            }
        }
        
        else if (int(valdiating_char) < 65 || int(valdiating_char) > 90) {
            
            return false;
        }
    }
    
        return full_name[full_name.length() - 1] != ' ' && spaces == 1;
}

void get_board_dimesions(int &rows, int &columns) {
    
    string user_generated_dimesions;
    bool validate_dimesions = true;
    
    do {
        
        cout << "Enter amount of rows by columns for the board: ";
        getline(cin, user_generated_dimesions);
        
        if (user_generated_dimesions.length() > 5) {
            cout << "Invalid input" << endl;
        }
        
        else {
            int counter = 0;
            
            while (validate_dimesions && counter < user_generated_dimesions.length()) {
                
                if (user_generated_dimesions[counter] < 49 && user_generated_dimesions[counter] > 57) {
                    
                    validate_dimesions = false;
                    
                }
            }
        }
    
    } while (!validate_dimesions);
    
    //rows =  stoi(user_genrated_row);
    //columns = stoi(user_genrated_column);
}
