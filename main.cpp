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
#define SizeOfSwimGap1 8    
#define SizeOfSwimGap2 6    
#define SizeOfSwimGap3 4    


using namespace std;

char Fish1[1][6] = { '>','<','{','{','"','>', };

char Fish2[2][9] = { 'D',';','-','-','{','{','{','\\',',',
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

	CONSOLE_CURSOR_INFO lpCursor{};
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


void ProducePlastic1(int ind) {
	srand(time(NULL)); 
	SwimGapPosition[ind] = 3 + rand() % 14;
}


void drawPlastic1(int ind) {
	if (PlasticFlag[ind] == true) {  
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "=======";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap1; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "=======";
		}
	}
}


void erasePlastic1(int ind) {
	if (PlasticFlag[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "       ";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap1; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "       ";
		}
	}
}




void ProducePlastic2(int ind) {
	srand(time(NULL));
	SwimGapPosition[ind] = 3 + rand() % 14;
}


void drawPlastic2(int ind) {
	if (PlasticFlag[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "===================================";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap2; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "====================================";
		}
	}
}


void erasePlastic2(int ind) {
	if (PlasticFlag[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "                                   ";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap2; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "                                    ";
		}
	}
}




void ProducePlastic3(int ind) {
	srand(time(NULL));
	SwimGapPosition[ind] = 3 + rand() % 14;
}


void drawPlastic3(int ind) {
	if (PlasticFlag[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "===================================";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap3; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "====================================";
		}
	}
}


void erasePlastic3(int ind) {
	if (PlasticFlag[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "                                   ";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap3; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "                                    ";
		}
	}
}










void drawFish1() {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + FishPosition); cout << Fish1[i][j];
		}
	}
}


void eraseFish1() {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + FishPosition); cout << " ";
		}
	}
}

void drawFish2() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(j + 2, i + FishPosition); cout << Fish2[i][j];
		}
	}
}


void eraseFish2() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(j + 2, i + FishPosition); cout << " ";
		}
	}
}





int collision1() {
	if (PlasticPosition[0] >= 61) {
		if (FishPosition < SwimGapPosition[0] || FishPosition > SwimGapPosition[0] + SizeOfSwimGap1) {
			_getch();
			return 1;
		}
	}
	return 0;
}

int collision2() {
	if (PlasticPosition[0] >= 61) {
		if (FishPosition < SwimGapPosition[0] || FishPosition > SwimGapPosition[0] + SizeOfSwimGap2) {
			_getch();
			return 1;
		}
	}
	return 0;
}

int collision3() {
	if (PlasticPosition[0] >= 61) {
		if (FishPosition < SwimGapPosition[0] || FishPosition > SwimGapPosition[0] + SizeOfSwimGap3) {
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
	cout << "\n\n\n\n\t\tPlastic is reducing fish numbers.\n\n\n\n";
	srand(time(NULL));
	int choice = std::rand() % 10;
	switch (choice) {
	case 0:
		cout << "\t\tThe Fish was Swallowed Up by Plastic in the Ocean.\n";
		break;
	case 1:
		cout << "\t\tKilled by Plastic..... AGAIN!\n";
		break;
	case 2:
		cout << "\t\tYou are an adult, don't litter.\n";
		break;
	case 3:
		cout << "\t\tFour R's, my friend: Reduce, reuse, recycle, Rihanna.\n";
		break;
	case 4:
		cout << "\t\tNo no no, think you throw away your litter.\n";
		break;
	case 5:
		cout << "\t\tSWALLOWED UP BY PLASTIC.\n";
		break;
	case 6:
		cout << "\t\tEnd the take, make, waste economy. Think CIRCULARITY\nSingle use plastic is a BIG no no.";
		break;
	case 7:
		cout << "\t\tCarpe dayum!\n";
		break;
	case 8:
		cout << "\t\tWhat can YOU do to stop plastic entering the oceans\n";
		break;
	case 9:
		cout << "\t\tBe the change you want to SEA in the world.\n";
		break;
	default:
		cout << "\t\tThe time to ACT is NOW.\n";
		break;
	}
	cout << "\n\n\n\t\tPress any key to go back to menu.";
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


void playGame1() {

	FishPosition = 6;
	Scoreboard = 0;
	PlasticFlag[0] = 1;
	PlasticFlag[1] = 0;
	PlasticPosition[0] = PlasticPosition[1] = 4;

	system("cls");
	drawBorder();
	ProducePlastic1(0);
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

		drawFish1();
		drawPlastic1(0);
		drawPlastic1(1);
		if (collision1() == 1) {
			Game_Over();
			return;
		}
		Sleep(100);

		eraseFish1();
		erasePlastic1(0);
		erasePlastic1(1);
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
			ProducePlastic1(1);
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


void playGame2() {

	FishPosition = 6; 
	Scoreboard = 0;   
	PlasticFlag[0] = 1;
	PlasticFlag[1] = 0;
	PlasticPosition[0] = PlasticPosition[1] = 4;

	system("cls"); 
	drawBorder();
	ProducePlastic2(0);
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

		drawFish2();
		drawPlastic2(0);
		drawPlastic2(1);
		if (collision2() == 1) {
			Game_Over();
			return;
		}
		Sleep(100); 
		
		eraseFish2();
		erasePlastic2(0);
		erasePlastic2(1);
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
			ProducePlastic2(1);
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


void playGame3() {

	FishPosition = 6;
	Scoreboard = 0;
	PlasticFlag[0] = 1;
	PlasticFlag[1] = 0;
	PlasticPosition[0] = PlasticPosition[1] = 4;

	system("cls");
	drawBorder();
	ProducePlastic3(0);
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

		drawFish2();
		drawPlastic3(0);
		drawPlastic3(1);
		if (collision3() == 1) {
			Game_Over();
			return;
		}
		Sleep(100);
		
		eraseFish2();
		erasePlastic3(0);
		erasePlastic3(1);
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
			ProducePlastic3(1);
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


void LevelSelect() {
	system("cls");
	gotoxy(10, 5); cout << "                              ";
	gotoxy(10, 6); cout << "Choose your level.";
	gotoxy(10, 9); cout << "\n----------------";
	gotoxy(10, 10); cout << "\n1.   Level 1. The Ocean as it was in 1900";
	gotoxy(10, 11); cout << "\n2.   Level 2. The Ocean as it was in 1970.";
	gotoxy(10, 12); cout << "\n3.   Level 3. The Plastic Ocean as it is today.\n\n";
	gotoxy(10, 14); cout << "\n4.   Back to Main Menu";
	char levelSelect = _getch();
	if (levelSelect == '1') playGame1();
	else if (levelSelect == '2') playGame2();
	else if (levelSelect == '3') playGame3();
	//else if (levelSelect == '4') MainMenu();
}


void MainMenu() {

	system("cls");
	gotoxy(10, 5); cout << "                              ";
	gotoxy(10, 6); cout << "   Fish in a Plastic Ocean    ";
	gotoxy(10, 7); cout << "                              ";
	gotoxy(10, 9); cout << "1. Start Game";
	gotoxy(10, 10); cout << "2. User Information";
	gotoxy(10, 11); cout << "3. Quit";
	gotoxy(10, 13); cout << "Pick your selection: ";
	char op = _getch();

	if (op == '1') LevelSelect();
	else if (op == '2') User_Information();
	else if (op == '3') exit(0);

}






int main()
{
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	
	do {
		MainMenu();
	} while (1);


	return 0;
}



