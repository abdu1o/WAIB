#include "Global.h"

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("title WAIB");
    
	MoveWindow(GetConsoleWindow(), 220, 80, 800, 550, true);

	CONSOLE_FONT_INFOEX font;

	font.cbSize = sizeof(font);
	font.dwFontSize.Y = 30;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;

	wcscpy_s(font.FaceName, 9, L"Algerian");
	SetCurrentConsoleFontEx(h, 0, &font);

	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(h, &cursor);
}
