#include "Global.h"
#include "Enums.h"
#include "Move.h"


class LevelMap
{

private:
    static const int WIDTH = 67;
    static const int HEIGHT = 23;

    static const int StartWIDTH = 2;
    static const int StartHEIGHT = 2;

    static const int EndWIDTH = WIDTH - 9;
    static const int EndHEIGHT = HEIGHT - 1;


    int menu_box[HEIGHT][WIDTH] = {};

    HANDLE h;
    COORD menu;

public:

    LevelMap()
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
        this->menu.X = 1;
        this->menu.Y = 1;


        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {

                //BORDERS=============================================================================
                if (y == StartHEIGHT && x == StartWIDTH)
                {
                    menu_box[y][x] = Border::CORNER_01; // corner 1
                }

                else if (y == StartHEIGHT && x == EndWIDTH)
                {
                    menu_box[y][x] = Border::CORNER_02; // corner 2
                }

                else if (y == EndHEIGHT && x == EndWIDTH)
                {
                    menu_box[y][x] = Border::CORNER_03; // corner 3
                }

                else if (y == EndHEIGHT && x == StartWIDTH)
                {
                    menu_box[y][x] = Border::CORNER_04; // corner 4
                }

                else if (y == StartHEIGHT && x >= StartWIDTH && x <= EndWIDTH || y == EndHEIGHT && x >= StartWIDTH && x <= EndWIDTH)
                {
                    menu_box[y][x] = Border::BORDER_UP_DOWN; // up and down borders
                }

                else if (y >= StartHEIGHT && x == StartWIDTH && y <= EndWIDTH || y >= StartHEIGHT && x == EndWIDTH && y <= EndHEIGHT)
                {
                    menu_box[y][x] = Border::BORDER_LEFT_RIGHT; // left and right borders
                }

                //====================================================================================

                else
                {
                    menu_box[y][x] = Border::EMPTY; // nihuya
                }

                int box_Y = 0;
                int box_X = -10;
                int steps = 0;


                for (int i = 0; i < 9; i++)
                {
                    box_X += 18;

                    if (x == EndWIDTH - 10 && y == StartHEIGHT + 7)
                    {
                        menu_box[y][x] = LevelBox::LEVEL_BORDER_LEFT_RIGHT;
                    }

                    if (x == StartWIDTH + 10 && y == StartHEIGHT + 13)
                    {
                        menu_box[y][x] = LevelBox::LEVEL_BORDER_LEFT_RIGHT;
                    }

                    else if (y == StartHEIGHT + 3 + box_Y && x == StartWIDTH + box_X)//3 7
                    {
                        menu_box[y][x] = LevelBox::LEVEL_CORNER_01;
                    }

                    else if (y == StartHEIGHT + 3 + box_Y && x == StartWIDTH + 4 + box_X)//3 7
                    {
                        menu_box[y][x] = LevelBox::LEVEL_CORNER_02;
                    }

                    else if (y == StartHEIGHT + 5 + box_Y && x == StartWIDTH + 4 + box_X)//3 7
                    {
                        menu_box[y][x] = LevelBox::LEVEL_CORNER_03;
                    }

                    else if (y == StartHEIGHT + 5 + box_Y && x == StartWIDTH + box_X)//3 7
                    {
                        menu_box[y][x] = LevelBox::LEVEL_CORNER_04;
                    }

                    else if (y == StartHEIGHT + 4 + box_Y && x == StartWIDTH + 2 + box_X)
                    {
                        menu_box[y][x] = 100 + steps + 1;
                    }

                    steps++;


                    if (steps % 3 == 0)
                    {
                        box_Y += 6;
                        box_X = -10;
                    }


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
                case Border::EMPTY: // nihuya
                    cout << (char)Border::_EMPTY;
                    break;


                case Border::BORDER_UP_DOWN: // up and down borders
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::_BORDER_UP_DOWN;
                    break;


                case Border::BORDER_LEFT_RIGHT: // left and right borders
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::_BORDER_LEFT_RIGHT;
                    break;


                case Border::CORNER_01: // corner 1
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::_CORNER_01;
                    break;


                case Border::CORNER_02: // corner 2
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::_CORNER_02;
                    break;


                case Border::CORNER_03: // corner 3
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::_CORNER_03;
                    break;


                case Border::CORNER_04: // corner 4
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::_CORNER_04;
                    break;

                    // LEVEL =========================================

                case LevelBox::LEVEL_BORDER_LEFT_RIGHT:
                    SetConsoleTextAttribute(h, DARKGRAY);
                    cout << (char)Border::_BORDER_LEFT_RIGHT;
                    break;

                case LevelBox::LEVEL_BORDER_UP_DOWN:
                    SetConsoleTextAttribute(h, DARKGRAY);
                    cout << (char)Border::_BORDER_UP_DOWN;
                    break;

                case LevelBox::LEVEL_CORNER_01:
                    SetConsoleTextAttribute(h, DARKGRAY);
                    cout << (char)Border::_CORNER_01;
                    break;

                case LevelBox::LEVEL_CORNER_02:
                    SetConsoleTextAttribute(h, DARKGRAY);
                    cout << (char)Border::_CORNER_02;
                    break;

                case LevelBox::LEVEL_CORNER_03:
                    SetConsoleTextAttribute(h, DARKGRAY);
                    cout << (char)Border::_CORNER_03;
                    break;

                case LevelBox::LEVEL_CORNER_04:
                    SetConsoleTextAttribute(h, DARKGRAY);
                    cout << (char)Border::_CORNER_04;
                    break;

                case 101: // Level 1
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "1";
                    break;

                case 102: // Level 2
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "2";
                    break;

                case 103: // Level 3
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "3";
                    break;

                case 104: // Level 4
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "4";
                    break;

                case 105: // Level 5
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "5";
                    break;

                case 106: // Level 6 
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "6";
                    break;

                case 107: // Level 7
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "7";
                    break;

                case 108: // Level 8 
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "8";
                    break;

                case 109: // Level 9
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "9";
                    break;


                }
            }
            cout << "\n";
        }
        cout << "\n";

        // Movement ====================================================

        Move Cursor = { NULL, StartWIDTH, StartHEIGHT };
        Cursor.SetPosition();

        while (true)
        {
            if (_kbhit())
            {
                int code = _getch();

                if (code == 224)
                {
                    code = _getch();
                }


            }
        }

    }
};