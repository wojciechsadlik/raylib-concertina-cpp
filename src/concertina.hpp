#ifndef CONCERTINA_HPP
#define CONCERTINA_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "raylib.h"
#include "concertinaBtn.hpp"
#include "concertinaSoundRenderer.hpp"

class Concertina {
private:
    Vector2 bgAnchor;
    Texture2D bg;
    Texture2D pullHighlight;
    Texture2D pushHighlight;
    Rectangle pushPullBounds;
    std::unordered_map<std::string, ConcertinaBtn> btns;
    std::unordered_set<KeyboardKey> btnKeysHeld;
    ConcertinaSoundRenderer soundRenderer;
    bool isPushing = false;
public:
    Concertina(int screenWidth, int screenHeight);
    ~Concertina();
    void drawBg() const;
    void drawBtnHls() const;
    void updateBtnPressed(KeyboardKey key);
    void updateBtnsPressed(const std::vector<Vector2>& touchPoints);
    void changeDirection();
};

#endif