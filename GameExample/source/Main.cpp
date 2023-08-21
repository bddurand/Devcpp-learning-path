#include "Globals.h"

void insertWord(Block** grid, Word* word, int start_x, int start_y, Orientation orientation) {

	const string data = word->data;
	int size = word->size;

	for (int offset = 0; offset < size; offset++) {
		Block block;
		block.data = data[offset];
		block.isWord = true;


		switch (orientation) {
		
			case Orientation::Horizontally:
				block.x_position = start_x;
				block.y_position = start_y + offset;

				grid[start_y][start_x + offset] = block;
				break;
		
			case Orientation::Vertically:
				block.x_position = start_x + offset;
				block.y_position = start_y;

				grid[start_y + offset][start_x] = block;
				break;

			case Orientation::Diagonally:
				block.x_position = start_x + offset;
				block.y_position = start_y + offset;

				grid[start_y + offset][start_x + offset] = block;
				break;
		}
	}

	word->orientation = orientation;
	word->x_position = start_x;
	word->y_position = start_y;

}

bool canInsertWord(Block** grid, Word word, int start_x, int start_y, Orientation orientation) {
	
	int size = word.size;

	if (DIMENSION < size ) {
		display("No puedo insertar: palabra mas grande que grilla");
		return false;
	}


	switch (orientation) {

		case Orientation::Horizontally:
			if (DIMENSION < start_x + size) {
				//std::cout << "No puedo insertar: palabra cortada " << orientation << " " << start_y << " " << start_x << std::endl;
				return false;
			}

			for (int offset = 0; offset < size; offset++) {
				Block block = grid[start_y][start_x + offset];
				if (block.isWord) {
					
					if (block.data != word.data[offset]) {
						//std::cout << "No puedo insertar: ya esta ocupado" << std::endl;
						return false;
					}
				}
			}
			break;

		case Orientation::Vertically:
			if (DIMENSION < start_y + size) {
				//std::cout << "No puedo insertar: palabra cortada " << orientation << " " << start_y << " " << start_x << std::endl;
				return false;
			}
			for (int offset = 0; offset < size; offset++) {
				Block block = grid[start_y + offset][start_x];
				if (block.isWord) {
					if (block.data != word.data[offset]) {
						//std::cout << "No puedo insertar: ya esta ocupado" << std::endl;
						return false;
					}
				}
			}
			break;

		case Orientation::Diagonally:

			if (DIMENSION < start_x + size) {
				//std::cout << "No puedo insertar: palabra cortada " << orientation << " " << start_y << " " << start_x << std::endl;
				return false;
			}

			if (DIMENSION < start_y + size) {
				//std::cout << "No puedo insertar: palabra cortada " << orientation << " " << start_y << " " << start_x << std::endl;
				return false;
			}

			for (int offset = 0; offset < size; offset++) {
				Block block = grid[start_y + offset][start_x + offset];
				if (block.isWord) {
					if (block.data != word.data[offset]) {
						//std::cout << "No puedo insertar: ya esta ocupado" << std::endl;
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
	display("*****************************");

	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			cout << grid[i][j].data << " ";
		}
		cout << endl;
	}
	display("*****************************");
	display("\n\n");

}

void printWithColors(Block** grid) {


	display("\n");
	display("*****************************");

	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			highlightWord(grid[i][j].color);
			cout << grid[i][j].data;
			cout << " ";			
		}
		cout << endl;
	}
	display("*****************************");
	display("\n\n");

}

void initializeGrid(Block** grid) {
	for (int i = 0; i < DIMENSION; i++) {
		grid[i] = new Block[DIMENSION];

		for (int j = 0; j < DIMENSION; j++) {
			Block block;
			block.data = '*'; // getRandomChar();
			block.x_position = 0;
			block.y_position = 0;
			block.isWord = false;
			grid[i][j] = block;
		}
	}
}

string getRandomEntry() {
	int i = rand() % MAX_WORDS_PER_DICTIONARY - 0;
	return heroes[i];
}

void initializeWords(Word* words) {
	
	for (int i = 0; i < MAX_WORDS; i++) {
		Word word;
		word.data = getRandomEntry();
		word.size = word.data.length();
		word.x_position = 0;
		word.y_position = 0;
		word.orientation = Orientation::Horizontally;
		word.wasFound = false;
		word.wasInserted = false;

		words[i] = word;
	}
}

void fillGrid(Block** grid, Word* words) {

	const int max_tries_per_word = 3;
	int tries = 0;

	for (int i = 0; i < MAX_WORDS; i++) {
		
		while (tries <= max_tries_per_word && words[i].wasInserted != true) {
			int x = rand() % DIMENSION - 0;
			int y = rand() % DIMENSION - 0;

			Orientation orientation = static_cast<Orientation> (rand() % ORIENTATION_COUNT);

			if (canInsertWord(grid, words[i], x, y, orientation)) {
				insertWord(grid, &words[i], x, y, orientation);
				words[i].wasInserted = true;
			}
			tries++;
		}

		tries = 0;
	}
}

Word search(Block** grid, Word* words, string word) {
	for (int i = 0; i < MAX_WORDS; i++) {
		if (word.compare(words[i].data) == 0) {
			return words[i];
		}
	}
	return {""};
}

int count(Word* words) {
	int inserted = 0;

	for (int i = 0; i < MAX_WORDS; i ++) {
		if (words[i].wasInserted)
			inserted++;
	}

	return inserted;
}

void markWord(Block** grid, Word* word) {

	int size = word->size;
	switch(word->orientation) {
		
	case Orientation::Horizontally:
		for (int i = 0; i < size; i++) {
			grid[word->y_position][word->x_position + i].color = Color::Red;
		}
		break;
	case Orientation::Vertically:
		for (int i = 0; i < size; i++) {
			grid[word->y_position + i][word->x_position].color = Color::Green;
		}
		break;
	case Orientation::Diagonally:
		for (int i = 0; i < size; i++) {
			grid[word->y_position + i][word->x_position + i].color = Color::Blue;
		}
		break;
	}
}

void printWaitingDots() {
	cout << ". ";
	this_thread::sleep_for(200ms);
	cout << ". ";
	this_thread::sleep_for(200ms);
	cout << ". ";
	this_thread::sleep_for(200ms);
}

string toUpperCase(string& s) {

	for (int i = 0; i < static_cast<int>(s.length()); i++) {
		s[i] = toupper(s[i]);
	}

	return s;
}

int main() {

	srand(time(NULL));

	Word words[MAX_WORDS] = {};
	Block** grid = new Block* [DIMENSION] {};
	bool mustContinue = true;
	string input = "";
	int tries = 3;
	int found = 0;
	int inserted = 0;

	initializeGrid(grid);
	initializeWords(words);

	fillGrid(grid, words);
	inserted = count(words);
	
	display("<<<<< SOPA DE LETRAS! >>>>>");
	display(">> Este juego consiste en una grilla de " +  to_string(DIMENSION) + " FILAS y " + to_string(DIMENSION) + " COLUMNAS.");
	display(">> Hay " + to_string(inserted) + " palabras ocultas que deberas encontrar.");
	display(">> Tenes " + to_string(tries) + " intentos.");
	display(">> Presione 'ENTER' para iniciar.");
	cin.get();

	while(mustContinue && tries > 0) {


		printWaitingDots();
		system("cls");
		display(">> Cantidad de palabras encontradas " + to_string(found) + " de " + to_string(inserted) + ".");
		display(">> Intentos restantes " + to_string(tries) + ".");
		printGrid(grid);

		if ( found == inserted) {

			display(">> GANASTE! :) Encontraste todas las palabras.\n");
			display(">> Resultado: ");
			mustContinue = false;
		}
		else {

			display(">> Inserte una palabra para buscar: ");
			cin >> input;
			
			printWaitingDots();
			
			Word word = search(grid, words, toUpperCase(input));
			if (word.data != "") {
				found++;
				markWord(grid, &word);
				display(">> Bien! Ya encontraste: " + to_string(found) + " de " + to_string(inserted) + " palabras.\n");
			}
			else {
				tries--;
				this_thread::sleep_for(2000ms);
				system("cls");
				display(">> Que pena! :( La respuesta es incorrecta. Te quedan: " + to_string(tries) + " intentos.");
				
				if (tries == 0) {
					display(">> GAME OVER! <<");
					//MostrarSolucion;
					break;
				}

				
				display(">> Desea continuar buscando? Si/No: ");
				cin >> input;
				if (input == "no")
					mustContinue = false;
			}
		}

		printWithColors(grid);
	}

	cin.get();
}