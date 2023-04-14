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
	EMPTY = 255,
	FAKE_EMPTY
};

enum Door
{
	DOOR = 999,
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
	_A, _A1, _A2,
	_B, _B1, _B2,
	_C, _C1, _C_2, // "_C_2" (_C2) - define error
	_D, _D1, _D2,
	_E, _E1, _E2,
	_F, _F1, _F2,
	_G, _G1, _G2,
	_H, _H1, _H2,
	_I, _I1, _I2,
	_J, _J1, _J2,
	_K, _K1, _K2,
	_L, _L1, _L2,
	_M, _M1, _M2,
	_N, _N1, _N2,
	_O, _O1, _O2,
	_P, _P1, _P2,
	_Q, _Q1, _Q2,
	_R, _R1, _R2,
	_S, _S1, _S2,
	_T, _T1, _T2,
	_U, _U1, _U2,
	_V, _V1, _V2,
	_W, _W1, _W2,
	_X, _X1, _X2,
	_Y, _Y1, _Y2,
	_Z,	_Z1, _Z2,
	KEY, KEY1, _KEY = 20
};

enum LevelBox
{
	LEVEL_BORDER_UP_DOWN = 301,
	LEVEL_BORDER_LEFT_RIGHT = 302,
	LEVEL_CORNER_01 = 303,
	LEVEL_CORNER_02 = 304,
	LEVEL_CORNER_03 = 305,
	LEVEL_CORNER_04 = 306,
	LEVEL_LETTER_FIELD = 249,

	CAR = 212,
};

enum MenuWords { PLAY = 31, CREATORS = 32, EXIT = 33 }; // words protect 

enum LevelNum { First = 101, Second = 102, Third = 103, Fourth = 104, Fifth = 105, Sixth = 106, Seventh = 107, Eighth = 108, Ninth = 109 };