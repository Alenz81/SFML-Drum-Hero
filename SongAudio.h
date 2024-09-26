//
// Created by super on 4/12/2023.
//

#ifndef SFML_DRUM_HERO_SONGAUDIO_H
#define SFML_DRUM_HERO_SONGAUDIO_H

#include "SFML/Audio.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Engine.h"
#include "Menu.h"


class SongAudio {
private:
     static int audioFileCount;
     static std::vector<sf::Music> musicStems;
     std::vector<std::string> fileNames;
     std::string filePath;
     static bool songPlaying;

public:
    SongAudio();
    void initializeSong();
    static void playAllMusic();
    void pauseAllMusic();
    void createFileOfSongs();
    void initializeVectorStrings();
    int getLongestTrack();
    void initializeMusicStems();
    bool isSongPlaying() const;
    bool isSongOver();
    void setSongPlaying(bool songPlaying);
    void emptyAudioFileCount();
};


#endif //SFML_DRUM_HERO_SONGAUDIO_H
