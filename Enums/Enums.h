#pragma once
enum Color
{
	BLACKK = 0,
	DARKBLUE = 1,
	DARKGREEN = 2,
	DARKCYAN = 3,
	DARKRED = 4,
	DARKMAGENTA = 5,
	DARKYELLOW = 6,
	GRAY = 7,
	DARKGRAY = 8,
	BLUE = 9,
	GREEN = 10,
	CYAN = 11,
	RED = 12,
	MAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

enum KeyCode
{
	ENTER = 13,
	ESCAPE = 27,
	SPACE = 32,
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80
};


enum Border
{
	BORDER_UP_DOWN = 1,
	BORDER_LEFT_RIGHT = 2,
	CORNER_01 = 3,
	CORNER_02 = 4,
	CORNER_03 = 5,
	CORNER_04 = 6,
	EMPTY = 0,

	//char elements
	_BORDER_UP_DOWN = 205,
	_BORDER_LEFT_RIGHT = 186,
	_CORNER_01 = 201,
	_CORNER_02 = 187,
	_CORNER_03 = 188,
	_CORNER_04 = 200,
	_EMPTY = 255
};



enum MenuLetters { P = 'P', C = 'C', E = 'E' };

enum MenuWords {PLAY = 31, CREATORS = 32, EXIT = 33}; // words protect