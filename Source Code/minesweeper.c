// A C++ Program to Implement and Play Minesweeper 
// without taking input from user 

//#include<bits/stdc++.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<time.h> 
#include<string.h> 
#include<stdbool.h>

//using namespace std; 

#define BEGINNER 0 
#define INTERMEDIATE 1 
#define ADVANCED 2 
#define MAXSIDE 25 
#define MAXMINES 99 
#define MOVESIZE 526 // (25 * 25 - 99) 
extern int validation();
int remain=10;
int SIDE ; // side length of the board 
int MINES ; // number of mines on the board
bool flag;
int fl[9][9] ={0};


void ck(int *hh, int *mm, int *ss)
{
	time_t s, val = 1; 
	struct tm* current_time; 
	int timse;
	// time in seconds 
	s = time(NULL); 

	// to get current time 
	current_time = localtime(&s); 

	// print time in minutes, 
	// hours and seconds 
	*hh=current_time->tm_hour;
	*mm=current_time->tm_min;
	*ss=current_time->tm_sec;
} 

// A Utility Function to check whether given cell (row, col) 
// is a valid cell or not 
bool isValid(int row, int col) 
{ 
	// Returns true if row number and column number 
	// is in range 
	return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE); 
} 

// A Utility Function to check whether given cell (row, col) 
// has a mine or not. 
bool isMine (int row, int col, char board[][MAXSIDE]) 
{ 
	if (board[row][col] == '*') 
		return (true); 
	else
		return (false); 
} 

// A Function to get the user's move and print it 
// All the moves are assumed to be distinct and valid. 
void makeMove (int *x, int *y, int moves[][2], int currentMoveIndex) 
{ 	
	*x = moves[currentMoveIndex][0]; 
	*y = moves[currentMoveIndex][1]; 

	printf ("\nMy move is (%d, %d)\n", *x, *y); 

	/* 
	// The above moves are pre-defined 
	// If you want to make your own move 
	// then uncomment this section and comment 
	// the above section 
	*/

	return; 
} 

// A Function to randomly assign moves 
void assignMoves (int moves[][2], int movesLeft) 
{ 
	bool mark[MAXSIDE*MAXSIDE]; 

	memset(mark, false, sizeof(mark)); 

	// Continue until all moves are assigned. 
	for (int i=0; i<movesLeft; ) 
	{ 
		int random = rand() % (SIDE*SIDE); 
		int x,y;
		scanf("%d %d",&x,&y); 

		// Add the mine if no mine is placed at this 
		// position on the board 
		if (mark[random] == false) 
		{ 
			// Row Index of the Mine 
			moves[i][0]= x; 
			// Column Index of the Mine 
			moves[i][1] = y; 

			mark[random] = true; 
			i++; 
		} 
	} 

	return; 
} 

// A Function to print the current gameplay board 
void printBoard(char myBoard[][MAXSIDE]) 
{ 
	int i,j; ;
	printf("Remaining mines: %d\n\n",remain);
	printf ("     "); 

	for (i=0; i<SIDE; i++) 
		printf ("%d   ", i+1); 

	printf ("\n\n"); 

	for (i=0; i<SIDE; i++) 
	{ 
		if(i<10) printf(" ");
		printf ("%c   ", (i+65)); 
		for (j=0; j<SIDE; j++) 
		{
			if(fl[i][j]==1)
				printf("+   ");
			else
				printf ("%c   ", myBoard[i][j]);
			if(j>9)
				printf(" ");
		}
		printf ("\n"); 
	} 
	return; 
} 

// A Function to count the number of 
// mines in the adjacent cells 
int countAdjacentMines(int row ,int col ,int mines[][2], char realBoard[][MAXSIDE]) 
{ 
	int i; 
	int count = 0; 

	/* 
	Count all the mines in the 8 adjacent 
	cells 

	N.W    N       N.E 
	\      |       / 
	 \     |      / 
	 W----Cell----E 
	 /     |      \ 
	/      |       \ 
	S.W   S      S.E 
 
	Cell-->Current Cell (row, col) 
	N -->  North        (row-1, col) 
	S -->  South        (row+1, col) 
	E -->  East         (row, col+1) 
	W -->  West            (row, col-1) 
	N.E--> North-East   (row-1, col+1) 
	N.W--> North-West   (row-1, col-1) 
	S.E--> South-East   (row+1, col+1) 
	S.W--> South-West   (row+1, col-1) 
	*/

	//----------- 1st Neighbour (North) ------------ 

	// Only process this cell if this is a valid one 
	if (isValid (row-1, col) == true) 
	{ 
		if (isMine (row-1, col, realBoard) == true) 
		count++; 
	} 

	//----------- 2nd Neighbour (South) ------------ 

	// Only process this cell if this is a valid one 
	if (isValid (row+1, col) == true) 
	{ 
		if (isMine (row+1, col, realBoard) == true) 
		count++; 
	} 

	//----------- 3rd Neighbour (East) ------------ 

	// Only process this cell if this is a valid one 
	if (isValid (row, col+1) == true) 
	{ 
		if (isMine (row, col+1, realBoard) == true) 
		count++; 
	} 

	//----------- 4th Neighbour (West) ------------ 

	// Only process this cell if this is a valid one 
	if (isValid (row, col-1) == true) 
	{ 
		if (isMine (row, col-1, realBoard) == true) 
		count++; 
	} 

	//----------- 5th Neighbour (North-East) ------------ 

	// Only process this cell if this is a valid one 
	if (isValid (row-1, col+1) == true) 
	{ 
		if (isMine (row-1, col+1, realBoard) == true) 
		count++; 
	} 

	//----------- 6th Neighbour (North-West) ------------ 

	// Only process this cell if this is a valid one 
	if (isValid (row-1, col-1) == true) 
	{ 
		if (isMine (row-1, col-1, realBoard) == true) 
		count++; 
	} 

	//----------- 7th Neighbour (South-East) ------------ 

	// Only process this cell if this is a valid one 
	if (isValid (row+1, col+1) == true) 
	{ 
		if (isMine (row+1, col+1, realBoard) == true) 
		count++; 
	} 

	//----------- 8th Neighbour (South-West) ------------ 

	// Only process this cell if this is a valid one 
	if (isValid (row+1, col-1) == true) 
	{ 
		if (isMine (row+1, col-1, realBoard) == true) 
		count++; 
	} 

	return (count); 
} 

// A Recursive Fucntion to play the Minesweeper Game 
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], 
int mines[][2], int row, int col, int *movesLeft) 
{ 

	// Base Case of Recursion 
	if (myBoard[row][col]!='-') 
		return (false); 

	int i, j; 

	// You opened a mine 
	// You are going to lose 
	if (realBoard[row][col] == '*') 
	{ 
		myBoard[row][col]='*'; 

		for (i=0; i<MINES; i++) 
			myBoard[mines[i][0]][mines[i][1]]='*'; 

		printBoard (myBoard); 
		printf ("\nGame Over. You hit a mine.\n");
		flag = false;
		return (true) ; 
	} 

	else
	{ 

		// Calculate the number of adjacent mines and put it 
		// on the board. 
		int count = countAdjacentMines(row, col, mines, realBoard); 
		(*movesLeft)--; 

		myBoard[row][col] = count + '0'; 

		if (!count) 
		{ 
			/* 
			Recur for all 8 adjacent cells 

			N.W   N   N.E 
			\   |   / 
			\  |  / 
			W----Cell----E 
			/ | \ 
			/   |  \ 
			S.W    S   S.E 

			Cell-->Current Cell (row, col) 
			N -->  North        (row-1, col) 
			S -->  South        (row+1, col) 
			E -->  East         (row, col+1) 
			W -->  West            (row, col-1) 
			N.E--> North-East   (row-1, col+1) 
			N.W--> North-West   (row-1, col-1) 
			S.E--> South-East   (row+1, col+1) 
			S.W--> South-West   (row+1, col-1) 
			*/

			//----------- 1st Neighbour (North) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row-1, col) == true) 
			{ 
				if (isMine (row-1, col, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft); 
			} 

			//----------- 2nd Neighbour (South) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row+1, col) == true) 
			{ 
				if (isMine (row+1, col, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft); 
			} 

			//----------- 3rd Neighbour (East) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row, col+1) == true) 
			{ 
				if (isMine (row, col+1, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft); 
			} 

			//----------- 4th Neighbour (West) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row, col-1) == true) 
			{ 
				if (isMine (row, col-1, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft); 
			} 

			//----------- 5th Neighbour (North-East) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row-1, col+1) == true) 
			{ 
				if (isMine (row-1, col+1, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft); 
			} 

			//----------- 6th Neighbour (North-West) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row-1, col-1) == true) 
			{ 
				if (isMine (row-1, col-1, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft); 
			} 

			//----------- 7th Neighbour (South-East) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row+1, col+1) == true) 
			{ 
				if (isMine (row+1, col+1, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft); 
			} 

			//----------- 8th Neighbour (South-West) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row+1, col-1) == true) 
			{ 
				if (isMine (row+1, col-1, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft); 
			} 
		} 

		return (false); 
	} 
} 

// A Function to place the mines randomly 
// on the board 
void placeMines(int mines[][2], char realBoard[][MAXSIDE]) 
{ 
	bool mark[MAXSIDE*MAXSIDE]; 

	memset (mark, false, sizeof (mark)); 

	// Continue until all random mines have been created. 
	for (int i=0; i<MINES; ) 
	{ 
		int random = rand() % (SIDE*SIDE); 
		int x = random / SIDE; 
		int y = random % SIDE; 

		// Add the mine if no mine is placed at this 
		// position on the board 
		if (mark[random] == false) 
		{ 
			// Row Index of the Mine 
			mines[i][0]= x; 
			// Column Index of the Mine 
			mines[i][1] = y; 

			// Place the mine 
			realBoard[mines[i][0]][mines[i][1]] = '*'; 
			mark[random] = true; 
			i++; 
		} 
	} 

	return; 
} 

// A Function to initialise the game 
void initialise (char realBoard[][MAXSIDE], char myBoard[][MAXSIDE]) 
{ 
	// Initiate the random number generator so that 
	// the same configuration doesn't arises 
	srand (time (NULL)); 

	// Assign all the cells as mine-free 
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
		{ 
			myBoard[i][j] = realBoard[i][j] = '-'; 
		} 
	} 

	return; 
} 

// A Function to cheat by revealing where the mines are 
// placed. 
void cheatMinesweeper (char realBoard[][MAXSIDE]) 
{ 
	printf ("The mines locations are-\n"); 
	printBoard (realBoard); 
	return; 
} 

// A function to replace the mine from (row, col) and put 
// it to a vacant space 
void replaceMine (int row, int col, char board[][MAXSIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
		{ 
			// Find the first location in the board 
			// which is not having a mine and put a mine 
			// there. 
			if (board[i][j] != '*') 
			{ 
				board[i][j] = '*'; 
				board[row][col] = '-'; 
				return; 
			} 
		} 
	} 
	return; 
} 

// A Function to play Minesweeper game 
void playMinesweeper () 
{ 
	// Initially the game is not over 
	bool gameOver = false; 

	// Actual Board and My Board 
	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE]; 

	int movesLeft = SIDE * SIDE - MINES, x, y; 
	int mines[MAXMINES][2]; // Stores (x, y) coordinates of all mines. 
	int moves[MOVESIZE][2]; // Stores (x, y) coordinates of the moves 

	// Initialise the Game 
	initialise (realBoard, myBoard); 

	// Place the Mines randomly 
	placeMines (mines, realBoard); 

	// Assign Moves 
	// If you want to make your own input move, 
	// then the below function should be commnented 
	//assignMoves (moves, movesLeft); 

	/* 
	//If you want to cheat and know 
	//where mines are before playing the game 
	//then uncomment this part 

	cheatMinesweeper(realBoard); 
	*/

	// You are in the game until you have not opened a mine 
	// So keep playing 

	int currentMoveIndex = 0;int ii=-1; 
	while (gameOver == false) 
	{ 
		printf ("Current Status of Board : \n"); 
		printBoard (myBoard); 
		char opt;
		printf("\nChoose an option\n<R> Reveal Tile\n<P> Place Flag\n<Q> Quit Game\n\nOption (R,P,Q): ");
		scanf(" %c",&opt);
		if(opt=='R')
		{
			int xx,yy;char one,two;
			printf("Enter tile coordinates: ");
			scanf(" %c %c",&one,&two);
			
			if(one>='A' && one<='I')
				{xx=one-65;yy=two-49;}
			else
				{xx=20;yy=20;}
			if(fl[xx][yy]==0)
			{
				ii++;			
				moves[ii][0]=xx;moves[ii][1]=yy;
			
				makeMove (&x, &y, moves, currentMoveIndex); 

				// This is to guarantee that the first move is 
				// always safe 
				// If it is the first move of the game 
				if (currentMoveIndex == 0) 
				{ 
					// If the first move itself is a mine 
					// then we remove the mine from that location 
					if (isMine (x, y, realBoard) == true) 
					replaceMine (x, y, realBoard); 
				} 

				currentMoveIndex ++; 

				gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft); 

				if (((gameOver == false) && (movesLeft == 0))|| remain==0) 
				{ 
					printBoard (myBoard);  
					printf ("\nCongratulations! You have located all the mines.\nYou won in ");
					flag = true;
					gameOver = true; 
				}
			}
		}
		else
		if(opt=='P')
		{
			int xxx,yyy;char onee,twoo;
			printf("Enter tile coordinates: ");
			scanf(" %c %c",&onee,&twoo);
			if(onee>='A' && onee<='I')
				{xxx=onee-65;yyy=twoo-49;}
			else
				{xxx=20;yyy=20;}
			if(myBoard[xxx][yyy]=='-')
			{
			if (isMine (xxx, yyy, realBoard) == true ) 
				remain-=1;
			else
				printf("\n========================\nNo mine at this location\n========================\n\n");
			fl[xxx][yyy]=1;
			if ( remain==0) 
				{ 
					printBoard (myBoard);  
					printf ("\nCongratulations! You have located all the mines.\nYou won in ");
					flag = true;
					gameOver = true; 
				}
			}
		}
		else
		if(opt=='Q')
		{
			flag = false;
			gameOver = true;
		}
			
	} 

	return; 
} 

void leader()
{
	FILE *f1,*f2;
	char lead[1000][20],scor[20],user[20],r[2];
	int time[1000] = {0};
	int i=0,play[1000] = {0},win[1000]={0}, count = 0;
	f1 = fopen("leaderboard.txt", "r");
	fscanf(f1,"%s",lead[count]);
	if(feof(f1))
		printf("\nThere is no information currently stored in leaderboard. Try again later.\n");
	else
	{
		while(!feof(f1))
		{
			
			fscanf(f1,"%d",&time[count]);
			if(feof(f1))
				break;
			f2 = fopen("score.txt", "r");
		
			while(!feof(f2))
			{
				fscanf(f2,"%s",scor);
				fscanf(f2,"%s",r);
				if(feof(f2))
					break;			
							
				if(strcmp(lead[count],scor)==0)
				{
					play[count]++;
					if(strcmp(r,"1")==0)
						win[count]++;
				}
				//printf("%s %ssecond %d %d\n",lead,time,play,win);
			}
			int test=7-strlen(lead[count]);
			while(test--)
				printf(" ");
			count++;
			fclose(f2);
			fscanf(f1,"%s",lead[count]);
		}
		count = 0;
		int count1, count2;
		for (count1 = 0; count1 < 1000; count1++)
		{
			for (count2 = count1 + 1; count2 < 1000; count2++)
			{
				if (time[count1] < time[count2])
				{
					char temporary[20];
					strcpy(temporary, lead[count1]);
					strcpy(lead[count1], lead[count2]);
					strcpy(lead[count2], temporary);
					int temp = time[count1];
					time[count1] = time[count2];
					time[count2] = temp;
					temp = play[count1];
					play[count1] = play[count2];
					play[count2] = temp;
					temp = win[count1];
					win[count1] = win[count2];
					win[count2] = temp;
				}
				else if (time[count1] == time[count2] && win[count1] > win[count2])
				{
					char temporary[20];
					strcpy(temporary, lead[count1]);
					strcpy(lead[count1], lead[count2]);
					strcpy(lead[count2], temporary);
					int temp = time[count1];
					time[count1] = time[count2];
					time[count2] = temp;
					temp = play[count1];
					play[count1] = play[count2];
					play[count2] = temp;
					temp = win[count1];
					win[count1] = win[count2];
					win[count2] = temp;
				}
			}
		}
		printf("\n");

		for (count1 = 0; count1 < 1000; count1++)
		{
			if (time[count1] != 0)
			{
				printf("%s\t",lead[count1]);
				printf("\t%d seconds \t%d games won, %d games played\n",time[count1],win[count1],play[count1]);
			}
			else
				break;
		}
	}
	fclose(f1);
}

// A Function to choose the difficulty level 
// of the game 
void chooseDifficultyLevel (int level) 
{ 
	/* 
	--> BEGINNER = 9 * 9 Cells and 10 Mines 
	--> INTERMEDIATE = 16 * 16 Cells and 40 Mines 
	--> ADVANCED = 24 * 24 Cells and 99 Mines 
	*/

	if (level == BEGINNER) 
	{ 
		SIDE = 9; 
		MINES = 10; 
	} 

	if (level == INTERMEDIATE) 
	{ 
		SIDE = 16; 
		MINES = 40; 
	} 

	if (level == ADVANCED) 
	{ 
		SIDE = 24; 
		MINES = 99; 
	} 

	return; 
} 

// Driver Program to test above functions 
int start() 
{ 
	/* Choose a level between 
	--> BEGINNER = 9 * 9 Cells and 10 Mines 
	--> INTERMEDIATE = 16 * 16 Cells and 40 Mines 
	--> ADVANCED = 24 * 24 Cells and 99 Mines */

	int ch, lo, ver = 0, choice, why = 0, lol;
	char user[10], pass[20], user1[10], pass1[20], user2[10], seconds[10], sec_string[8], won[10], won_string[9], played[10], played_string[12];
	printf("Welcome to Online minesweeper gaming system\n\nYou are required to enter username and password\nUsername: ");
	scanf("%s", user);
	printf("Password: ");
	scanf("%s", pass);
	FILE *ff2;
	ff2=fopen("auth.txt","w");
	fprintf(ff2,"%s ",user);
	fprintf(ff2,"%s",pass);
	fclose(ff2);	
	int cxx=validation();

	if (cxx==1)
	{
		while(1)
		{
			do
			{
				printf("\n<1> Play Minesweeper\n<2> Show Leaderboard\n<3> Quit\nSelection Option (1-3): ");
				scanf("%d",&ch);
				if(ch==1)
				{
					why=1; 
					break;
				}
				else if(ch==2) 
				{
					why=0;
					leader();
				} 
				else if(ch==3)
					return (0); 
			} while (ch!=1 && ch!=2 && ch!=3); 
			if(why==1)
			{
				chooseDifficultyLevel (BEGINNER); 
				int hh, mm, ss, hh2, mm2, ss2, hh1, mm1, ss1, sec, sec1;
				ck(&hh, &mm, &ss);
				hh1 = hh; mm1 = mm; ss1 = ss;
				playMinesweeper ();
				ck(&hh, &mm, &ss);
				hh2 = hh; mm2 = mm; ss2 = ss;
				sec1 = hh2 * 3600 + mm2 * 60 + ss2;
				sec = hh1 * 3600 + mm1 * 60 + ss1;
				if( flag== true)
					printf("%d seconds.\n", sec1-sec);
				FILE *f1,*f2;
				f1 = fopen("leaderboard.txt", "a");
				f2 = fopen("score.txt", "a");
					
				if (flag)
				{
					fprintf(f1,"%s %d\n",user,sec1-sec);
					fprintf(f2,"%s %d\n",user,1);
				}
				else
				{
					fprintf(f2,"%s %d\n",user,0);
				}
				fclose(f1);
				fclose(f2);
					
			} 
			do
			{
				printf("\nDo You Want To Continue \nPress 1 for Yes and 0 for No: ");
				scanf("%d",&choice);
				if(choice == 0)
					exit(0);
			} while (choice != 0 && choice != 1);
		}
		ver = 1;
	}

	if (ver == 0)
		printf("You have entered either a worng username or password. Disconnecting.. \n");
	return (0); 
}

