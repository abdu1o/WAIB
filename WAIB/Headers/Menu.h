#include "Global.h"
#include "Move.h"
#include "Enums.h"

class Menu
{

private:

    static const int WIDTH = 28;
    static const int HEIGHT = 11;

    static const int StartWIDTH = 13;
    static const int StartHEIGHT = 1;

    static const int EndWIDTH = WIDTH - 1;
    static const int EndHEIGHT = HEIGHT - 1;

    int menu_box[HEIGHT][WIDTH] = {};

    HANDLE h;
    COORD menu;

public:

    Menu()
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
        this->menu.X = 17;
        this->menu.Y = 3;


        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {

                //Play
                if (y == menu.Y && x == menu.X)
                {
                    menu_box[y][x] = Alphabet::P;
                }

                else if (y == menu.Y && x == menu.X + 2)
                {
                    menu_box[y][x] = 7;
                }

                else if (y == menu.Y && x == menu.X + 3 || y == menu.Y && x == menu.X + 4) // words protect
                {
                    menu_box[y][x] = MenuWords::PLAY;
                }

                //Creators
                else if (y == menu.Y + 2 && x == menu.X)
                {
                    menu_box[y][x] = Alphabet::C;
                }

                else if (y == menu.Y + 2 && x == menu.X + 2)
                {
                    menu_box[y][x] = 8;
                }

                else if (y == menu.Y + 2 && x == menu.X + 3 || y == menu.Y + 2 && x == menu.X + 4 || y == menu.Y + 2 && x == menu.X + 5 || y == menu.Y + 2 && x == menu.X + 6 || y == menu.Y + 2 && x == menu.X + 7 || y == menu.Y + 2 && x == menu.X + 8) // words protect
                {
                    menu_box[y][x] = MenuWords::CREATORS;
                }

                //Exit
                else if (y == menu.Y + 4 && x == menu.X)
                {
                    menu_box[y][x] = Alphabet::E;
                }

                else if (y == menu.Y + 4 && x == menu.X + 2)
                {
                    menu_box[y][x] = 9;
                }

                else if (y == menu.Y + 4 && x == menu.X + 3 || y == menu.Y + 4 && x == menu.X + 4) // words protect
                {
                    menu_box[y][x] = MenuWords::EXIT;
                }


                //BORDERS=============================================================================

                else if (y == StartHEIGHT && x == StartWIDTH)
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

                else if (y >= StartHEIGHT && x == StartWIDTH && y <= EndHEIGHT || y >= StartHEIGHT && x == EndWIDTH && y <= EndWIDTH)
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


                case Alphabet::P:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "P";
                    break;


                case 7:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "LAY";
                    break;


                case Alphabet::C:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "C";
                    break;


                case 8:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << "REATORS";
                    break;


                case Alphabet::E:
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


        // Movement ====================================================

        Move player = { 2, 15, 3 };
        player.SetPosition();
        player.SetColor(Color::BLUE);
        player.PrintEmoji();

        while (true)
        {
            if (_kbhit())
            {
                int code = _getch();

                if (code == 224)
                {
                    code = _getch();
                }

                //remove old coord------------------
                player.SetPosition();
                cout << " ";



                if (code == KeyCode::UP && menu_box[player.GetY() - 1][player.GetX()] != Border::BORDER_UP_DOWN &&
                    //no eating letters
                    menu_box[player.GetY() - 1][player.GetX()] != P && menu_box[player.GetY() - 1][player.GetX()] != 7 &&
                    menu_box[player.GetY() - 1][player.GetX()] != C && menu_box[player.GetY() - 1][player.GetX()] != 8 &&
                    menu_box[player.GetY() - 1][player.GetX()] != E && menu_box[player.GetY() - 1][player.GetX()] != 9 &&
                    menu_box[player.GetY() - 1][player.GetX()] != MenuWords::PLAY && menu_box[player.GetY() - 1][player.GetX()] != MenuWords::CREATORS && menu_box[player.GetY() - 1][player.GetX()] != MenuWords::EXIT)
                {
                    player.MoveUp();
                }



                else if (code == KeyCode::DOWN && menu_box[player.GetY() + 1][player.GetX()] != Border::BORDER_UP_DOWN &&
                    //no eating letters
                    menu_box[player.GetY() + 1][player.GetX()] != P && menu_box[player.GetY() + 1][player.GetX()] != 7 &&
                    menu_box[player.GetY() + 1][player.GetX()] != C && menu_box[player.GetY() + 1][player.GetX()] != 8 &&
                    menu_box[player.GetY() + 1][player.GetX()] != E && menu_box[player.GetY() + 1][player.GetX()] != 9 &&
                    menu_box[player.GetY() + 1][player.GetX()] != MenuWords::PLAY && menu_box[player.GetY() + 1][player.GetX()] != MenuWords::CREATORS && menu_box[player.GetY() + 1][player.GetX()] != MenuWords::EXIT)
                {
                    player.MoveDown();
                }



                else if (code == KeyCode::LEFT && menu_box[player.GetY()][player.GetX() - 1] != Border::BORDER_LEFT_RIGHT &&
                    //no eating letters
                    menu_box[player.GetY()][player.GetX() - 1] != P && menu_box[player.GetY()][player.GetX() - 1] != 7 &&
                    menu_box[player.GetY()][player.GetX() - 1] != C && menu_box[player.GetY()][player.GetX() - 1] != 8 &&
                    menu_box[player.GetY()][player.GetX() - 1] != E && menu_box[player.GetY()][player.GetX() - 1] != 9 &&
                    menu_box[player.GetY()][player.GetX() - 1] != MenuWords::PLAY && menu_box[player.GetY()][player.GetX() - 1] != MenuWords::CREATORS && menu_box[player.GetY()][player.GetX() - 1] != MenuWords::EXIT)
                {
                    player.MoveLeft();
                }



                else if (code == KeyCode::RIGHT && menu_box[player.GetY()][player.GetX() + 1] != Border::BORDER_LEFT_RIGHT &&
                    //no eating words 
                    menu_box[player.GetY()][player.GetX() + 1] != 7 &&
                    menu_box[player.GetY()][player.GetX() + 1] != 8 &&
                    menu_box[player.GetY()][player.GetX() + 1] != 9 &&
                    menu_box[player.GetY()][player.GetX() + 1] != MenuWords::PLAY && menu_box[player.GetY()][player.GetX() + 1] != MenuWords::CREATORS && menu_box[player.GetY()][player.GetX() + 1] != MenuWords::EXIT)
                {
                    player.MoveRight();
                }

                //set new coord---------------------------
                player.SetPosition();
                player.SetColor(Color::BLUE);
                player.PrintEmoji();


                //letter movement-------------------------
                menu.X = 17;
                menu.Y = 3;
                Menu obj;

                //P
                if (menu_box[player.GetY()][player.GetX()] == menu_box[menu.Y][menu.X])
                {
                    obj.LetterMove('P', menu.X += 1, menu.Y);
                    break;
                }

                //C
                if (menu_box[player.GetY()][player.GetX()] == menu_box[menu.Y + 2][menu.X])
                {
                    obj.LetterMove('C', menu.X += 1, menu.Y += 2);
                    system("start https://github.com/abdu1o");
                    system("start https://github.com/MX322");
                    system("start https://github.com/eleonoraisaiko");
                    system("cls");
                    Show();
                }

                //E
                if (menu_box[player.GetY()][player.GetX()] == menu_box[menu.Y + 4][menu.X])
                {
                    obj.LetterMove('E', menu.X += 1, menu.Y += 4);
                    int choice = MessageBoxA(0, "\tAre you sure want to exit?", "Birds do not exist", MB_YESNO);

                    if (choice == IDYES)
                    {
                        system("cls");
                        exit(0);
                    }
                    else
                    {
                        system("cls");
                        Show();
                    }
                }
            }
        }
        system("cls");

    }

    void LetterMove(char ch, int X, int Y)
    {
        SetConsoleTextAttribute(h, WHITE);
        menu.X = X;
        menu.Y = Y;
        SetConsoleCursorPosition(h, menu);
        cout << ch;
        Sleep(100); //without this letter won`t visually move
    }
};