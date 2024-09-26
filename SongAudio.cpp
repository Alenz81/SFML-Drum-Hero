//
// Created by super on 4/12/2023.
//

#include "SongAudio.h"


int SongAudio::audioFileCount(0);
bool SongAudio::songPlaying = false;
//std::vector<std::string> SongAudio::fileNames;
//std::string SongAudio::filePath;
std::vector<sf::Music> SongAudio::musicStems(20);

SongAudio::SongAudio() /*: audioFileCount(0), songPlaying(false)*/{

}

void SongAudio::initializeSong() {
    filePath = "songs\\" + Menu::selectedSong;
    createFileOfSongs();
    initializeVectorStrings();
    initializeMusicStems();
}

void SongAudio::createFileOfSongs() {
    Engine::readFiles(filePath, "SongFiles.txt");
}

void SongAudio::initializeVectorStrings() {
    std::ifstream songData("SongFiles.txt");
    std::string nextLine;
    if (songData.is_open()) {
        while (songData) {
            std::getline (songData, nextLine);
            if (nextLine != ""){
                fileNames.push_back(nextLine);
            }
        }
    }
}

void SongAudio::initializeMusicStems() {
    for (int i = 0; i < fileNames.size(); i++){
        std::string tempString = fileNames.at(i);
        tempString = tempString.substr(tempString.length() - 3, 3);
        if (tempString == "ogg" || tempString == "wav"){
            //std::cout << filePath + "\\" + fileNames.at(i) << std::endl;
            musicStems.at(audioFileCount).openFromFile( filePath + "\\" + fileNames.at(i));
            audioFileCount++;
            //std::cout << "count" << audioFileCount;
        }
    }
}
//
int SongAudio::getLongestTrack() {
    int longestTrack = 0;
    float longestTrackTime = musicStems.at(longestTrack).getDuration().asSeconds();
    for (int i = 0; i < audioFileCount; i++){
        float temp = musicStems.at(i).getDuration().asSeconds();
        if (longestTrackTime < temp) {
            longestTrack = i;
            longestTrackTime = temp;
        }
    }
    return longestTrackTime;
}

void SongAudio::playAllMusic() {
    for (int i = 0; i < audioFileCount; i++){
        musicStems.at(i).play();
    }
    songPlaying = true;
    //std::cout << "Audio count" << audioFileCount;
}

void SongAudio::pauseAllMusic() {
    for (int i = 0; i < audioFileCount; i++){
        musicStems.at(i).pause();
    }
    songPlaying = false;
}

bool SongAudio::isSongPlaying() const {
    return songPlaying;
}

bool SongAudio::isSongOver() {
    for (int i = 0; i < audioFileCount; i++){
        if (musicStems.at(i).getStatus() != sf::SoundSource::Status::Stopped){
            return false;
        }
    }
    return true;
}

void SongAudio::setSongPlaying(bool songPlaying) {
    SongAudio::songPlaying = songPlaying;
}

void SongAudio::emptyAudioFileCount() {
    audioFileCount = 0;
    while (!fileNames.empty()){
        fileNames.pop_back();
    }
}
