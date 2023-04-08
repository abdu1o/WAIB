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
                    cout << (char)Border::EMPTY;
                }
            }
        }
    }

public:

    Level1()
    {
        srand(time(0));
        vector<int> randX(7);
        vector<int> randY(7);

        for (int i = 0; i < 7; i++) 
        {
            randX[i] = 3 + rand() % 35;
        }
        for (int i = 0; i < 7; i++)
        {
            randY[i] = 5 + rand() % 8;
        }

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


                //Letter fields ======================================================================
                //place to put the letters

                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 18)
                {
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 19)
                {
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 20)
                {
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 21)
                {
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }

                //Move letters =======================================================================

                else if (y == StartHEIGHT + randY[0] && x == StartWIDTH + randX[0])
                {                                       
                    menu_box[y][x] = Move_Alphabet::_O; 
                }                                       
                else if (y == StartHEIGHT + randY[1] && x == StartWIDTH + randX[1])
                {                                       
                    menu_box[y][x] = Move_Alphabet::_J; 
                }                                       
                else if (y == StartHEIGHT + randY[2] && x == StartWIDTH + randX[2])
                {                                       
                    menu_box[y][x] = Move_Alphabet::_K; 
                }                                       
                else if (y == StartHEIGHT + randY[3] && x == StartWIDTH + randX[3])
                {                                       
                    menu_box[y][x] = Move_Alphabet::_P; 
                }                                       
                else if (y == StartHEIGHT + randY[4] && x == StartWIDTH + randX[4])
                {                                       
                    menu_box[y][x] = Move_Alphabet::_E; 
                }                                       
                else if (y == StartHEIGHT + randY[5] && x == StartWIDTH + randX[5] )
                {                                       
                    menu_box[y][x] = Move_Alphabet::_N; 
                }                                       
                else if (y == StartHEIGHT + randY[6] && x == StartWIDTH + randX[6])
                {
                    menu_box[y][x] = Move_Alphabet::_Q;
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
                    cout << (char)Border::EMPTY;
                    break;
                case Border::BORDER_UP_DOWN: // up and down borders
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::BORDER_UP_DOWN;
                    break;
                case Border::BORDER_LEFT_RIGHT: // left and right borders
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::BORDER_LEFT_RIGHT;
                    break;
                case Border::CORNER_01: // corner 1
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::CORNER_01;
                    break;
                case Border::CORNER_02: // corner 2
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::CORNER_02;
                    break;
                case Border::CORNER_03: // corner 3
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::CORNER_03;
                    break;
                case Border::CORNER_04: // corner 4
                    SetConsoleTextAttribute(h, DARKYELLOW);
                    cout << (char)Border::CORNER_04;
                    break;
                case Door::DOOR: // DOOR
                    SetConsoleTextAttribute(h, GRAY);
                    cout << (char)Door::_DOOR;
                    break;
                case Static_Alphabet::D: // D
                    SetConsoleTextAttribute(h, DARKRED);
                    cout << (char)Static_Alphabet::D;
                    break;
                case Static_Alphabet::O: // O
                    SetConsoleTextAttribute(h, DARKRED);
                    cout << (char)Static_Alphabet::O;
                    break;
                case Static_Alphabet::R: // R
                    SetConsoleTextAttribute(h, DARKRED);
                    cout << (char)Static_Alphabet::R;
                    break;
                case Static_Alphabet::I: // I
                    SetConsoleTextAttribute(h, DARKRED);
                    cout << (char)Static_Alphabet::I;
                    break;
                case Static_Alphabet::S: // S
                    SetConsoleTextAttribute(h, DARKRED);
                    cout << (char)Static_Alphabet::S;
                    break;
                case LevelBox::LEVEL_LETTER_FIELD: // place to put the letters
                    SetConsoleTextAttribute(h, RED);
                    cout << (char)LevelBox::LEVEL_LETTER_FIELD;
                    break;
                case Move_Alphabet::_O: // O which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::O;
                    break;
                case Move_Alphabet::_P: // P which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::P;
                    break;
                case Move_Alphabet::_E: // E which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::E;
                    break;
                case Move_Alphabet::_N: // N which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::N;
                    break;
                case Move_Alphabet::_Q: // Q which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::Q;
                    break;
                case Move_Alphabet::_J: // J which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::J;
                    break;
                case Move_Alphabet::_K: // K which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::K;
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
                if (menu_box[player.GetY()][player.GetX()] == LevelBox::LEVEL_LETTER_FIELD)
                {
                    //no eat letter fields
                    player.SetPosition();
                    SetConsoleTextAttribute(h, RED);
                    cout << (char)LevelBox::LEVEL_LETTER_FIELD;
                }
                else
                {
                    player.SetPosition();
                    cout << " ";
                }
                
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