#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
#include <conio.h>

class Node {
public:
	Node();
	bool isAlive;
	int liveNeighbors;
};

Node::Node() {
	isAlive = false;
	liveNeighbors = 0;
}

Node** gameBoard;
int size = 40;

void createBoard();
void clearBoard();
void updateNodes();
void printBoard();
void eventHandler();
void shutdown();
void pulsar();
void gliderGun();

int findLiveNeighbors(const int &x, const int &y);

bool shouldExit = false;

enum states {MENU, RUNNING, QUITTING} state;

int main(){
	std::thread event(eventHandler);
	std::vector<states> stateMgr;
	stateMgr.push_back(MENU);
	
	createBoard();

	do {
		printBoard();
		Sleep(250);
		updateNodes();
		
	} while(!shouldExit);

	event.join();
	shutdown();
	return 0;
}

void clearBoard() {
	for(int x = 0; x < size; x++)
		for(int y = 0; y < size; y++)
			gameBoard[x][y].isAlive = false;
}

void updateNodes() {
	for(int x = 0; x < size; x++) {
		for(int y = 0; y < size; y++) {
			gameBoard[x][y].liveNeighbors = findLiveNeighbors(x, y);
		}
	}
	
	for(int x = 0; x < size; x++) {
		for(int y = 0; y < size; y++) {
			Node* current = &gameBoard[x][y];
			
			if(current->isAlive) {
				if(current->liveNeighbors < 2)
					current->isAlive = false;
				if(current->liveNeighbors >= 2 && current->liveNeighbors <= 3) 
					current->isAlive = true;
				if(current->liveNeighbors > 3)
					current->isAlive = false;
			}

			if(!current->isAlive) {
				if(current->liveNeighbors == 3)
					current->isAlive = true;
			}
		}
	}
}

void pulsar() {
	gameBoard[3][5].isAlive = true;
	gameBoard[3][6].isAlive = true;
	gameBoard[3][7].isAlive = true;
	gameBoard[3][11].isAlive = true;
	gameBoard[3][12].isAlive = true;
	gameBoard[3][13].isAlive = true;

	gameBoard[5][3].isAlive = true;
	gameBoard[5][8].isAlive = true;
	gameBoard[5][10].isAlive = true;
	gameBoard[5][15].isAlive = true;

	gameBoard[6][3].isAlive = true;
	gameBoard[6][8].isAlive = true;
	gameBoard[6][10].isAlive = true;
	gameBoard[6][15].isAlive = true;

	gameBoard[7][3].isAlive = true;
	gameBoard[7][8].isAlive = true;
	gameBoard[7][10].isAlive = true;
	gameBoard[7][15].isAlive = true;

	gameBoard[8][5].isAlive = true;
	gameBoard[8][6].isAlive = true;
	gameBoard[8][7].isAlive = true;
	gameBoard[8][11].isAlive = true;
	gameBoard[8][12].isAlive = true;
	gameBoard[8][13].isAlive = true;

	gameBoard[10][5].isAlive = true;
	gameBoard[10][6].isAlive = true;
	gameBoard[10][7].isAlive = true;
	gameBoard[10][11].isAlive = true;
	gameBoard[10][12].isAlive = true;
	gameBoard[10][13].isAlive = true;

	gameBoard[11][3].isAlive = true;
	gameBoard[11][8].isAlive = true;
	gameBoard[11][10].isAlive = true;
	gameBoard[11][15].isAlive = true;

	gameBoard[12][3].isAlive = true;
	gameBoard[12][8].isAlive = true;
	gameBoard[12][10].isAlive = true;
	gameBoard[12][15].isAlive = true;

	gameBoard[13][3].isAlive = true;
	gameBoard[13][8].isAlive = true;
	gameBoard[13][10].isAlive = true;
	gameBoard[13][15].isAlive = true;

	gameBoard[15][5].isAlive = true;
	gameBoard[15][6].isAlive = true;
	gameBoard[15][7].isAlive = true;
	gameBoard[15][11].isAlive = true;
	gameBoard[15][12].isAlive = true;
	gameBoard[15][13].isAlive = true;
}
void gliderGun() {
	gameBoard[2][26].isAlive = true;
	
	gameBoard[3][24].isAlive = true;
	gameBoard[3][26].isAlive = true;

	gameBoard[4][14].isAlive = true;
	gameBoard[4][15].isAlive = true;
	gameBoard[4][22].isAlive = true;
	gameBoard[4][23].isAlive = true;
	gameBoard[4][36].isAlive = true;
	gameBoard[4][37].isAlive = true;

	gameBoard[5][13].isAlive = true;
	gameBoard[5][17].isAlive = true;
	gameBoard[5][22].isAlive = true;
	gameBoard[5][23].isAlive = true;
	gameBoard[5][36].isAlive = true;
	gameBoard[5][37].isAlive = true;

	gameBoard[6][2].isAlive = true;
	gameBoard[6][3].isAlive = true;
	gameBoard[6][12].isAlive = true;
	gameBoard[6][18].isAlive = true;
	gameBoard[6][22].isAlive = true;
	gameBoard[6][23].isAlive = true;

	gameBoard[7][2].isAlive = true;
	gameBoard[7][3].isAlive = true;
	gameBoard[7][12].isAlive = true;
	gameBoard[7][16].isAlive = true;
	gameBoard[7][18].isAlive = true;
	gameBoard[7][19].isAlive = true;
	gameBoard[7][24].isAlive = true;
	gameBoard[7][26].isAlive = true;

	gameBoard[8][12].isAlive = true;
	gameBoard[8][18].isAlive = true;
	gameBoard[8][26].isAlive = true;

	gameBoard[9][13].isAlive = true;
	gameBoard[9][17].isAlive = true;

	gameBoard[10][14].isAlive = true;
	gameBoard[10][15].isAlive = true;

}

int findLiveNeighbors(const int &x, const int &y) {
	int count = 0;
	
	if(x > 0) {
		if(y > 0)
			if(gameBoard[x - 1][y - 1].isAlive)
				count++;
		if(gameBoard[x - 1][y].isAlive)
			count++;
		if(y < size - 2)
			if(gameBoard[x - 1][y + 1].isAlive)
				count++;
	}
	
	if(y > 0)
		if(gameBoard[x][y - 1].isAlive)
				count++;
	if(y < size - 2)
		if(gameBoard[x][y + 1].isAlive)
				count++;
		
	if(x < size - 2) {
		if(y > 0)
			if(gameBoard[x + 1][y - 1].isAlive)
				count++;
		if(gameBoard[x + 1][y].isAlive)
			count++;
		if(y < size - 2)
			if(gameBoard[x + 1][y + 1].isAlive)
				count++;
	}
	return count;
}


void eventHandler() {
	while(!shouldExit) {
		char cmd = _getch();

		if(cmd == 'q' || cmd == (char)27) {
			shouldExit = true;
		}
		if(cmd == 'g') {
			clearBoard();
			gliderGun();
		}
		if(cmd == 'p') {
			clearBoard();
			pulsar();
		}
	}
}

void printBoard() {
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	for(int x = 0; x < size; x++) {
		for(int y = 0; y < size; y++) {
			std::cout << (gameBoard[x][y].isAlive ? '#' : ' ') << " ";
		}
		std::cout << std::endl;
	}
}

void createBoard() {
	gameBoard = new Node*[size];
	for(int x = 0; x < size; x++)
		gameBoard[x] = new Node[size];
}

void shutdown() {
	for(int x = 0; x < size; x++)
		delete[] gameBoard[x];

	delete[] gameBoard;
}
