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

	ConsoleSet(40, 1600, 920); 
	//40 - font size
	//1600 - window width
	//920 - window height

	// its for tests, show keeper AFTER level choice
	WordKeeper keeper;
	keeper.Show();
	
	/*phrases spoken by Keeper
	(need to optimize)*/
	vector<string> phrase;
	phrase.push_back("Welcome home traveler!");
	phrase.push_back("or not home...");
	phrase.push_back("I am the Word Keeper,");
	phrase.push_back("and I am here to help you");
	phrase.push_back("get out of this terrible place.");
	phrase.push_back("First, try to use your gift of thinking");
	
	keeper.Say(phrase, 3, 2);
	//txt - phrase to say
	//3 - cord X for start txt 
	//2 - cord Y for start txt 

	LevelMap map;
	map.Show();
}