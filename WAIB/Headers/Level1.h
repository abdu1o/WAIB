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
    bool isLetter;

    COORD coord_O{};
    COORD coord_P{};
    COORD coord_E{};
    COORD coord_N{};
    COORD coord_Q{};
    COORD coord_J{};
    COORD coord_K{};

    COORD field_1{};
    COORD field_2{};
    COORD field_3{};
    COORD field_4{};


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

    void PrintField()
    {
        if (menu_box[field_1.Y][field_1.X] == LevelBox::LEVEL_LETTER_FIELD ||
            menu_box[field_1.Y][field_1.X] == Border::EMPTY)
        {
            SetConsoleCursorPosition(h, field_1);
            SetConsoleTextAttribute(h, RED);
            cout << (char)LevelBox::LEVEL_LETTER_FIELD;
        }
        else if (menu_box[field_2.Y][field_2.X] == LevelBox::LEVEL_LETTER_FIELD ||
            menu_box[field_1.Y][field_1.X] == Border::EMPTY)
        {
            SetConsoleCursorPosition(h, field_2);
            SetConsoleTextAttribute(h, RED);
            cout << (char)LevelBox::LEVEL_LETTER_FIELD;
        }
        else if (menu_box[field_3.Y][field_3.X] == LevelBox::LEVEL_LETTER_FIELD ||
            menu_box[field_1.Y][field_1.X] == Border::EMPTY)
        {
            SetConsoleCursorPosition(h, field_3);
            SetConsoleTextAttribute(h, RED);
            cout << (char)LevelBox::LEVEL_LETTER_FIELD;
        }
        else if (menu_box[field_4.Y][field_4.X] == LevelBox::LEVEL_LETTER_FIELD ||
            menu_box[field_1.Y][field_1.X] == Border::EMPTY)
        {
            SetConsoleCursorPosition(h, field_4);
            SetConsoleTextAttribute(h, RED);
            cout << (char)LevelBox::LEVEL_LETTER_FIELD;
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

        PrintField();

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
                    field_1.Y = StartHEIGHT + 3;
                    field_1.X = StartWIDTH + 18;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 19)
                {
                    field_2.Y = StartHEIGHT + 3;
                    field_2.X = StartWIDTH + 19;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 20)
                {
                    field_3.Y = StartHEIGHT + 3;
                    field_3.X = StartWIDTH + 20;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 21)
                {
                    field_4.Y = StartHEIGHT + 3;
                    field_4.X = StartWIDTH + 21;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }

                //Move letters =======================================================================

                else if (y == StartHEIGHT + randY[0] && x == StartWIDTH + randX[0])
                {
                    coord_O.X = StartWIDTH + randX[0];
                    coord_O.Y = StartHEIGHT + randY[0];
                    menu_box[y][x] = Move_Alphabet::_O;
                }
                else if (y == StartHEIGHT + randY[1] && x == StartWIDTH + randX[1])
                {
                    coord_J.X = StartWIDTH + randX[1];
                    coord_J.Y = StartHEIGHT + randY[1];
                    menu_box[y][x] = Move_Alphabet::_J;
                }
                else if (y == StartHEIGHT + randY[2] && x == StartWIDTH + randX[2])
                {
                    coord_K.X = StartWIDTH + randX[2];
                    coord_K.Y = StartHEIGHT + randY[2];
                    menu_box[y][x] = Move_Alphabet::_K;
                }
                else if (y == StartHEIGHT + randY[3] && x == StartWIDTH + randX[3])
                {
                    coord_P.X = StartWIDTH + randX[3];
                    coord_P.Y = StartHEIGHT + randY[3];
                    menu_box[y][x] = Move_Alphabet::_P;
                }
                else if (y == StartHEIGHT + randY[4] && x == StartWIDTH + randX[4])
                {
                    coord_E.X = StartWIDTH + randX[4];
                    coord_E.Y = StartHEIGHT + randY[4];
                    menu_box[y][x] = Move_Alphabet::_E;
                }
                else if (y == StartHEIGHT + randY[5] && x == StartWIDTH + randX[5])
                {
                    coord_N.X = StartWIDTH + randX[5];
                    coord_N.Y = StartHEIGHT + randY[5];
                    menu_box[y][x] = Move_Alphabet::_N;
                }
                else if (y == StartHEIGHT + randY[6] && x == StartWIDTH + randX[6])
                {
                    coord_Q.X = StartWIDTH + randX[6];
                    coord_Q.Y = StartHEIGHT + randY[6];
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
                    //it just works !!DO NOT TOUCH!!
                    if (menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Border::BORDER_UP_DOWN ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Static_Alphabet::D ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Static_Alphabet::O ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Static_Alphabet::R ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Static_Alphabet::I ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                        menu_box[player.GetY() - 2][player.GetX()] == Static_Alphabet::S ||
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
                    menu_box[player.GetY() + 1][player.GetX()] != Door::DOOR &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::D &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::O &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::R &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::I &&
                    menu_box[player.GetY() + 1][player.GetX()] != Static_Alphabet::S)
                {
                     if (menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY() + 2][player.GetX()] == Border::BORDER_UP_DOWN ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY() + 2][player.GetX()] == Static_Alphabet::D ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY() + 2][player.GetX()] == Static_Alphabet::O ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY() + 2][player.GetX()] == Static_Alphabet::R ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY() + 2][player.GetX()] == Static_Alphabet::I ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY() + 2][player.GetX()] == Static_Alphabet::S ||
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
                    menu_box[player.GetY()][player.GetX() - 1] != Door::DOOR &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::D &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::O &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::R &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::I &&
                    menu_box[player.GetY()][player.GetX() - 1] != Static_Alphabet::S)
                {
                     if (menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() - 2] == Border::BORDER_LEFT_RIGHT ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() - 2] == Static_Alphabet::D ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() - 2] == Static_Alphabet::O ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() - 2] == Static_Alphabet::R ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() - 2] == Static_Alphabet::I ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() - 2] == Static_Alphabet::S ||
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
                    menu_box[player.GetY()][player.GetX() + 1] != Door::DOOR &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::D &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::O &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::R &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::I &&
                    menu_box[player.GetY()][player.GetX() + 1] != Static_Alphabet::S)
                {
                     if (menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() + 2] == Border::BORDER_LEFT_RIGHT ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() + 2] == Static_Alphabet::D ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() + 2] == Static_Alphabet::O ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() + 2] == Static_Alphabet::R ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() + 2] == Static_Alphabet::I ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_O | _P | _E | _N | _J | _K | _Q &&
                         menu_box[player.GetY()][player.GetX() + 2] == Static_Alphabet::S ||
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
