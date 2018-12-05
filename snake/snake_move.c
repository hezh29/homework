//snake_move.c
//snake
//
//Created by Zehao HE on 18-12-5
//Copyright(c)
//
#include<stdio.h>

#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define WALL_CELL '*'
#define SNAKE_MAX_LENGTH 20

//return 1 is over, return 0 is not over
int isGameOver(int headCoordinate[]);
//dy:0(stop),1(down),-1(up);dx:0(stop),1(right),-1(left)
void snakeMove(int snakeCoordinate[][2], char map[12][12], int snakeLength, int dx, int dy);
//output the map
void printMap(char map[][12]);
//reset the living space of snake
void clearMap(char map[][12]);

int main() {
	char direction;
	char map[12][12] = {
		"************",
		"*XXXXH     *",
		"*          *",
		"*          *",
		"*          *",
		"*          *",
		"*          *",
		"*          *",
		"*          *",
		"*          *",
		"*          *",
		"************",
	};
	int snakeCoordinate[SNAKE_MAX_LENGTH][2] = { {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1} }, snakeLength = 5;

	printMap(map);

	while (!isGameOver(snakeCoordinate[0])) {
		scanf("%c", &direction);

		switch (direction) {
		case 'A':snakeMove(snakeCoordinate, map, snakeLength, -1, 0); break;
		case 'D':snakeMove(snakeCoordinate, map, snakeLength, 1, 0); break;
		case 'W':snakeMove(snakeCoordinate, map, snakeLength, -1, 0); break;
		case 'S':snakeMove(snakeCoordinate, map, snakeLength, 1, 0); break;
		default: continue;
		}

		printMap(map);
	}

	printf("Gameover\n");
	
	return 0;
}

int isGameOver(int headCoordinate[]) {
	//If the coordinates of the head coincide with those of the wall, return 1
	if (headCoordinate[0] == 0 || headCoordinate[0] == 11 || headCoordinate[1] == 0 || headCoordinate[1] == 11)
		return 1;
	return 0;
}

void snakeMove(int snakeCoordinate[][2], char map[12][12], int snakeLength, int dx, int dy) {
	for (int i = snakeLength - 1; i >= 1; i--) {
		snakeCoordinate[i][0] = snakeCoordinate[i - 1][0];
		snakeCoordinate[i][1] = snakeCoordinate[i - 1][1];
	}

	snakeCoordinate[0][0] += dx;
	snakeCoordinate[0][1] += dy;
	clearMap(map);
	map[snakeCoordinate[0][1]][snakeCoordinate[0][0]] = 'H';

	for (int i = 1; i < snakeLength; i++) {
		map[snakeCoordinate[i][1]][snakeCoordinate[i][0]] = 'X';
	}
}

void clearMap(char map[][12]) {
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			map[i][j] = ' ';
		}
	}
}

void printMap(char map[][12]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			printf("%c", map[i][j]);
		}

		printf("\n");
	}
}