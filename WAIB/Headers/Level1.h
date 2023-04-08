#include "Global.h"
#include "Move.h"
#include "Enums/Enums.h"

class Level1 : public Move
{
private:
    static const int WIDTH = 60;
    static const int HEIGHT = 18;

    static const int StartWIDTH = 10;
    static const int StartHEIGHT = 3;

    static const int EndWIDTH = WIDTH - 1;
    static const int EndHEIGHT = HEIGHT - 1;

    int menu_box[HEIGHT][WIDTH] = {};

    HANDLE h;

    bool finish;

    void OpenDoor()
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (menu_box[y][x] == Door::DOOR)
                {
                    COORD DOOR;
                    DOOR.Y = y;
                    DOOR.X = x;
                    SetConsoleCursorPosition(h, DOOR);
                    cout << (char)Border::_EMPTY;
                }
            }
        }
    }

public:

    Level1()
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
        finish = false;

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {

                //BORDERS=============================================================================
                if (y == StartHEIGHT && x == StartWIDTH || y == EndHEIGHT / 2 && x == EndWIDTH - 7)
                {
                    menu_box[y][x] = Border::CORNER_01; // corner 1
                }

                else if (y == StartHEIGHT && x == EndWIDTH || y == EndHEIGHT / 2 + 4 && x == EndWIDTH)
                {
                    menu_box[y][x] = Border::CORNER_02; // corner 2
                }

                else if (y == EndHEIGHT && x == EndWIDTH || x == EndWIDTH && y == EndHEIGHT / 2)
                {
                    menu_box[y][x] = Border::CORNER_03; // corner 3
                }

                else if (y == EndHEIGHT && x == StartWIDTH || y == EndHEIGHT / 2 + 4 && x == EndWIDTH - 7)
                {
                    menu_box[y][x] = Border::CORNER_04; // corner 4
                }

                else if (y == StartHEIGHT && x >= StartWIDTH && x <= EndWIDTH || y == EndHEIGHT && x >= StartWIDTH && x <= EndWIDTH)
                {
                    menu_box[y][x] = Border::BORDER_UP_DOWN; // up and down borders
                }

                else if (y >= StartHEIGHT && x == StartWIDTH && y <= EndWIDTH || y >= StartHEIGHT && x == EndWIDTH && y <= EndHEIGHT / 2 || y >= EndHEIGHT / 2 + 4 && x == EndWIDTH && y <= EndHEIGHT)
                {
                    menu_box[y][x] = Border::BORDER_LEFT_RIGHT; // left and right borders
                }


                //Exit ===============================================================================

                else if (y == EndHEIGHT / 2 && x >= EndWIDTH - 7 && x <= EndWIDTH)
                {
                    menu_box[y][x] = Border::BORDER_UP_DOWN;
                }

                else if (y == EndHEIGHT / 2 + 4 && x >= EndWIDTH - 7 && x <= EndWIDTH)
                {
                    menu_box[y][x] = Border::BORDER_UP_DOWN;
                }

                else if (x == EndWIDTH - 7 && y >= EndHEIGHT / 2 + 1 && y <= EndHEIGHT / 2 + 3)
                {
                    menu_box[y][x] = Door::DOOR;
                }


                //Static letters =====================================================================

                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 10)
                {
                    menu_box[y][x] = Static_Alphabet::D;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 11)
                {
                    menu_box[y][x] = Static_Alphabet::O;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 12)
                {
                    menu_box[y][x] = Static_Alphabet::O;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 13)
                {
                    menu_box[y][x] = Static_Alphabet::R;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 15)
                {
                    menu_box[y][x] = Static_Alphabet::I;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 16)
                {
                    menu_box[y][x] = Static_Alphabet::S;
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
        system("cls");
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

                case Door::DOOR: // DOOR
                    SetConsoleTextAttribute(h, GRAY);
                    cout << (char)Door::_DOOR;
                    break;
                case Static_Alphabet::D: // D
                    SetConsoleTextAttribute(h, RED);
                    cout << (char)Static_Alphabet::D;
                    break;
                case Static_Alphabet::O: // O
                    SetConsoleTextAttribute(h, RED);
                    cout << (char)Static_Alphabet::O;
                    break;
                case Static_Alphabet::R: // R
                    SetConsoleTextAttribute(h, RED);
                    cout << (char)Static_Alphabet::R;
                    break;
                case Static_Alphabet::I: // I
                    SetConsoleTextAttribute(h, RED);
                    cout << (char)Static_Alphabet::I;
                    break;
                case Static_Alphabet::S: // S
                    SetConsoleTextAttribute(h, RED);
                    cout << (char)Static_Alphabet::S;
                    break;
                }
            }
            cout << "\n";
        }
        cout << "\n";

        // Movement ====================================================

        Move player = { 2, 15, 6 };
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
                    menu_box[player.GetY() - 1][player.GetX()] != Border::CORNER_04 && 
                    menu_box[player.GetY() - 1][player.GetX()] != Border::CORNER_03 && 
                    menu_box[player.GetY() - 1][player.GetX()] != Border::CORNER_02 && 
                    menu_box[player.GetY() - 1][player.GetX()] != Border::CORNER_01 &&
                    menu_box[player.GetY() - 1][player.GetX()] != Door::DOOR &&
                    menu_box[player.GetY() - 1][player.GetX()] != Static_Alphabet::D &&
                    menu_box[player.GetY() - 1][player.GetX()] != Static_Alphabet::O &&
                    menu_box[player.GetY() - 1][player.GetX()] != Static_Alphabet::R &&
                    menu_box[player.GetY() - 1][player.GetX()] != Static_Alphabet::I &&
                    menu_box[player.GetY() - 1][player.GetX()] != Static_Alphabet::S)
                {
                    player.MoveUp();
                }


                else if (code == KeyCode::DOWN && menu_box[player.GetY() + 1][player.GetX()] != Border::BORDER_UP_DOWN &&
                    menu_box[player.GetY() + 1][player.GetX()] != Border::CORNER_04 &&
                    menu_box[player.GetY() + 1][player.GetX()] != Border::CORNER_03 &&
                    menu_box[player.GetY() + 1][player.GetX()] != Border::CORNER_02 &&
                    menu_box[player.GetY() + 1][player.GetX()] != Border::CORNER_01 &&
                    menu_box[player.GetY() + 1][player.GetX()] != Door::DOOR &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::D &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::O &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::R &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::I &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::S)
                {
                    player.MoveDown();
                }


                else if (code == KeyCode::LEFT && menu_box[player.GetY()][player.GetX() - 1] != Border::BORDER_LEFT_RIGHT &&
                    menu_box[player.GetY()][player.GetX() - 1] != Border::CORNER_04 &&
                    menu_box[player.GetY()][player.GetX() - 1] != Border::CORNER_03 &&
                    menu_box[player.GetY()][player.GetX() - 1] != Border::CORNER_02 &&
                    menu_box[player.GetY()][player.GetX() - 1] != Border::CORNER_01 &&
                    menu_box[player.GetY()][player.GetX() - 1] != Door::DOOR &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::D &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::O &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::R &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::I &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::S)
                {
                    player.MoveLeft();
                }



                else if (code == KeyCode::RIGHT && menu_box[player.GetY()][player.GetX() + 1] != Border::BORDER_LEFT_RIGHT &&
                    menu_box[player.GetY()][player.GetX() + 1] != Border::CORNER_04 &&
                    menu_box[player.GetY()][player.GetX() + 1] != Border::CORNER_03 &&
                    menu_box[player.GetY()][player.GetX() + 1] != Border::CORNER_02 &&
                    menu_box[player.GetY()][player.GetX() + 1] != Border::CORNER_01 &&
                    menu_box[player.GetY()][player.GetX() + 1] != Door::DOOR &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::D &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::O &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::R &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::I &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::S)
                {
                    player.MoveRight();
                }

                //set new coord---------------------------
                player.SetPosition();
                player.SetColor(Color::BLUE);
                player.PrintEmoji();


                if (finish)
                {
                    Level1::OpenDoor();
                }

            }
        }

    }

};