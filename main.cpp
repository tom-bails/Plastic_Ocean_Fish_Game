#include<iostream> 
#include <windows.h> 
#include<dos.h>
#include<stdlib.h> 
#include <stdio.h>
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




/////////// Colours ///////////////////
enum ColorAttribute
{
	caNORMAL = 0,
	caBOLD = 1,
	caUNDERLINE = 4,
	caBLINKING = 5,
	caREVERSED = 7,
	caCONCEALED = 8
};
enum ForegroundColor
{
	fgBLACK = 30,
	fgRED = 31,
	fgGREEN = 32,
	fgORANGE = 33,
	fgBLUE = 34,
	fgPURPLE = 35,
	fgCYAN = 36,
	fgGREY = 37,
	fgGRAY = 37,
	fgDARKGREY = 90,
	fgDARKGRAY = 90,
	fgLIGHTRED = 91,
	fgLIGHTGREEN = 92,
	fgYELLOW = 93,
	fgLIGHTBLUE = 94,
	fgLIGHTPURPLE = 95,
	fgTURQUOISE = 96
};
enum BackgroundColor
{
	bgBLACK = 40,
	bgRED = 41,
	bgGREEN = 42,
	bgORANGE = 43,
	bgBLUE = 44,
	bgPURPLE = 45,
	bgCYAN = 46,
	bgGREY = 47,
	bgGRAY = 47,
	bgDARKGREY = 100,
	bgDARKGRAY = 100,
	bgLIGHTRED = 101,
	bgLIGHTGREEN = 102,
	bgYELLOW = 103,
	bgLIGHTBLUE = 104,
	bgLIGHTPURPLE = 105,
	bgTURQUOISE = 106
};
void setcolors(int foreground, int background, int attribute)
{
	printf("\033[%i;%i;%im", attribute, foreground, background);
}
void resetcolors(void)
{
	printf("\033[0m");
}
int printfc(int fg, int bg, int attr, const char* format, ...)
{
	int count;    /* characters printed (like printf) */
	va_list args; /* list of args from ...            */

	va_start(args, format);        /* find args         */
	setcolors(fg, bg, attr);       /* change the colors */
	count = vprintf(format, args); /* do the printing   */
	va_end(args);                  /* done              */

	resetcolors();                 /* reset the colors         */
	printf("\n");                  /* should the user do this? */
	return count;                  /* mimic printf             */
}

void INFO(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printfc(fgYELLOW, bgLIGHTBLUE, caNORMAL, format, args);
	va_end(args);
}
void PLASTIC_COLOUR(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printfc(fgGRAY, bgGREY, caBOLD, format, args);
	va_end(args);
}
void GAME_OVER_COLOUR(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printfc(fgYELLOW, bgBLACK, caBLINKING, format, args);
	va_end(args);
}

/*
int main(void)
{
  int code = 7560; // To demonstrate variadic function

INFO("The weather today is going to be cold and clear.");
PLASTIC_COLOUR("The mountains may get up to a foot of snow by 8 pm.");
GAME_OVER_COLOUR("Unable to contact the weather station. (ERR:C%i)", code);

return 0;
}
*/


/////////////////////////





char Fish1[1][6] = { '>','<','{','{','"','>', };

char Fish2[2][9] = { 'D',';','-','-','{','{','{','\\',',',
					'D','"','_','_','{','{','{','/','"' };


int FishPosition = 6; 
int Scoreboard = 0;   
int PlasticPosition[3];
int SwimGapPosition[3];
int PlasticFlag1[7];
int PlasticFlag2[7];
int PlasticFlag3[7];

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
	if (PlasticFlag1[ind] == true) {  
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("=======");
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap1; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("=======");
		}
	}
}


void erasePlastic1(int ind) {
	if (PlasticFlag1[ind] == true) {
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
	if (PlasticFlag2[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("===================================");
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap2; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("====================================");
		}
	}
}


void erasePlastic2(int ind) {
	if (PlasticFlag2[ind] == true) {
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
	if (PlasticFlag3[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("===================================");
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap3; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("====================================");
		}
	}
}


void erasePlastic3(int ind) {
	if (PlasticFlag3[ind] == true) {
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

void drawFish3() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(j + 2, i + FishPosition); cout << Fish2[i][j];
		}
	}
}


void eraseFish3() {
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
	cout << "\t\t";
	GAME_OVER_COLOUR("______   GAME   ___________");
	cout << "\t\t";
	GAME_OVER_COLOUR("________   OVER   _________");
	cout << "\t\t"; 
	GAME_OVER_COLOUR("___________________________\n\n");
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
		cout << "\t\tEnd the take, make, waste economy. Think CIRCULARITY\n\t\tSingle use plastic is a BIG no no.";
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
	PlasticFlag1[0] = 1;
	PlasticFlag1[1] = 0;
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_INTENSITY |
			BACKGROUND_BLUE
		);
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


		if (PlasticFlag1[0] == 1)
			PlasticPosition[0] += 2;

		if (PlasticFlag1[1] == 1)
			PlasticPosition[1] += 2;

		if (PlasticPosition[0] >= 40 && PlasticPosition[0] < 42) {
			PlasticFlag1[1] = 1;
			PlasticPosition[1] = 4;
			ProducePlastic1(1);
		}
		if (PlasticPosition[0] > 68) {
			Scoreboard++;
			UpdateScoreboard();
			PlasticFlag1[1] = 0;
			PlasticPosition[0] = PlasticPosition[1];
			SwimGapPosition[0] = SwimGapPosition[1];
		}

	}

}


void playGame2() {

	FishPosition = 6; 
	Scoreboard = 0;   
	PlasticFlag2[0] = 1;
	PlasticFlag2[1] = 0;
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

		drawFish1();
		drawPlastic2(0);
		drawPlastic2(1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_INTENSITY |
			BACKGROUND_BLUE
		);
		if (collision2() == 1) {
			Game_Over();
			return;
		}
		Sleep(100); 
		
		eraseFish1();
		erasePlastic2(0);
		erasePlastic2(1);
		FishPosition += 1;

		if (FishPosition > HEIGHT_OF_CONSOLE - 3) {  
			Game_Over();
			return;
		}


		if (PlasticFlag2[0] == 1)
			PlasticPosition[0] += 2;
		if (PlasticFlag2[1] == 1)
			PlasticPosition[1] += 2;
		if (PlasticPosition[0] >= 40 && PlasticPosition[0] < 42) {
			PlasticFlag2[1] = 1;
			PlasticPosition[1] = 4;
			ProducePlastic2(1);
		}
		if (PlasticPosition[0] > 68) {
			Scoreboard++;
			UpdateScoreboard();
			PlasticFlag2[1] = 0;
			PlasticPosition[0] = PlasticPosition[1];
			SwimGapPosition[0] = SwimGapPosition[1];
		}

	}

}


void playGame3() {

	FishPosition = 6;
	Scoreboard = 0;
	PlasticFlag3[0] = 1;
	PlasticFlag3[1] = 0;
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

		drawFish3();
		drawPlastic3(0);
		drawPlastic3(1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_INTENSITY |
			BACKGROUND_BLUE
		);
		if (collision3() == 1) {
			Game_Over();
			return;
		}
		Sleep(100);
		
		eraseFish3();
		erasePlastic3(0);
		erasePlastic3(1);
		FishPosition += 1;

		if (FishPosition > HEIGHT_OF_CONSOLE - 3) {
			Game_Over();
			return;
		}


		if (PlasticFlag3[0] == 1)
			PlasticPosition[0] += 2;

		if (PlasticFlag3[1] == 1)
			PlasticPosition[1] += 2;

		if (PlasticPosition[0] >= 40 && PlasticPosition[0] < 42) {
			PlasticFlag3[1] = 1;
			PlasticPosition[1] = 4;
			ProducePlastic3(1);
		}
		if (PlasticPosition[0] > 68) {
			Scoreboard++;
			UpdateScoreboard();
			PlasticFlag3[1] = 0;
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY |
		BACKGROUND_BLUE
	); 
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	
	do {
		MainMenu();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_INTENSITY |
			BACKGROUND_BLUE
		);
	} while (1);


	return 0;
}



