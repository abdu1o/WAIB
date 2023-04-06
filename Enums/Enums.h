#pragma once
enum Color
{
	BLACK = 0,
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

enum Door
{
	DOOR = 51,
	_DOOR = 177
};


enum Alphabet
{
	A = 'A',
	B = 'B',
	C = 'C',
	D = 'D',
	E = 'E',
	F = 'F',
	G = 'G',
	H = 'H',
	I = 'I',
	J = 'J',
	K = 'K',
	L = 'L',
	M = 'M',
	N = 'N',
	O = 'O',
	P = 'P',
	Q = 'Q',
	R = 'R',
	S = 'S',
	T = 'T',
	U = 'U',
	V = 'V',
	W = 'W',
	X = 'X',
	Y = 'Y',
	Z = 'Z',
};

enum LevelBox
{
	LEVEL_BORDER_UP_DOWN = 301,
	LEVEL_BORDER_LEFT_RIGHT = 302,
	LEVEL_CORNER_01 = 303,
	LEVEL_CORNER_02 = 304,
	LEVEL_CORNER_03 = 305,
	LEVEL_CORNER_04 = 306,

};

enum MenuWords { PLAY = 31, CREATORS = 32, EXIT = 33 }; // words protect 