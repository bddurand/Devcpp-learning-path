#include <iostream>

int main() {

	int a = 5;
	int b = 2;

	int c = 8;
	int d = 6;

	int& ref = a; //Reference to A
	ref = b; //Reference equal to B

	//a = 2 , b = 2 => a = b; 

	int* ref2 = &c; //Reference to C address
	*ref2 = 16; //Assigning 16 to the address pointed by ref2
	ref2 = &d; //Reference to D address
	*ref2= 12; //Assigning 12 to the address pointed by ref2



	std::cout << a << std::endl;
	std::cout << b << std::endl;

	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cin.get();

}