#include "stdio.h"
#include <time.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

int getKeyBoard()
{
    int a = _getch();
    return a;
}

int main(){
    SetConsoleTitleA("行车记录仪测试程序");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD w = {0, 0};
    CONSOLE_CURSOR_INFO cursorInfo = {1, FALSE};
    SetConsoleCursorInfo(hOut, &cursorInfo);

    int i = 0;
    while (1){
        int key = 0;

        if (_kbhit()){
            key = getKeyBoard();
        }

        switch (key) {
            case 'a':
            case 'A':
                ++i;
                break;
        }

        SetConsoleCursorPosition(hOut, w);
        printf("============%d", i);
        printf("============%d", i);
        printf("============%d", i);
        printf("============%d", i);
        printf("============%d", i);
        printf("============%d", i);

        char str[200];
        int i = 0, n;
        n  = sprintf(str, "a = %d, b = %d.", 11, 22);
        i += n;
        n  = sprintf(str, "b = %d, c = %d.", 33, 44);
        i += n;
        n  = sprintf(str, "d = %d, e = %d.", 55, 66);
        i += n;

        Sleep(50);
    }


    return 0;
}