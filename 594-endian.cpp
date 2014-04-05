#include <iostream>
#include <sstream>
using namespace std;


int convert_endians(int num) {
	int byte1 = num << 24;
	int byte2 = (num << 8)&0x00ff0000;
	int byte3 = (num >> 8)&0x0000ff00;
	int byte4 = (num >> 24)&0x000000ff;

	return byte1|byte2|byte3|byte4;
}

int convert_string2int(string in) {
	stringstream ss;
	ss << in;

	int result;
	ss >> result;

	return result;
}


int main(void) {
	string line;
	int number;

	while(getline(cin,line)!=NULL) {
		number = convert_string2int(line);
		cout << number << " converts to " << convert_endians(number);
		cout << endl;
	}

}