#include "concertinaSoundRenderer.hpp"

#include <filesystem>
#include <memory>

#include "raylib.h"

#define TSF_IMPLEMENTATION
#include "tsf.h"


constexpr const char* SF_PATH = "assets/Real-Life_Recorded_Accordion.sf2";

tsf* tsfCbPtr = nullptr;

void renderAudioCallback(void* buffer, unsigned int frames)
{
    short* bufferShort = (short*) buffer;
    tsf_render_short(tsfCbPtr, bufferShort, frames);
}

ConcertinaSoundRenderer::ConcertinaSoundRenderer(
    int sampleRate, int sampleSize, TSFOutputMode mode)
{
    this->tinySoundFont = tsf_load_filename(SF_PATH);
    tsf_set_output(this->tinySoundFont, mode, sampleRate, 0);
    tsfCbPtr = this->tinySoundFont;

    int channels = 1;
    if (mode == TSF_STEREO_INTERLEAVED) {
        channels = 2;
    }
    this->stream = LoadAudioStream(sampleRate, sampleSize, channels);
    SetAudioStreamCallback(this->stream, renderAudioCallback);
    PlayAudioStream(this->stream);
}

ConcertinaSoundRenderer::~ConcertinaSoundRenderer()
{
    UnloadAudioStream(this->stream);
    tsf_close(this->tinySoundFont);
}

void ConcertinaSoundRenderer::btnOn(int midiNoteNr)
{
    tsf_note_on(this->tinySoundFont, 0, midiNoteNr, 1.0);
}

void ConcertinaSoundRenderer::btnOff(int midiNoteNr)
{
    tsf_note_off(this->tinySoundFont, 0, midiNoteNr);
}

void ConcertinaSoundRenderer::allBtnsOff()
{
    tsf_note_off_all(this->tinySoundFont);
}
