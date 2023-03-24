#include "Global.h"
#include "Enums/Enums.h"


class LevelMap
{

private:
    static const int WIDTH = 70;
    static const int HEIGHT = 20;

    static const int StartWIDTH = 10;
    static const int StartHEIGHT = 2;

    static const int EndWIDTH = WIDTH - 1;
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

                else if (y >= StartHEIGHT && x == StartWIDTH && y <= EndWIDTH || y >= StartHEIGHT && x ==EndWIDTH && y <= EndHEIGHT)
                {
                    menu_box[y][x] = Border::BORDER_LEFT_RIGHT; // left and right borders
                }
               
                //====================================================================================

                else
                {
                    menu_box[y][x] = Border::EMPTY; // nihuya
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

                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
};