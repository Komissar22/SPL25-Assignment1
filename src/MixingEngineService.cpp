#include "MixingEngineService.h"
#include <iostream>
#include <memory>


/**
 * TODO: Implement MixingEngineService constructor
 */
MixingEngineService::MixingEngineService()
    : decks(), active_deck(0), auto_sync(false), bpm_tolerance(0)
{
    decks[0]=nullptr;
    decks[1]=nullptr;
    std::cout << "[MixingEngineService] Initialized with 2 empty decks."<< std::endl;
}

/**
 * TODO: Implement MixingEngineService destructor
 */
MixingEngineService::~MixingEngineService() {
    std::cout << "[MixingEngineService] Cleaning up decks..."<< std::endl;
    delete decks[0];
    delete decks[1];
    decks[0]=nullptr;
    decks[1]=nullptr;
}


/**
 * TODO: Implement loadTrackToDeck method
 * @param track: Reference to the track to be loaded
 * @return: Index of the deck where track was loaded, or -1 on failure
 */
int MixingEngineService::loadTrackToDeck(const AudioTrack& track) {
    std::cout << "\n=== Loading Track to Deck ==="<< std::endl;
    PointerWrapper<AudioTrack> cloned = track.clone();
    if (!cloned) {
        std::cerr << "[ERROR] Track: \"" << track.get_title()
                  << "\" failed to clone" << std::endl;
        return -1;
    }
    size_t target;
    if (decks[0] == nullptr && decks[1] == nullptr){target = 0;}
    else{
        target = 1 - active_deck;
        std::cout << "[Deck Switch] Target deck: " << target << std::endl;
        if (decks[target] != nullptr) {
            delete decks[target];
            decks[target] = nullptr;
        }
    }

    if (decks[active_deck] && auto_sync && can_mix_tracks){
        sync_bpm(cloned);
    }

    decks[target]=cloned.release();
    std::cout << "[Load Complete] " << track.get_title() << 
                " is now loaded on deck " << target << std::endl;
    if(decks[active_deck]){
        delete decks[active_deck];
        decks[active_deck]=nullptr;
    }
   std::cout << "[Unload] Unloading previous deck " << active_deck << track.get_title() << std::endl;
    
   active_deck=target;
    std::cout << "[Active Deck] Switched to deck " << target << std::endl;
    return target;
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
    // Your implementation here
    return false; // Placeholder
}

/**
 * TODO: Implement sync_bpm method
 * @param track: Track to synchronize with active deck
 */
void MixingEngineService::sync_bpm(const PointerWrapper<AudioTrack>& track) const {
    // Your implementation here
}
