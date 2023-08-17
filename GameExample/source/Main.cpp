#include "Globals.h"

void insertWord(Block** grid, Word word, int start_x, int start_y, Orientation orientation) {

	const std::string data = word.data;
	int size = word.size;

	for (int offset = 0; offset < size; offset++) {
		Block block;
		block.data = data[offset];
		block.isWord = true;


		switch (orientation) {
		
			case 0: //horizontally
				block.x_position = start_x;
				block.y_position = start_y + offset;

				grid[start_y][start_x + offset] = block;
				break;
		
			case 1: //vertically
				block.x_position = start_x + offset;
				block.y_position = start_y;

				grid[start_y + offset][start_x] = block;
				break;

			case 2: //diagonally
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
		display("No puedo insertar: palabra mas grande que grilla");
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


	display("\n");
	display("***********************");

	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			std::cout << grid[i][j].data << " ";
		}
		std::cout << std::endl;
	}

	display("***********************");
	display("\n\n");

}

void initializeGrid(Block** grid) {
	for (int i = 0; i < DIMENSION; i++) {
		grid[i] = new Block[DIMENSION];

		for (int j = 0; j < DIMENSION; j++) {
			Block block;
			block.data = '*';//getRandomChar();
			block.x_position = 0;
			block.y_position = 0;
			block.isWord = false;
			grid[i][j] = block;
		}
	}
}

std::string getRandomEntry() {
	srand(time(NULL));
	int i = rand() % MAX_WORDS_PER_DICTIONARY - 0;
	return heroes[i];
}

void initializeWords(Word* words) {
	
	for (int i = 0; i < MAX_WORDS; i++) {
		Word word;
		word.data = getRandomEntry();
		word.size = word.data.length();
		word.wasFound = false;
		word.wasInserted = false;

		words[i] = word;
	}
}

void fillGrid(Block** grid, Word* words) {

	for (int i = 0; i < MAX_WORDS; i++) {

		int x = rand() % DIMENSION - 0;
		int y = rand() % DIMENSION - 0;

		Orientation orientation = static_cast<Orientation> (rand() % 3);

		if (canInsertWord(grid, words[i], x, y, orientation)) {
			insertWord(grid, words[i], x, y, orientation);
			words[i].wasInserted = true;
		}
	}
}

bool search(Block** grid, Word* words, std::string& word) {
	for (int i = 0; i < MAX_WORDS; i++) {
		if (word.compare(words[i].data) == 0) {
			return true;
		}
	}
	return false;
}

int count(Word* words) {
	int inserted = 0;

	for (int i = 0; i < MAX_WORDS; i ++) {
		if (words[i].wasInserted)
			inserted++;
	}

	return inserted;
}

int main() {

	srand(time(NULL));

	Word words[MAX_WORDS] = {};
	Block** grid = new Block* [DIMENSION] {};
	bool mustContinue = true;
	std::string input = "";
	int tries = 3;
	int found = 0;
	int inserted = 0;

	display("<<<<< SOPA DE LETRAS! >>>>>");
	display(">> Este juego consiste en una grilla de 10x10.");
	display(">> Hay palabras ocultas que deberas encontrar.");
	display(">> Tenes 3 intentos.");
	display(">> Presione 'ENTER' para iniciar.");
	std::cin.get();

	initializeGrid(grid);
	initializeWords(words);

	fillGrid(grid, words);
	inserted = count(words);

	printGrid(grid);
	
	while(mustContinue) {

		if (found < inserted) {

			display(">> Inserte una palabra para buscar: ");
			std::cin >> input;
			bool correct = search(grid, words, input);
			if (correct) {
				found++;
				display(">> Bien! Ya encontraste: " + std::to_string(found) + " de " + std::to_string(inserted) + " palabras.\n");
			}
			else {
				tries--;
				display(">> Que pena! :( La respuesta es incorrecta. Te quedan: " + std::to_string(tries) + " intentos.");
				display(">> Desea continuar buscando? Si/No: ");
				std::cin >> input;
				if (input == "no")
					mustContinue = false;
			}
		}
		else {
			display(">> GANASTE! :) Encontraste todas las palabras.\n");
			display(">> Resultado: ");
			printGrid(grid);
			mustContinue = false;
		}
	}

	std::cin.get();
}