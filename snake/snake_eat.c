//snake_eat.c
//snake
//
//Created by Zehao HE on 18-12-6
//Copyright(c)
//
#include<stdio.h>
#include <stdlib.h> 
#include <time.h> 

#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define WALL_CELL '*'
#define SNAKE_MAX_LENGTH 20
#define SNAKE_FOOD '$'

//return 1 is over, return 0 is not over
int isGameOver(int snakeCoordinate[][2], int snakeLength);
//dy:0(stop),1(down),-1(up);dx:0(stop),1(right),-1(left)
void snakeMove(int snakeCoordinate[][2], char map[12][12], int *snakeLength_ptr, int foodCoordinate[2], int dx, int dy);
//output the map
void printMap(char map[][12]);
//set the map
void setMap(int snakeCoordinate[][2], char map[12][12], int *snakeLength_ptr, int foodCoordinate[2]);
//creat food
void creatFood(int snakeCoordinate[][2], int *snakeLength_ptr, int foodCoordinate[2]);
//judge if the snake eats food
int eatfood(int snakeCoordinate[][2], int *snakeLength_ptr, int foodCoordinate[2], int dx, int dy);
//get random integer 1 <= x <= 10
int randomNum(void);
//outs when gameover
void gameover(int snakeLength);

int main() {
	char direction;
	char map[12][12] = {
		"************",
		"*XXXXH     *",
		"*          *",
		"*          *",
		"*          *",
		"*     $    *",
		"*          *",
		"*          *",
		"*          *",
		"*          *",
		"*          *",
		"************",
	};
	int snakeCoordinate[SNAKE_MAX_LENGTH][2] = { {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1} }, snakeLength = 5;//the snakeCoordinate[snakeLength - 1] is the head of the snake
	int foodCoordinate[2] = { 6, 5 };
	
	printMap(map);

	while (!isGameOver(snakeCoordinate, snakeLength)) {
		scanf("%c", &direction);

		switch (direction) {
		case 'A':snakeMove(snakeCoordinate, map, &snakeLength, foodCoordinate, -1, 0); break;
		case 'D':snakeMove(snakeCoordinate, map, &snakeLength, foodCoordinate, 1, 0); break;
		case 'W':snakeMove(snakeCoordinate, map, &snakeLength, foodCoordinate, 0, -1); break;
		case 'S':snakeMove(snakeCoordinate, map, &snakeLength, foodCoordinate, 0, 1); break;
		default: continue;
		}

		printMap(map);
	}

	gameover(snakeLength);

	return 0;
}

void gameover(int snakeLength) {
	if (snakeLength >= SNAKE_MAX_LENGTH) {
		printf("You win");
	}
	else {
		printf("Gameover\n");
	}
}

int isGameOver(int snakeCoordinate[][2], int snakeLength) {
	//hit the wall
	if (snakeCoordinate[snakeLength - 1][0] == 0 || snakeCoordinate[snakeLength - 1][0] == 11 || snakeCoordinate[snakeLength - 1][1] == 0 || snakeCoordinate[snakeLength - 1][1] == 11)
		return 1;

	//eat itself
	for (int i = 0; i < snakeLength - 1; i++) {
		if (snakeCoordinate[i][0] == snakeCoordinate[snakeLength - 1][0] && snakeCoordinate[i][1] == snakeCoordinate[snakeLength - 1][1])
			return 1;
	}

	//too long
	if (snakeLength >= SNAKE_MAX_LENGTH)
		return 1;

	return 0;
}

void snakeMove(int snakeCoordinate[][2], char map[12][12], int *snakeLength_ptr ,int foodCoordinate[2], int dx, int dy) {
	if (!eatfood(snakeCoordinate, snakeLength_ptr, foodCoordinate, dx, dy)) {
		for (int i = 0; i < *snakeLength_ptr - 1; i++) {
			snakeCoordinate[i][0] = snakeCoordinate[i + 1][0];
			snakeCoordinate[i][1] = snakeCoordinate[i + 1][1];
		}

		snakeCoordinate[*snakeLength_ptr - 1][0] += dx;
		snakeCoordinate[*snakeLength_ptr - 1][1] += dy;
	}

	setMap(snakeCoordinate, map, snakeLength_ptr, foodCoordinate);
}

int eatfood(int snakeCoordinate[][2], int *snakeLength_ptr, int foodCoordinate[2], int dx, int dy) {
	if (snakeCoordinate[*snakeLength_ptr - 1][0] + dx == foodCoordinate[0] && snakeCoordinate[*snakeLength_ptr - 1][1] + dy == foodCoordinate[1]) {
		(*snakeLength_ptr)++;
		snakeCoordinate[*snakeLength_ptr - 1][0] = foodCoordinate[0];
		snakeCoordinate[*snakeLength_ptr - 1][1] = foodCoordinate[1];
		creatFood(snakeCoordinate, snakeLength_ptr, foodCoordinate);
		return 1;
	}

	return 0;
}

void creatFood(int snakeCoordinate[][2], int *snakeLength_ptr, int foodCoordinate[2]) {
	int flag = 0;

	do {
		foodCoordinate[0] = randomNum();
		foodCoordinate[1] = randomNum();
		for (int i = 0; i < *snakeLength_ptr; i++) {
			if (snakeCoordinate[i][0] == foodCoordinate[0] && snakeCoordinate[i][1] == foodCoordinate[1]) {
				flag = 1;
				break;
			}
			else {
				flag = 0;
			}
		}
	} while (flag);
}

void setMap(int snakeCoordinate[][2], char map[12][12], int *snakeLength_ptr, int foodCoordinate[2]) {
	// clear the map
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			map[i][j] = BLANK_CELL;
		}
	}

	//set the snake
	for (int i = 0; i < *snakeLength_ptr - 1; i++) {
		map[snakeCoordinate[i][1]][snakeCoordinate[i][0]] = SNAKE_BODY;
	}

	map[snakeCoordinate[*snakeLength_ptr - 1][1]][snakeCoordinate[*snakeLength_ptr - 1][0]] = SNAKE_HEAD;

	//set food
	map[foodCoordinate[1]][foodCoordinate[0]] = SNAKE_FOOD;
}

void printMap(char map[][12]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			printf("%c", map[i][j]);
		}

		printf("\n");
	}
}

int randomNum(void) {
	srand((unsigned)time(NULL));
	return ((int)rand() % 10 + 1);
}