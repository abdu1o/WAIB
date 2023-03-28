#include "Headers/Global.h"
#include "Headers/GameManager.h"
#include "Headers/ShowKeeper.h"

int main()
{
    system("title WAIB");
    
	MoveWindow(GetConsoleWindow(), 150, 50, 1500, 1000, true);

	CONSOLE_FONT_INFOEX font;

	font.cbSize = sizeof(font);
	font.dwFontSize.Y = 60;
	font.FontFamily = FF_MODERN;
	font.FontWeight = FW_DEMIBOLD;

	wcscpy_s(font.FaceName, 9, L"Pica");
	SetCurrentConsoleFontEx(h, 0, &font);

	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(h, &cursor);

	Start();
}
