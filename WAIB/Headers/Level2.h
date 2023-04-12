#include "Global.h"
#include "Move.h"
#include "Enums/Enums.h"

class Level2
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

    COORD fields[15] = 
    {
        COORD{}, COORD{}, COORD{}, COORD{}, COORD{},
        COORD{}, COORD{}, COORD{}, COORD{}, COORD{},
        COORD{}, COORD{}, COORD{}, COORD{}, COORD{}
    };

    COORD coord_W{};
    COORD coord_A1{};
    COORD coord_A2{};
    COORD coord_I1{};
    COORD coord_I2{};
    COORD coord_R1{};
    COORD coord_R2{};
    COORD coord_S1{};
    COORD coord_S2{};
    COORD coord_L1{};
    COORD coord_L2{};
    COORD coord_L3{};
    COORD coord_C{};
    COORD coord_K{};
    COORD coord_E{};
    COORD coord_Y{};

    COORD txt{};

    void ShowTxt()
    {
        txt.Y = EndHEIGHT + 3;
        txt.X = 10;
        SetConsoleTextAttribute(h, CYAN);
        SetConsoleCursorPosition(h, txt);

        string info = "Press ENTER to restart";
        for (int i = 0; i < info.length(); i++)
        {
            cout << info[i];
        }
    }

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
                    menu_box[y][x] = Border::EMPTY;
                    cout << (char)Border::EMPTY;
                }
            }
        }
    }

    void LetterMove(char ch, COORD& letter, int direction, Move_Alphabet move_char)
    {
        if (menu_box[letter.Y][letter.X] == LevelBox::LEVEL_LETTER_FIELD)
        {
            menu_box[letter.Y][letter.X] = LevelBox::LEVEL_LETTER_FIELD;
        }
        else
        {
            menu_box[letter.Y][letter.X] = Border::EMPTY;
        }

        switch (direction)
        {
        case 1:
            letter.Y -= 1; //up
            break;
        case 2:
            letter.Y += 1; // down
            break;
        case 3:
            letter.X -= 1; // left
            break;
        case 4:
            letter.X += 1; // right
            break;
        }
        menu_box[letter.Y][letter.X] = move_char;
        SetConsoleTextAttribute(h, WHITE);
        SetConsoleCursorPosition(h, letter);
        cout << ch;
    }

public:

    Level2()
    {
        srand(time(0));
        vector<int> randX(16);
        vector<int> randY(16);

        for (int i = 0; i < 7; i++)
        {
            randX[i] = 3 + rand() % 40;
        }
        for (int i = 0; i < 7; i++)
        {
            randY[i] = 3 + rand() % 8;
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

                //Letter fields ======================================================================
                //place to put the letters

                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 12)
                {
                    fields[1].Y = StartHEIGHT + 3;
                    fields[1].X = StartWIDTH + 18;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 13)
                {
                    fields[2].Y = StartHEIGHT + 3;
                    fields[2].X = StartWIDTH + 19;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 14)
                {
                    fields[3].Y = StartHEIGHT + 3;
                    fields[3].X = StartWIDTH + 20;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 15)
                {
                    fields[4].Y = StartHEIGHT + 3;
                    fields[4].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 16)
                {
                    fields[5].Y = StartHEIGHT + 3;
                    fields[5].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 17)
                {
                    fields[6].Y = StartHEIGHT + 3;
                    fields[6].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 18)
                {
                    fields[7].Y = StartHEIGHT + 3;
                    fields[7].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 19)
                {
                    fields[8].Y = StartHEIGHT + 3;
                    fields[8].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 20)
                {
                    fields[9].Y = StartHEIGHT + 3;
                    fields[9].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 21)
                {
                    fields[10].Y = StartHEIGHT + 3;
                    fields[10].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 22)
                {
                    fields[11].Y = StartHEIGHT + 3;
                    fields[11].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 23)
                {
                    fields[12].Y = StartHEIGHT + 3;
                    fields[12].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 24)
                {
                    fields[13].Y = StartHEIGHT + 3;
                    fields[13].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 25)
                {
                    fields[14].Y = StartHEIGHT + 3;
                    fields[14].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 26)
                {
                    fields[15].Y = StartHEIGHT + 3;
                    fields[15].X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }

                //Move letters =======================================================================

                else if (y == StartHEIGHT + randY[0] - 1 && x == StartWIDTH + randX[0])
                {
                    coord_W.X = StartWIDTH + randX[0];
                    coord_W.Y = StartHEIGHT + randY[0] - 1;
                    menu_box[y][x] = Move_Alphabet::_W;
                }
                else if (y == StartHEIGHT + randY[1] - 1 && x == StartWIDTH + randX[1])
                {
                    coord_A1.X = StartWIDTH + randX[1];
                    coord_A1.Y = StartHEIGHT + randY[1] - 1;
                    menu_box[y][x] = Move_Alphabet::_A;
                }
                else if (y == StartHEIGHT + randY[2] - 1 && x == StartWIDTH + randX[2])
                {
                    coord_A2.X = StartWIDTH + randX[2];
                    coord_A2.Y = StartHEIGHT + randY[2] - 1;
                    menu_box[y][x] = Move_Alphabet::_A1;
                }
                else if (y == StartHEIGHT + randY[3] - 1 && x == StartWIDTH + randX[3])
                {
                    coord_I1.X = StartWIDTH + randX[3];
                    coord_I1.Y = StartHEIGHT + randY[3] - 1;
                    menu_box[y][x] = Move_Alphabet::_I;
                }
                else if (y == StartHEIGHT + randY[4] - 1 && x == StartWIDTH + randX[4])
                {
                    coord_I2.X = StartWIDTH + randX[4];
                    coord_I2.Y = StartHEIGHT + randY[4] - 1;
                    menu_box[y][x] = Move_Alphabet::_I1;
                }
                else if (y == StartHEIGHT + randY[5] - 1 && x == StartWIDTH + randX[5])
                {
                    coord_R1.X = StartWIDTH + randX[5];
                    coord_R1.Y = StartHEIGHT + randY[5] - 1;
                    menu_box[y][x] = Move_Alphabet::_R;
                }
                else if (y == StartHEIGHT + randY[6] - 1 && x == StartWIDTH + randX[6])
                {
                    coord_R2.X = StartWIDTH + randX[6];
                    coord_R2.Y = StartHEIGHT + randY[6] - 1;
                    menu_box[y][x] = Move_Alphabet::_R1;
                }
                else if (y == StartHEIGHT + randY[7] - 1 && x == StartWIDTH + randX[7])
                {
                    coord_S1.X = StartWIDTH + randX[7];
                    coord_S1.Y = StartHEIGHT + randY[7] - 1;
                    menu_box[y][x] = Move_Alphabet::_S;
                }
                else if (y == StartHEIGHT + randY[8] - 1 && x == StartWIDTH + randX[8])
                {
                    coord_S2.X = StartWIDTH + randX[8];
                    coord_S2.Y = StartHEIGHT + randY[8] - 1;
                    menu_box[y][x] = Move_Alphabet::_S1;
                }
                else if (y == StartHEIGHT + randY[9] - 1 && x == StartWIDTH + randX[9])
                {
                    coord_L1.X = StartWIDTH + randX[9];
                    coord_L1.Y = StartHEIGHT + randY[9] - 1;
                    menu_box[y][x] = Move_Alphabet::_L;
                }
                else if (y == StartHEIGHT + randY[10] - 1 && x == StartWIDTH + randX[10])
                {
                    coord_L2.X = StartWIDTH + randX[10];
                    coord_L2.Y = StartHEIGHT + randY[10] - 1;
                    menu_box[y][x] = Move_Alphabet::_L1;
                }
                else if (y == StartHEIGHT + randY[11] - 1 && x == StartWIDTH + randX[11])
                {
                    coord_L3.X = StartWIDTH + randX[11];
                    coord_L3.Y = StartHEIGHT + randY[11] - 1;
                    menu_box[y][x] = Move_Alphabet::_L2;
                }
                else if (y == StartHEIGHT + randY[12] - 1 && x == StartWIDTH + randX[12])
                {
                    coord_C.X = StartWIDTH + randX[12];
                    coord_C.Y = StartHEIGHT + randY[12] - 1;
                    menu_box[y][x] = Move_Alphabet::_C;
                }
                else if (y == StartHEIGHT + randY[13] - 1 && x == StartWIDTH + randX[13])
                {
                    coord_K.X = StartWIDTH + randX[13];
                    coord_K.Y = StartHEIGHT + randY[13] - 1;
                    menu_box[y][x] = Move_Alphabet::_K;
                }
                else if (y == StartHEIGHT + randY[14] - 1 && x == StartWIDTH + randX[14])
                {
                    coord_E.X = StartWIDTH + randX[14];
                    coord_E.Y = StartHEIGHT + randY[14] - 1;
                    menu_box[y][x] = Move_Alphabet::_E;
                }
                else if (y == StartHEIGHT + randY[15] - 1 && x == StartWIDTH + randX[15])
                {
                    coord_Y.X = StartWIDTH + randX[15];
                    coord_Y.Y = StartHEIGHT + randY[15] - 1;
                    menu_box[y][x] = Move_Alphabet::_Y;
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

        ShowTxt();

        // Movement ====================================================

        Move player = { 2, 15, 6 };
        player.SetPosition();
        player.SetColor(Color::BLUE);
        player.PrintEmoji();

        //for tests
        /*Level2::OpenDoor();*/

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
                    menu_box[player.GetY() - 1][player.GetX()] != Door::DOOR)
                {
                    //it just works !!DO NOT TOUCH!!
                    if (menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Border::BORDER_UP_DOWN ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_O ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_P ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_E ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_N ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_J ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_K ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_Q)
                    {
                        player.SetPosition();
                        player.SetColor(Color::BLUE);
                        player.PrintEmoji();
                        continue;
                    }
                    /*direction to move:
                    1 - move up
                    2 - move down
                    3 - move left
                    4 - move right*/
                    else
                    {
                        player.MoveUp();
                        switch (menu_box[player.GetY()][player.GetX()])
                        {
                        case Move_Alphabet::_O:
                            LetterMove(Static_Alphabet::O, coord_O, 1, _O);
                            menu_box[coord_O.Y][coord_O.X] = Move_Alphabet::_O;
                            break;
                        case Move_Alphabet::_P:
                            LetterMove(Static_Alphabet::P, coord_P, 1, _P);
                            menu_box[coord_P.Y][coord_P.X] = Move_Alphabet::_P;
                            break;
                        case Move_Alphabet::_E:
                            LetterMove(Static_Alphabet::E, coord_E, 1, _E);
                            menu_box[coord_E.Y][coord_E.X] = Move_Alphabet::_E;
                            break;
                        case Move_Alphabet::_N:
                            LetterMove(Static_Alphabet::N, coord_N, 1, _N);
                            menu_box[coord_N.Y][coord_N.X] = Move_Alphabet::_N;
                            break;
                        case Move_Alphabet::_Q:
                            LetterMove(Static_Alphabet::Q, coord_Q, 1, _Q);
                            menu_box[coord_Q.Y][coord_Q.X] = Move_Alphabet::_Q;
                            break;
                        case Move_Alphabet::_J:
                            LetterMove(Static_Alphabet::J, coord_J, 1, _J);
                            menu_box[coord_J.Y][coord_J.X] = Move_Alphabet::_J;
                            break;
                        case Move_Alphabet::_K:
                            LetterMove(Static_Alphabet::K, coord_K, 1, _K);
                            menu_box[coord_K.Y][coord_K.X] = Move_Alphabet::_K;
                            break;
                        }
                    }
                }


                else if (code == KeyCode::DOWN && menu_box[player.GetY() + 1][player.GetX()] != Border::BORDER_UP_DOWN &&
                    menu_box[player.GetY() + 1][player.GetX()] != Border::CORNER_04 &&
                    menu_box[player.GetY() + 1][player.GetX()] != Border::CORNER_03 &&
                    menu_box[player.GetY() + 1][player.GetX()] != Border::CORNER_02 &&
                    menu_box[player.GetY() + 1][player.GetX()] != Border::CORNER_01 &&
                    menu_box[player.GetY() + 1][player.GetX()] != Door::DOOR)
                {
                    if (menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() + 2][player.GetX()] == Border::BORDER_UP_DOWN ||
                        menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_O ||
                        menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_P ||
                        menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_E ||
                        menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_N ||
                        menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_J ||
                        menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_K ||
                        menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_Q)
                    {
                        player.SetPosition();
                        player.SetColor(Color::BLUE);
                        player.PrintEmoji();
                        continue;
                    }
                    else
                    {
                        player.MoveDown();
                        switch (menu_box[player.GetY()][player.GetX()])
                        {
                        case Move_Alphabet::_O:
                            LetterMove(Static_Alphabet::O, coord_O, 2, _O);
                            menu_box[coord_O.Y][coord_O.X] = Move_Alphabet::_O;
                            break;
                        case Move_Alphabet::_P:
                            LetterMove(Static_Alphabet::P, coord_P, 2, _P);
                            menu_box[coord_P.Y][coord_P.X] = Move_Alphabet::_P;
                            break;
                        case Move_Alphabet::_E:
                            LetterMove(Static_Alphabet::E, coord_E, 2, _E);
                            menu_box[coord_E.Y][coord_E.X] = Move_Alphabet::_E;
                            break;
                        case Move_Alphabet::_N:
                            LetterMove(Static_Alphabet::N, coord_N, 2, _N);
                            menu_box[coord_N.Y][coord_N.X] = Move_Alphabet::_N;
                            break;
                        case Move_Alphabet::_Q:
                            LetterMove(Static_Alphabet::Q, coord_Q, 2, _Q);
                            menu_box[coord_Q.Y][coord_Q.X] = Move_Alphabet::_Q;
                            break;
                        case Move_Alphabet::_J:
                            LetterMove(Static_Alphabet::J, coord_J, 2, _J);
                            menu_box[coord_J.Y][coord_J.X] = Move_Alphabet::_J;
                            break;
                        case Move_Alphabet::_K:
                            LetterMove(Static_Alphabet::K, coord_K, 2, _K);
                            menu_box[coord_K.Y][coord_K.X] = Move_Alphabet::_K;
                            break;
                        }
                    }
                }


                else if (code == KeyCode::LEFT && menu_box[player.GetY()][player.GetX() - 1] != Border::BORDER_LEFT_RIGHT &&
                    menu_box[player.GetY()][player.GetX() - 1] != Border::CORNER_04 &&
                    menu_box[player.GetY()][player.GetX() - 1] != Border::CORNER_03 &&
                    menu_box[player.GetY()][player.GetX() - 1] != Border::CORNER_02 &&
                    menu_box[player.GetY()][player.GetX() - 1] != Border::CORNER_01 &&
                    menu_box[player.GetY()][player.GetX() - 1] != Door::DOOR)
                {
                    if (menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Border::BORDER_LEFT_RIGHT ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_O ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_P ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_E ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_N ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_J ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_K ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_Q ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == Door::DOOR ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == LevelBox::LEVEL_CORNER_01 ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == LevelBox::LEVEL_CORNER_02 ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == LevelBox::LEVEL_CORNER_03 ||
                        menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() - 2] == LevelBox::LEVEL_CORNER_04)
                    {
                        player.SetPosition();
                        player.SetColor(Color::BLUE);
                        player.PrintEmoji();
                        continue;
                    }
                    else
                    {
                        player.MoveLeft();
                        switch (menu_box[player.GetY()][player.GetX()])
                        {
                        case Move_Alphabet::_O:
                            LetterMove(Static_Alphabet::O, coord_O, 3, _O);
                            menu_box[coord_O.Y][coord_O.X] = Move_Alphabet::_O;
                            break;
                        case Move_Alphabet::_P:
                            LetterMove(Static_Alphabet::P, coord_P, 3, _P);
                            menu_box[coord_P.Y][coord_P.X] = Move_Alphabet::_P;
                            break;
                        case Move_Alphabet::_E:
                            LetterMove(Static_Alphabet::E, coord_E, 3, _E);
                            menu_box[coord_E.Y][coord_E.X] = Move_Alphabet::_E;
                            break;
                        case Move_Alphabet::_N:
                            LetterMove(Static_Alphabet::N, coord_N, 3, _N);
                            menu_box[coord_N.Y][coord_N.X] = Move_Alphabet::_N;
                            break;
                        case Move_Alphabet::_Q:
                            LetterMove(Static_Alphabet::Q, coord_Q, 3, _Q);
                            menu_box[coord_Q.Y][coord_Q.X] = Move_Alphabet::_Q;
                            break;
                        case Move_Alphabet::_J:
                            LetterMove(Static_Alphabet::J, coord_J, 3, _J);
                            menu_box[coord_J.Y][coord_J.X] = Move_Alphabet::_J;
                            break;
                        case Move_Alphabet::_K:
                            LetterMove(Static_Alphabet::K, coord_K, 3, _K);
                            menu_box[coord_K.Y][coord_K.X] = Move_Alphabet::_K;
                            break;
                        }
                    }
                }

                else if (code == KeyCode::RIGHT && menu_box[player.GetY()][player.GetX() + 1] != Border::BORDER_LEFT_RIGHT &&
                    menu_box[player.GetY()][player.GetX() + 1] != Border::CORNER_04 &&
                    menu_box[player.GetY()][player.GetX() + 1] != Border::CORNER_03 &&
                    menu_box[player.GetY()][player.GetX() + 1] != Border::CORNER_02 &&
                    menu_box[player.GetY()][player.GetX() + 1] != Border::CORNER_01 &&
                    menu_box[player.GetY()][player.GetX() + 1] != Door::DOOR)
                {
                    if (menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Border::BORDER_LEFT_RIGHT ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_O ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_P ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_E ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_N ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_J ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_K ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_Q ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == Door::DOOR ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == LevelBox::LEVEL_CORNER_01 ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == LevelBox::LEVEL_CORNER_02 ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == LevelBox::LEVEL_CORNER_03 ||
                        menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY()][player.GetX() + 2] == LevelBox::LEVEL_CORNER_04)
                    {
                        player.SetPosition();
                        player.SetColor(Color::BLUE);
                        player.PrintEmoji();
                        continue;
                    }
                    else
                    {
                        player.MoveRight();
                        switch (menu_box[player.GetY()][player.GetX()])
                        {
                        case Move_Alphabet::_O:
                            LetterMove(Static_Alphabet::O, coord_O, 4, _O);
                            menu_box[coord_O.Y][coord_O.X] = Move_Alphabet::_O;
                            break;
                        case Move_Alphabet::_P:
                            LetterMove(Static_Alphabet::P, coord_P, 4, _P);
                            menu_box[coord_P.Y][coord_P.X] = Move_Alphabet::_P;
                            break;
                        case Move_Alphabet::_E:
                            LetterMove(Static_Alphabet::E, coord_E, 4, _E);
                            menu_box[coord_E.Y][coord_E.X] = Move_Alphabet::_E;
                            break;
                        case Move_Alphabet::_N:
                            LetterMove(Static_Alphabet::N, coord_N, 4, _N);
                            menu_box[coord_N.Y][coord_N.X] = Move_Alphabet::_N;
                            break;
                        case Move_Alphabet::_Q:
                            LetterMove(Static_Alphabet::Q, coord_Q, 4, _Q);
                            menu_box[coord_Q.Y][coord_Q.X] = Move_Alphabet::_Q;
                            break;
                        case Move_Alphabet::_J:
                            LetterMove(Static_Alphabet::J, coord_J, 4, _J);
                            menu_box[coord_J.Y][coord_J.X] = Move_Alphabet::_J;
                            break;
                        case Move_Alphabet::_K:
                            LetterMove(Static_Alphabet::K, coord_K, 4, _K);
                            menu_box[coord_K.Y][coord_K.X] = Move_Alphabet::_K;
                            break;
                        }
                    }
                }
                //level restart if letter stuck
                else if (code == KeyCode::ENTER)
                {
                    system("cls");
                    Level2 obj;
                    obj.Show();
                }

                //check is win?
                if (menu_box[field_1.Y][field_1.X] == Move_Alphabet::_O &&
                    menu_box[field_2.Y][field_2.X] == Move_Alphabet::_P &&
                    menu_box[field_3.Y][field_3.X] == Move_Alphabet::_E &&
                    menu_box[field_4.Y][field_4.X] == Move_Alphabet::_N)
                {
                    Level2::OpenDoor();
                }

                //escape 
                if (player.GetX() >= EndWIDTH)
                {
                    system("cls");
                    //add transition to level map         
                    break;
                }

                //set new coord---------------------------
                player.SetPosition();
                player.SetColor(Color::BLUE);
                player.PrintEmoji();
            }
        }

    }
};