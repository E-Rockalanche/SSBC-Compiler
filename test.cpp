#include <iostream>
using namespace std;

struct Block{
	int data[8];
};

int main(){
	int array[3] = {1, 2, 3};
	int* var = array;
	int*& ref = var;
	int c = *ref;

	cout << "Block size = " << sizeof(Block) << '\n';
	cout << "Array size = " << sizeof(array) << '\n';

	cout << "array = " << array << '\n';
	cout << "&array = " << &array << '\n';
	cout << "var contents = " << var << '\n';

	cout << "array[0] = " << array[0] << '\n';

	cout << "*(var + 1) = " << *(var + 1) << '\n';

	cout << "ref[2] = " << ref[2] << '\n';

	cout << "c = " << c << '\n';
}