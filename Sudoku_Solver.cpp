#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Prints a solid straight Line
void printLine() {

	for (int i = 0; i < 25; i++)
		cout << "-";
	cout << endl;

}

//Prints out board in sudoku grid
void printBoard(int Board[][9]) {

	for (int x = 0; x < 9; x++) {
		if (x == 0 || x == 3 || x == 6)
			printLine();
		cout << "| ";
		for (int y = 0; y < 9; y++) {
			cout << Board[x][y] << " ";
			if (y == 2 || y == 5 || y == 8)
				cout << "| ";
		}
		cout << endl;
	}
	printLine();

}

//checks if the board is solved
bool finish(int Board[][9]) {

	int sum = 0;

	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			sum += Board[x][y];
		}
	}

	if (sum == 405)
		return true;
	else
		return false;

}

/*Figures out which box the program is looking at in the format:
1 2 3
4 5 6
7 8 9
*/
int Box(int x, int y) {

	int box = 0;

	if (y < 3) {
		box = 1;
	}
	else if (y >= 3 && y < 6)
		box = 2;
	else if (y >= 6)
		box = 3;

	if (x < 3)
		box += 0;
	else if (x >= 3 && x < 6)
		box += 3;
	else if (x >= 6)
		box += 6;

	return box;

}

//Gets the top left cord of the box X position
int BoxCordY(int i) {
	int x;

	if (i == 1 || i == 4 || i == 7)
		x = 0;
	else if (i == 2 || i == 5 || i == 8)
		x = 3;
	else
		x = 6;
	return x;
}

//Gets the top left cord of the box Y position
int BoxCordX(int i) {
	int x;

	if (i == 1 || i == 2 || i == 3)
		x = 0;
	else if (i == 4 || i == 5 || i == 6)
		x = 3;
	else
		x = 6;
	return x;
}

//checks if it is legal to put number in a spot
bool checkLegal(int Board[][9], int Num, int x, int y) {
	int notLegal = 0;

	for (int i = 0; i < 9; i++) {
		if (Board[i][y] == Num)
			notLegal++;
	}

	for (int i = 0; i < 9; i++) {
		if (Board[x][i] == Num)
			notLegal++;
	}

	for (int i = 0; i < 3; i++) {
		for (int a = 0; a < 3; a++) {
			if (Board[BoxCordX(Box(x, y)) + i][BoxCordY(Box(x, y)) + a] == Num)
				notLegal++;
		}
	}

	if (Board[x][y] > 0)
		notLegal++;

	if (notLegal > 0)
		return false;
	else
		return true;
}

int main() {

	int board[9][9];
	int position[2];
	int x = 0;
	int y = 0;
	int temp = 0;

	string line;
	
	ifstream myfile("samplesudoku1.txt");
	
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			for (int i = 0; i < line.size(); i++) {
				if (isdigit(line[i])) {
					temp = x / 2;
					board[temp][y] = line[i]-48;
					y++;
				}
			}
			y = 0;
			x++;
		}
		myfile.close();
		x = 0;
		y = 0;
	}
	else cout << "Unable to open file";

	int Num = 0;

	while (finish(board) == 0) {

		for (int a = 1; a < 10; a++) {
			for (int i = 1; i < 10; i++) {
				temp = 0;
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						if (checkLegal(board, a, BoxCordX(i) + x, BoxCordY(i) + y) == 1) {
							temp++;
							if (temp == 1) {
								position[0] = BoxCordX(i) + x;
								position[1] = BoxCordY(i) + y;
							}
						}
					}
				}
				if (temp == 1) {
					board[position[0]][position[1]] = a;
				}
			}
		}
	}

	printBoard(board);
	
	cout << endl << endl;

	system("pause");

	return 0;
}
