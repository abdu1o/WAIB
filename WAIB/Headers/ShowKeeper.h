#include "Global.h"
#include "Enums.h"

void ShowKeeper()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD doneArt{};
	doneArt.X = 2;
	doneArt.Y = 1;

	COORD art{};
	art.X;
	art.Y;

	for (art.Y = doneArt.Y; art.Y < doneArt.Y + 10; art.Y++)
	{
		for (art.X = doneArt.X; art.X < doneArt.X + 16; art.X++)
		{
			//hair
			if (art.Y == doneArt.Y && art.X > doneArt.X + 1 && art.X < doneArt.X + 13
				|| art.Y == doneArt.Y + 1 && art.X > doneArt.X && art.X < doneArt.X + 5
				|| art.Y == doneArt.Y + 1 && art.X > doneArt.X + 11 && art.X < doneArt.X + 14
				|| art.Y == doneArt.Y + 2 && art.X > doneArt.X - 1 && art.X < doneArt.X + 4
				|| art.Y == doneArt.Y + 2 && art.X > doneArt.X + 12 && art.X < doneArt.X + 15
				|| art.Y == doneArt.Y + 3 && art.X > doneArt.X && art.X < doneArt.X + 3
				|| art.Y == doneArt.Y + 3 && art.X == doneArt.X + 14
				|| art.Y == doneArt.Y + 4 && art.X > doneArt.X && art.X < doneArt.X + 4
				|| art.Y == doneArt.Y + 4 && art.X == doneArt.X + 14
				|| art.Y == doneArt.Y + 5 && art.X > doneArt.X + 1 && art.X < doneArt.X + 4
				|| art.Y == doneArt.Y + 5 && art.X > doneArt.X + 12 && art.X < doneArt.X + 15
				|| art.Y == doneArt.Y + 6 && art.X > doneArt.X + 1 && art.X < doneArt.X + 5
				|| art.Y == doneArt.Y + 6 && art.X > doneArt.X + 11 && art.X < doneArt.X + 14
				|| art.Y == doneArt.Y + 7 && art.X > doneArt.X + 2 && art.X < doneArt.X + 6
				|| art.Y == doneArt.Y + 7 && art.X == doneArt.X + 12
				|| art.Y == doneArt.Y + 8 && art.X > doneArt.X + 4 && art.X < doneArt.X + 7
				|| art.Y == doneArt.Y + 9 && art.X == doneArt.X + 6)
			{
				SetConsoleTextAttribute(h, 8);
			}
			//skin
			else if (art.Y == doneArt.Y + 1 && art.X > doneArt.X + 4 && art.X < doneArt.X + 12
				|| art.Y == doneArt.Y + 2 && art.X > doneArt.X + 3 && art.X < doneArt.X + 6
				|| art.Y == doneArt.Y + 2 && art.X > doneArt.X + 7 && art.X < doneArt.X + 10
				|| art.Y == doneArt.Y + 2 && art.X == doneArt.X + 12
				|| art.Y == doneArt.Y + 3 && art.X > doneArt.X + 2 && art.X < doneArt.X + 6
				|| art.Y == doneArt.Y + 3 && art.X > doneArt.X + 7 && art.X < doneArt.X + 10
				|| art.Y == doneArt.Y + 3 && art.X > doneArt.X + 11 && art.X < doneArt.X + 14
				|| art.Y == doneArt.Y + 4 && art.X > doneArt.X + 3 && art.X < doneArt.X + 14
				|| art.Y == doneArt.Y + 5 && art.X > doneArt.X + 3 && art.X < doneArt.X + 8
				|| art.Y == doneArt.Y + 5 && art.X > doneArt.X + 10 && art.X < doneArt.X + 14
				|| art.Y == doneArt.Y + 6 && art.X > doneArt.X + 6 && art.X < doneArt.X + 13)
			{
				SetConsoleTextAttribute(h, 14);
			}
			//eyes (white part)
			else if (art.Y == doneArt.Y + 2 && art.X > doneArt.X + 5 && art.X < doneArt.X + 9
				|| art.Y == doneArt.Y + 2 && art.X > doneArt.X + 9 && art.X < doneArt.X + 13)
			{
				SetConsoleTextAttribute(h, 15);
			}
			//eyes (pupil lightblue)
			else if (art.Y == doneArt.Y + 3 && art.X == doneArt.X + 6
				|| art.Y == doneArt.Y + 3 && art.X == doneArt.X + 10)
			{
				SetConsoleTextAttribute(h, 11);
			}
			//eyes (pupil darkblue)
			else if (art.Y == doneArt.Y + 3 && art.X == doneArt.X + 7
				|| art.Y == doneArt.Y + 3 && art.X == doneArt.X + 11)
			{
				SetConsoleTextAttribute(h, 1);
			}
			//lips
			else if (art.Y == doneArt.Y + 5 && art.X > doneArt.X + 7 && art.X < doneArt.X + 12)
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