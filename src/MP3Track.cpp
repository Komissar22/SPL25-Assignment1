#include "MP3Track.h"
#include <iostream>
#include <cmath>
#include <algorithm>

// Constructor (no debug prints allowed)
MP3Track::MP3Track(const std::string& title, const std::vector<std::string>& artists, 
                   int duration, int bpm, int bitrate, bool has_tags)
    : AudioTrack(title, artists, duration, bpm), bitrate(bitrate), has_id3_tags(has_tags)
{
    // No creation print here — the manager prints it
}

//
// ===========================
//        load()
// ===========================
// Format must match exactly the required output
//
void MP3Track::load() 
{
    std::cout << "[MP3Track::load] Loading MP3: \"" << title
              << "\" at " << bitrate << " kbps...\n";

    if(has_id3_tags) {
        std::cout << "  → Processing ID3 metadata (artist info, album art, etc.)...\n";
    } else {
        std::cout << "  → No ID3 tags found.\n";
    }

    std::cout << "  → Decoding MP3 frames...\n";
    std::cout << "  → Load complete.\n";
}

//
// ===========================
//   analyze_beatgrid()
// ===========================
// Must print both arrows on the same line
//
void MP3Track::analyze_beatgrid()
{
    std::cout << "[MP3Track::analyze_beatgrid] Analyzing beat grid for: \"" 
              << title << "\"\n";

    int estimated_beats = (duration_seconds / 60.0) * bpm;
    double precision_factor = bitrate / 320.0;

    std::cout << "  → Estimated beats: " << estimated_beats
              << "  → Compression precision factor: " << precision_factor << "\n";
}

//
// ===========================
//     get_quality_score()
// ===========================
// No printing — only returns a computed score
//
double MP3Track::get_quality_score() const 
{
    double base_score = (bitrate / 320.0) * 100.0;

    if(has_id3_tags) base_score += 5;
    if(bitrate < 128) base_score -= 10;

    return base_score;
}

//
// ===========================
//           clone()
// ===========================
// Returns a deep copy (polymorphic clone)
//
PointerWrapper<AudioTrack> MP3Track::clone() const 
{
    return PointerWrapper<AudioTrack>(new MP3Track(*this));
}
