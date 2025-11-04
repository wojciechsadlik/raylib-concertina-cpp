#ifndef CONCERTINA_BTN_MAP_HPP
#define CONCERTINA_BTN_MAP_HPP

#include <map>
#include <string>

#include "raylib.h"

struct BtnData {
    std::string id;
    int pushMidiNoteNr;
    int pullMidiNoteNr;
    Rectangle bounds;
};

inline const std::map<std::string, const BtnData> BTN_ID_TO_DATA = {
    {"l06", {"l06", 67, 69, {381.116,166.67,69.2566,101.498}}},
    {"l07", {"l07", 64, 65, {303.62,166.67,69.2566,101.498}}},
    {"l08", {"l08", 60, 62, {224.138,166.67,69.2566,101.498}}}
};

#endif