#include<iostream> 
#include <windows.h> 
#include<dos.h>
#include<stdlib.h> 
#include<string.h>
#include<conio.h>
#include <time.h>

#define WIDTH_OF_CONSOLE 90
#define HEIGHT_OF_CONSOLE 26
#define WIDTH_OF_CONSOLE 70   
#define WIDTH_OF_MENU 20
#define SizeOfSwimGap 7    

using namespace std;


char Fish[2][9] = { 'D',';','-','-','{','{','{','\\',',',
					'D','"','_','_','{','{','{','/','"' };


int FishPosition = 6; 
int Scoreboard = 0;   
int PlasticPosition[3];
int SwimGapPosition[3];
int PlasticFlag[3];


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD PositioningOfCursor; 
void gotoxy(int x, int y)
{
	PositioningOfCursor.X = x;  
	PositioningOfCursor.Y = y;  
	SetConsoleCursorPosition(console, PositioningOfCursor); 
}

void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20; 

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}


void drawBorder() {
	
	for (int i = 0; i < WIDTH_OF_CONSOLE; i++) {
		gotoxy(i, 0); cout << "=";
		gotoxy(i, HEIGHT_OF_CONSOLE); cout << "=";
	}

	for (int i = 0; i < HEIGHT_OF_CONSOLE; i++) {
		gotoxy(0, i); cout << "=";
		gotoxy(WIDTH_OF_CONSOLE, i); cout << "=";
	}
	for (int i = 0; i < HEIGHT_OF_CONSOLE; i++) {
		gotoxy(WIDTH_OF_CONSOLE, i); cout << "=";
	}
}


void ProducePlastic(int ind) {
	srand(time(NULL)); 
	SwimGapPosition[ind] = 3 + rand() % 14;
}


void drawPlastic(int ind) {
	if (PlasticFlag[ind] == true) {  
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "=======";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "=======";
		}
	}
}


void erasePlastic(int ind) {
	if (PlasticFlag[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "       ";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "       ";
		}
	}
}





void drawFish() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(j + 2, i + FishPosition); cout << Fish[i][j];
		}
	}
}


void eraseFish() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(j + 2, i + FishPosition); cout << " ";
		}
	}
}



int collision() {
	if (PlasticPosition[0] >= 61) {
		if (FishPosition < SwimGapPosition[0] || FishPosition > SwimGapPosition[0] + SizeOfSwimGap) {
			srand(time(NULL));
			int choice = std::rand() % 10;
			switch (choice) { 
			case 0:
				cout << "The Fish was Swallowed Up by Plastic in the Ocean.\n";
				break;
			case 1:
				cout << "Killed by Plastic..... AGAIN!\n";
				break;
			case 2:
				cout << "You are an adult, don't litter.\n";
				break;
			case 3:
				cout << "Four R's, my friend: Reduce, reuse, recycle, Rihanna.\n";
				break;
			case 4:
				cout << "No no no, think you throw away your litter.\n";
				break;
			case 5:
				cout << "SWALLOWED UP BY PLASTIC.\n";
				break;
			case 6:
				cout << "End the take, make, waste economy. Think CIRCULARITY\nSingle use plastic is a BIG no no.";
				break;
			case 7:
				cout << "Carpe dayum!\n";
				break;
			case 8:
				cout << "What can YOU do to stop plastic entering the oceans\n";
				break;
			case 9:
				cout << "Be the change you want to SEA in the world.\n";
				break;
			default:
				cout << "The time to ACT is NOW.\n";
				break;
			}
			_getch();
			return 1;
		}
	}
	return 0;
}


void Game_Over() {
	system("cls"); 
	cout << endl;
	cout << "             ______   GAME   ___________" << endl;
	cout << "             ________   OVER   _________" << endl;
	cout << "             ___________________________" << endl << endl;
	cout << "\t\tPlastic is reducing fish numbers.";
	cout << "\t\tPress any key to go back to menu.";
	_getch();

}
void UpdateScoreboard() {
	gotoxy(WIDTH_OF_CONSOLE + 7, 5); cout << "Score: " << Scoreboard << endl;
}

void User_Information() {

	system("cls");
	cout << "User_Information";
	cout << "\n----------------";
	cout << "\nSadly there is plenty of plastic polluting the oceans.";
	cout << "\nSpacebar triggers the Fish to swim upwards to escape the plastic mountains.";
	cout << "\n\nFor the Main Menu, Tap a Button";
	_getch();
}

void playGame() {

	FishPosition = 6; 
	Scoreboard = 0;   
	PlasticFlag[0] = 1;
	PlasticFlag[1] = 0;
	PlasticPosition[0] = PlasticPosition[1] = 4;

	system("cls"); 
	drawBorder();
	ProducePlastic(0);
	UpdateScoreboard();

	gotoxy(WIDTH_OF_CONSOLE + 3, 2); cout << "Plastic Ocean";
	gotoxy(WIDTH_OF_CONSOLE + 6, 4); cout << "   Fish";
	gotoxy(WIDTH_OF_CONSOLE + 6, 6); cout << "             ";
	gotoxy(WIDTH_OF_CONSOLE + 7, 12); cout << "          ";
	gotoxy(WIDTH_OF_CONSOLE + 7, 13); cout << "         ";
	gotoxy(WIDTH_OF_CONSOLE + 2, 14); cout << "  Spacebar = swim";
	gotoxy(10, 5); cout << "Press a button to Start Game";
	_getch();
	gotoxy(10, 5); cout << "                      ";

	while (1) {

		if (_kbhit()) {
			char spacebar = _getch();
			if (spacebar == 32) {
				if (FishPosition > 3)
					FishPosition -= 3;
			}
			if (spacebar == 27) {
				break;
			}
		}

		drawFish();
		drawPlastic(0);
		drawPlastic(1);
		if (collision() == 1) {
			Game_Over();
			return;
		}
		Sleep(100); 
		
		eraseFish();
		erasePlastic(0);
		erasePlastic(1);
		FishPosition += 1;

		if (FishPosition > HEIGHT_OF_CONSOLE - 3) {  
			Game_Over();
			return;
		}


		if (PlasticFlag[0] == 1)
			PlasticPosition[0] += 2;

		if (PlasticFlag[1] == 1)
			PlasticPosition[1] += 2;

		if (PlasticPosition[0] >= 40 && PlasticPosition[0] < 42) {
			PlasticFlag[1] = 1;
			PlasticPosition[1] = 4;
			ProducePlastic(1);
		}
		if (PlasticPosition[0] > 68) {
			Scoreboard++;
			UpdateScoreboard();
			PlasticFlag[1] = 0;
			PlasticPosition[0] = PlasticPosition[1];
			SwimGapPosition[0] = SwimGapPosition[1];
		}

	}

}

int main()
{
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	
	do {
		system("cls");
		gotoxy(10, 5); cout << "                              ";
		gotoxy(10, 6); cout << "   Fish in a Plastic Ocean    ";
		gotoxy(10, 7); cout << "                              ";
		gotoxy(10, 9); cout << "1. Start Game";
		gotoxy(10, 10); cout << "2. User Information";
		gotoxy(10, 11); cout << "3. Quit";
		gotoxy(10, 13); cout << "Pick your selection: ";
		char op = _getch();

		if (op == '1') playGame();
		else if (op == '2') User_Information();
		else if (op == '3') exit(0);

	} while (1);

	return 0;
}
