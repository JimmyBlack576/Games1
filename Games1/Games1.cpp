#include <iostream>
#include <time.h>
#include <iomanip>
#include <ctime>

#define X 'X'
#define O 'O'

using namespace std;

char firstPlayer[50];
char secondPlayer[50];
int nF = 0, nS = 0;

void EnterName() {
	cout << "Enter firts player name: ";
	cin >> firstPlayer;

	cout << "Enter second player name: ";
	cin >> secondPlayer;
}

void ChoiceChar() {
	char c;
	cout << "What character will you play " << firstPlayer
		<< "? (X or O)";
	cin >> c;
	(c == 'X') ? nF = 1 : nS = 1;
}

void menu() {
	char c;
	bool flag = true;
	do {
		cout << " \"Tic-Tac-Toe\"\n\n";
		cout << "1. Name input" << firstPlayer
			<< " / " << secondPlayer << "\n";
		cout << "2. Character selection(X or O) \n";
		cout << "3. Exit\n";
		cin >> c;
		switch (c)
		{
		case '1':
			EnterName();
			system("cls");
			break;
		case '2':
			ChoiceChar();
			flag = false;
			break;
		case '3':
			exit(0);
			break;
		}
	} while (c != '3' && flag);
}

const int SIZE = 8;//Размер сетки
const int FIFTEEN = 4;
int arrx[8] = { 1,2,2,1,-1,-2,-2,-1 };
int arry[8] = { 2,1,-1,-2,-2,-1,1,2 };
//Функция отображения доски
void print_arr(int arr[][SIZE]);
//Рекурсивная функция хода коня
void Knight(int arr[][SIZE], int num, int i0, int j0);

char board[3][3];

void show() {
	cout << " 1  2  3\n";
	for (int i = 0; i < 3; i++) {
		cout << i + 1;
		for (int j = 0; j < 3; j++) {
			cout << "|" << board[i][j];
		}
		cout << "|\n";
	}
}

void stepPlayer(int a) {
	int c1, c2;
	do {
		cout << "Select horizontal value: ";
		cin >> c1;
		cout << "Select vertical value: ";
		cin >> c2;
		if (c1 > 3 || c2 > 3 || c1 < 0 || c2 < 0) {
			cout << "Incorrect value!\n";
			continue;
		}
		if (board[c1 - 1][c2 - 1] == 'X' || board[c1 - 1][c2 - 1] == 'O') {
			cout << "This cell is busy!\n";
		}
	} while (board[--c1][--c2] != '_');
	a ? board[--c1][--c2] = X : board[--c1][--c2] = O;
	show();
}


bool win() {
	//по горизонтали
	if (board[0][0] == board[0][1] && board[0][1] == board[0][2]
		&& board[0][0] != '_')return false;
	if (board[1][0] == board[1][1] && board[1][1] == board[1][2]
		&& board[1][0] != '_')return false;
	if (board[2][0] == board[2][1] && board[2][1] == board[2][2]
		&& board[2][0] != '_')return false;

	//по вертикали
	if (board[0][0] == board[1][0] && board[1][0] == board[2][0]
		&& board[0][0] != '_')return false;
	if (board[0][1] == board[1][1] && board[1][1] == board[2][1]
		&& board[0][1] != '_')return false;
	if (board[0][2] == board[1][2] && board[1][2] == board[2][2]
		&& board[0][2] != '_')return false;

	//по диагонали
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]
		&& board[0][0] != '_') return false;
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]
		&& board[0][2] != '_') return false;

	return true;
}


int main()
{
	srand(time(NULL));
	//Task "Horse path"____________________
	/*int x, y;
	cout << "Specify the cell in which the horse should be (1-8): \n";
	cout << "X: ";
	cin >> x;
	cout << "Y: ";
	cin >> y;
	int deck[SIZE][SIZE] = {};
	Knight(deck, 1, y-1 ,x-1);
	system("pause");
	system("cls");*/
	//Task "TicTacToe"_____________________
	menu();
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '_';
		}
	}
	show();
	while (win() && count != 9) {
		cout << "Player turn " << firstPlayer << endl;
		stepPlayer(nF);
		if (!win()) {
			cout << "Player " << firstPlayer << " win!\n";
			break;
		}
		count++;
		if (count == 9) {
			cout << "Draw!";
			break;
		}
		cout << "Player turn " << secondPlayer << endl;
		stepPlayer(nS);
		if (!win()) {
			cout << "Player " << secondPlayer << " win!\n";
			break;
		}
		count++;
		if (count == 9) cout << "Draw!";

	}
}

void print_arr(int arr[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << setw(3) << arr[i][j];
		}
		cout << endl;
	}
}

void Knight(int arr[][SIZE], int num, int i0, int j0) {
	arr[i0][j0] = num++;
	//print_arr(arr);
	//system("pause");    // для просмотра хода пошагово, раскомментировать 
	for (int i = 0; i < 8; i++) {
		int inew = i0 + arry[i];
		int jnew = j0 + arrx[i];

		if (num > SIZE * SIZE) {
			print_arr(arr);
			exit(0);
		}
		if (inew<0 || inew>SIZE - 1 || jnew<0 || jnew>SIZE - 1 || arr[inew][jnew] != 0)
			continue;
		Knight(arr, num, inew, jnew);
		arr[inew][jnew] = 0;
	}
}
