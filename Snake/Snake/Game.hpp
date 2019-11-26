#pragma once
#include "Console.hpp"
#include <ctime>
#include <iostream>
using namespace std;

#define TOP_WALL 2
#define BOT_WALL 22
#define LEFT_WALL 19
#define RIGHT_WALL 69
//
#define HEAD_SNAKE 2
#define BODY_SNAKE 15
#define FOOD 3

enum Direction
{
	Up, Down, Left, Right
};

struct Position
{
	int x, y;
};
typedef Position Food;

struct Snake
{
	Position* position;
	int size;
};

bool operator==(Position positionLeft, Position positionRight);
//
Snake initialSnake(int size, Direction direction);
Food initialFood();
Position nodeEnd(Snake snake);
//
void pollEvent(Direction &direction);
void drawWall();
void drawSnake(Snake snake);
void drawFood(Food food);
void eraseNode(Position node);
void displayScore(int score);
void move(Snake &snake, Direction direction);
void actionEatFood(Snake &snake);
void actionDie();
void run();
//s
bool isErrorFood(Snake snake, Food food);
bool isEatFood(Snake snake, Food food);
bool isDie(Snake snake);
