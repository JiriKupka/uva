#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdio>

using namespace std;
int board_size = 400;


// Zpracování křivky rekurzivně podle gramatiky
// http://cs.wikipedia.org/wiki/Dra%C4%8D%C3%AD_k%C5%99ivka
string dragon_curve(string in, int iter) {
	if(iter<0) return in;

	stringstream out;
	for(int i=0;i<in.length();i++) {
		if(in[i]=='L') out << "L+R+";
		else if(in[i]=='R') out << "-L-R";
		else out << in[i];
	}

	return dragon_curve(out.str(),iter-1);
}


char **process_curve(string dragon, int *rows, int *columns) {
	char **board;

	board = new char*[board_size];
	for(int i = 0;i<board_size;i++) board[i] = new char[board_size];
	for(int row = 0;row<board_size;row++) {
		for(int column = 0;column<board_size;column++) board[row][column] = ' ';
	}

	int dragon_length = dragon.length();
	int degree = 0, prev_degree = 0, row = board_size/2, column = board_size/2;
	int left = column, bottom = 0, right = 0, top = row;

	for(int i=0;i<dragon_length;i++) {
		if((degree==0||degree==180)&&(dragon[i]=='L'||dragon[i]=='R')) {
			if(degree==0) column += 1;
			else column -= 1;

			if(degree==0) board[row][column] = '_';
			else board[row][column] = '_';

			if(degree==0) column += 1;
			else column -= 1;
		}
		else if((degree==90||degree==270)&&(dragon[i]=='L'||dragon[i]=='R')) {
			if(degree==270) row += 1;

			if(degree==90) board[row][column] = '|';
			else board[row][column] = '|';

			if(degree==90) row -= 1;
		}
		else if(dragon[i]=='+') {
			prev_degree = degree;
			degree += 90;
			if(degree==360) degree = 0;
		}
		else if(dragon[i]=='-') {
			prev_degree = degree;
			degree -= 90;
			if(degree==-90) degree = 270;
		}


		// Zjištění velikosti pole
		if(row<top) top = row;
		if(row>bottom) bottom = row;
		if(column<left) left = column;
		if(column>right) right = column;
	}

	*rows = bottom-top+1;
	*columns = right-left+1;

	// cout << "rows: " << *rows << endl;
	// cout << "columns: " << *columns << endl;
	// cout << "bottom: " << bottom << endl;
	// cout << "top: " << top << endl;
	// cout << "left: " << left << endl;
	// cout << "right: " << right << endl;

	char **mini_board = new char*[*rows];
	for(int i=0;i<*rows;i++) mini_board[i] = new char[*columns];

	for(int row=top;row<bottom+1;row++) {
		for(int column=left;column<right+1;column++) {
			mini_board[row-top][column-left] = board[row][column];
		}
	}

	for(int row=0;row<*rows;row++) {
		for(int column=*columns-1;column>=0;column--) {
			if(mini_board[row][column]==' ') mini_board[row][column] = '0';
			else break;
		}
	}

	return mini_board;
}


int main(void) {
	int level, input_number = 0;

	while(scanf("%d",&level)==1) {
		if(level==0) return 0;

		int rows, columns;
		char **board;
		string dragon_string;
		dragon_string = dragon_curve("L",level-1);
		board = process_curve(dragon_string, &rows, &columns);

		for(int row=0;row<rows;row++) {
			for(int column=0;column<columns;column++) {
				if(row==1&&column==0&&level==1) continue;
				if(board[row][column]=='0') break;
				else cout << board[row][column];
			}
			if(board[row][0]!='0') cout << endl;
		}
		cout << '^' << endl;

		input_number++;
	}

	return 0;
}