#include "Global.h"
#include "Move.h"
#include "Enums/Enums.h"

DWORD WINAPI SecretMusic(void* param)
{
    PlaySoundA("WAIB/Music/secret_music.WAV", NULL, SND_LOOP | SND_ASYNC);
    return 0;
}

class WordTriggers
{
public:
    static Color level_color;
    static bool car_trigger;

    Color GetColor() 
    {
        return level_color;
    }

    void SetColor(Color color) 
    {
        level_color = color;
    }

    void SetCar(bool car)
    {
        car_trigger = car;
    }


};

Color WordTriggers::level_color = DARKYELLOW;
bool WordTriggers::car_trigger = false;

class Level2 : public WordTriggers
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

    COORD fields[10] = 
    {
        COORD{}, COORD{}, COORD{}, COORD{}, COORD{},
        COORD{}, COORD{}, COORD{}, COORD{}, COORD{}
    };

    COORD coord_A1{};
    COORD coord_A2{};
    COORD coord_L1{};
    COORD coord_L2{};
    COORD coord_K{};
    COORD coord_E{};
    COORD coord_Y{};
    COORD coord_I1{};
    COORD coord_I2{};
    COORD coord_C{};
    COORD coord_W{};
    COORD coord_R{};
    COORD coord_S{};
    
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

    void Restart()
    {
        system("cls");
        Level2 obj;
        obj.Show();
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

    void CheckWords()
    {
        //Alice
        if (menu_box[fields[0].Y][fields[0].X] == Move_Alphabet::_A | _A1 &&
            menu_box[fields[1].Y][fields[1].X] == Move_Alphabet::_L | _L1 &&
            menu_box[fields[2].Y][fields[2].X] == Move_Alphabet::_I | _I1 &&
            menu_box[fields[3].Y][fields[3].X] == Move_Alphabet::_C &&
            menu_box[fields[4].Y][fields[4].X] == Move_Alphabet::_E)
        { 
            WordTriggers::SetColor(DARKGREEN);
            Sleep(50);
            CreateThread(0, 0, SecretMusic, 0, 0, 0);
            Restart();
        }
        //Car
        else if (menu_box[fields[0].Y][fields[0].X] == Move_Alphabet::_C &&
            menu_box[fields[1].Y][fields[1].X] == Move_Alphabet::_A | _A1 &&
            menu_box[fields[2].Y][fields[2].X] == Move_Alphabet::_R)
        {
            WordTriggers::SetCar(true);
            Sleep(50);
            Restart();
        }
    }

    

public:

    Level2()
    {
        srand(time(0));
        int letters = 13;
        vector<int> randX(letters);
        vector<int> randY(letters);

        for (int i = 0; i < letters; i++)
        {
            randX[i] = 3 + rand() % 35;
        }
        for (int i = 0; i < letters; i++)
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
                    if (car_trigger)
                    {
                        menu_box[y][x] = Border::FAKE_EMPTY;
                    }
                    else
                    {
                        menu_box[y][x] = Door::DOOR;
                    }
                }

                //Letter fields ======================================================================
                //place to put the letters

                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 7)
                {
                    fields[0].Y = StartHEIGHT + 3;
                    fields[0].X = StartWIDTH + 7;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 8)
                {
                    fields[1].Y = StartHEIGHT + 3;
                    fields[1].X = StartWIDTH + 8;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 9)
                {
                    fields[2].Y = StartHEIGHT + 3;
                    fields[2].X = StartWIDTH + 9;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 10)
                {
                    fields[3].Y = StartHEIGHT + 3;
                    fields[3].X = StartWIDTH + 10;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 11)
                {
                    fields[4].Y = StartHEIGHT + 3;
                    fields[4].X = StartWIDTH + 11;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 12)
                {
                    fields[5].Y = StartHEIGHT + 3;
                    fields[5].X = StartWIDTH + 12;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 13)
                {
                    fields[6].Y = StartHEIGHT + 3;
                    fields[6].X = StartWIDTH + 13;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 14)
                {
                    fields[7].Y = StartHEIGHT + 3;
                    fields[7].X = StartWIDTH + 14;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 15)
                {
                    fields[8].Y = StartHEIGHT + 3;
                    fields[8].X = StartWIDTH + 15;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 16)
                {
                    fields[9].Y = StartHEIGHT + 3;
                    fields[9].X = StartWIDTH + 16;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                else if (y == StartHEIGHT + 3 && x == StartWIDTH + 17)
                {
                    fields[10].Y = StartHEIGHT + 3;
                    fields[10].X = StartWIDTH + 17;
                    menu_box[y][x] = LevelBox::LEVEL_LETTER_FIELD;
                }
                

                //Move letters =======================================================================

                else if (y == StartHEIGHT + randY[0] - 1 && x == StartWIDTH + randX[0])
                {
                    coord_A1.X = StartWIDTH + randX[0];
                    coord_A1.Y = StartHEIGHT + randY[0] - 1;
                    menu_box[y][x] = Move_Alphabet::_A;
                }
                else if (y == StartHEIGHT + randY[1] - 1 && x == StartWIDTH + randX[1])
                {
                    coord_A2.X = StartWIDTH + randX[1];
                    coord_A2.Y = StartHEIGHT + randY[1] - 1;
                    menu_box[y][x] = Move_Alphabet::_A1;
                }
                else if (y == StartHEIGHT + randY[2] - 1 && x == StartWIDTH + randX[2])
                {
                    coord_L1.X = StartWIDTH + randX[2];
                    coord_L1.Y = StartHEIGHT + randY[2] - 1;
                    menu_box[y][x] = Move_Alphabet::_L;
                }
                else if (y == StartHEIGHT + randY[3] - 1 && x == StartWIDTH + randX[3])
                {
                    coord_L2.X = StartWIDTH + randX[3];
                    coord_L2.Y = StartHEIGHT + randY[3] - 1;
                    menu_box[y][x] = Move_Alphabet::_L1;
                }
                else if (y == StartHEIGHT + randY[4] - 1 && x == StartWIDTH + randX[4])
                {
                    coord_K.X = StartWIDTH + randX[4];
                    coord_K.Y = StartHEIGHT + randY[4] - 1;
                    menu_box[y][x] = Move_Alphabet::_K;
                }
                else if (y == StartHEIGHT + randY[5] - 1 && x == StartWIDTH + randX[5])
                {
                    coord_E.X = StartWIDTH + randX[5];
                    coord_E.Y = StartHEIGHT + randY[5] - 1;
                    menu_box[y][x] = Move_Alphabet::_E;
                }
                else if (y == StartHEIGHT + randY[6] - 1 && x == StartWIDTH + randX[6])
                {
                    coord_Y.X = StartWIDTH + randX[6];
                    coord_Y.Y = StartHEIGHT + randY[6] - 1;
                    menu_box[y][x] = Move_Alphabet::_Y;
                }
                else if (y == StartHEIGHT + randY[7] - 1 && x == StartWIDTH + randX[7])
                {
                    coord_I1.X = StartWIDTH + randX[7];
                    coord_I1.Y = StartHEIGHT + randY[7] - 1;
                    menu_box[y][x] = Move_Alphabet::_I;
                }
                else if (y == StartHEIGHT + randY[8] - 1 && x == StartWIDTH + randX[8])
                {
                    coord_C.X = StartWIDTH + randX[8];
                    coord_C.Y = StartHEIGHT + randY[8] - 1;
                    menu_box[y][x] = Move_Alphabet::_C;
                }
                else if (y == StartHEIGHT + randY[9] - 1 && x == StartWIDTH + randX[9])
                {
                    coord_W.X = StartWIDTH + randX[9];
                    coord_W.Y = StartHEIGHT + randY[9] - 1;
                    menu_box[y][x] = Move_Alphabet::_W;
                }
                else if (y == StartHEIGHT + randY[10] - 1 && x == StartWIDTH + randX[10])
                {
                    coord_R.X = StartWIDTH + randX[10];
                    coord_R.Y = StartHEIGHT + randY[10] - 1;
                    menu_box[y][x] = Move_Alphabet::_R;
                }
                else if (y == StartHEIGHT + randY[11] - 1 && x == StartWIDTH + randX[11])
                {
                    coord_S.X = StartWIDTH + randX[11];
                    coord_S.Y = StartHEIGHT + randY[11] - 1;
                    menu_box[y][x] = Move_Alphabet::_S;
                }
                else if (y == StartHEIGHT + randY[12] - 1 && x == StartWIDTH + randX[12])
                {
                    coord_I2.X = StartWIDTH + randX[12];
                    coord_I2.Y = StartHEIGHT + randY[12] - 1;
                    menu_box[y][x] = Move_Alphabet::_I1;
                }

                //====================================================================================

                else
                {
                    menu_box[y][x] = Border::EMPTY; // 
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
                case Border::EMPTY: // 
                    cout << (char)Border::EMPTY;
                    break;
                case Border::BORDER_UP_DOWN: // up and down borders
                    SetConsoleTextAttribute(h, GetColor());
                    cout << (char)Border::BORDER_UP_DOWN;
                    break;
                case Border::BORDER_LEFT_RIGHT: // left and right borders
                    SetConsoleTextAttribute(h, GetColor());
                    cout << (char)Border::BORDER_LEFT_RIGHT;
                    break;
                case Border::CORNER_01: // corner 1
                    SetConsoleTextAttribute(h, GetColor());
                    cout << (char)Border::CORNER_01;
                    break;
                case Border::CORNER_02: // corner 2
                    SetConsoleTextAttribute(h, GetColor());
                    cout << (char)Border::CORNER_02;
                    break;
                case Border::CORNER_03: // corner 3
                    SetConsoleTextAttribute(h, GetColor());
                    cout << (char)Border::CORNER_03;
                    break;
                case Border::CORNER_04: // corner 4
                    SetConsoleTextAttribute(h, GetColor());
                    cout << (char)Border::CORNER_04;
                    break;
                case Door::DOOR: // DOOR
                    SetConsoleTextAttribute(h, GRAY);
                    cout << (char)Door::_DOOR;
                    break;
                case Border::FAKE_EMPTY: // fake door
                    SetConsoleTextAttribute(h, GRAY);
                    cout << (char)Door::_DOOR;
                    break;
                case LevelBox::LEVEL_LETTER_FIELD: // place to put the letters
                    SetConsoleTextAttribute(h, RED);
                    cout << (char)LevelBox::LEVEL_LETTER_FIELD;
                    break;
                case Move_Alphabet::_A:
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::A;
                    break;
                case Move_Alphabet::_A1: // A which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::A;
                    break;
                case Move_Alphabet::_L:// L which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::L;
                    break;
                case Move_Alphabet::_L1:// L which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::L;
                    break; 
                case Move_Alphabet::_K: // K which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::K;
                    break;
                case Move_Alphabet::_E: 
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::E;
                    break;
                case Move_Alphabet::_Y: 
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::Y;
                    break;
                case Move_Alphabet::_I: // I which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::I;
                    break;
                case Move_Alphabet::_I1: // I which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::I;
                    break;
                case Move_Alphabet::_C: // C which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::C;
                    break;
                case Move_Alphabet::_W: 
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::W;
                    break;
                case Move_Alphabet::_R: // S which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::R;
                    break;
                case Move_Alphabet::_S: // C which can move
                    SetConsoleTextAttribute(h, WHITE);
                    cout << (char)Static_Alphabet::S;
                    break;
                }
            }
            cout << "\n";
        }
        cout << "\n";

        ShowTxt();

        // Movement ====================================================

        Move player;
        if (car_trigger)
        {
            player = { 22, 15, 6 };
        }
        else
        {
            player = { 2, 15, 6 };
        }
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
                    menu_box[player.GetY() - 1][player.GetX()] != Border::CORNER_01)
                {
                    //it just works !!DO NOT TOUCH!!
                    if (menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Border::BORDER_UP_DOWN ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_A ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_A1 ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_L ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_L1 ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_K ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_E ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_Y ||
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_I || 
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_C || 
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_W || 
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_R || 
                        menu_box[player.GetY() - 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                        menu_box[player.GetY() - 2][player.GetX()] == Move_Alphabet::_S )
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
                        case Move_Alphabet::_A:
                            LetterMove(Static_Alphabet::A, coord_A1, 1, _A);
                            break;
                        case Move_Alphabet::_A1:
                            LetterMove(Static_Alphabet::A, coord_A2, 1, _A1);
                            break;
                        case Move_Alphabet::_L:
                            LetterMove(Static_Alphabet::L, coord_L1, 1, _L);
                            break;
                        case Move_Alphabet::_L1:
                            LetterMove(Static_Alphabet::L, coord_L2, 1, _L1);
                            break;
                        case Move_Alphabet::_K:
                            LetterMove(Static_Alphabet::K, coord_K, 1, _K);
                            break;
                        case Move_Alphabet::_E:
                            LetterMove(Static_Alphabet::E, coord_E, 1, _E);
                            break;
                        case Move_Alphabet::_Y:
                            LetterMove(Static_Alphabet::Y, coord_Y, 1, _Y);
                            break;
                        case Move_Alphabet::_I:
                            LetterMove(Static_Alphabet::I, coord_I1, 1, _I);
                            break;
                        case Move_Alphabet::_I1:
                            LetterMove(Static_Alphabet::I, coord_I2, 1, _I1);
                            break;
                        case Move_Alphabet::_C:
                            LetterMove(Static_Alphabet::C, coord_C, 1, _C);
                            break;
                        case Move_Alphabet::_W:
                            LetterMove(Static_Alphabet::W, coord_W, 1, _W);
                            break;
                        case Move_Alphabet::_R:
                            LetterMove(Static_Alphabet::R, coord_R, 1, _R);
                            break;
                        case Move_Alphabet::_S:
                            LetterMove(Static_Alphabet::S, coord_S, 1, _S);
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
                     if (menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Border::BORDER_UP_DOWN ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_A ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_A1 ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_L ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_L1 ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_K ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_E ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_Y ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_I ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_C ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_W ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_R ||
                         menu_box[player.GetY() + 1][player.GetX()] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY() + 2][player.GetX()] == Move_Alphabet::_S)
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
                         case Move_Alphabet::_A:
                             LetterMove(Static_Alphabet::A, coord_A1, 2, _A);
                             break;
                         case Move_Alphabet::_A1:
                             LetterMove(Static_Alphabet::A, coord_A2, 2, _A1);
                             break;
                         case Move_Alphabet::_L:
                             LetterMove(Static_Alphabet::L, coord_L1, 2, _L);
                             break;
                         case Move_Alphabet::_L1:
                             LetterMove(Static_Alphabet::L, coord_L2, 2, _L1);
                             break;
                         case Move_Alphabet::_K:
                             LetterMove(Static_Alphabet::K, coord_K, 2, _K);
                             break;
                         case Move_Alphabet::_E:
                             LetterMove(Static_Alphabet::E, coord_E, 2, _E);
                             break;
                         case Move_Alphabet::_Y:
                             LetterMove(Static_Alphabet::Y, coord_Y, 2, _Y);
                             break;
                         case Move_Alphabet::_I:
                             LetterMove(Static_Alphabet::I, coord_I1, 2, _I);
                             break;
                         case Move_Alphabet::_I1:
                             LetterMove(Static_Alphabet::I, coord_I2, 2, _I1);
                             break;
                         case Move_Alphabet::_C:
                             LetterMove(Static_Alphabet::C, coord_C, 2, _C);
                             break;
                         case Move_Alphabet::_W:
                             LetterMove(Static_Alphabet::W, coord_W, 2, _W);
                             break;
                         case Move_Alphabet::_R:
                             LetterMove(Static_Alphabet::R, coord_R, 2, _R);
                             break;
                         case Move_Alphabet::_S:
                             LetterMove(Static_Alphabet::S, coord_S, 2, _S);
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
                     if (menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Border::BORDER_LEFT_RIGHT ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Border::CORNER_01 ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Border::CORNER_02 ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Border::CORNER_03 ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Border::CORNER_04 ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_A ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_A1 ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_L ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_L1 ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_K ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_E ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_Y ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_I ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_C ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_W ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_R ||
                         menu_box[player.GetY()][player.GetX() - 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() - 2] == Move_Alphabet::_S)
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
                         case Move_Alphabet::_A:
                             LetterMove(Static_Alphabet::A, coord_A1, 3, _A);
                             break;
                         case Move_Alphabet::_A1:
                             LetterMove(Static_Alphabet::A, coord_A2, 3, _A1);
                             break;
                         case Move_Alphabet::_L:
                             LetterMove(Static_Alphabet::L, coord_L1, 3, _L);
                             break;
                         case Move_Alphabet::_L1:
                             LetterMove(Static_Alphabet::L, coord_L2, 3, _L1);
                             break;
                         case Move_Alphabet::_K:
                             LetterMove(Static_Alphabet::K, coord_K, 3, _K);
                             break;
                         case Move_Alphabet::_E:
                             LetterMove(Static_Alphabet::E, coord_E, 3, _E);
                             break;
                         case Move_Alphabet::_Y:
                             LetterMove(Static_Alphabet::Y, coord_Y, 3, _Y);
                             break;
                         case Move_Alphabet::_I:
                             LetterMove(Static_Alphabet::I, coord_I1, 3, _I);
                             break;
                         case Move_Alphabet::_I1:
                             LetterMove(Static_Alphabet::I, coord_I2, 3, _I1);
                             break;
                         case Move_Alphabet::_C:
                             LetterMove(Static_Alphabet::C, coord_C, 3, _C);
                             break;
                         case Move_Alphabet::_W:
                             LetterMove(Static_Alphabet::W, coord_W, 3, _W);
                             break;
                         case Move_Alphabet::_R:
                             LetterMove(Static_Alphabet::R, coord_R, 3, _R);
                             break;
                         case Move_Alphabet::_S:
                             LetterMove(Static_Alphabet::S, coord_S, 3, _S);
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
                     if (menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Border::BORDER_LEFT_RIGHT ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Border::CORNER_01 ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Border::CORNER_02 ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Border::CORNER_03 ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Border::CORNER_04 ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_A ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_A1 ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_L ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_L1 ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_K ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_E ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_Y ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_I ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_C ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_W ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_R ||
                         menu_box[player.GetY()][player.GetX() + 1] == Move_Alphabet::_A | _A1 | _L | _L1 | _K | _E | _Y | _I | _C | _W | _R | _S &&
                         menu_box[player.GetY()][player.GetX() + 2] == Move_Alphabet::_S)
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
                         case Move_Alphabet::_A:
                             LetterMove(Static_Alphabet::A, coord_A1, 4, _A);
                             break;
                         case Move_Alphabet::_A1:
                             LetterMove(Static_Alphabet::A, coord_A2, 4, _A1);
                             break;
                         case Move_Alphabet::_L:
                             LetterMove(Static_Alphabet::L, coord_L1, 4, _L);
                             break;
                         case Move_Alphabet::_L1:
                             LetterMove(Static_Alphabet::L, coord_L2, 4, _L1);
                             break;
                         case Move_Alphabet::_K:
                             LetterMove(Static_Alphabet::K, coord_K, 4, _K);
                             break;
                         case Move_Alphabet::_E:
                             LetterMove(Static_Alphabet::E, coord_E, 4, _E);
                             break;
                         case Move_Alphabet::_Y:
                             LetterMove(Static_Alphabet::Y, coord_Y, 4, _Y);
                             break;
                         case Move_Alphabet::_I:
                             LetterMove(Static_Alphabet::I, coord_I1, 4, _I);
                             break;
                         case Move_Alphabet::_I1:
                             LetterMove(Static_Alphabet::I, coord_I2, 4, _I1);
                             break;
                         case Move_Alphabet::_C:
                             LetterMove(Static_Alphabet::C, coord_C, 4, _C);
                             break;
                         case Move_Alphabet::_W:
                             LetterMove(Static_Alphabet::W, coord_W, 4, _W);
                             break;
                         case Move_Alphabet::_R:
                             LetterMove(Static_Alphabet::R, coord_R, 4, _R);
                             break;
                         case Move_Alphabet::_S:
                             LetterMove(Static_Alphabet::S, coord_S, 4, _S);
                             break;
                         }
                     }
                }

                //level restart if letter stuck
                else if (code == KeyCode::ENTER)
                {
                    Restart();
                }

                CheckWords();
                

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