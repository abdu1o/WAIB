#include "Global.h"
#include "Enums/Enums.h"
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
                    SetConsoleTextAttribute(h, GREEN);
                    cout << "1";
                    break;

                case 102: // Level 2
                    SetConsoleTextAttribute(h, RED);
                    cout << "2";
                    break;

                case 103: // Level 3
                    SetConsoleTextAttribute(h, RED);
                    cout << "3";
                    break;

                case 104: // Level 4
                    SetConsoleTextAttribute(h, RED);
                    cout << "4";
                    break;

                case 105: // Level 5
                    SetConsoleTextAttribute(h, RED);
                    cout << "5";
                    break;

                case 106: // Level 6 
                    SetConsoleTextAttribute(h, RED);
                    cout << "6";
                    break;

                case 107: // Level 7
                    SetConsoleTextAttribute(h, RED);
                    cout << "7";
                    break;

                case 108: // Level 8 
                    SetConsoleTextAttribute(h, RED);
                    cout << "8";
                    break;

                case 109: // Level 9
                    SetConsoleTextAttribute(h, RED);
                    cout << "9";
                    break;


                }
            }
            cout << "\n";

        }
        cout << "\n";



        // Movement ====================================================

        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);

        INPUT_RECORD inputRecords[128];
        DWORD eventsCount;
        HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(inputHandle, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

        while (true)
        {
            if (ReadConsoleInput(inputHandle, inputRecords, 128, &eventsCount))
            {
                for (DWORD i = 0; i < eventsCount; ++i)
                {
                    if (inputRecords[i].EventType == MOUSE_EVENT)
                    {
                        MOUSE_EVENT_RECORD& mouseEvent = inputRecords[i].Event.MouseEvent;

                        // !! Need to add condition - Level open? !!

                        if (mouseEvent.dwMousePosition.X >= StartWIDTH + 8 && mouseEvent.dwMousePosition.X <= StartWIDTH + 12 // Level 1
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 3 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 5)
                        {
                            // Open Level
                            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                            {
                                std::cout << "Level 1" << std::endl;
                            }
                        }



                        else if (mouseEvent.dwMousePosition.X >= StartWIDTH + 26 && mouseEvent.dwMousePosition.X <= StartWIDTH + 30 // Level 2
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 3 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 5)
                        {
                            // Open Level
                            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                            {

                                // Set Green Color for Level

                               /* for (int y = 0; y < HEIGHT; y++)
                                {
                                    for (int x = 0; x < WIDTH; x++)
                                    {
                                        if (menu_box[y][x] == 102)
                                        {
                                            COORD Level_02;
                                            Level_02.Y = y;
                                            Level_02.X = x;
                                            SetConsoleCursorPosition(h, Level_02);
                                            SetConsoleTextAttribute(h, GREEN);
                                            cout << "2";
                                        }
                                    }
                                }*/
                                

                                std::cout << "Level 2" << std::endl;
                            }
                        }



                        else if (mouseEvent.dwMousePosition.X >= StartWIDTH + 44 && mouseEvent.dwMousePosition.X <= StartWIDTH + 48 // Level 3
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 3 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 5)
                        {
                            // Open Level
                            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                            {
                                std::cout << "Level 3" << std::endl;
                            }
                        }



                        else if (mouseEvent.dwMousePosition.X >= StartWIDTH + 8 && mouseEvent.dwMousePosition.X <= StartWIDTH + 12 // Level 4
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 9 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 11)
                        {
                            // Open Level
                            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                            {
                                std::cout << "Level 4" << std::endl;
                            }
                        }



                        else if (mouseEvent.dwMousePosition.X >= StartWIDTH + 26 && mouseEvent.dwMousePosition.X <= StartWIDTH + 30 // Level 5
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 9 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 11)
                        {
                            // Open Level
                            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                            {
                                std::cout << "Level 5" << std::endl;
                            }
                        }



                        else if (mouseEvent.dwMousePosition.X >= StartWIDTH + 44 && mouseEvent.dwMousePosition.X <= StartWIDTH + 48 // Level 6
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 9 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 11)
                        {
                            // Open Level
                            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                            {
                                std::cout << "Level 6" << std::endl;
                            }
                        }



                        else if (mouseEvent.dwMousePosition.X >= StartWIDTH + 8 && mouseEvent.dwMousePosition.X <= StartWIDTH + 12 // Level 7
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 15 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 17)
                        {
                            // Open Level
                            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                            {
                                std::cout << "Level 7" << std::endl;
                            }
                        }



                        else if (mouseEvent.dwMousePosition.X >= StartWIDTH + 26 && mouseEvent.dwMousePosition.X <= StartWIDTH + 30 // Level 8
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 15 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 17)
                        {
                                // Open Level
                                if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                                {
                                    std::cout << "Level 8" << std::endl;
                                }
                        }



                        else if (mouseEvent.dwMousePosition.X >= StartWIDTH + 44 && mouseEvent.dwMousePosition.X <= StartWIDTH + 48 // Level 9
                            && mouseEvent.dwMousePosition.Y >= StartHEIGHT + 15 && mouseEvent.dwMousePosition.Y <= StartHEIGHT + 17)
                        {
                                // Open Level
                                if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                                {
                                    std::cout << "Level 9" << std::endl;
                                }
                        }

                    }
                }
            }
        }


    }
};