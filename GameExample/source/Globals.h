#pragma once

#include <iostream>
#include <time.h>

const int DIMENSION = 10;
const int MAX_WORDS = 7;

struct Block {

	char data;
	int x_position;
	int y_position;
	bool isWord;
};

struct Word {

	const char* data;
	int size;
};


char getRandomChar() {
	return rand() % (91 - 65) + 65;
}

enum Orientation {

	Horizontally = 0, 
	Vertically = 1, 
	Diagonally = 2
};