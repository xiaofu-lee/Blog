<!--
{
	"author": "lxf",
	"title": "DFS实现迷宫求解",
	"date": "2019-06-10 04:16:44",
	"category": "数据结构与算法"
}
-->

DFS实现迷宫求解
------------------------------------------------------------
源代码如下
```
#include <math.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MARTIX 10

#define NO_ACCESS 0
#define ACCESS 1
#define ACCESSED -1

using namespace std;

int map[MARTIX][MARTIX] = {
//   0  1  2  3  4  5  6  7  8  9
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
    {0, 0, 1, 0, 1, 1, 1, 1, 1, 0}, // 1
    {0, 1, 0, 0, 1, 0, 1, 0, 1, 0}, // 2
    {0, 1, 1, 1, 1, 0, 0, 1, 1, 0}, // 3
    {0, 1, 0, 0, 1, 1, 1, 1, 0, 0}, // 4
    {0, 1, 1, 1, 0, 1, 0, 1, 1, 0}, // 5
    {0, 1, 0, 1, 1, 1, 0, 0, 1, 0}, // 6
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 0}, // 7
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // 8
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}  // 9
};

enum Direct
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct _POS
{
    int x;
    int y;
} POS;

struct Player
{
    int x;
    int y;
} player;

stack<POS> his_pos_stack;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_GREEN);
    SetConsoleCursorPosition(handle, coord);
}

void gotoEnd()
{
    gotoxy(0, MARTIX + 1);
}

void InitMap(int (*agr)[10])
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            gotoxy(j * 2, i);
            if (agr[i][j] == 1)
            {
                printf("?");
            }
            else
            {
                printf("?");
            }
        }
        printf("\n");
    }
}

void drawPlayer()
{
    gotoxy(player.x * 2, player.y);
    printf("?");
    gotoEnd();
}

void SetPlayerPos(Player *mPlayer, int x, int y)
{
    mPlayer->x = x;
    mPlayer->y = y;
}

int GetPositionStatus(int (*args)[10], int x, int y)
{
    return args[y][x];
}

void SetPositionStatus(int (*args)[10], int x, int y, int status)
{
    args[y][x] = status;
}

void back()
{
    gotoxy(player.x * 2, player.y);
    printf("?");
    gotoEnd();
    his_pos_stack.pop();
    POS last_pos = his_pos_stack.top();
    player.x = last_pos.x;
    player.y = last_pos.y;
    drawPlayer();
}

void go(int x, int y)
{
    gotoxy(player.x * 2, player.y);
    printf("?");
    gotoEnd();
    SetPositionStatus(map, x, y, ACCESSED);
    SetPlayerPos(&player, x, y);
    drawPlayer();
    POS new_pos;
    new_pos.x = x;
    new_pos.y = y;
    his_pos_stack.push(new_pos);
}

void move()
{
    POS last_pos = his_pos_stack.top();
    POS cur_pos[4];
    int length = -1;
    if (GetPositionStatus(map, last_pos.x, last_pos.y - 1) == ACCESS)
    {
        cur_pos[++length].x = last_pos.x;
        cur_pos[length].y = last_pos.y - 1;
    }
    if (GetPositionStatus(map, last_pos.x, last_pos.y + 1) == ACCESS)
    {
        cur_pos[++length].x = last_pos.x;
        cur_pos[length].y = last_pos.y + 1;
    }
    if (GetPositionStatus(map, last_pos.x - 1, last_pos.y) == ACCESS)
    {
        cur_pos[++length].x = last_pos.x - 1;
        cur_pos[length].y = last_pos.y;
    }
    if (GetPositionStatus(map, last_pos.x + 1, last_pos.y) == ACCESS)
    {
        cur_pos[++length].x = last_pos.x + 1;
        cur_pos[length].y = last_pos.y;
    }
    if (length > -1)
    {
        int index = rand() % (length + 1);
        go(cur_pos[index].x, cur_pos[index].y);
    }
    else
    {
        back();
    }
}

void InitPos(int x, int y)
{
    SetPlayerPos(&player, x, y);
    SetPositionStatus(map, x, y, ACCESSED);
    POS init_pos;
    init_pos.x = x;
    init_pos.y = x;
    his_pos_stack.push(init_pos);
}

void init()
{
    InitMap(map);
    InitPos(1, 1);
    drawPlayer();
}

int main(int argc, char const *argv[])
{
    srand((unsigned int)time(NULL));
    init();
    while (1)
    {
        Sleep(1000);
        move();
        if (player.x == 8 && player.y == 9)
        {
            printf("winer\n");
            break;
        }
    }
	system("pause");
    return 0;
}

```
------------------------------------------------------------
[返回上级目录](./../../../../categories/数据结构与算法/README.md)  |
[返回首页](./../../../../README.md)