#include <iostream>
#include "Log.h"

void InitLog(const char* message) {

	Log("Log initialized");

}

void Log(const char* message) {
	std::cout << message << std::endl;
}