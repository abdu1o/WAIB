#include "Headers/Move.h"

Move::Move(char _emoji, COORD _Cursor, int x, int y) // êîíñòðóêòîð 
{
	this->emoji = _emoji;
	this->Cursor = _Cursor;
	Cursor.X = x;
	Cursor.Y = y;

}

void Move::SetPosition() // óñòàíîâêà êóðñîðà
{
	SetConsoleCursorPosition(h, Cursor);
}

void Move::SetColor(int attribute) // óñòàíîâêà öâåòà 
{
	SetConsoleTextAttribute(h, attribute);
}

void Move::PrintEmoji()  // âûâîä ýìîäæè â êîíñîëü 
{
	cout << emoji;
}


void Move::MoveUp()
{
	Cursor.Y--;
}

void Move::MoveDown()
{
	Cursor.Y++;
}

void Move::MoveRight()
{
	Cursor.X++;
}

void Move::MoveLeft()
{
	Cursor.X++;
}