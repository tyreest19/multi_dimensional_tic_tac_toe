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

bool Validate_Name(string full_name);
int Get_User_Choosen_Dimension(string name_of_dimension, int min, int max);
void Get_Player_Move(Board &board, string firstname, char piece);
int Get_Players(Player players[]);
int Get_Next_Game_Starter(int next_player, int amount_of_turns, int number_of_players);
void Play_Game(Player players[], int number_of_players, int &draws, int &next_player);
void Update_Loses(Player player[], int winning_index, int amount_players);
void Display_Stats(Player player[], int amount_of_players, int draws, int total_games_played);
string Set_Display_Space(Player player[], int amount_of_players, int current_player_name_length);
void Standardize_Names(Player &player, string user_entered_name);

int main()
{
    cout << "Hello, You are Playing multi dimensional Tic-Tac-Toe" << endl;
    cout << "Instructions" << endl;
    cout << " - Enter players name." << endl;
    cout << " - Enter the Dimensions of the board" << endl;
    cout << " - To move your piece enter the row letter infront of column number EX: \'A11\' or \'A5\'" << endl;
    cout << endl;
    
    Player players[5];
    int number_of_players = Get_Players(players);
    int draws = 0;
    int total_games_played = 0;
    int index_of_next_player = 0;
    string user_choice;
    
    do
    {
        
        user_choice.clear();
        
        Play_Game(players, number_of_players, draws, index_of_next_player);
        total_games_played += 1;
        Display_Stats(players, number_of_players, draws, total_games_played);
        
        while (user_choice != "Y" && user_choice != "N")
        {
           
            cout << "If you wish to continue enter Y and if you want to quit enter N: ";
            getline(cin, user_choice);
            user_choice[0] = toupper(user_choice[0]);
            
            if (user_choice != "Y" && user_choice != "N") {
                cout << "Invalid Input" << endl;
        }
    }
        
    } while (user_choice == "Y" );
    
    return 0;
}

//============================================================================================
// Takes an array of Player objects by which is used to update players stats.
// Creates a board object
// Then allows the players to play a tic-tac_toe game which displays, updates, and checks for win/draw after every // move
//============================================================================================

void Play_Game(Player players[], int number_of_players, int &draws, int &next_player)
{
    
    int rows = Get_User_Choosen_Dimension("rows", 3, 13);
    int columns = Get_User_Choosen_Dimension("columns", 3, 16);
    int amount_of_turns = next_player;
    int total_moves = 0;
    int starting_player = next_player;
    bool game_won = false;
    
    Board board(rows, columns);
    
    while (total_moves != (rows * columns) && !game_won)
    {
        cout << endl;
        board.Display_Board();
        cout << endl;
        Get_Player_Move(board, players[amount_of_turns].firstname, players[amount_of_turns].piece);
        
        if (board.Search_For_Win(players[amount_of_turns].piece))
        {
            
            cout << endl;
            board.Display_Board();
            
            cout << endl;
            cout << "Congrats " << players[amount_of_turns].firstname << ", you won !";
            cout << endl;
            
            players[amount_of_turns].wins += 1;
            game_won = true;
            next_player = Get_Next_Game_Starter(next_player, amount_of_turns, number_of_players);
            
            Update_Loses(players, amount_of_turns, number_of_players);
        }
        
        else if (amount_of_turns >= number_of_players - 1)
        {
            amount_of_turns = 0;
            total_moves += 1;
        }
        
        else
        {
            amount_of_turns += 1;
            total_moves += 1;
        }
    }
    
    if (board.Search_For_Tie_Game(total_moves))
    {
        
        board.Display_Board();
        draws += 1;
        next_player = Get_Next_Game_Starter(starting_player, amount_of_turns, number_of_players);
        cout << endl;
        cout <<"The game ended in a draw";
        cout << endl;
        
    }
}

//============================================================================================
// Gets player move and places piece on the board.
// Parameters: The Game Board, Player's firstname, and Player's piece
// also valdiates the player move and prompts player to enter correct move.
//============================================================================================

void Get_Player_Move(Board &board, string firstname, char piece)
{
    
    string move;
    int rows;
    int columns;
    bool valid_move;
    int counter;
    char rows_minium = 'A';
    char rows_maxium = 'M';
    char column_minum = '0';
    char column_maxium = '9';
     do
     {
         
         rows = 0;
         columns = 0;
         counter = 0;
         valid_move = true;
         string temporary_columns = "";
         
         cout << endl;
         cout << firstname << " (your piece is \'" << piece << "\')" << ", enter the number on the board where you want to move: ";
         getline(cin,move);
         cout << endl;
         
         move[0] = toupper(move[0]);
         
         if (move.length() < 2 || move.length() > 3)
         {
             
             cout << "Invalid Input";
             cout << endl;
             
             valid_move = false;
             
         }
         
         else
         {
             
             if(!(move[0] >= rows_minium && move[0] <= rows_maxium))
             {
                 
                 cout << "Invalid Input";
                 cout << endl;
                 
                 valid_move = false;
             }
             
             while (valid_move && counter < move.length())
             {
                 
                 if (counter == 0)
                 {
                     rows += (move[0] - rows_minium);
                 }

                 else if(!(move[counter] >= rows_minium && move[counter] <= rows_maxium))
                 {
                    
                     if(!(move[counter] >= column_minum && move[counter] <= column_maxium))
                     {
                     
                         cout << "Invalid Input";
                         cout << endl;
                         
                     valid_move = false;
                         
                    }
                     
                     else
                     {
                         temporary_columns += move[counter];
                     }
                 }
            
                 counter += 1;
             }
             
             if (valid_move)
             {
                 columns += stoi(temporary_columns) - 1;
                 valid_move = (board.Check_Avaiblity(rows, columns)) && (board.Check_Bounds(rows, columns));
                 if (columns + 1 > board.Check_Columns_Size() || !valid_move || columns + 1 < 1)
                 {
                     cout << endl;
                     cout << "Invalid input";
                     cout << endl;
                     valid_move = false;
                }
            }
        }
         
     }while (!valid_move);
    
    board.Edit_Board(rows, columns, piece);
    
}

//============================================================================================
// Allows the user to enter in the number of players.
// Uses the number of players to load players first and lastname into an array of player objects.
// Returns number of players.
//============================================================================================

int Get_Players(Player players[])
{
    
    string number_of_players;
    bool validated_amount_of_players_choosen;
    
    do
    {
        
        cout << "How many Players are playing must be between 2 to 5 players and must be a number: ";
        getline(cin, number_of_players);
        cout << endl;
        
        validated_amount_of_players_choosen = (number_of_players[0] <= 49) || (number_of_players[0] > 53)
                                              || (number_of_players.length() != 1);
        
        if (validated_amount_of_players_choosen)
        {

            cout << endl;
            cout << "Invalid Input";
            cout << endl;
            cout << endl;

            
        }
        
    }while (validated_amount_of_players_choosen);
    
    int amount_of_players_playing = stoi(number_of_players);
    
    for (int i = 0; i < amount_of_players_playing; i++)
    {
        
        string user_entered_name;
        bool validated_name;
        
        do
        {
            cout << "Player " << i + 1 << " enter your full name: ";
            getline(cin, user_entered_name);
            validated_name = Validate_Name(user_entered_name);
            
            
            if (!validated_name) {
                
                cout << endl;
                cout << "Invalid Input";
                cout << endl;
                cout << endl;
                
        }
        
            else
            {
                
                Standardize_Names(players[i], user_entered_name);
                validated_name = !(players[i].lastname != " ") || !players[i].lastname.empty();
                
                if (!validated_name)
                {
                    
                    cout << endl;
                    cout << "Invalid Input";
                    cout << endl;
                    cout << endl;

                    
                }
                
            }
            
        } while (!validated_name);
        
        players[i].piece = 'a' + i;
        
        cout << endl;
        cout << "Your name is: " << players[i].firstname << players[i].lastname << endl;
        cout << "You are piece: " << players[i].piece;
        cout << endl << endl;
        
    }
    
    return amount_of_players_playing;
}

//============================================================================================
// This function Standardizes names by making the first name capitalized capital and the follwing lowercased.
//============================================================================================

void Standardize_Names(Player &player, string user_entered_name)
{
    
    int spaces = 0;
    player.firstname[0] = toupper(user_entered_name[0]);
    
    for (int i = 1; i < user_entered_name.length(); i++)
    {
        
        if (user_entered_name[i] == ' ') {
            
            spaces += 1;
            player.lastname += user_entered_name[i];
            player.lastname += toupper(user_entered_name[i + 1]);
            i += 1;
            
    }
        
        else if (spaces >= 1)
        {
            
            player.lastname += tolower(user_entered_name[i]);
            
        }
        
        else
        {
            
            player.firstname += user_entered_name[i];
            
        }
    }
    
    player.lastname.erase(0,1);
}

//==================================
// Updates players loses
//==================================

void Update_Loses(Player player[], int winning_index, int amount_players)
{
    
    for (int i = 0; i < amount_players; i++)
    {
        
        if (i == winning_index)
        {
            
            player[i].loses += 0;
            
        }
        
        else
        {
            
            player[i].loses += 1;
            
        }
    }
}

//============================================================================================
// This function displays players stats and total games played.
//============================================================================================


void Display_Stats(Player player[], int amount_of_players, int draws, int total_games_played)
{
    
    string spaces = Set_Display_Space(player, amount_of_players, 0);
    cout << endl;
    cout << "Total game played = " << total_games_played << endl << endl;
    cout << spaces << "    WIN  LOSS  DRAWS    " << endl;
    cout << spaces << "  ------ ----- ---- " << endl;
    
    for (int i = 0; i < amount_of_players; i++)
    {
        
        int length_of_current_name = int(player[i].firstname.length() + player[i].lastname.length());
        
        if (length_of_current_name < 3) {
            
            length_of_current_name = 3;
            
    }
        
        string spaces = Set_Display_Space(player, amount_of_players, length_of_current_name);
        cout << player[i].firstname <<player[i].lastname << ' ' << spaces;
        cout << "|  " << player[i].wins;
        cout << "   |  " << player[i].loses;
        cout << "  |  " << draws << " |" << endl;
        
        spaces = Set_Display_Space(player, amount_of_players, 0);
        
        cout << spaces << "  ------ ----- ---- " << endl;
        
    }
}

//============================================================================================
// This function creates the spacing for "display_stats" function
//============================================================================================

string Set_Display_Space(Player player[], int amount_of_players, int current_player_name_length)
{
    
    int longest_name = 0;
    
    for (int i = 0; i < amount_of_players; i++)
    {
        
        int length_of_full_name = int(player[i].firstname.length() + 1 + player[i].lastname.length());
        
        if (length_of_full_name > longest_name)
        {
            
            longest_name = length_of_full_name;
    
        }
    }
    
    string empty_string = "";
    
    for (int i = 0; i < (longest_name + 2) - current_player_name_length; i++)
    {
        
        empty_string += " ";
        
    }
    
        return empty_string;
    
}

//======================================================================================
// Validates users name.
//======================================================================================

bool Validate_Name(string full_name)
{
    char minimum_char = 'A';
    char maximum_char = 'Z';
    
    
    if (full_name[0] == ' ')
    {
        
        return false;
        
    }
    
    for (int i = 0; i < full_name.length(); i++) {
    
        char valdiating_char = toupper(full_name[i]);
        
        if ((int(valdiating_char) < minimum_char || int(valdiating_char) > maximum_char) && valdiating_char != ' ') {
            
            return false;
            
        }
    }
    
        return full_name[full_name.length() - 1] != ' ';
}

//======================================================================================
// Gets boards dimesions and stores them into a rows and columns reference variable.
// also validates the input.
//======================================================================================

int Get_User_Choosen_Dimension(string name_of_dimension, int min, int max) {
    
    string dimension;
    int numeric_value_of_dimnesion;
    char minimum_dimension = '0';
    char maximum_dimension = '9';
    
    do
    {
        
        numeric_value_of_dimnesion = 0;
        
        cout << "Enter the amount of " << name_of_dimension  << " for your Tic-Tac-Toe board, must be between from "<< min << " to "  << max
                                                                                                                                    << ": ";
        getline(cin, dimension);
        
        if (dimension.length() <= 2)
        {
            
            if (int(dimension[0]) >= minimum_dimension && int(dimension[0]) <= maximum_dimension && dimension.length() == 1)
                {
                    
                    numeric_value_of_dimnesion = stoi(dimension);
                
                    if (!(numeric_value_of_dimnesion >= min && numeric_value_of_dimnesion <= max))
                        {
                        cout << endl;
                        cout << "Invalid input";
                        cout << endl;
                        cout << endl;
                        }
                 }
                
                else if (dimension.length() == 2 && int(dimension[1]) >= minimum_dimension && int(dimension[1]) <= maximum_dimension)
                    {
                    
                    numeric_value_of_dimnesion = stoi(dimension);
                    
                        if (!(numeric_value_of_dimnesion >= min && numeric_value_of_dimnesion <= max))
                        {
                            cout << endl;
                            cout << "Invalid input";
                            cout << endl;
                            cout << endl;
                        }
                    
                    }
                
                else
                {
                    cout << endl;
                    cout << "Invalid input";
                    cout << endl;
                    cout << endl;
                }
            }
        
        else
        {
                cout << endl;
                cout << "Invalid Input";
                cout << endl;
                cout << endl;

        }
        
    } while (!(numeric_value_of_dimnesion >= min && numeric_value_of_dimnesion <= max));
    
    cout << endl;
    cout << "Your game has " << dimension << " " << name_of_dimension << "." << endl;
    cout << endl;
    
    return numeric_value_of_dimnesion;
}

//======================================================================================
// Returns the index of the next player to start the game.
//======================================================================================

int Get_Next_Game_Starter(int next_player, int amount_of_turns, int number_of_players)
{
    
    next_player = amount_of_turns + 1;
    
    if (next_player >= number_of_players)
    {
        
        next_player = 0;
        
    }
    
    return next_player;
}
