#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

// Zápis pomocí segmentů, podobně jako na segmentovém LCD displayi
//  --0-- 
//  5   1
// 	--6--
//  4   2
//  --3--

char SEGMENT_MASKS[7] = {1,2,4,8,16,32,64};
char CHAR_MASKS[10] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,
						0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
int MAX_SIZE = 12;

// Vykresluje řádky segmentového displeje
void draw_row(int *num_list_int, int length, char segment_mask, int size) {
	for(int i=0;i<length;i++) {
		cout << " ";
		for(int a=0;a<size;a++) {
			if(segment_mask&CHAR_MASKS[num_list_int[i]]) cout << "-";
			else cout << " ";
		}
		cout << " ";

		// mezery mezi cislicemi - pokud neni cislo posledni
		if(i!=length-1) cout << " ";	
	}

	cout << endl;
}


// Vykresluje sloupce segmentového displeje
void draw_columns(int *num_list_int, int length, char segment1_mask, char segment2_mask, int size) {
	for(int row=0;row<size;row++) {
		for(int i=0;i<length;i++) {
			if(segment1_mask&CHAR_MASKS[num_list_int[i]]) cout << "|";
			else cout << " ";

			for(int column=0;column<size;column++) cout << " ";

			if(segment2_mask&CHAR_MASKS[num_list_int[i]]) cout << "|";
			else cout << " ";

			// mezery mezi cislicemi - pokud neni cislo posledni
			if(i!=length-1) cout << " ";
		}
		cout << endl;
	}	
}

// Převod cpp řetězce s čísly na pole čísel int
int *string_to_int_array(string numbers) {
	int *numbers_array = new int[numbers.length()];

	for(int i=0;i<numbers.length();i++) {
		stringstream ss;
		ss << numbers[i];

		int result;
		ss >> result;		
		numbers_array[i] = result;
	}

	return numbers_array;
}


int main(int argc, char *argv[]) {
	int size, line_counter = 0;
	char *char_array = new char[MAX_SIZE];

	while(scanf("%d %s", &size, char_array) != EOF) {
		string numbers(char_array);
		int *numbers_array = string_to_int_array(numbers);

		if(size!=0) {
			if(line_counter++!=0) cout << endl;
			draw_row(numbers_array,numbers.length(),SEGMENT_MASKS[0], size);
			draw_columns(numbers_array,numbers.length(),SEGMENT_MASKS[5],SEGMENT_MASKS[1],size);
			draw_row(numbers_array,numbers.length(),SEGMENT_MASKS[6], size);
			draw_columns(numbers_array,numbers.length(),SEGMENT_MASKS[4],SEGMENT_MASKS[2],size);
			draw_row(numbers_array,numbers.length(),SEGMENT_MASKS[3], size);
		}

	}

	cout << endl;

	return 0;
}