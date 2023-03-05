#pragma once
#include "Global.h"

class Move
{
private:
	char emoji;
	COORD Cursor;

public:
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	Move(char _emoji, COORD _Cursor, int x, int y) // êîíñòðóêòîð 
	{
		this->emoji = _emoji;
		this->Cursor = _Cursor;
		Cursor.X = x;
		Cursor.Y = y;
	}

	void SetPosition()
	{
		SetConsoleCursorPosition(h, Cursor);
	}

	void SetColor(int attribute)
	{
		SetConsoleTextAttribute(h, attribute);
	}

	void PrintEmoji()
	{
		cout << emoji;
	}

	void MoveUp()
	{
		Cursor.Y--;
	}
	void MoveDown()
	{
		Cursor.Y++;
	}
	void MoveRight()
	{
		Cursor.X++;
	}
	void MoveLeft()
	{
		Cursor.X++;
	}
};