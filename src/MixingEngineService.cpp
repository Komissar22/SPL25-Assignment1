#include "MixingEngineService.h"
#include <iostream>
#include <memory>


/**
 * TODO: Implement MixingEngineService constructor
 */
MixingEngineService::MixingEngineService()
    : active_deck(0)
{
    // Your implementation here
}

/**
 * TODO: Implement MixingEngineService destructor
 */
MixingEngineService::~MixingEngineService() {
    // Your implementation here
}


/**
 * TODO: Implement loadTrackToDeck method
 * @param track: Reference to the track to be loaded
 * @return: Index of the deck where track was loaded, or -1 on failure
 */
int MixingEngineService::loadTrackToDeck(const AudioTrack& track) {
    // Your implementation here
    return -1; // Placeholder
}

/**
 * @brief Display current deck status
 */
void MixingEngineService::displayDeckStatus() const {
    std::cout << "\n=== Deck Status ===\n";
    for (size_t i = 0; i < 2; ++i) {
        if (decks[i])
            std::cout << "Deck " << i << ": " << decks[i]->get_title() << "\n";
        else
            std::cout << "Deck " << i << ": [EMPTY]\n";
    }
    std::cout << "Active Deck: " << active_deck << "\n";
    std::cout << "===================\n";
}

/**
 * TODO: Implement can_mix_tracks method
 * 
 * Check if two tracks can be mixed based on BPM difference.
 * 
 * @param track: Track to check for mixing compatibility
 * @return: true if BPM difference <= tolerance, false otherwise
 */
bool MixingEngineService::can_mix_tracks(const PointerWrapper<AudioTrack>& track) const {
    if (decks[active_deck]== nullptr){
        return false;
    }

    if(track.get() == nullptr){
        return false;
    }

    int bpm_active = decks[active_deck]->get_bpm();
    int bpm_new = track.get()->get_bpm();
    int diff = std::abs(bpm_active - bpm_new);
    return (diff <= bpm_tolerance);

}

/**
 * TODO: Implement sync_bpm method
 * @param track: Track to synchronize with active deck
 */
void MixingEngineService::sync_bpm(const PointerWrapper<AudioTrack>& track) const {
    if (track.get() != nullptr && decks[active_deck] != nullptr){
        int new_bpm = track.get()->get_bpm();
        int active_bpm   = decks[active_deck]->get_bpm();
        int avg_bpm      = (active_bpm + new_bpm) / 2;
        track.get()->set_bpm(avg_bpm);
        std::cout << "[Sync BPM] Syncing BPM from "
          << new_bpm << " to " << avg_bpm << "\n";
    }
}
