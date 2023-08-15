#include <iostream>

int main() {

	//1
	void* ptr = NULL;
	void* ptr2 = 0;
	void* ptr3 = nullptr;

	//2
	int var = 9;
	void* var_ptr = &var;

	//3
	char* char_ptr = new char[8];
	memset(char_ptr, 0, 8);
	
	char** char_ptr_ptr = &char_ptr; //char_ptr_ptr will store the char_ptr address in memory. 
	//x86 cpu addresses use 32bit. So when we take a look at char_ptr address we'll see 00 00 00 00 00

	delete[] char_ptr;

	std::cin.get();
}