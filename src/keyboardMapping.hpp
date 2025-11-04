#ifndef KEYBOARD_MAPPING_HPP
#define KEYBOARD_MAPPING_HPP

#include <unordered_map>
#include <string>

#include "raylib.h"

inline const std::unordered_map<KeyboardKey, const std::string> KEY_TO_BTN = {
    {KeyboardKey::KEY_G, "l06"},
    {KeyboardKey::KEY_F, "l07"},
    {KeyboardKey::KEY_D, "l08"}
};

inline const std::unordered_map<std::string, KeyboardKey> BTN_TO_KEY = {
    {"l06", KeyboardKey::KEY_G},
    {"l07", KeyboardKey::KEY_F},
    {"l08", KeyboardKey::KEY_D}
};

#endif