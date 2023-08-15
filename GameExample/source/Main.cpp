#include "Globals.h"


void insertWord(Block** grid, Word word, int start_x, int start_y, Orientation orientation) {

	const char* data = word.data;
	int size = word.size;

	for (int offset = 0; offset < size; offset++) {
		Block block;
		block.data = data[offset];
		block.isWord = true;


		switch (orientation) {
		
			case 0: //horizontal
				block.x_position = start_x;
				block.y_position = start_y + offset;

				grid[start_y][start_x + offset] = block;
				break;
		
			case 1: //vertical
				block.x_position = start_x + offset;
				block.y_position = start_y;

				grid[start_y + offset][start_x] = block;
				break;

			case 2:
				block.x_position = start_x + offset;
				block.y_position = start_y + offset;

				grid[start_y + offset][start_x + offset] = block;
				break;
		}
	}

}

bool canInsertWord(Block** grid, Word word, int start_x, int start_y, Orientation orientation) {
	
	int size = word.size;

	if (DIMENSION < size ) {
		std::cout << "No puedo insertar: palabra mas grande que grilla" << std::endl;
		return false;
	}


	switch (orientation) {

		case 0: //horizontal
			if (DIMENSION < start_x + size) {
				std::cout << "No puedo insertar: palabra cortada " << orientation << " " << start_y << " " << start_x << std::endl;
				return false;
			}

			for (int offset = 0; offset < size; offset++) {
				Block block = grid[start_y][start_x + offset];
				if (block.isWord) {
					
					if (block.data != word.data[offset]) {
						std::cout << "No puedo insertar: ya esta ocupado" << std::endl;
						return false;
					}
				}
			}
			break;

		case 1: //vertical
			if (DIMENSION < start_y + size) {
				std::cout << "No puedo insertar: palabra cortada " << orientation << " " << start_y << " " << start_x << std::endl;
				return false;
			}
			for (int offset = 0; offset < size; offset++) {
				Block block = grid[start_y][start_x + offset];
				if (block.isWord) {
					if (block.data != word.data[offset]) {
						std::cout << "No puedo insertar: ya esta ocupado" << std::endl;
						return false;
					}
				}
			}
			break;

		case 2:

			if (DIMENSION < start_x + size) {
				std::cout << "No puedo insertar: palabra cortada " << orientation << " " << start_y << " " << start_x << std::endl;
				return false;
			}

			if (DIMENSION < start_y + size) {
				std::cout << "No puedo insertar: palabra cortada " << orientation << " " << start_y << " " << start_x << std::endl;
				return false;
			}

			for (int offset = 0; offset < size; offset++) {
				Block block = grid[start_y + offset][start_x + offset];
				if (block.isWord) {
					if (block.data != word.data[offset]) {
						std::cout << "No puedo insertar: ya esta ocupado" << std::endl;
						return false;
					}
				}
			}
			break;
	}	

	return true;
}

void printGrid(Block** grid) {


	std::cout << std::endl;

	for (int i = 0; i < DIMENSION; i++) {

		for (int j = 0; j < DIMENSION; j++) {

			std::cout << grid[i][j].data << " ";
		}

		std::cout << std::endl;
	}
}

int main() {

	srand(time(NULL));
	Word words[MAX_WORDS] = { };

	Block** grid = new Block* [DIMENSION] {};


	//Initialize Grid
	for (int i = 0; i < DIMENSION; i++) {
		grid[i] = new Block[DIMENSION];

		for (int j = 0; j < DIMENSION; j++) {
			Block block;
			block.data = '*'; //replace with random letter
			block.x_position = 0;
			block.y_position = 0;
			block.isWord = false;
			grid[i][j] = block;
		}
	}

	printGrid(grid);


	//Initialize Words
	for (int i = 0; i < MAX_WORDS; i++) {
		Word word;
		word.data = "asd";
		word.size = (int) strlen(word.data);

		words[i] = word;
	}

	//Insert Words into Grid
	for (int i = 0; i < MAX_WORDS; i++) {

		int x = rand() % DIMENSION - 0;
		int y = rand() % DIMENSION - 0;

		Orientation orientation = static_cast<Orientation> (rand() % 3);

		if(canInsertWord(grid, words[i], x, y, orientation))
			insertWord(grid, words[i], x, y, orientation);
	}

	printGrid(grid);

	std::cin.get();
}