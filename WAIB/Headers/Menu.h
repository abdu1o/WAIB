#include "Headers/Global.h"
#include "Enums/Enums.h"

class Menu 
{

private:

    static const int WIDTH = 40;
    static const int HEIGHT = 11;
    int menu_box[HEIGHT][WIDTH] = {};
    HANDLE h;

public:

    Menu() 
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD menu;
        menu.X = 17;
        menu.Y = 3;


        for (int y = 0; y < HEIGHT; y++) 
        {
            for (int x = 0; x < WIDTH; x++) 
            {
                
                //Play
                if (y == menu.Y && x == menu.X)
                {
                    menu_box[y][x] = MenuLetters::P; 
                }
                else if (y == menu.Y && x == menu.X + 2)
                {
                    menu_box[y][x] = 7;
                }

                //Author
                else if (y == menu.Y + 2 && x == menu.X)
                {
                    menu_box[y][x] = MenuLetters::C;
                }
                else if (y == menu.Y + 2 && x == menu.X + 2)
                {
                    menu_box[y][x] = 8;
                }

                //Exit
                else if (y == menu.Y + 4 && x == menu.X)
                {
                    menu_box[y][x] = MenuLetters::E;
                }
                else if (y == menu.Y + 4 && x == menu.X + 2)
                {
                    menu_box[y][x] = 9;
                }


                //BORDERS=============================================================================
                else if (y == 1 && x >= 14 && x <= 28 || y == 10 && x >= 14 && x <= 28)
                {
                    menu_box[y][x] = 1; // up and down borders
                }
                else if (y >= 2 && x == 13 && y <= 9 
                    || y == 2 && x == 29 || y == 3 && x == 27 || y == 4 && x == 29 || y == 5 && x == 23 || y == 6 && x == 29 || y == 7 && x == 27 || y == 8 && x == 29 || y == 9 && x == 29) //29, 9
                {
                    menu_box[y][x] = 2; // left and right borders
                }
                else if (y == 1 && x == 13)
                {
                    menu_box[y][x] = 3; // corner 1
                }
                else if (y == 1 && x == 29)
                {
                    menu_box[y][x] = 4; // corner 2
                }
                else if (y == 10 && x == 29)
                {
                    menu_box[y][x] = 5; // corner 3
                }
                else if (y == 10 && x == 13)
                {
                    menu_box[y][x] = 6; // corner 4
                }
                //====================================================================================

                else 
                {
                    menu_box[y][x] = 0; // nihuya
                }
            }
        }
    }

    void Show() 
    {
        for (int y = 0; y < HEIGHT; y++) 
        {
            for (int x = 0; x < WIDTH; x++) 
            {
                switch (menu_box[y][x])
                {
                case 0: // nihuya
                    cout << " ";
                    break;

                case 1: // up and down borders
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)205;
                    break;

                case 2: // left and right borders
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)186;
                    break;

                case 3: // corner 1
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)201;
                    break;

                case 4: // corner 2
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)187;
                    break;

                case 5: // corner 3
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)188;
                    break;

                case 6: // corner 4
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)200;
                    break;

                case MenuLetters::P: 
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "P";
                    break;
                case 7:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "LAY";
                    break;

                case MenuLetters::C:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "C";
                    break;
                case 8:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "REATORS";
                    break;

                case MenuLetters::E:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "E";
                    break;
                case 9:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "XIT";
                    break;
                }
            }
            cout << "\n";
        }
        cout << "\n";

        COORD position; // player coord
        position.X = 15;
        position.Y = 3;
        SetConsoleCursorPosition(h, position);
        SetConsoleTextAttribute(h, Color::BLUE);
        cout << (char)2;

        //for future movement
        while (true)
        {

        }
    }
};