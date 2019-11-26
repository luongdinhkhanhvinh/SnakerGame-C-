#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>

enum Color
{
	Black, DarkBlue, DarkGreen, DarkCyan, DarkRed, DarkPink, DarkYellow, DarkWhite, Grey, Blue, Green, Cyan, Red, Pink, Yellow, White
};
enum DirectionKey
{
	KeyUp = 1072,
	KeyDown = 1080,
	KeyLeft = 1075,
	KeyRight = 1077,
	KeyNone = -1
};

int inputKey();
void clrscr();
void gotoXY(int x, int y);
int whereX();
int whereY();
void noCursorType();
void setTextColor(Color color);
void setTitle(char *title);
void resizeCsl(int width, int height);