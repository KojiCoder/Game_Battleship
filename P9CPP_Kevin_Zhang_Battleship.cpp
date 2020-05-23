#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
using namespace std;

// lines 9-11: declare all necessary global variables
int game_size, aim_col, aim_row, ship_remain = 5;
bool replace_ship = false, is_coor = true, miss = false;
bool passA = false, passB = false, passC = false, passD = false, passS = false;

// lines 14-15: declare all necessary global arrays
char hid_gameboard[15][15];
char show_gameboard[15][15];

// function to set up boards
void set_board(int size){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			hid_gameboard[i][j] = '_';
			show_gameboard[i][j] = '_';
		}
	}
}

// function to display the boards

/**
	If you want to show the board with all the ship, change board to be less than 2
	in the for loop on line 36
**/

void display_gameboards(int size){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int board = 0; board < 1; board++){
		cout<<"\t   ";
		for (int i = 0; i < size; i++){
			cout<<char(65 + i)<<" ";
		}
		cout<<endl<<endl;
		for (int i = 0; i < size; i++){
			if (i < 10){
				cout<<"\t "<<i<<" ";
			}
			else{
				cout<<"\t"<<i<<" ";
			}
			for (int j = 0; j < size; j++){
				if (board == 0){
					if (hid_gameboard[i][j] == 'X'){
						// set x to red
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); 
						cout<<hid_gameboard[i][j]<<" ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else if (hid_gameboard[i][j] == 'O'){
						// set o to blue
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
						cout<<hid_gameboard[i][j]<<" ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					else{
						cout<<hid_gameboard[i][j]<<" ";
					}
				}
				else{
					cout<<show_gameboard[i][j]<<" ";
				}
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}
}

// function to place ships on the board
void place_ship(char ship, int ship_size, int board_size){
	srand(time(0));
	// declare all necessary local variables
	int direction, start_col, start_row, boundary_num, reserved = 0;
	// lines 82-84: randomly generate numbers for direction of the ship and the placement of ship
	direction = rand() % 4;
	start_col = rand() % board_size;
	start_row = rand() % board_size;
	// lines 87-88: randomly generate again if selected spot is taken
	while (show_gameboard[start_col][start_row] != '_'){
		start_col = rand() % board_size;
		start_row = rand() % board_size;
	}
	for (int i = 0; i < ship_size; i++){
		switch(direction){
			// check if ship can be horizontally placed in the right direction
			case 0: boundary_num = start_col + i; break;
			// check if ship can be horizontally placed in the left direction
			case 1: boundary_num = start_col - i; break;
			// check if ship can be place vertically upward
			case 2: boundary_num = start_row + i; break;
			// check if ship can be place vertically downward
			case 3: boundary_num = start_row - i; break;
		}
		if (boundary_num >= board_size || boundary_num < 0){
			replace_ship = true;
		}
		else{
			replace_ship = false;
		}
	}
	// lines 109-164: place ship base on their direction
	for (int i = 0; i < ship_size && replace_ship == false; i++){
		switch(direction){
			case 0:
				if (show_gameboard[start_row][start_col+i] == '_'){
					reserved++;
				}
				else{
					replace_ship = true;
				}
				if (reserved == ship_size){
					for (int j = 0; j < ship_size; j++){
						show_gameboard[start_row][start_col+j] = ship;
					}
				}
				break;
			case 1: 
				if (show_gameboard[start_row][start_col-i] == '_'){
					reserved++;
				}
				else{
					replace_ship = true;
				}
				if (reserved == ship_size){
					for (int j = 0; j < ship_size; j++){
						show_gameboard[start_row][start_col-j] = ship;
					}
				}
				break;
			case 2:
				if (show_gameboard[start_row+i][start_col] == '_'){
					reserved++;
				}
				else{
					replace_ship = true;
				}
				if (reserved == ship_size){
					for (int j = 0; j < ship_size; j++){
						show_gameboard[start_row+j][start_col] = ship;
					}
				}
				break;
			case 3:
				if (show_gameboard[start_row-i][start_col] == '_'){
					reserved++;
				}
				else{
					replace_ship = true;
				}
				if (reserved == ship_size){
					for (int j = 0; j < ship_size; j++){
						show_gameboard[start_row-j][start_col] = ship;
					}
				}
				break;
		}
	}
}

// function to place ship and also checks if it needs repalcement of ship
void ship_placement_sys(char ship_char, int ship_size, int game_size){
	place_ship(ship_char, ship_size, game_size);
	while (replace_ship == true){
		place_ship(ship_char, ship_size, game_size);
	}
}

// function to find column based on user input
char find_coor_char(string coor_input){
	char coor_char;
	if (isalpha(coor_input[0])){
		coor_char = tolower(coor_input[0]);
	}
	else if (isalpha(coor_input[1])){
		coor_char = tolower(coor_input[1]);
	}
	else if (isalpha(coor_input[2])){
		coor_char = tolower(coor_input[2]);
	}
	return coor_char;
}

// function to find the row based on user input
char find_coor_num_tens(string coor_input){
	char coor_num_tens;
	if (coor_input.length() == 2){
		coor_num_tens = '0';
	}
	else{
		if (isalpha(coor_input[0])){
			coor_num_tens = coor_input[1];
		}
		else if (isalpha(coor_input[2])){
			coor_num_tens = coor_input[0];
		}
	}
	return coor_num_tens;
}

// function to find the row based on user input
char find_coor_num_ones(string coor_input){
	char coor_num_ones;
	if (coor_input.length() == 2){
		if (isalpha(coor_input[0])){
			coor_num_ones = coor_input[1];
		}
		else{
			coor_num_ones = coor_input[0];
		}
	}
	else{
		if (isalpha(coor_input[0])){
			coor_num_ones = coor_input[2];
		}
		else if (isalpha(coor_input[2])){
			coor_num_ones = coor_input[1];
		}
	}
	return coor_num_ones;
}

// function to check if the user's coor is correct
bool check_is_coor(string coor_input){
	int num_char = 0;
	for (int i = 0; i < coor_input.length(); i++){
		if (isalpha(coor_input[i])){
			num_char++;
		}
	}
	if (game_size != 15){
		if (coor_input.length() != 2 || num_char != 1){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		if (coor_input.length() < 2 || coor_input.length() > 3 || num_char != 1 || (coor_input.length() == 3 && isalpha(coor_input[1]))){
			return false;
		}
		else{
			return true;
		}
	}
}

// function that converts user's input into column and row
void coor_convert(char coor_char, char coor_num_tens, char coor_num_ones, int board_size){
	int check_cor = 0, check_row = 0;
	string col_alpha = "abcdefghijklmno";
	string row_num = "0123456789";
	for (int i = 0; i < board_size; i++){
		if (coor_char == col_alpha[i]){
			aim_col = i;
			is_coor = true;
			i = 20;
		}
		else{
			check_cor++;
		}
	}
	if (coor_num_tens == row_num[0]){
		for (int j = 0; j < board_size; j++){
			if (coor_num_ones == row_num[j]){
				aim_row = j;
				is_coor = true;
				j = 20; 
			}
			else{
				check_row++;
			}
		}
	}
	else if (coor_num_tens == row_num[1]){
		for (int k = 0; k < board_size; k++){
			if (coor_num_ones == row_num[k]){
				aim_row = 10 + k;
				is_coor = true;
				k = 20; 
			}
			else{
				check_row++;
			}
		}
	}
	else{
		is_coor = false;
	}
	if (check_cor == board_size || check_row == board_size){
		is_coor = false;
	}
}

// function that determines if the user's coordinate is a hit or a miss
void hit_or_miss(){
	if (show_gameboard[aim_row][aim_col] == '_'){
		hid_gameboard[aim_row][aim_col] = 'X';
		miss = true;
	}
	else{
		hid_gameboard[aim_row][aim_col] = 'O';
		miss = false;
	}
}

// function that determines if a ship is fully destroyed and tells how many ships are left
void check_ships(){
	int total_A = 5, total_B = 4, total_C = 3, total_D = 2, total_S = 3;
	for (int i = 0; i < game_size; i++){
		for (int j = 0; j < game_size; j++){
			if (show_gameboard[i][j] == 'A' && hid_gameboard[i][j] == 'O'){
				total_A--;
			}
			if (show_gameboard[i][j] == 'B' && hid_gameboard[i][j] == 'O'){
				total_B--;
			}
			if (show_gameboard[i][j] == 'C' && hid_gameboard[i][j] == 'O'){
				total_C--;
			}
			if (show_gameboard[i][j] == 'D' && hid_gameboard[i][j] == 'O'){
				total_D--;
			}
			if (show_gameboard[i][j] == 'S' && hid_gameboard[i][j] == 'O'){
				total_S--;
			}
		}
	}
	if (total_A == 0 && passA == false){
		ship_remain--;
		passA = true;
		cout<<"You have destroyed an Aircraft Carrier!!! "<<ship_remain<<" ship(s) left!!!"<<endl<<endl;
	}
	if (total_B == 0 && passB == false){
		ship_remain--;
		passB = true;
		cout<<"You have destroyed a Battleship!!! "<<ship_remain<<" ship(s) left!!!"<<endl<<endl;
		
	}
	if (total_C == 0 && passC == false){
		ship_remain--;
		passC = true;
		cout<<"You have destroyed a Cruiser!!! "<<ship_remain<<" ship(s) left!!!"<<endl<<endl;
		
	}
	if (total_D == 0 && passD == false){
		ship_remain--;
		passD = true;
		cout<<"You have destroyed a Destroyer!!! "<<ship_remain<<" ship(s) left!!!"<<endl<<endl;
		
	}
	if (total_S == 0 && passS == false){
		ship_remain--;
		passS = true;
		cout<<"You have destroyed a Submarine!!! "<<ship_remain<<" ship(s) left!!!"<<endl<<endl;
	}
}

int main(){
	// lines 368-369: declare all necessary local variables
	int size_pick, mode, turns;
	string coor_input;
	cout<<"Hello! Welcome to Battleship!!!!"<<endl;
	cout<<"Please enter fullscreen for a better experience!!!"<<endl;
	cout<<"Before we start the game, what board size do you want to play on?"<<endl<<endl;
	cout<<"\t1. Small (6x6)*"<<endl;
	cout<<"\t2. Medium (10x10)"<<endl;
	cout<<"\t3. Large (15x15)"<<endl<<endl<<endl;
	cout<<"*NOTE: Due to the small size of the board, it might take longer than usual to randomly generate the board."<<endl;
	cout<<"       Please be patient and wait for a few seconds. (At max 30 seconds)"<<endl<<endl;
	cout<<"Please enter your selection here: ";
	// asks user for input
	cin>>size_pick;
	// lines 382-391: checks user input
	while(size_pick < 1 || size_pick > 3){
		cout<<"You have selected a size that wasn't stated above."<<endl<<endl;
		cout<<"\t1. Small (6x6)*"<<endl;
		cout<<"\t2. Medium (10x10)"<<endl;
		cout<<"\t3. Large (15x15)"<<endl<<endl<<endl;
		cout<<"*NOTE: Due to the small size of the board, it might take longer than usual to randomly generate the board."<<endl;
		cout<<"       Please be patient and wait for a few seconds. (At max 30 seconds)"<<endl<<endl;
		cout<<"Please enter your selection here: ";
		cin>>size_pick;
	}
	cout<<"How difficult do you want the game to be (1-Easy, 2-Normal, 3-Hard): ";
	// asks user for input
	cin>>mode;
	// lines 396-400: checks user input
	while(mode < 1 || mode > 3){
		cout<<"You have failed to select a mode."<<endl;
		cout<<"How difficult do you want the game to be (1-Easy, 2-Normal, 3-Hard): ";
		cin>>mode;
	}
	cout<<endl<<endl;
	// lines 403-449: run code based on user input
	switch(size_pick){
		case 1:
			game_size = 6;
			switch(mode){
				case 1: turns = 30; break;
				case 2: turns = 26; break;
				case 3: turns = 20; break;
			}
			// setup boards
			set_board(game_size);
			// place aircraft carrier
			ship_placement_sys('A', 5, game_size);
			// place battleship
			ship_placement_sys('B', 4, game_size);
			// place cruiser
			ship_placement_sys('C', 3, game_size);
			// place destroyer
			ship_placement_sys('D', 2, game_size);
			// place submarine
			ship_placement_sys('S', 3, game_size);
			// display board
			display_gameboards(game_size);
			break;
		case 2:
			game_size = 10;
			switch(mode){
				case 1: turns = 78; break;
				case 2: turns = 65; break;
				case 3: turns = 45; break;
			}
			// setup boards
			set_board(game_size);
			// place aircraft carrier
			ship_placement_sys('A', 5, game_size);
			// place battleship
			ship_placement_sys('B', 4, game_size);
			// place cruiser
			ship_placement_sys('C', 3, game_size);
			// place destroyer
			ship_placement_sys('D', 2, game_size);
			// place submarine
			ship_placement_sys('S', 3, game_size);
			// display board
			display_gameboards(game_size);
			break;
		case 3:
			game_size = 15;
			switch(mode){
				case 1: turns = 175; break;
				case 2: turns = 140; break;
				case 3: turns = 105; break;
			}
			// setup boards
			set_board(game_size);
			// place aircraft carrier
			ship_placement_sys('A', 5, game_size);
			// place battleship
			ship_placement_sys('B', 4, game_size);
			// place cruiser
			ship_placement_sys('C', 3, game_size);
			// place destroyer
			ship_placement_sys('D', 2, game_size);
			// place submarine
			ship_placement_sys('S', 3, game_size);
			// display board
			display_gameboards(game_size);
			break;
	}
	// repeats lines 472-519 if condition remains true (main game)
	for (turns; turns > 0 && ship_remain != 0; turns--){
		cout<<"You have "<<turns<<" shell(s) remaining left!!!"<<endl<<endl;
		cout<<"Please enter a coordinate to fire at on the board: ";
		// asks user for coordinate
		cin>>coor_input;
		cout<<endl;
		// lines 479-492: checks user input base on board size
		if (game_size != 15){
			while (check_is_coor(coor_input) == false){
				cout<<"You have entered something that wasn't a coordinate!!!"<<endl;
				cout<<"Please again enter a coordinate to fire at on the board: ";
				cin>>coor_input;
			}
		}
		else{
			while (check_is_coor(coor_input) == false){
				cout<<"You have entered something that wasn't a coordinate!!!"<<endl;
				cout<<"Please again enter a coordinate to fire at on the board: ";
				cin>>coor_input;
			}
		}
		// convert user input
		coor_convert(find_coor_char(coor_input), find_coor_num_tens(coor_input), find_coor_num_ones(coor_input), game_size);
		// lines 496-506: checks user coordinate
		while (is_coor == false){
			cout<<"The coordinate that you have entered isn't on the board!!!"<<endl;
			cout<<"Please again enter a coordinate to fire at on the board: ";
			cin>>coor_input;
			while (check_is_coor(coor_input) == false){
				cout<<"You have entered something that wasn't a coordinate!!!"<<endl;
				cout<<"Please again enter a coordinate to fire at on the board: ";
				cin>>coor_input;
			}
			coor_convert(find_coor_char(coor_input), find_coor_num_tens(coor_input), find_coor_num_ones(coor_input), game_size);
		}
		// determine if hit or miss
		hit_or_miss();
		// display gameboard
		display_gameboards(game_size);
		if (miss == true){
			cout<<"You missed!!! :("<<endl<<endl;
		}
		else{
			cout<<"A HIT!!!"<<endl<<endl;
		}
		// check ships on the board
		check_ships();
	}
	if (ship_remain == 0){
		cout<<"Congrats!!! You have won!!!"<<endl<<endl;
	}
	else{
		cout<<"You have failed to sink all of the enemy's ship. :("<<endl<<endl;
	}
	// lines 527-545: displays enemy ships
	cout<<"Enemy ships:"<<endl<<endl;
	cout<<"\t   ";
	for (int i = 0; i < game_size; i++){
		cout<<char(65 + i)<<" ";
	}
	cout<<endl<<endl;
	for (int i = 0; i < game_size; i++){
		if (i < 10){
			cout<<"\t "<<i<<" ";
		}
		else{
			cout<<"\t"<<i<<" ";
		}
		for (int j = 0; j < game_size; j++){
			cout<<show_gameboard[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
