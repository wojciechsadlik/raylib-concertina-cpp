#include <memory>
#include <vector>

extern "C" {
#include "raylib.h"
}

#include "concertina.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define MAX_TOUCH_POINTS 10

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

static const double FRAME_LENGTH = 1.0 / 60.0;
static double lastFrameT = 0.0;

std::unique_ptr<Concertina> concertina;

void init(void) {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib-concertina");
    InitAudioDevice();
    lastFrameT = GetTime();
    concertina = std::make_unique<Concertina>(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void close(void) {
    CloseAudioDevice();
    CloseWindow();
}

void gameLoop()
{
    std::vector<Vector2> touchPoints(MAX_TOUCH_POINTS, {0.0, 0.0});
    int touchCnt = GetTouchPointCount();
    for (int i = 0; i < touchCnt; i++) touchPoints[i] = GetTouchPosition(i);

    concertina->updateBtnsPressed(touchPoints);

    double currT = GetTime();
    if (currT - lastFrameT < FRAME_LENGTH) return;
    lastFrameT = currT;

    BeginDrawing();
        ClearBackground(WHITE);

        concertina->drawBg();
        concertina->drawBtnHls();
    EndDrawing();
}

int main(void) {
    init();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(gameLoop, 0, 1);
#else
    while (!WindowShouldClose()) {
        gameLoop();
    }
#endif

    close();
    return 0;
}
