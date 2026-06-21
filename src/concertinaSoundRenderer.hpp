#ifndef CONCERTINA_SOUND_RENDERER_HPP
#define CONCERTINA_SOUND_RENDERER_HPP

#include <vector>
#include <memory>

#include "raylib.h"
#include "tsf.h"

class ConcertinaSoundRenderer {
private:
    tsf* tinySoundFont;
    AudioStream stream;
public:
    ConcertinaSoundRenderer() : ConcertinaSoundRenderer(48000, 16, TSF_STEREO_INTERLEAVED) {};
    ConcertinaSoundRenderer(int sampleRate, int sampleSize, TSFOutputMode mode);
    ~ConcertinaSoundRenderer();
    void btnOn(int midiNoteNr);
    void btnOff(int midiNoteNr);
    void allBtnsOff();
};

#endif