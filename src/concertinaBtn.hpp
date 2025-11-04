#ifndef CONCERTINA_BTN_HPP
#define CONCERTINA_BTN_HPP

#include <string>
#include <memory>

#include "raylib.h"
#include "concertinaBtnMap.hpp"
#include "concertinaSoundRenderer.hpp"

class ConcertinaBtn {
private:
    Vector2 highlightAnchor;
    Rectangle bounds;
    Texture2D pushHighlight;
    int pushMidiNoteNr;
    Texture2D pullHighlight;
    int pullMidiNoteNr;
    ConcertinaSoundRenderer& soundRenderer;
    bool _isPressed = false;
public:
    const bool& isPressed = _isPressed;
    ConcertinaBtn(
        const BtnData& btnData,
        int screenWidth, int screenHeight,
        ConcertinaSoundRenderer& soundRenderer);
    ~ConcertinaBtn();
    void drawBtnHighlight(bool isPushing) const;
    void press(bool isPushing);
    void release(bool isPushing);
    bool isTouched(const Vector2 touchPoint) const;
};

#endif