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
    string firstname;
    string lastname;
    int wins = 0;
    int loses = 0;
    char piece;
    bool turn;
};

string get_player_move(string firstname);
int get_players(Player players[5]);
void play_game(Player players[5], int number_of_players, int &draws);
void update_loses(Player player[5], int winning_index, int amount_players);
void display_stats(Player player[5], int amount_of_players, int draws, int total_games_played);
string set_display_space(Player player[5], int amount_of_players, int current_player_name_length);
string standardize_names(string name);

using namespace std;
int main(int argc, const char * argv[]) {
    Player players[5];
    int number_of_players = get_players(players);
    int draws = 0;
    //play_game(players, number_players, draws);
    int total_games_played;
    display_stats(players, number_of_players, draws, total_games_played);
    
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
    
    cout << "Enter amount of rows for the board: ";
    cin >> rows;
    cout << "Enter amount of columns for the board: ";
    cin >> columns;
    
    Board board(rows, columns);
    
    while (player_turn <= (rows * columns) && !game_won) {
        cout << "amout of turns: " << amount_of_turns << endl;
        Player current_player = players[amount_of_turns];
        board.display_board();
        board.edit_board(get_player_move(current_player.firstname), current_player.piece);
        
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

string get_player_move(string firstname) {
    
    string move;
    
    cout << endl << firstname <<", enter the number on the board where you want to move: ";
    cin >> move;
    
    return move;
    
}

//============================================================================================
// Allows the user to enter in the number of players.
// Uses the number of players to load players first and lastname into an array of player objects.
// Returns number of players.
//============================================================================================

int get_players(Player players[]) {
    
    int number_of_players;

    cout << "How many Players are playing: ";
    cin >> number_of_players;
    
    for (int i = 0; i < number_of_players; i++) {
        
        cout << "Enter Player " << i + 1 << " full name: ";
        cin >> players[i].firstname >> players[i].lastname;
        
        players[i].firstname = standardize_names(players[i].firstname);
        players[i].lastname = standardize_names(players[i].lastname);
        players[i].piece = 'a' + i;
       
        
    }
    return number_of_players;
}

//============================================================================================
// This function Standardizes names by making the first name capitalized capital and the follwing lowercased.
//============================================================================================

string standardize_names(string name) {
    
    name[0] = toupper(name[0]);
    
    for (int i = 1; i < name.length(); i++) {
        name[i] = tolower(name[i]);
    }
    return name;
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
