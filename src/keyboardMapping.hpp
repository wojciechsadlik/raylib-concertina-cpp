#ifndef KEYBOARD_MAPPING_HPP
#define KEYBOARD_MAPPING_HPP

#include <unordered_map>
#include <string>

#include "raylib.h"

inline const std::unordered_map<KeyboardKey, const std::string> KEY_TO_BTN = {
    {KeyboardKey::KEY_T, "l01"},
    {KeyboardKey::KEY_R, "l02"},
    {KeyboardKey::KEY_E, "l03"},
    {KeyboardKey::KEY_W, "l04"},
    {KeyboardKey::KEY_Q, "l05"},
    {KeyboardKey::KEY_G, "l06"},
    {KeyboardKey::KEY_F, "l07"},
    {KeyboardKey::KEY_D, "l08"},
    {KeyboardKey::KEY_S, "l09"},
    {KeyboardKey::KEY_A, "l10"},
    {KeyboardKey::KEY_B, "l11"},
    {KeyboardKey::KEY_V, "l12"},
    {KeyboardKey::KEY_C, "l13"},
    {KeyboardKey::KEY_X, "l14"},
    {KeyboardKey::KEY_Z, "l15"},
    {KeyboardKey::KEY_U, "r01"},
    {KeyboardKey::KEY_I, "r02"},
    {KeyboardKey::KEY_O, "r03"},
    {KeyboardKey::KEY_P, "r04"},
    {KeyboardKey::KEY_LEFT_BRACKET, "r05"},
    {KeyboardKey::KEY_J, "r06"},
    {KeyboardKey::KEY_K, "r07"},
    {KeyboardKey::KEY_L, "r08"},
    {KeyboardKey::KEY_SEMICOLON, "r09"},
    {KeyboardKey::KEY_APOSTROPHE, "r10"},
    {KeyboardKey::KEY_N, "r11"},
    {KeyboardKey::KEY_M, "r12"},
    {KeyboardKey::KEY_COMMA, "r13"},
    {KeyboardKey::KEY_PERIOD, "r14"},
    {KeyboardKey::KEY_SLASH, "r15"}
};

inline const std::unordered_map<std::string, KeyboardKey> BTN_TO_KEY = {
    {"l01", KeyboardKey::KEY_T},
    {"l02", KeyboardKey::KEY_R},
    {"l03", KeyboardKey::KEY_E},
    {"l04", KeyboardKey::KEY_W},
    {"l05", KeyboardKey::KEY_Q},
    {"l06", KeyboardKey::KEY_G},
    {"l07", KeyboardKey::KEY_F},
    {"l08", KeyboardKey::KEY_D},
    {"l09", KeyboardKey::KEY_S},
    {"l10", KeyboardKey::KEY_A},
    {"l11", KeyboardKey::KEY_B},
    {"l12", KeyboardKey::KEY_V},
    {"l13", KeyboardKey::KEY_C},
    {"l14", KeyboardKey::KEY_X},
    {"l15", KeyboardKey::KEY_Z},
    {"r01", KeyboardKey::KEY_U},
    {"r02", KeyboardKey::KEY_I},
    {"r03", KeyboardKey::KEY_O},
    {"r04", KeyboardKey::KEY_P},
    {"r05", KeyboardKey::KEY_LEFT_BRACKET},
    {"r06", KeyboardKey::KEY_J},
    {"r07", KeyboardKey::KEY_K},
    {"r08", KeyboardKey::KEY_L},
    {"r09", KeyboardKey::KEY_SEMICOLON},
    {"r10", KeyboardKey::KEY_APOSTROPHE},
    {"r11", KeyboardKey::KEY_N},
    {"r12", KeyboardKey::KEY_M},
    {"r13", KeyboardKey::KEY_COMMA},
    {"r14", KeyboardKey::KEY_PERIOD},
    {"r15", KeyboardKey::KEY_SLASH}
};

#endif