#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <filesystem>
#include <algorithm>
#include <tuple>

#include "raylib.h"

namespace fs = std::filesystem;

const fs::path BG_PATH = "assets/concertina_bg/concertina_layout.png";
const fs::path BTN_HLS_PATH = "assets/concertina_btn_hls";
const fs::path BTN_PS_HLS_PATH = BTN_HLS_PATH / "ps";
const fs::path BTN_PL_HLS_PATH = BTN_HLS_PATH / "pl";

inline Rectangle scaleRect(const Rectangle& rect, float scale)
{
    return {
        rect.x * scale,
        rect.y * scale,
        rect.width * scale,
        rect.height * scale
    };
}

inline std::tuple<Texture2D, float> loadImgToTexture(
    fs::path path,
    int screenWidth,
    int screenHeight)
{
    std::string pathStr = path.string();
    auto img = LoadImage(pathStr.c_str());

    float scale = std::min(
        screenWidth / (float)img.width,
        screenHeight / (float)img.height);
    ImageResize(&img, img.width * scale, img.height * scale);

    Texture2D texture = LoadTextureFromImage(img);

    UnloadImage(img);
    return {texture, scale};
}

#endif