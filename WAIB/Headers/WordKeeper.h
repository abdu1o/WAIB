#include "Global.h"
#include "Enums/Enums.h"


class WordKeeper
{
private:
	COORD startArt;

public:

	//start pos for art 
	WordKeeper()
	{
		this->startArt.X = 4;
		this->startArt.Y = 2;
	}

	void Show()
	{

		COORD art;
		art.X;
		art.Y;

		for (art.Y = startArt.Y; art.Y < startArt.Y + 10; art.Y++)
		{
			for (art.X = startArt.X; art.X < startArt.X + 16; art.X++)
			{
				//hair
				if (art.Y == startArt.Y && art.X > startArt.X + 1 && art.X < startArt.X + 13
					|| art.Y == startArt.Y + 1 && art.X > startArt.X && art.X < startArt.X + 5
					|| art.Y == startArt.Y + 1 && art.X > startArt.X + 11 && art.X < startArt.X + 14
					|| art.Y == startArt.Y + 2 && art.X > startArt.X - 1 && art.X < startArt.X + 4
					|| art.Y == startArt.Y + 2 && art.X > startArt.X + 12 && art.X < startArt.X + 15
					|| art.Y == startArt.Y + 3 && art.X > startArt.X && art.X < startArt.X + 3
					|| art.Y == startArt.Y + 3 && art.X == startArt.X + 14
					|| art.Y == startArt.Y + 4 && art.X > startArt.X && art.X < startArt.X + 4
					|| art.Y == startArt.Y + 4 && art.X == startArt.X + 14
					|| art.Y == startArt.Y + 5 && art.X > startArt.X + 1 && art.X < startArt.X + 4
					|| art.Y == startArt.Y + 5 && art.X > startArt.X + 12 && art.X < startArt.X + 15
					|| art.Y == startArt.Y + 6 && art.X > startArt.X + 1 && art.X < startArt.X + 5
					|| art.Y == startArt.Y + 6 && art.X > startArt.X + 11 && art.X < startArt.X + 14
					|| art.Y == startArt.Y + 7 && art.X > startArt.X + 2 && art.X < startArt.X + 6
					|| art.Y == startArt.Y + 7 && art.X == startArt.X + 12
					|| art.Y == startArt.Y + 8 && art.X > startArt.X + 4 && art.X < startArt.X + 7
					|| art.Y == startArt.Y + 9 && art.X == startArt.X + 6)
				{
					SetConsoleTextAttribute(h, 8);
				}
				//skin
				else if (art.Y == startArt.Y + 1 && art.X > startArt.X + 4 && art.X < startArt.X + 12
					|| art.Y == startArt.Y + 2 && art.X > startArt.X + 3 && art.X < startArt.X + 6
					|| art.Y == startArt.Y + 2 && art.X > startArt.X + 7 && art.X < startArt.X + 10
					|| art.Y == startArt.Y + 2 && art.X == startArt.X + 12
					|| art.Y == startArt.Y + 3 && art.X > startArt.X + 2 && art.X < startArt.X + 6
					|| art.Y == startArt.Y + 3 && art.X > startArt.X + 7 && art.X < startArt.X + 10
					|| art.Y == startArt.Y + 3 && art.X > startArt.X + 11 && art.X < startArt.X + 14
					|| art.Y == startArt.Y + 4 && art.X > startArt.X + 3 && art.X < startArt.X + 14
					|| art.Y == startArt.Y + 5 && art.X > startArt.X + 3 && art.X < startArt.X + 8
					|| art.Y == startArt.Y + 5 && art.X > startArt.X + 10 && art.X < startArt.X + 14
					|| art.Y == startArt.Y + 6 && art.X > startArt.X + 6 && art.X < startArt.X + 13)
				{
					SetConsoleTextAttribute(h, 14);
				}
				//eyes (white part)
				else if (art.Y == startArt.Y + 2 && art.X > startArt.X + 5 && art.X < startArt.X + 9
					|| art.Y == startArt.Y + 2 && art.X > startArt.X + 9 && art.X < startArt.X + 13)
				{
					SetConsoleTextAttribute(h, 15);
				}
				//eyes (pupil lightblue)
				else if (art.Y == startArt.Y + 3 && art.X == startArt.X + 6
					|| art.Y == startArt.Y + 3 && art.X == startArt.X + 10)
				{
					SetConsoleTextAttribute(h, 11);
				}
				//eyes (pupil darkblue)
				else if (art.Y == startArt.Y + 3 && art.X == startArt.X + 7
					|| art.Y == startArt.Y + 3 && art.X == startArt.X + 11)
				{
					SetConsoleTextAttribute(h, 1);
				}
				//lips
				else if (art.Y == startArt.Y + 5 && art.X > startArt.X + 7 && art.X < startArt.X + 12)
				{
					SetConsoleTextAttribute(h, 4);
				}

				else
				{
					SetConsoleTextAttribute(h, 0);
				}
				SetConsoleCursorPosition(h, art);
				cout << char(219);
			}
		}
	}

	void Say(vector<string> phrase, int startX, int startY)
	{
		//start pos of first Keeper phrase
		COORD txt;
		txt.X = startX + startArt.X + 16; //right of the keeper
		txt.Y = startY;
		SetConsoleCursorPosition(h, txt);
		SetConsoleTextAttribute(h, Color::DARKYELLOW);

		//keeper talk alghorithm
		for (int i = 0; i < phrase.size(); i++) //iteration string in vector
		{
			for (int j = 0; j < phrase[i].length(); j++) //iteration letters of vector element
			{
				cout << phrase[i][j];
				Sleep(25);
			}
			Sleep(250);
			//transition to new line
			txt.Y++;
			SetConsoleCursorPosition(h, txt);
		}
		txt.Y++;
		SetConsoleCursorPosition(h, txt);
		system("pause");
		system("cls");
	}
};

