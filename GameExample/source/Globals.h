#pragma once

#include <iostream>
#include <time.h>
#include <string>

const int DIMENSION = 10;
const int MAX_WORDS = 3;
const int MAX_WORDS_PER_DICTIONARY = 5;

struct Block {

	char data;
	int x_position;
	int y_position;
	bool isWord;
};

struct Word {

	std::string data;
	int size;
	bool wasFound;
	bool wasInserted;
};


char getRandomChar() {
	return rand() % (91 - 65) + 65;
}

enum Orientation {

	Horizontally = 0, 
	Vertically = 1, 
	Diagonally = 2
};

const std::string heroes[MAX_WORDS_PER_DICTIONARY] = {
	"SUPERMAN",
	"BATMAN",
	"FLASH",
	"ROBIN",
	"AQUAMAN"
};

void display(const std::string& message) {
	std::cout << message << std::endl;
}