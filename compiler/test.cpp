#include <string>
#include <iostream>
using namespace std;

int main(){
	int i = stoi("", NULL, 16);
	cout << "0x = " << i << '\n';
	return 0;
}