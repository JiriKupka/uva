#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>

using namespace std;

bool is_int(char c) {
	return c>='0'&&c<='9';
}


int char_to_int(char c) {
	return (int) c-'0';
}


string remove_empty_chars(string input) {
	if(input[0]==' ') return remove_empty_chars(input.substr(1));
	if(input[input.length()-1]==' ') return remove_empty_chars(input.substr(0,input.length()-2));
	return input;
}


int evl(int num1, int num2, char op) {
	switch(op) {
		case '*': return num1*num2;
		case '+': return num1+num2;
		case '/': return num1/num2;
		case '-': return num1-num2;
		default: return 0;
	}
}

int load_data(string in, int numbers[50],char operators[50]) {
	int number = 0, positive = 1, index = 0;
	bool set = true, set_operator = false;

	for(int i=0;i<in.length()+1;i++) {
		// Pro první číslo
		if(i==0&&in[i]=='+') {
			positive = 1;
			continue;
		}
		if(i==0&&in[i]=='-') {
			positive = -1;
			continue;
		} 

		// Pro ostatní čísla
		if(is_int(in[i])) {
			set = true;
			if(set) number *= 10;
			number += char_to_int(in[i]);
		}
		else {
			if(set) {
				number *= positive;
				set_operator = false;
				set = false;
				numbers[index++] = number;

				number = 0;
			}
			if(in[i]=='+'||in[i]=='-'||in[i]=='*'||in[i]=='/') {
				if(!set_operator) {
					operators[index-1] = in[i];
					set_operator = true;
					positive = 1;
				}
				else {
					if(in[i]=='-') positive *= -1;
				}
			}
		}
	}

	return index;
}


void print_line(int numbers[50],char operators[50],int count,string result) {
	for(int i=0;i<count;i++) {
		cout << numbers[i];
		if(i<count-1) cout << " " << operators[i] << " ";
	}
	cout << " = " << result;
	cout << endl;
}

void eliminate_line(int numbers[50],char operators[50],int count, string result) {
	int index = 0;
	int lvl = 0;

	for(int i = 0;i<count-1;i++) {
		if(operators[i]=='*'||operators[i]=='/') {
			index = i;
			lvl = 1;
			break;
		}
	}

	for(int i = 0;i<count-1;i++) {
		if(index==i) {
			numbers[i] = evl(numbers[i],numbers[i+1],operators[i]);
		}
		else if(i>index) {
			numbers[i] = numbers[i+1];
			operators[i-1] = operators[i];
		}
	}

	print_line(numbers,operators,count-1,result);
}


int main(void) {
	int first = 0;
	char buffer[100];

	while(!cin.eof()) {

		int numbers[50];
		char operators[50];
		string in, result;

		getline(cin,in);
		if(in=="") continue;
		in = remove_empty_chars(in);
		result = remove_empty_chars(in.substr(in.find("=")+1));
		in = in.substr(0,in.find("="));

		int index = load_data(in,numbers,operators);
		if(result!="") print_line(numbers,operators,index,result);
		while(index>1) {
			eliminate_line(numbers,operators,index--,result);
		}

		cout << endl;
	}

	return 0;
}