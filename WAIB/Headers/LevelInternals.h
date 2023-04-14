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
    static bool clear_trigger;
    static bool key;
    static bool wall_trigger;

    Color GetColor()
    {
        return level_color;
    }

    void SetColor(Color color)
    {
        level_color = color;
    }

    void SetCar(bool trigger)
    {
        car_trigger = trigger;
    }

    void Clear(bool trigger)
    {
        clear_trigger = trigger;
    }

    void SetKey(bool trigger)
    {
        key = trigger;
    }

    void SetKeyS(bool trigger)
    {
        keys = trigger;
    }

    void SetWall(bool trigger)
    {
        wall_trigger = trigger;
    }

};


Color WordTriggers::level_color = DARKYELLOW;
bool WordTriggers::car_trigger = false;
bool WordTriggers::clear_trigger = false;
bool WordTriggers::key = false;
bool WordTriggers::wall_trigger = false;

class LevelInternals : public WordTriggers
{
protected:
    static const int WIDTH = 60;
    static const int HEIGHT = 18;

    static const int StartWIDTH = 10;
    static const int StartHEIGHT = 3;

    static const int EndWIDTH = WIDTH - 1;
    static const int EndHEIGHT = HEIGHT - 1;

    int menu_box[HEIGHT][WIDTH] = {};

    HANDLE h;

    bool finish;

    COORD fields[11] =
    {
        COORD{}, COORD{}, COORD{}, COORD{}, COORD{},
        COORD{}, COORD{}, COORD{}, COORD{}, COORD{},
        COORD{}
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

    COORD coord_KEY{};
    COORD coord_KEY2{};

    COORD txt{};

    void ShowTxt()
    {
        if (!WordTriggers::clear_trigger)
        {
            txt.Y = EndHEIGHT + 3;
            txt.X = 10;
            SetConsoleTextAttribute(h, CYAN);
            SetConsoleCursorPosition(h, txt);

            string info = "Press ENTER to restart";
            for (int i = 0; i < info.length(); i++)
            {
                Sleep(20);
                cout << info[i];
            }
        }
        else
        {
            txt.Y = EndHEIGHT;
            txt.X = 10;
            SetConsoleTextAttribute(h, CYAN);
            SetConsoleCursorPosition(h, txt);

            string txt1 = "Well...";
            for (int i = 0; i < txt1.length(); i++)
            {
                Sleep(20);
                cout << txt1[i];
            }
            Sleep(1000);
            string txt2 = "I didn`t expect this";
            for (int i = 0; i < txt2.length(); i++)
            {
                Sleep(20);
                cout << txt2[i];
            }

            Sleep(1000);
            txt.Y = 8;
            txt.X = 60;
            SetConsoleTextAttribute(h, GREEN);
            SetConsoleCursorPosition(h, txt);
            cout << (char)16 << (char)16;
        }
    }



    virtual void Restart()
    {
        system("cls");
        LevelInternals obj;
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

    void LetterMove(char ch, COORD& letter, int direction, Move_Alphabet move_char, Color color)
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
        SetConsoleTextAttribute(h, color);
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
        //Clear
        else if (menu_box[fields[0].Y][fields[0].X] == Move_Alphabet::_C &&
            menu_box[fields[1].Y][fields[1].X] == Move_Alphabet::_L | _L1 &&
            menu_box[fields[2].Y][fields[2].X] == Move_Alphabet::_E &&
            menu_box[fields[3].Y][fields[3].X] == Move_Alphabet::_A | _A1 &&
            menu_box[fields[4].Y][fields[4].X] == Move_Alphabet::_R)
        {
            WordTriggers::Clear(true);
            Sleep(50);
            Restart();
        }
        //Key
        else if (menu_box[fields[0].Y][fields[0].X] == Move_Alphabet::_K &&
            menu_box[fields[1].Y][fields[1].X] == Move_Alphabet::_E &&
            menu_box[fields[2].Y][fields[2].X] == Move_Alphabet::_Y)
        {
            WordTriggers::SetKey(true);
            Sleep(50);
            Restart();
        }
        //Air (do nothing)
        else if (menu_box[fields[0].Y][fields[0].X] == Move_Alphabet::_A | _A1 &&
            menu_box[fields[1].Y][fields[1].X] == Move_Alphabet::_I | _I1 &&
            menu_box[fields[2].Y][fields[2].X] == Move_Alphabet::_R)
        {
            Sleep(50);
            Restart();
        }
        //Wall is air
        else if (menu_box[fields[0].Y][fields[0].X] == Move_Alphabet::_W &&
            menu_box[fields[1].Y][fields[1].X] == Move_Alphabet::_A | _A1 &&
            menu_box[fields[2].Y][fields[2].X] == Move_Alphabet::_L | _L1 &&
            menu_box[fields[2].Y][fields[3].X] == Move_Alphabet::_L | _L1 &&
            menu_box[fields[4].Y][fields[5].X] == Move_Alphabet::_I | _I1 &&
            menu_box[fields[5].Y][fields[6].X] == Move_Alphabet::_S &&
            menu_box[fields[7].Y][fields[8].X] == Move_Alphabet::_A | _A1 &&
            menu_box[fields[8].Y][fields[9].X] == Move_Alphabet::_I | _I1 &&
            menu_box[fields[9].Y][fields[10].X] == Move_Alphabet::_R)
        {
            WordTriggers::SetWall(true);
            Sleep(50);
            Restart();
        }
    }

public:
    virtual void Show() {};
};

