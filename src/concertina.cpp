#include "concertina.hpp"

#include <filesystem>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "helpers.hpp"
#include "concertinaBtnMap.hpp"
#include "keyboardMapping.hpp"

namespace fs = std::filesystem;

const fs::path PULL_HL_PATH = BTN_HLS_PATH / "pull_hl.png";
const fs::path PUSH_HL_PATH = BTN_HLS_PATH / "push_hl.png";
const Rectangle PUSH_PULL_BOUNDS = {424.618,433.585,174.767,110.745};

Concertina::Concertina(int screenWidth, int screenHeight)
{
    float scale;
    std::tie(this->bg, scale) = loadImgToTexture(BG_PATH,
                                                 screenWidth, screenHeight);
    std::tie(this->pullHighlight, std::ignore) = loadImgToTexture(
                                                    PULL_HL_PATH,
                                                    screenWidth,
                                                    screenHeight);
    std::tie(this->pushHighlight, std::ignore) = loadImgToTexture(
                                                    PUSH_HL_PATH,
                                                    screenWidth,
                                                    screenHeight);

    this->pushPullBounds = scaleRect(PUSH_PULL_BOUNDS, scale);

    this->bgAnchor = {0, (screenHeight - this->bg.height) / 2.0f};

    for (const auto& btnId2BtnData : BTN_ID_TO_DATA) {
        this->btns.emplace(std::piecewise_construct,
                           std::forward_as_tuple(btnId2BtnData.first),
                           std::forward_as_tuple(btnId2BtnData.second,
                                                 screenWidth, screenHeight,
                                                 this->soundRenderer));
    }
}

Concertina::~Concertina()
{
    UnloadTexture(this->bg);
}

void Concertina::drawBg() const
{
    DrawTexture(this->bg, this->bgAnchor.x, this->bgAnchor.y, WHITE);
    if (this->isPushing) {
        DrawTexture(
            this->pushHighlight, this->bgAnchor.x, this->bgAnchor.y, WHITE);
    }
    else {
        DrawTexture(
            this->pullHighlight, this->bgAnchor.x, this->bgAnchor.y, WHITE);
    }
}

void Concertina::drawBtnHls() const
{
    for (const auto& [id, btn] : this->btns) {
        if (btn.isPressed) {
            btn.drawBtnHighlight(this->isPushing);
        }
    }
}

void Concertina::updateBtnPressed(KeyboardKey key)
{
    if (this->btnKeysHeld.contains(key)) return;

    if (KEY_TO_BTN.contains(key) && btns.contains(KEY_TO_BTN.at(key))) {
        btns.at(KEY_TO_BTN.at(key)).press(this->isPushing);
        this->btnKeysHeld.insert(key);
    }
}

void Concertina::updateBtnsPressed(const std::vector<Vector2>& touchPoints)
{
    std::unordered_set<KeyboardKey> touchedKeys;
    for (const auto& touchPoint : touchPoints) {
        if (CheckCollisionPointRec(touchPoint, this->pushPullBounds)) {
            touchedKeys.insert(KEY_SPACE);
            continue;
        }

        for (const auto& [id, btn] : this->btns) {
            if (btn.isTouched(touchPoint)) {
                touchedKeys.insert(BTN_TO_KEY.at(id));
            }
        }
    }

    for (auto it = btnKeysHeld.begin(); it != btnKeysHeld.end();) {
        KeyboardKey key = *it;
        if (IsKeyUp(key) && !touchedKeys.contains(key)) {
            btns.at(KEY_TO_BTN.at(key)).release(this->isPushing);
            it = btnKeysHeld.erase(it);
        }
        else {
            it++;
        }
    }

    while (const KeyboardKey key = KeyboardKey(GetKeyPressed())) {
        this->updateBtnPressed(key);
    }

    for (const auto& key : touchedKeys) {
        this->updateBtnPressed(key);
    }

    if (IsKeyDown(KeyboardKey::KEY_SPACE)
        || touchedKeys.contains(KeyboardKey::KEY_SPACE)) {
        if (!this->isPushing) this->changeDirection();
    }
    else {
        if (this->isPushing) this->changeDirection();
    }
}

void Concertina::changeDirection()
{
    this->soundRenderer.allBtnsOff();
    this->isPushing = !this->isPushing;
    for (const auto& key : this->btnKeysHeld) {
        btns.at(KEY_TO_BTN.at(key)).press(this->isPushing);
    }
}
