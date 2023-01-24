#ifndef __TETRIS_HELPER_H__
#define __TETRIS_HELPER_H__

/*
 클래스101 개발자 라라
 10년 차 개발자의 [게임 개발/앱 개발/프로그래밍]을 위한 C/C++ 입문
 함께 만드는 코딩 #2- 테트리스 게임 만들기 과제
 */

// 반드시 읽어주세요! 맥 사용자를 위한 주의사항
// 맥 사용자는 wasd 를 통해 코드를 만들지만 실제로는 방향키로 조작하게 됩니다.
// 맥 사용자는 왼쪽 상단의 프로젝트를 클릭하고
// Frameworks And Libraries 에서 Carbon.framework를 추가해야합니다.
// 추가로 Edit Scheme 를 열고 Options > Console > Use Terminal 을 사용해야 합니다.

#include <termios.h>
#include <cstdio>
#include <thread>
#include <Carbon/Carbon.h>

#include "TetrisHelper.h"

bool consoleInitialized = false;
int lastX = 0;
int lastY = 0;

void putStringOnPosition(int x, int y, const char* content) {
    char buff[100] = { 0, };
    sprintf(buff, "\033[%d;%dH", y, x);
    printf("%s", buff);
    printf("%s", content);
    lastX = x;
    lastY = y;
}

void showConsoleCursor(bool showFlag) {
}

void drawPosition(int x, int y, bool filled) {
    if(!consoleInitialized) {
        consoleInitialized = true;
        printf("\033[2J");
    }
    putStringOnPosition(x+1, y, filled ? "■" : "□");
}

Boolean isPressed( unsigned short inKeyCode ){
    unsigned char keyMap[16];
    GetKeys((BigEndianUInt32*) &keyMap);
    putStringOnPosition(lastX, lastY, "         "); // remove arrow input character
    return (0 != ((keyMap[ inKeyCode >> 3] >> (inKeyCode & 7)) & 1));
}

bool keyState(char c) {
    bool ret;
    // keycode from http://web.archive.org/web/20100501161453/http://www.classicteck.com/rbarticles/mackeyboard.php
    switch (c) {
        case 'a': ret = isPressed(123); break;
        case 'd': ret = isPressed(124); break;
        case 's': ret = isPressed(125); break;
        case 'w': ret = isPressed(126); break;
        default: ret = false;
    }
    
    return ret;
}


#endif // !__TETRIS_HELPER_H__
