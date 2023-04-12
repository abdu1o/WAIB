#pragma once
//!!VERY BIG ERROR!!
//!!IN ENUMS!!
//!!DO NOT USE NUMBERS FROM 0 TO 25 
//FOR DEFINING LEVEL ELEMENTS (borders, corners...)!!

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
	BORDER_UP_DOWN = 205,
	BORDER_LEFT_RIGHT = 186,
	CORNER_01 = 201,
	CORNER_02 = 187,
	CORNER_03 = 188,
	CORNER_04 = 200,
	EMPTY = 255
};

enum Door
{
	DOOR = 51,
	_DOOR = 177
};

enum Static_Alphabet
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

enum Move_Alphabet
{
	_A,
	_B,
	_C,
	_D,
	_E,
	_F,
	_G,
	_H,
	_I,
	_J,
	_K,
	_L,
	_M,
	_N,
	_O,
	_P,
	_Q,
	_R,
	_S,
	_T,
	_U,
	_V,
	_W,
	_X,
	_Y,
	_Z
};

enum LevelBox
{
	LEVEL_BORDER_UP_DOWN = 301,
	LEVEL_BORDER_LEFT_RIGHT = 302,
	LEVEL_CORNER_01 = 303,
	LEVEL_CORNER_02 = 304,
	LEVEL_CORNER_03 = 305,
	LEVEL_CORNER_04 = 306,
	LEVEL_LETTER_FIELD = 249
};

enum MenuWords { PLAY = 31, CREATORS = 32, EXIT = 33 }; // words protect 

enum LevelNum { First = 101, Second = 102, Third = 103, Fourth = 104, Fifth = 105, Sixth = 106, Seventh = 107, Eighth = 108, Ninth = 109 };