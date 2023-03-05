#pragma once
#include "Headers/Global.h"

class Move
{
private:
	char emoji;
	COORD Cursor;

public:
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	Move(char _emoji, COORD _Cursor, int x, int y); // êîíñòðóêòîð 


	void SetPosition(); // óñòàíîâêà êóðñîðà

	void SetColor(int attribute); // óñòàíîâêà öâåòà 

	void PrintEmoji(); // âûâîä ýìîäæè â êîíñîëü 


	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
};