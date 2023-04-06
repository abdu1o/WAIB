#include "Global.h"
#include "Menu.h"
#include "ConsoleSetter.h"
#include "WordKeeper.h"
#include "Level.h"

DWORD WINAPI Music_Menu(void* param)
{
	PlaySoundA("WAIB/Music/menu.WAV", NULL, SND_LOOP | SND_ASYNC);
	return 0;
}

void Start()
{
	CreateThread(0, 0, Music_Menu, 0, 0, 0);

	Menu menu;
	menu.Show();

	//personal console window settings for each computer
	//change by needed

	ConsoleSet(40, 1600, 1100);
	//40 - font size
	//1600 - window width
	//920 - window height

	LevelMap map;
	map.Show();

	ConsoleSet(35, 1600, 920);

	/*phrases spoken by Keeper
	(need to optimize)*/
	vector<string> txt;
	switch (map.GetLevelTrigger())
	{
		case 1://on the LevelMap selected the first level
		{
			WordKeeper keeper;
			keeper.Show();

			txt.push_back("Welcome home traveler!");
			txt.push_back("or not home...");
			txt.push_back("I am the Word Keeper,");
			txt.push_back("and I am here to help you");
			txt.push_back("get out of this terrible place.");
			txt.push_back("First, try to use your gift of thinking");

			keeper.Say(txt, 3, 3);
			//txt - phrase to say
			//3 - cord X for start txt 
			//2 - cord Y for start txt
		}
		case 3:
		{

		}
		case 4:
		{

		}
		case 5:
		{

		}
		case 6:
		{

		}
		case 7:
		{

		}
		case 8:
		{

		}
		case 9:
		{

		}
	}
}