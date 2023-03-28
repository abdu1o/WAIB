#include "Global.h"
#include "Menu.h"
#include "Level.h"

DWORD WINAPI Music_Menu(void* param)
{
	PlaySoundA("WAIB/Music/menu.WAV", NULL, SND_LOOP | SND_ASYNC);
	return 0;
}

void GameManager() 
{
	CreateThread(0, 0, Music_Menu, 0, 0, 0);

	Menu menu;
	menu.Show();

	LevelMap map;
	map.Show();
}