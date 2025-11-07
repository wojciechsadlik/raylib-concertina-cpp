#include <memory>
#include <vector>

#include "raylib.h"

#include "concertina.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define MAX_TOUCH_POINTS 10

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

std::unique_ptr<Concertina> concertina;

void init(void) {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib-concertina");
    InitAudioDevice();
    concertina = std::make_unique<Concertina>(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void close(void) {
    CloseAudioDevice();
    CloseWindow();
}

void updateFrame()
{
    std::vector<Vector2> touchPoints(MAX_TOUCH_POINTS, {0.0, 0.0});
    int touchCnt = GetTouchPointCount();
    for (int i = 0; i < touchCnt; i++) touchPoints[i] = GetTouchPosition(i);

    concertina->updateBtnsPressed(touchPoints);

    BeginDrawing();
        ClearBackground(WHITE);

        concertina->drawBg();
        concertina->drawBtnHls();
    EndDrawing();
}

int main(void) {
    init();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(updateFrame, 60, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        updateFrame();
    }
#endif

    close();
    return 0;
}
