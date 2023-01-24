#include "main.h"

#define INTERVAL 1.0/60.0

int main(){
    srand(time(0));
    float prev = (float)clock() / CLOCKS_PER_SEC;
    Display* display = new Display();
    GameEngine* gameEngine = new GameEngine();
    gameEngine->init();
    
    showConsoleCursor(false);
    
    while(true) {
        float curr = (float)clock() / CLOCKS_PER_SEC;
        float dt = curr - prev; // delta time
        
        if ( dt < INTERVAL ) continue;
        prev = curr;
        
        bool left = keyState('a');
        bool right = keyState('d');
        bool down = keyState('s');
        if (left){
            //왼쪽으로 블록 이동
            gameEngine->next(dt, 'a');
        }
        else if (right) {
            gameEngine->next(dt, 'd');
        }
        else if (down) {
            gameEngine->next(dt, 's');
        }
        else {
            //블록 떨어지기
            gameEngine->next(dt, 0);
        }
        
        gameEngine->next(dt, 0);
        
        //화면 출력
        gameEngine->makeDisplayData();
        display->draw();
        //게임 상태 판별
        
        if(gameEngine->state == GameEngine::GameState::GAMEOVER){
            break;
        }
    }
    
    return 0;
}
