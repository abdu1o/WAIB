#include "Headers/Global.h"
#include "Headers/GameManager.h"

int main()
{
    system("title WAIB");
    
	ConsoleSet(60, 1600, 950);
	//60 - font size
	//1600 - window width
	//950 - window height

	wcscpy_s(font.FaceName, 9, L"Pica");

	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(h, &cursor);
	WordTriggers::level_color = DARKYELLOW;
	Start();
}
