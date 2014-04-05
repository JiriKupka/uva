#include <iostream>
#include <cstdio>

using namespace std;

int BOARD_SIZE = 8;

int character_to_int(char character) {
	switch(character) {
		case 'P': return 1;
		case 'R': return 2;
		case 'B': return 3;
		case 'Q': return 4;
		case 'K': return 5;
		case 'N': return 6;
		case 'p': return -1;
		case 'r': return -2;
		case 'b': return -3;
		case 'q': return -4;
		case 'k': return -5;
		case 'n': return -6;
		default: return 0;
	}
}

int reset_board(int board[8][8]) {
	for(int row=0;row<BOARD_SIZE;row++) {
		for(int column=0;column<BOARD_SIZE;column++) {
			board[row][column] = 0;
		}
	}
}

void save_line(int board[8][8],string line, int n) {
	for(int i=0;i<BOARD_SIZE;i++) {
		board[n][i] = character_to_int(line[i]);
	}
}

void print_board(int board[8][8]) {
	for(int row=0;row<BOARD_SIZE;row++) {
		for(int column=0;column<BOARD_SIZE;column++) {
			cout << board[row][column] << " ";
		}
		cout << endl;
	}
}


bool solve_pawn(int board[8][8],int row, int column, int look_for) {
	if(look_for>0) {
		if(row+1<BOARD_SIZE) {
			if(column-1>=0) {
				if(board[row+1][column-1]==look_for) return true;
			}
			if(column+1<BOARD_SIZE) {
				if(board[row+1][column+1]==look_for) return true;
			}
		}
	}
	else {
		if(row-1>0) {
			if(column-1>=0) {
				if(board[row-1][column-1]==look_for) return true;
			}
			if(column+1<BOARD_SIZE) {
				if(board[row-1][column+1]==look_for) return true;
			}
		}	
	}
	return false;
}

bool solve_rook(int board[8][8],int row, int column, int look_for) {
	for(int i=row;i>=0;i--) {
		if(i==row) continue;
		if(board[i][column]!=0&&board[i][column]!=look_for) break;
		if(board[i][column]==look_for) return true;
	}
	for(int i=row;i<BOARD_SIZE;i++) {
		if(i==row) continue;
		if(board[i][column]!=0&&board[i][column]!=look_for) break;
		if(board[i][column]==look_for) return true;
	}
	for(int i=column;i>=0;i--) {
		if(i==column) continue;
		if(board[row][i]!=0&&board[row][i]!=look_for) break;
		if(board[row][i]==look_for) return true;
	}
	for(int i=column;i<BOARD_SIZE;i++) {
		if(i==column) continue;
		if(board[row][i]!=0&&board[row][i]!=look_for) break;
		if(board[row][i]==look_for) return true;
	}
	return false;	
}

bool solve_bishop(int board[8][8],int row, int column, int look_for) {
	for(int r=row,c=column;r>=0&&c>=0;r--,c--) {
		if(r==row&&c==column) continue;
		if(board[r][c]!=0&&board[r][c]!=look_for) break;
		if(board[r][c]==look_for) return true;
	}
	for(int r=row,c=column;r>=0&&c<BOARD_SIZE;r--,c++) {
		if(r==row&&c==column) continue;
		if(board[r][c]!=0&&board[r][c]!=look_for) break;
		if(board[r][c]==look_for) return true;
	}
	for(int r=row,c=column;r<BOARD_SIZE&&c>=0;r++,c--) {
		if(r==row&&c==column) continue;
		if(board[r][c]!=0&&board[r][c]!=look_for) break;
		if(board[r][c]==look_for) return true;
	}
	for(int r=row,c=column;r<BOARD_SIZE&&c<BOARD_SIZE;r++,c++) {
		if(r==row&&c==column) continue;
		if(board[r][c]!=0&&board[r][c]!=look_for) break;
		if(board[r][c]==look_for) return true;
	}
	return false;	
}

bool solve_queen(int board[8][8],int row, int column, int look_for) {
	return solve_rook(board,row,column,look_for)||solve_bishop(board,row,column,look_for);	
}

bool solve_king(int board[8][8],int row, int column, int look_for) {
	if(row-1>=0) {
		if(board[row-1][column]==look_for) return true;
		if(column-1>=0) {
			if(board[row-1][column-1]==look_for) return true;
		}
		if(column+1<BOARD_SIZE) {
			if(board[row-1][column+1]==look_for) return true;
		}
	}
	if(row+1<BOARD_SIZE) {
		if(board[row+1][column]==look_for) return true;
		if(column-1>=0) {
			if(board[row+1][column-1]==look_for) return true;
		}
		if(column+1<BOARD_SIZE) {
			if(board[row+1][column+1]==look_for) return true;
		}
	}

	if(column-1>=0) {
		if(board[row][column-1]==look_for) return true;
	}
	if(column+1<BOARD_SIZE) {
		if(board[row][column+1]==look_for) return true;
	}

	return false;	
}

bool solve_knight(int board[8][8],int row, int column, int look_for) {
	if(row-2>=0) {
		if(column+1<BOARD_SIZE) {
			if(board[row-2][column+1]==look_for) return true;
		}
		if(column-1>=0) {
			if(board[row-2][column-1]==look_for) return true;
		}
	}
	if(row-1>=0) {
		if(column+2<BOARD_SIZE) {
			if(board[row-1][column+2]==look_for) return true;
		}
		if(column-2>=0) {
			if(board[row-1][column-2]==look_for) return true;
		}
	}
	if(row+2<BOARD_SIZE) {
		if(column+1<BOARD_SIZE) {
			if(board[row+2][column+1]==look_for) return true;
		}
		if(column-1>=0) {
			if(board[row+2][column-1]==look_for) return true;
		}
	}
	if(row+1<BOARD_SIZE) {
		if(column+2<BOARD_SIZE) {
			if(board[row+1][column+2]==look_for) return true;
		}
		if(column-2>=0) {
			if(board[row+1][column-2]==look_for) return true;
		}
	}
	return false;	
}


bool check_field(int board[8][8],int row,int column) {
	int look_for;
	bool check;

	look_for = ((board[row][column]<0)?5:-5);

	switch(board[row][column]) {
		case 1:
		case -1:
			check = solve_pawn(board,row,column,look_for);
			break;
		case 2:
		case -2:
			check = solve_rook(board,row,column,look_for);
			break;
		case 3:
		case -3:
			check = solve_bishop(board,row,column,look_for);
			break;
		case 4:
		case -4:
			check = solve_queen(board,row,column,look_for);
			break;
		case 5:
		case -5:
			check = solve_king(board,row,column,look_for);
			break;
		case 6:
		case -6:
			check = solve_knight(board,row,column,look_for);
	}
	return check;
}


// Pokud ma bily sach, vrati 0
// cerny vrati 1
// nikdo nema sach -1
int check_check(int board[8][8]) {
	bool check = false;
	for(int row=0;row<BOARD_SIZE;row++) {
		for(int column=0;column<BOARD_SIZE;column++) {
			check = check_field(board,row,column);
			if(check) {
				if(board[row][column]>0) return 0;
				if(board[row][column]<1) return 1;
			}
		}
	}
	return -1;
}

int main(void) {
	int board[8][8];
	int check, n = 0, game = 1;
	bool not_empty_board = false;
	string line;
	reset_board(board);

	while (cin.good()) {
		getline(cin,line);

		if(line!="........"&&!line.empty()) {
			not_empty_board = true;
		}

		if(line.empty()) {
			check = check_check(board);
			if(check==0) {
				cout << "Game #" << game << ": black king is in check." << endl;
			}
			else if(check==1) {
				cout << "Game #" << game << ": white king is in check." << endl;
			}
			else {
				if(not_empty_board) {
					cout << "Game #" << game << ": no king is in check." << endl;
				}
			}
			//print_board(board);
			reset_board(board);

			not_empty_board = false;
			n = 0;
			game++;
			continue;
		}
		
		save_line(board,line,n);
		n++;
	}

	return 0;
}