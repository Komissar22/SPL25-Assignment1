#include "DJLibraryService.h"
#include "SessionFileParser.h"
#include "MP3Track.h"
#include "WAVTrack.h"
#include <iostream>
#include <memory>
#include <filesystem>


DJLibraryService::DJLibraryService(const Playlist& playlist) 
    : playlist(playlist), library() {}
/**
 * @brief Load a playlist from track indices referencing the library
 * @param library_tracks Vector of track info from config
 */
void DJLibraryService::buildLibrary(const std::vector<SessionConfig::TrackInfo>& library_tracks) {
        for (const auto& info : library_tracks) {
        AudioTrack* track = nullptr;

        if (info.type == "MP3") {
            bool has_tags = (info.extra_param2 != 0);
            track = new MP3Track(
                info.title,
                info.artists,
                info.duration_seconds,
                info.bpm,
                info.extra_param1, // bitrate
                has_tags
            );
        }
        else if (info.type == "WAV") {
            track = new WAVTrack(
                info.title,
                info.artists,
                info.duration_seconds,
                info.bpm,
                info.extra_param1, // sample_rate
                info.extra_param2  // bit_depth
            );
        }
        else {
            continue;
        }

        library.push_back(track);
    }

    std::cout << "[INFO] Track library built: " 
              << library_tracks.size() 
              << " tracks loaded " << std::endl;

}

    

/**
 * @brief Display the current state of the DJ library playlist
 * 
 */
void DJLibraryService::displayLibrary() const {
    std::cout << "=== DJ Library Playlist: " 
              << playlist.get_name() << " ===" << std::endl;

    if (playlist.is_empty()) {
        std::cout << "[INFO] Playlist is empty.\n";
        return;
    }

    // Let Playlist handle printing all track info
    playlist.display();

    std::cout << "Total duration: " << playlist.get_total_duration() << " seconds" << std::endl;
}

/**
 * @brief Get a reference to the current playlist
 * 
 * @return Playlist& 
 */
Playlist& DJLibraryService::getPlaylist() {
    // Your implementation here
    return playlist;
}

/**
 * TODO: Implement findTrack method
 * 
 * HINT: Leverage Playlist's find_track method
 */
AudioTrack* DJLibraryService::findTrack(const std::string& track_title) {
    return playlist.find_track(track_title);
}

void DJLibraryService::loadPlaylistFromIndices(const std::string& playlist_name, 
                                               const std::vector<int>& track_indices) {
    std::cout <<"[INFO] Loading playlist: " << playlist_name << std::endl;
    playlist = Playlist (playlist_name);

    for(int index : track_indices){
        if(index<=0 || index > library.size()){
            std::cout << "[WARNING] Invalid track index: " << index << std::endl;
            continue;
        }
        AudioTrack* track = library[index - 1];

        PointerWrapper<AudioTrack> cloned = track->clone();
        if(!cloned){
            std::cout << "[WARNING] Invalid track index: " << index << std::endl;
            continue;
        }
        
        cloned->load();
        cloned->analyze_beatgrid();
        playlist.add_track(cloned.release());
    }
    
    std::cout << "[INFO] Playlist loaded: " << playlist_name
          << " (" << playlist.get_track_count() << " tracks)" << std::endl;
}
/**
 * TODO: Implement getTrackTitles method
 * @return Vector of track titles in the playlist
 */
std::vector<std::string> DJLibraryService::getTrackTitles() const {
    std::vector<std::string> titles;
     for (const auto& track : playlist.getTracks()) { 
        titles.push_back(track->get_title());
    }
    return titles;
}
