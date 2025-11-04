#include "concertinaBtn.hpp"

#include <string>
#include <filesystem>

#include "helpers.hpp"

namespace fs = std::filesystem;

ConcertinaBtn::ConcertinaBtn(
    const BtnData& btnData,
    int screenWidth, int screenHeight,
    ConcertinaSoundRenderer& soundRenderer
) : soundRenderer(soundRenderer)
{
    fs::path pullHlPath = BTN_PL_HLS_PATH / (btnData.id + ".png");
    fs::path pushHlPath = BTN_PS_HLS_PATH / (btnData.id + ".png");
    float scale;
    std::tie(this->pullHighlight, scale) = loadImgToTexture(
        pullHlPath, screenWidth, screenHeight);
    std::tie(this->pushHighlight, std::ignore) = loadImgToTexture(
        pushHlPath, screenWidth, screenHeight);

    this->bounds = scaleRect(btnData.bounds, scale);

    this->highlightAnchor = {
        0,
        (screenHeight - this->pullHighlight.height) / 2.0f
    };

    this->pullMidiNoteNr = btnData.pullMidiNoteNr;
    this->pushMidiNoteNr = btnData.pushMidiNoteNr;
}

ConcertinaBtn::~ConcertinaBtn()
{
    UnloadTexture(this->pullHighlight);
    UnloadTexture(this->pushHighlight);
}

void ConcertinaBtn::drawBtnHighlight(bool isPushing) const
{
    if (isPushing) {
        DrawTexture(this->pushHighlight,
            this->highlightAnchor.x, this->highlightAnchor.y, WHITE);
    }
    else {
        DrawTexture(this->pullHighlight,
            this->highlightAnchor.x, this->highlightAnchor.y, WHITE);
    }
}

void ConcertinaBtn::press(bool isPushing)
{
    if (isPushing) {
        this->soundRenderer.btnOn(this->pushMidiNoteNr);
    }
    else {  
        this->soundRenderer.btnOn(this->pullMidiNoteNr);
    }
    this->_isPressed = true;
}

void ConcertinaBtn::release(bool isPushing)
{
    if (isPushing) {
        this->soundRenderer.btnOff(this->pushMidiNoteNr);
    }
    else {  
        this->soundRenderer.btnOff(this->pullMidiNoteNr);
    }
    this->_isPressed = false;
}

bool ConcertinaBtn::isTouched(const Vector2 touchPoint) const
{
    return CheckCollisionPointRec(touchPoint, this->bounds);
}
