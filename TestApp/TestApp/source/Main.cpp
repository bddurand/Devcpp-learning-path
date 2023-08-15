#include <iostream>
#include "Log.h"


void Log(const char*);

int Multiply(int a, int b) {

	Log("Multiply");
	return a * b;
}

int main() {

	std::cout << Multiply(2 , 5) << std::endl;
	std::cin.get();
}