#include<iostream> // Enables reading and writing of standard input.
#include <windows.h> // Enables GetStdHandle(STD_OUTPU_HANDLE) for the console to write across.
#include<dos.h> // Enables functions for managing interrupts, sound, time, and dates.
#include<stdlib.h> // Enables srand() and cursor positioning functionality.
#include <stdio.h> // Enables print formatted colour functionality.
#include<conio.h> // Enables _kbhit(void); and _getch(); 
using namespace std;

#define WIDTH_OF_CONSOLE 90  //predefined console width
#define HEIGHT_OF_CONSOLE 26  //predefined console height
#define WIDTH_OF_CONSOLE 70  //predefined console width
#define SizeOfSwimGap1 10  //obstacle gap for level 1 i.e. game difficulty.
#define SizeOfSwimGap2 6  //obstacle gap for level 2
#define SizeOfSwimGap3 4  //obstacle gap for level 3
int AttemptCount = 0; //number of games played counter
int HighScore1 = 0;  //high score variable for level 1
int HighScore2 = 0;  //high score variable for level 2
int HighScore3 = 0;  //high score variable for level 3
int FishPosition = 6;  //initial posistion of character
int Scoreboard1 = 0;  //current score variable for level 1
int Scoreboard2 = 0;  //current score variable for level 2
int Scoreboard3 = 0;  //current score variable for level 3
int PlasticPosition[3];  //initial obstacle posistion
int SwimGapPosition[3];  //initial swim gap posistion
int PlasticFlag1[7];  //  obstacle posistion
int PlasticFlag2[7];  //  obstacle posistion
int PlasticFlag3[7];  //  obstacle posistion

// Setting Cursor Position to change the coordinates the text outputs to on the cmd.
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //obtains handle for console window.
// This gets a handle for use to write to the console. 
// Obtain a handle to the console screen buffer. 
// To specify the new position of the cursor that we will set.
// SetConsoleCursorPosition then uses that handle and the coordinates specified to place the blinking cursor in your command prompt.
COORD PositioningOfCursor;  //x and y coording structure for console

// Enumerated Colour Attributes
enum ColorAttribute
{
	caNORMAL = 0,
	caBOLD = 1,
	caUNDERLINE = 4,
	caBLINKING = 5,
	caREVERSED = 7,
	caCONCEALED = 8
};
// Enumerated Foreground Colours
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
// Enumerated Background Colours
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
// Function to designate the console with the requested highlight and text colours and text style (Mead's Notes, 2023).
void setcolors(int foreground, int background, int attribute)
{
	printf("\033[%i;%i;%im", attribute, foreground, background);
}
// Function for resetting that colour palette initially selected for the console.
void resetcolors(void)
{
	printf("\033[0m");
}
// Print-formatted-colour function.
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
// The INFO() function code set out below creates a white font and blue background.
void INFO(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printfc(fgYELLOW, bgLIGHTBLUE, caNORMAL, format, args);
	va_end(args);
}
// The PLASTIC_COLOUR function creates a grey backgound to a emboldened font, designed for the plastic obstacles.
void PLASTIC_COLOUR(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printfc(fgGRAY, bgGREY, caBOLD, format, args);
	va_end(args);
}
// The GAME_OVER_COLOUR function creates a print-formatted colour that blinks yellow to a black background.
void GAME_OVER_COLOUR(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printfc(fgYELLOW, bgBLACK, caBLINKING, format, args);
	va_end(args);
}

char Fish1[1][6] = { '>','<','{','{','"','>', };  //fish character 1 for level 1 and 2
char Fish2[2][9] = { 'D',';','-','-','{','{','{','\\',',',
					'D','"','_','_','{','{','{','/','"' };  //fish character 2 for level 2 and 3


/*
The gotoxy() function places the cursor at the desired location on the screen.
	This means it is possible to change the cursor location on the screen using the gotoxy() function.
	It is basically used to print text wherever the cursor is moved.*/
void gotoxy(int x, int y)
{
	PositioningOfCursor.X = x;  //initial console x posistion // Filling members of the COORD CursorPosition Struct
	PositioningOfCursor.Y = y;  //initial console y posistion
	SetConsoleCursorPosition(console, PositioningOfCursor); // Set cursor posiion based on the standard handle and cursor position Struct.
} //function to set the initial x and y positions within the console

void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20; //Enlarges the cursor to become invisible.
	// Should it be set to (0,0) in main, the cursor will disappear and sizing would be 20, and invisible.
	// Note: DWORD is enabled by <windows.h>. Although unsigned int only works for certain platforms given that Integers may be 16/32/64 bits.
	// Whereas, DWORD specifies gives itself its own size, a double word. I.e. twice a 16 bit word so 32 bits, enabled across any platform.
	CONSOLE_CURSOR_INFO lpCursor{};
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
} //sets the cursor (initial posistion on the console window) to a size of 20 if its equal to 0 and makes it visible)

void drawBorder() {

	for (int i = 0; i < WIDTH_OF_CONSOLE; i++) {
		gotoxy(i, 0); cout << "=";
		gotoxy(i, HEIGHT_OF_CONSOLE); cout << "=";
	}  //draws game boarder
	for (int i = 0; i < HEIGHT_OF_CONSOLE; i++) {
		gotoxy(0, i); cout << "=";
		gotoxy(WIDTH_OF_CONSOLE, i); cout << "=";
	}//draws game boarder
	for (int i = 0; i < HEIGHT_OF_CONSOLE; i++) {
		gotoxy(WIDTH_OF_CONSOLE, i); cout << "=";
	}//draws game boarder
}  //function to produce the game boarder using equal signs

//  Function to define the random vertical positioning of gap between columns.  
void ProducePlastic(int ind) {
	srand(time(NULL));
	SwimGapPosition[ind] = 3 + rand() % 14;
}  //function randomises the height of the obstacles from the floor and ceiling but keeps the swimgaps consistance depending on the level selected.

// This function draws the height of the plastic columns for the width of the window.
void drawPlastic1(int ind) {
	if (PlasticFlag1[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("=======");
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap1; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("=======");
		}
	}
}  //function to 'draw' the obstacles for level 1
void drawPlastic2(int ind) {
	if (PlasticFlag2[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("============");
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap2; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("============");
		}
	}
}  //function to 'draw' the obstacles for level 2

void drawPlastic3(int ind) {
	if (PlasticFlag3[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("================");
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap3; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); PLASTIC_COLOUR("================");
		}
	}
}  //function to 'draw' the obstacles for level 3


void erasePlastic1(int ind) {
	if (PlasticFlag1[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "       ";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap1; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "       ";
		}
	}
}  //function to remove the obstacles in level 1
void erasePlastic2(int ind) {
	if (PlasticFlag2[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "              ";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap2; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "              ";
		}
	}
}  //function to remove the obstacles in level 2
void erasePlastic3(int ind) {
	if (PlasticFlag3[ind] == true) {
		for (int i = 0; i < SwimGapPosition[ind]; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "                ";
		}
		for (int i = SwimGapPosition[ind] + SizeOfSwimGap3; i < HEIGHT_OF_CONSOLE - 1; i++) {
			gotoxy(WIDTH_OF_CONSOLE - PlasticPosition[ind], i + 1); cout << "                ";
		}
	}
}  //function to remove the obstacles in level 3

void drawFish1() {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + FishPosition); cout << Fish1[i][j];
		}
	}
}  //function to 'draw' the character in level 1 and 2 at initial x and y posistion
void drawFish3() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(j + 2, i + FishPosition); cout << Fish2[i][j];
		}
	}
}  //function to draw the character in level 3 at initial x and y position

void eraseFish1() {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + FishPosition); cout << " ";
		}
	}
}  //function to remove the character in level 1 and 2
void eraseFish3() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(j + 2, i + FishPosition); cout << " ";
		}
	}
}  //function to remove the character in level 3


// Function generates a game pause (until button press) when the fish collides with plastic.
int collision1() {
	if (PlasticPosition[0] >= 61) {
		if (FishPosition < SwimGapPosition[0] || FishPosition > SwimGapPosition[0] + SizeOfSwimGap1) {
			_getch(); //any keyboard input
			return 1;
		}
	}
	return 0;
}  //function detecting collision in level 1
int collision2() {
	if (PlasticPosition[0] >= 61) {
		if (FishPosition < SwimGapPosition[0] || FishPosition > SwimGapPosition[0] + SizeOfSwimGap2) {
			_getch();
			return 1;
		}
	}
	return 0;
}  //function detecting collision in level 2
int collision3() {
	if (PlasticPosition[0] >= 61) {
		if (FishPosition < SwimGapPosition[0] || FishPosition > SwimGapPosition[0] + SizeOfSwimGap3) {
			_getch();  //any keyboard input
			return 1;
		}
	}
	return 0;
}  //function detecting collision in level 1

// Set Game Over screen by clearing screen, setting statements, and ending function upon key press.
void Game_Over() {
	system("cls");  //clears the console window to prevent overlapping
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
	switch (choice) { // Random generated home message for the player when the fish collides with the plastic.
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
	AttemptCount++;
	_getch();  //any keyboard input

}  //function that display a game over screen when the character collides with the ceiling, base or obstacles 

void UpdateScoreboard1() {
	gotoxy(WIDTH_OF_CONSOLE + 7, 5); cout << "Score: " << Scoreboard1 << endl;
	gotoxy(WIDTH_OF_CONSOLE + 7, 7); cout << "Attempts: " << AttemptCount << endl;
	gotoxy(WIDTH_OF_CONSOLE + 7, 9); cout << "High Score: " << HighScore1 << endl;
}  //scoreboard display for level 1
void UpdateScoreboard2() {
	gotoxy(WIDTH_OF_CONSOLE + 7, 5); cout << "Score: " << Scoreboard2 << endl;
	gotoxy(WIDTH_OF_CONSOLE + 7, 7); cout << "Attempts: " << AttemptCount << endl;
	gotoxy(WIDTH_OF_CONSOLE + 7, 9); cout << "High Score: " << HighScore2 << endl;
}  //scoreboard counter for level 2
void UpdateScoreboard3() {
	gotoxy(WIDTH_OF_CONSOLE + 7, 5); cout << "Score: " << Scoreboard1 << endl;
	gotoxy(WIDTH_OF_CONSOLE + 7, 7); cout << "Attempts: " << AttemptCount << endl;
	gotoxy(WIDTH_OF_CONSOLE + 7, 9); cout << "High Score: " << HighScore2 << endl;
}  //scoreboard counter for level 3


// Set User Information screen by clearing screen, setting statements, and ending function upon key press.
void User_Information() {
	system("cls"); // system(“cls”) to make the screen/terminal clear.
	cout << "User_Information";
	cout << "\n----------------";
	cout << "\nSadly there is plenty of plastic polluting the oceans.";
	cout << "\nSpacebar triggers the Fish to swim upwards to escape the plastic mountains.";
	cout << "\n\nFor the Main Menu, Tap a Button";
	_getch();
}  //user information screen when keyboard input 2 is pressed on the main menu

void playGame1() {

	FishPosition = 6;
	Scoreboard1 = 0;
	PlasticFlag1[0] = 1;
	PlasticFlag1[1] = 0;
	PlasticPosition[0] = PlasticPosition[1] = 4;

	system("cls");
	drawBorder();
	ProducePlastic(0);
	UpdateScoreboard1();

	// Fixed instruction window on right of screen.
	gotoxy(WIDTH_OF_CONSOLE + 3, 2); cout << "Plastic Ocean";
	gotoxy(WIDTH_OF_CONSOLE + 6, 3); cout << "   Fish";
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
		}  //if statement which detects if spacebar is pressed to increase the fishes height else decrease

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

		// If statements to iterate the plastic along and restart once meets the left of the screen.
		if (PlasticFlag1[0] == 1)
			PlasticPosition[0] += 2;

		if (PlasticFlag1[1] == 1)
			PlasticPosition[1] += 2;

		if (PlasticPosition[0] >= 40 && PlasticPosition[0] < 42) {
			PlasticFlag1[1] = 1;
			PlasticPosition[1] = 4;
			ProducePlastic(1);
		}
		if (PlasticPosition[0] > 68) {
			Scoreboard1++;
			UpdateScoreboard1();
			PlasticFlag1[1] = 0;
			PlasticPosition[0] = PlasticPosition[1];
			SwimGapPosition[0] = SwimGapPosition[1];
		}
		if (Scoreboard1 >= HighScore1) {
			HighScore1 = Scoreboard1;
		}
	}

}  //function that plays level 1
void playGame2() {

	FishPosition = 6;
	Scoreboard2 = 0;
	PlasticFlag2[0] = 1;
	PlasticFlag2[1] = 0;
	PlasticPosition[0] = PlasticPosition[1] = 4;

	system("cls");
	drawBorder();
	ProducePlastic(0);
	UpdateScoreboard2();

	gotoxy(WIDTH_OF_CONSOLE + 3, 2); cout << "Plastic Ocean";
	gotoxy(WIDTH_OF_CONSOLE + 6, 3); cout << "   Fish";
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
			ProducePlastic(1);
		}
		if (PlasticPosition[0] > 68) {
			Scoreboard2++;
			UpdateScoreboard2();
			PlasticFlag2[1] = 0;
			PlasticPosition[0] = PlasticPosition[1];
			SwimGapPosition[0] = SwimGapPosition[1];
		}
		if (Scoreboard2 >= HighScore2) {
			HighScore2 = Scoreboard2;
		}
	}

}  //function that plays level 2
void playGame3() {

	FishPosition = 6;
	Scoreboard3 = 0;
	PlasticFlag3[0] = 1;
	PlasticFlag3[1] = 0;
	PlasticPosition[0] = PlasticPosition[1] = 4;

	system("cls");
	drawBorder();
	ProducePlastic(0);
	UpdateScoreboard3();

	gotoxy(WIDTH_OF_CONSOLE + 3, 2); cout << "Plastic Ocean";
	gotoxy(WIDTH_OF_CONSOLE + 6, 3); cout << "   Fish";
	gotoxy(WIDTH_OF_CONSOLE + 6, 6); cout << "             ";
	gotoxy(WIDTH_OF_CONSOLE + 7, 12); cout << "          ";
	gotoxy(WIDTH_OF_CONSOLE + 7, 13); cout << "         ";
	gotoxy(WIDTH_OF_CONSOLE + 2, 14); cout << "  Spacebar = swim";
	gotoxy(10, 5); cout << "Press a button to Start Game";
	_getch();
	gotoxy(10, 5); cout << "                      ";

	while (1) { // Method for providing an infinite loop that will be interrupted from within its code block.

		if (_kbhit()) { // _kbhit function monitors the console for a keyboard presses
			char spacebar = _getch(); // _getch  takes that keyboard press and as in this case is inserted and held by a char
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
			ProducePlastic(1);
		}
		if (PlasticPosition[0] > 68) {
			Scoreboard3++;
			UpdateScoreboard3();
			PlasticFlag3[1] = 0;
			PlasticPosition[0] = PlasticPosition[1];
			SwimGapPosition[0] = SwimGapPosition[1];
		}
		if (Scoreboard3 >= HighScore3) {
			HighScore3 = Scoreboard3;
		}


	}

}  //function that plays level 3

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
}  //level select screen when keyboard input 1 is pressed at the main menu

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

}  //main menu screen that allows the player to progress to the level select, user information screen or to quit the application

int main()
{
	// Sets background colour to blue to mimic ocean.
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
}  //when application is run the initial colours are assigned and the main menu function is run allowing the user to progress and play the game
