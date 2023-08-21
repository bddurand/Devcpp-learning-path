#pragma once

#include <iostream>
#include <thread>
#include <time.h>
#include <string>
#include <Windows.h>

using namespace std::chrono_literals;
using namespace std;

const int DIMENSION = 15;
const int MAX_WORDS = 5;
const int MAX_WORDS_PER_DICTIONARY = 15;
const int ORIENTATION_COUNT = 3;

enum Orientation {

	Horizontally = 0,
	Vertically = 1,
	Diagonally = 2
};

const string heroes[MAX_WORDS_PER_DICTIONARY] = {
	"SUPERMAN",
	"BATMAN",
	"FLASH",
	"ROBIN",
	"AQUAMAN",
	"WONDERWOMAN",
	"SPIDERMAN",
	"IRONMAN",
	"THOR",
	"HULK",
	"BLACKWIDOW",
	"ARROW",
	"GREENLANTERN",
	"CAPAMERICA",
	"WOLVERINE"
};

enum class Color
{
	Black, Blue, Green,
	Cyan, Red, Magenta,
	Brown, White, Gray,
	LightBlue, LightGreen, LightCyan,
	LightRed, LightMagenta, Yellow
};

struct Block {

	char data;
	int x_position;
	int y_position;
	bool isWord;
	Color color = Color::White;
};

struct Word {

	std::string data;
	int size;
	int x_position;
	int y_position;
	Orientation orientation;
	bool wasFound;
	bool wasInserted;
};


char getRandomChar() {
	return rand() % (91 - 65) + 65;
}

void display(const string& message) {
	cout << message << endl;
}

void highlightWord(Color color) {
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	wAttrib = screenBufferInfo.wAttributes;

	//wAttribute AND EQ -> NOT ( 0001 OR 0010 OR 0100 OR 1000)
	//wAttribute AND EQ -> NOT ( 1111 )
	//wAttribute AND EQ -> 0000
	//wAttrib -> 0000 AND 0000
	//wAttrib -> 0000 -> white color
	wAttrib &= ~(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

	
	int c = (int)color;

	if (c & (int)Color::Blue)
		wAttrib |= FOREGROUND_BLUE; // 0000 OR 0001 = 0001
	if (c & (int)Color::Green)
		wAttrib |= FOREGROUND_GREEN; // 0000 OR 0010 = 0010
	if (c & (int)Color::Red)
		wAttrib |= FOREGROUND_RED; // 0000 OR 0100 = 01000
	if (c & (int)Color::Gray)
		wAttrib |= FOREGROUND_INTENSITY; // 0000 OR 1000 = 1000

	SetConsoleTextAttribute(outputHandle, wAttrib);
}