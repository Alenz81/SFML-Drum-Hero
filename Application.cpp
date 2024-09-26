//
// Created by super on 4/12/2023.
//

#include "Application.h"

Application::Application() : songLength(0) {
    songEndMenu.setIsPercent(true);
    addComponent(menu);
    addComponent(difficultySelector);
    addComponent(highWay);
    addComponent(pauseMenu);
    addComponent(songEndMenu);
    for (int i = 0; i < 4; i++){
        partOfGame[i] = true;
    }

}

void Application::run() {
    highWay.setDisplayHighway(false);
    highWay.setPause(false);
    pauseMenu.setPaused(false);
    pauseMenu.setQuit(false);
    for (int i = 0; i < 6; i++){
        partOfGame[i] = true;
    }
    menu.setSongSelected(false);
    menu.restartClock();
    songAudio.emptyAudioFileCount();
    songAudio.setSongPlaying(false);
    window.create({1024, 720, 32}, "SFML Drum Hero");
    window.setFramerateLimit(120);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            for(ComponentDrums* c : components){
                static_cast<EventHandable*>(c)->eventHandler(window, event);
            }
            if (menu.getSongSelected() && partOfGame[0]){
                difficultySelector.setIsDifficultySelected(false);
                difficultySelector.restartClock();
                partOfGame[0] = false;
            }
            if (difficultySelector.isDifficultySelected1() && menu.getSongSelected() && partOfGame[1]){
                songAudio.initializeSong();
                songAudio.playAllMusic();
                partOfGame[1] = false;
            }
            if (songAudio.isSongPlaying() && partOfGame[2]){
                highWay.emptyHighways();
                highWay.populateNoteHighways(difficultySelector.getDifficulty());
                highWay.setDisplayHighway(true);
                highWay.restartSongTime();
                songClock.restart();
                //std::cout << "length " << songAudio.getLongestTrack();
                songLength = songAudio.getLongestTrack();
                partOfGame[2] = false;
            }
            if (highWay.isDisplayHighway() && partOfGame[3]){
                if (highWay.getPause() && !pauseMenu.isPaused()){
                    songAudio.pauseAllMusic();
                    pauseMenu.setPaused(true);
                }
                if (pauseMenu.isQuit()){
                    highWay.setDisplayHighway(false);
                    //highWay.emptyHighways();
                    highWay.setPause(false);
                    pauseMenu.setPaused(false);
                    pauseMenu.setQuit(false);
                    for (int i = 0; i < 6; i++){
                        partOfGame[i] = true;
                    }
                    menu.setSongSelected(false);
                    menu.restartClock();
                    songAudio.emptyAudioFileCount();
                    songAudio.setSongPlaying(false);
                }
                if (songAudio.isSongOver()){
                    highWay.setDisplayHighway(false);
                    partOfGame[3] = false;
                }
            }
            if (songAudio.isSongOver() && partOfGame[4] && !partOfGame[3]){
                if (!songEndMenu.getIsSongOver()) {
                    partOfGame[4] = false;
                    songAudio.emptyAudioFileCount();
                }
            }
            if (partOfGame[5] && !partOfGame[4] && !songEndMenu.getIsSongOver()){
                for (int i = 0; i < 6; i++){
                    partOfGame[i] = true;
                }
                menu.setSongSelected(false);
                songAudio.setSongPlaying(false);
                highWay.setDisplayHighway(false);
                menu.restartClock();
            }
        }

        if (highWay.isDisplayHighway() && partOfGame[3]){
            if (songAudio.isSongOver()){
                highWay.setDisplayHighway(false);
                songEndMenu.setIsSongOver(true);
                songEndMenu.setPercentText(highWay.getPercentNotesHit());
                songEndMenu.restartClock();
                partOfGame[3] = false;
            }
        }
        for (ComponentDrums *c: components) {
            reinterpret_cast<UpdatableDrums *>(c)->update();
        }

        window.clear();
        for(ComponentDrums* c : components){
            window.draw(*static_cast<sf::Drawable*>(c));
        }


        window.display();
    }

}

void Application::addComponent(ComponentDrums &component) {
    components.push_back(&component);
}

void Application::removeComponent() {
    components.pop_back();
}
