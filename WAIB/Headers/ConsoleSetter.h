#include "Global.h"

//console settings (font size + window size)
void ConsoleSet(int font_size, int wind_width, int wind_height)
{
	font.cbSize = sizeof(font);
	font.dwFontSize.Y = font_size;
	font.FontFamily = FF_MODERN;
	font.FontWeight = FW_DEMIBOLD;

	SetCurrentConsoleFontEx(h, 0, &font);
	
	MoveWindow(GetConsoleWindow(), 150, 50, wind_width, wind_height, true);
}