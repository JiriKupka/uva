#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>

using namespace std;


void print_indent(int length) {
	cout << "  ";
	for(int i=0;i<length;i++) {
		cout << "  ";
	}
}

char num_index_to_char(int index) {
	return 'a'+index;
}

int *get_number_list(int n) {
	int *number_list = new int[n];
	for(int i=0;i<n;i++) number_list[i] = i;
	return number_list;
}

string number_list_to_string(int *number_list, int n) {
	stringstream ss;
	for(int i=0;i<n;i++) {
		if(i!=0) ss << ',';
		ss << num_index_to_char(number_list[i]);
	}
	return ss.str();
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print_conditions(int *number_list, int n, int depth) {
	int *temp_list = get_number_list(n);

	if(depth<n-1) {
		memcpy(temp_list,number_list,n*sizeof(int));

		print_indent(depth);
		cout << "if " << num_index_to_char(temp_list[depth]) << " < " << num_index_to_char(temp_list[depth+1]) << " then" << endl;
		print_conditions(temp_list, n, depth + 1);

		for(int i = 0; i<depth; i++) {
			print_indent(depth);
			swap(temp_list[depth-i],temp_list[depth-i+1]);
			//cout << number_list_to_string(temp_list,n) << endl;
			cout << "else if " << num_index_to_char(temp_list[depth-i-1]) << " < " << num_index_to_char(temp_list[depth-i]) << " then" << endl;
			print_conditions(temp_list, n, depth + 1);
		}

		print_indent(depth);
		swap(temp_list[0], temp_list[1]);
		//cout << number_list_to_string(temp_list,n) << endl;
		cout << "else" << endl;
		print_conditions(temp_list, n, depth + 1);
	}

	else {
		print_indent(depth);
		cout << "writeln(" << number_list_to_string(number_list,n) << ")" << endl;
	}
}

int print_program(int *number_list, int n) {
	cout << "program sort(input,output);" << endl;
	cout << "var" << endl;
	cout << number_list_to_string(number_list, n) << " : integer;" << endl;
	cout << "begin" << endl;
	cout << "  readln(" << number_list_to_string(number_list,n) << ");" << endl;
	print_conditions(number_list, n, 0);
	cout << "end.";
	cout << endl;
}


int main() {
	int inputs = 0, n;
	int line = 0;

	do {
		if(inputs==0) scanf("%d",&inputs);
		else {
			if(line++!=0) cout << endl;
			scanf("%d",&n);
			int *number_list = get_number_list(n);
			print_program(number_list, n);
			inputs--;
		}
	}while(inputs>0);
	
	return 0;
}
