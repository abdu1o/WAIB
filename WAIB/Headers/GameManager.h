#include "Global.h"
#include "Menu.h"
#include "ConsoleSetter.h"
#include "WordKeeper.h"
#include "LevelMap.h"
#include "Level1.h"
#include "Level2.h"

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
	menu.~Menu();

	//personal console window settings for each computer
	//change by needed

	ConsoleSet(40, 1600, 1100);
	//40 - font size
	//1600 - window width
	//920 - window height

	LevelMap map;
	WordKeeper keeper;

	while (true)
	{
		map.Show();

		vector<string> txt;
		switch (map.GetLevelTrigger())
		{
		case 1://on the LevelMap selected the first level
		{
			ConsoleSet(35, 1600, 920);
			keeper.Show();
			txt.clear();

			txt.push_back("Welcome home traveler!");
			txt.push_back("or not home...");
			txt.push_back("I am the Word Keeper,");
			txt.push_back("and I am here to help you");
			txt.push_back("get out of this terrible place.");
			txt.push_back("First, try to use your gift of thinking");

			keeper.Say(txt, 3, 3);
			////txt - phrase to say
			////3 - cord X for start txt 
			////3 - cord Y for start txt

			Level1 obj;
			obj.Show();
			obj.~Level1();
			ConsoleSet(40, 1600, 1100); 
			map.nextlevel = true;
			break;
		}

		case 2:
		{
			ConsoleSet(35, 1600, 920);
			keeper.Show();
			txt.clear();

			txt.push_back("Oh! I see that all is not lost with you");
			txt.push_back("Although it was too easy...");
			txt.push_back("for the experimental children                      ");
			txt.push_back("Anyway, try to come up with something new this time");

			keeper.Say(txt, 3, 3);

			Level2 obj;
			obj.Show();
			obj.~Level2();
			ConsoleSet(40, 1600, 1100);
			map.nextlevel = false;
			break;
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
		map.Clear();
	}

}
