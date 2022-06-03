
#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
using namespace std;

enum TCell : char
{
    CROSS = 'X',
    ZERO = 'O',
    EMPTY = '_'
};

enum TProgress
{
    IN_PROGRESS,
    WON_HUMAN,
    WON_AI,
    DRAW
};

struct TCoord //координаты
{
    size_t y;
    size_t x;
};

struct TGame
{
    TCell** ppField{ nullptr };
    const size_t size{ 5 }; //5x5
    TCell human{ CROSS };
    TCell ai{ ZERO };
    size_t turn{ 0 }; //ход четные-человек, нечетные-компьютер
    TProgress progress{ IN_PROGRESS };
};

//=============================================================================

inline void clearScr()
{
    cout << "\x1B[2J\x1B[H";
}

int32_t __fastcall getRandomNum(int32_t min, int32_t max)
{
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}

//=============================================================================

void __fastcall initGame(TGame& g)
{
    g.ppField = new TCell * [g.size];
    for (size_t i = 0; i < g.size; i++)
    {
        g.ppField[i] = new TCell[g.size];
    }
    for (size_t y = 0; y < g.size; y++)
    {
        for (size_t x = 0; x < g.size; x++)
        {
            g.ppField[y][x] = EMPTY;
        }
    }
    if (getRandomNum(0, 1000) > 500)
    {
        g.human = CROSS;
        g.ai = ZERO;
        g.turn = 0;
    }
    else
    {
        g.human = ZERO;
        g.ai = CROSS;
        g.turn = 1;
    }

}

void __fastcall deinitGame(TGame& g)
{
    for (size_t i = 0; i < g.size; i++)
    {
        delete[] g.ppField[i];
    }
    delete[] g.ppField;
    g.ppField = nullptr;
}

void __fastcall printGame(const TGame& g)
{
    cout << "     ";
    for (size_t x = 0; x < g.size; x++)
        cout << x + 1 << "   ";
    cout << endl;
    for (size_t y = 0; y < g.size; y++)
    {
        cout << " " << y + 1 << " | ";
        for (size_t x = 0; x < g.size; x++)
        {
            cout << g.ppField[y][x] << " | ";
        }
        cout << endl;
    }
    cout << endl << "Human: " << g.human << endl << "Computer: " << g.ai << endl << endl;
}


TProgress __fastcall getWon(const TGame& g)
{   
    //выигрыш в строках
    for (size_t y = 0; y < g.size; y++) 
    {
        if (g.ppField[y][0] == g.ppField[y][1] && g.ppField[y][0] == g.ppField[y][2] && g.ppField[y][0] == g.ppField[y][3] && g.ppField[y][0] == g.ppField[y][4])
        {
            if (g.ppField[y][0] == g.human)
                return WON_HUMAN;

            if (g.ppField[y][0] == g.ai)
                return WON_AI;
        }
    }
    //выигрыш в столбцах
    for (size_t x = 0; x < g.size; x++)  
    {
        if (g.ppField[0][x] == g.ppField[1][x] && g.ppField[1][x] == g.ppField[2][x] && g.ppField[1][x] == g.ppField[3][x] && g.ppField[1][x] == g.ppField[4][x])
        {
            if (g.ppField[0][x] == g.human)
                return WON_HUMAN;

            if (g.ppField[0][x] == g.ai)
                return WON_AI;

        }
    }
    //диагональ 5x5
    if (g.ppField[0][0] == g.ppField[1][1] && g.ppField[0][0] == g.ppField[2][2] && g.ppField[0][0] == g.ppField[3][3] && g.ppField[0][0] == g.ppField[4][4]) 
    {
        if (g.ppField[0][0] == g.human)
            return WON_HUMAN;

        if (g.ppField[0][0] == g.ai)
            return WON_AI;

    }
    //диагональ 5x5
    if (g.ppField[4][0] == g.ppField[3][1] && g.ppField[3][1] == g.ppField[2][2] && g.ppField[2][2] == g.ppField[1][3] && g.ppField[1][3] == g.ppField[0][4])
    {
        if (g.ppField[4][0] == g.human)
            return WON_HUMAN;

        if (g.ppField[4][0] == g.ai)
            return WON_AI;

    }
    //проверка ничья
    bool draw{ true }; 
    for (size_t y = 0; y < g.size; y++)
    {
        for (size_t x = 0; x < g.size; x++)
        {
            if (g.ppField[y][x] == EMPTY)
            {
                draw = false;
                break;
            }
        }
        if (!draw)
            break;
    }
    if (draw)
        return DRAW;

    return IN_PROGRESS;
}


TCoord __fastcall getHumanCoord(const TGame& g)
{
    TCoord c{};
    do {
        cout << "Enter X (1...5): ";
        cin >> c.x;
        cout << "Enter Y (1...5): ";
        cin >> c.y;
        c.x--;
        c.y--;
    } while (c.x > 4 || c.y > 4 || g.ppField[c.y][c.x] != EMPTY);

    return c;
}


TCoord __fastcall getAICoord(TGame& g)
{
    // предвыигрышная
    for (size_t y = 0; y < g.size; y++)
    {
        for (size_t x = 0; x < g.size; x++)
        {
            if (g.ppField[y][x] == EMPTY)
            {
                g.ppField[y][x] = g.ai;
                if (getWon(g) == WON_AI)
                {
                    g.ppField[y][x] = EMPTY;
                    return { y, x };
                }
                g.ppField[y][x] = EMPTY;
            }
        }
    }
    // предпроирышная
    for (size_t y = 0; y < g.size; y++)
    {
        for (size_t x = 0; x < g.size; x++)
        {
            if (g.ppField[y][x] == EMPTY)
            {
                g.ppField[y][x] = g.human;
                if (getWon(g) == WON_HUMAN)
                {
                    g.ppField[y][x] = EMPTY;
                    return { y, x };
                }
                g.ppField[y][x] = EMPTY;
            }
        }
    }

    //центр
    if (g.ppField[2][2] == EMPTY)
    {
        return { 2, 2 };
    }

    //углы
    TCoord buf[4]{};
    size_t num{ 0 };
    if (g.ppField[0][0] == EMPTY)
    {
        buf[num] = { 0, 0 };
        num++;
    }
    if (g.ppField[0][4] == EMPTY)
    {
        buf[num] = { 0, 4 };
        num++;
    }
    if (g.ppField[4][0] == EMPTY)
    {
        buf[num] = { 4, 0 };
        num++;
    }
    if (g.ppField[4][4] == EMPTY)
    {
        buf[num] = { 4, 4 };
        num++;
    }
    if (num > 0)
    {
        const unsigned index = rand() % num;
        return buf[index];
    }
    num = 0;


    // рандомайз по полю, внутренние углы матрицы 3x3 из 5х5
    if (g.ppField[1][1] == EMPTY)
    {
         buf[num] = { 1, 1 };
         num++;
    }
    if (g.ppField[1][3] == EMPTY)
    {
         buf[num] = { 1, 3 };
         num++;
    }
    if (g.ppField[3][1] == EMPTY)
    {
         buf[num] = { 3, 1 };
         num++;
    }
    if (g.ppField[3][3] == EMPTY)
    {
         buf[num] = { 3, 3 };
         num++;
    }
    if (num > 0)
    {
         const unsigned index = rand() % num;
         return buf[index];
    }
    num = 0;

    // заполнение по строкам AI если в строке нет элементов HUMAN          
    // 1 строка
    if (g.ppField[0][0] != g.human && g.ppField[0][1] != g.human && g.ppField[0][2] != g.human && g.ppField[0][3] != g.human && g.ppField[0][4] != g.human)
    {
         if (g.ppField[0][1] == EMPTY) 
         {
             buf[num] = { 0, 1 };
             num++;
         }
         if (g.ppField[0][2] == EMPTY)
         {
             buf[num] = { 0, 2 };
             num++;
         }
         if (g.ppField[0][3] == EMPTY)
         {
             buf[num] = { 0, 3 };
             num++;
         }
         if (num > 0)
         {
             const unsigned index = rand() % num;
             return buf[index];
         }
    }
    num = 0;
    // 2 строка
    if (g.ppField[1][0] != g.human && g.ppField[1][1] != g.human && g.ppField[1][2] != g.human && g.ppField[1][3] != g.human && g.ppField[1][4] != g.human)
    {
         if (g.ppField[1][0] == EMPTY)
         {
             buf[num] = { 1, 0 };
             num++;
         }
         if (g.ppField[1][2] == EMPTY)
         {
             buf[num] = { 1, 2 };
             num++;
         }
         if (g.ppField[1][4] == EMPTY)
         {
             buf[num] = { 1, 4 };
             num++;
         }
         if (num > 0)
         {
             const unsigned index = rand() % num;
             return buf[index];
         }
    }
    num = 0;
    // 3 строка
    if (g.ppField[2][0] != g.human && g.ppField[2][1] != g.human && g.ppField[2][2] != g.human && g.ppField[2][3] != g.human && g.ppField[2][4] != g.human)
    {
        if (g.ppField[2][0] == EMPTY)
        {
            buf[num] = { 2, 0 };
            num++;
        }
        if (g.ppField[2][1] == EMPTY)
        {
            buf[num] = { 2, 1 };
            num++;
        }
        if (g.ppField[2][3] == EMPTY)
        {
            buf[num] = { 2, 3 };
            num++;
        }
        if (g.ppField[2][4] == EMPTY)
        {
            buf[num] = { 2, 4 };
            num++;
        }
        if (num > 0)
        {
            const unsigned index = rand() % num;
            return buf[index];
        }
    }
    num = 0;
    // 4 строка
    if (g.ppField[3][0] != g.human && g.ppField[3][1] != g.human && g.ppField[3][2] != g.human && g.ppField[3][3] != g.human && g.ppField[3][4] != g.human)
    {
        if (g.ppField[3][0] == EMPTY)
        {
            buf[num] = { 3, 0 };
            num++;
        }
        if (g.ppField[3][2] == EMPTY)
        {
            buf[num] = { 3, 2 };
            num++;
        }
        if (g.ppField[3][4] == EMPTY)
        {
            buf[num] = { 3, 4 };
            num++;
        }
        if (num > 0)
        {
            const unsigned index = rand() % num;
            return buf[index];
        }
    }
    num = 0;
    // 5 строка
    if (g.ppField[4][0] != g.human && g.ppField[4][1] != g.human && g.ppField[4][2] != g.human && g.ppField[4][3] != g.human && g.ppField[4][4] != g.human)
    {
        if (g.ppField[4][1] == EMPTY)
        {
            buf[num] = { 4, 1 };
            num++;
        }
        if (g.ppField[4][2] == EMPTY)
        {
            buf[num] = { 4, 2 };
            num++;
        }
        if (g.ppField[4][3] == EMPTY)
        {
            buf[num] = { 4, 3 };
            num++;
        }
        if (num > 0)
        {
            const unsigned index = rand() % num;
            return buf[index];
        }
    }
    num = 0;

    // заполнение по столбцам AI если в столбце нет элементов HUMAN
    // 1 столбец
    if (g.ppField[0][0] != g.human && g.ppField[1][0] != g.human && g.ppField[2][0] != g.human && g.ppField[3][0] != g.human && g.ppField[4][0] != g.human)
    {
        if (g.ppField[1][0] == EMPTY)
        {
            buf[num] = { 1, 1 };
            num++;
        }
        if (g.ppField[2][0] == EMPTY)
        {
            buf[num] = { 2, 0 };
            num++;
        }
        if (g.ppField[3][0] == EMPTY)
        {
            buf[num] = { 3, 0 };
            num++;
        }
        if (num > 0)
        {
            const unsigned index = rand() % num;
            return buf[index];
        }
    }
    num = 0;
    // 2 столбец
    if (g.ppField[0][1] != g.human && g.ppField[1][1] != g.human && g.ppField[2][1] != g.human && g.ppField[3][1] != g.human && g.ppField[4][1] != g.human)
    {
        if (g.ppField[0][1] == EMPTY)
        {
            buf[num] = { 0, 1 };
            num++;
        }
        if (g.ppField[2][1] == EMPTY)
        {
            buf[num] = { 2, 1 };
            num++;
        }
        if (g.ppField[4][1] == EMPTY)
        {
            buf[num] = { 4, 1 };
            num++;
        }
        if (num > 0)
        {
            const unsigned index = rand() % num;
            return buf[index];
        }
    }
    num = 0;
    // 3 столбец
    if (g.ppField[0][2] != g.human && g.ppField[1][2] != g.human && g.ppField[2][2] != g.human && g.ppField[3][2] != g.human && g.ppField[4][2] != g.human)
    {
        if (g.ppField[0][2] == EMPTY)
        {
            buf[num] = { 0, 2 };
            num++;
        }
        if (g.ppField[1][2] == EMPTY)
        {
            buf[num] = { 1, 2 };
            num++;
        }
        if (g.ppField[3][2] == EMPTY)
        {
            buf[num] = { 3, 2 };
            num++;
        }
        if (g.ppField[4][2] == EMPTY)
        {
            buf[num] = { 4, 2 };
            num++;
        }
        if (num > 0)
        {
            const unsigned index = rand() % num;
            return buf[index];
        }
    }
    num = 0;
    // 4 столбец
    if (g.ppField[0][3] != g.human && g.ppField[1][3] != g.human && g.ppField[2][3] != g.human && g.ppField[3][3] != g.human && g.ppField[4][3] != g.human)
    {
        if (g.ppField[0][3] == EMPTY)
        {
            buf[num] = { 0, 3 };
            num++;
        }
        if (g.ppField[2][3] == EMPTY)
        {
            buf[num] = { 2, 3 };
            num++;
        }
        if (g.ppField[4][3] == EMPTY)
        {
            buf[num] = { 4, 3 };
            num++;
        }
        if (num > 0)
        {
            const unsigned index = rand() % num;
            return buf[index];
        }
    }
    // 5 столбец
    if (g.ppField[0][4] != g.human && g.ppField[1][4] != g.human && g.ppField[2][4] != g.human && g.ppField[3][4] != g.human && g.ppField[4][4] != g.human)
    {
        if (g.ppField[1][4] == EMPTY)
        {
            buf[num] = { 1, 4 };
            num++;
        }
        if (g.ppField[2][4] == EMPTY)
        {
            buf[num] = { 2, 4 };
            num++;
        }
        if (g.ppField[3][4] == EMPTY)
        {
            buf[num] = { 3, 4 };
            num++;
        }
        if (num > 0)
        {
            const unsigned index = rand() % num;
            return buf[index];
        }
    }
    
    TProgress progress = DRAW;
    num = 0;
         
            //рандомайз по полю, оставшиеся элементы, нерезультативные ходы до заполнения поля (наступления DRAW)
            TCoord buf4[16];
            size_t num4{ 0 };

            if (g.ppField[0][1] == EMPTY)
            {
                buf4[num4] = { 0, 1 };
                num4++;
            }
            if (g.ppField[0][2] == EMPTY)
            {
                buf4[num4] = { 0, 2 };
                num4++;
            }
            if (g.ppField[0][3] == EMPTY)
            {
                buf4[num4] = { 0, 3 };
                num4++;
            }
            if (g.ppField[1][0] == EMPTY)
            {
                buf4[num4] = { 1, 0 };
                num4++;
            }
            if (g.ppField[1][2] == EMPTY)
            {
                buf4[num4] = { 1, 2 };
                num4++;
            }
            if (g.ppField[1][4] == EMPTY)
            {
                buf4[num4] = { 1, 4 };
                num4++;
            }
            if (g.ppField[2][0] == EMPTY)
            {
                buf4[num4] = { 2, 0 };
                num4++;
            }
            if (g.ppField[2][1] == EMPTY)
            {
                buf4[num4] = { 2, 1 };
                num4++;
            }
            if (g.ppField[2][3] == EMPTY)
            {
                buf4[num4] = { 2, 3 };
                num4++;
            }
            if (g.ppField[2][4] == EMPTY)
            {
                buf4[num4] = { 2, 4 };
                num4++;
            }
            if (g.ppField[3][0] == EMPTY)
            {
                buf4[num4] = { 3, 0 };
                num4++;
            }
            if (g.ppField[3][2] == EMPTY)
            {
                buf4[num4] = { 3, 2 };
                num4++;
            }
            if (g.ppField[3][4] == EMPTY)
            {
                buf4[num4] = { 3, 4 };
                num4++;
            }
            if (g.ppField[4][1] == EMPTY)
            {
                buf4[num4] = { 4, 1 };
                num4++;
            }
            if (g.ppField[4][2] == EMPTY)
            {
                buf4[num4] = { 4, 2 };
                num4++;
            }
            if (g.ppField[4][3] == EMPTY)
            {
                buf4[num4] = { 4, 3 };
                num4++;
            }
            if (num4 > 0)
            {
                const unsigned index = rand() % num4;
                return buf4[index];
            }
}




    inline void Congrats(const TGame & g)
    {
        if (g.progress == WON_HUMAN)
            cout << "Human won!" << endl;
        else if (g.progress == WON_AI)
            cout << "Computer won!" << endl;
        else if (g.progress == DRAW)
            cout << "Draw!" << endl;
    }

    //=============================================================================

    int main()
    {
        TGame g;
        initGame(g);
        clearScr();
        printGame(g);

        do
        {
            if (g.turn % 2 == 0)
            {
                TCoord c = getHumanCoord(g);
                g.ppField[c.y][c.x] = g.human;
            }
            else
            {
                TCoord c = getAICoord(g);
                g.ppField[c.y][c.x] = g.ai;
            }

            clearScr();
            printGame(g);
            g.turn++;
            g.progress = getWon(g);

        } while (g.progress == IN_PROGRESS);

        Congrats(g);
        deinitGame(g);
    }
