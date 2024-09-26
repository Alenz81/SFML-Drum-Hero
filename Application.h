//
// Created by super on 4/12/2023.
//

#ifndef SFML_DRUM_HERO_APPLICATION_H
#define SFML_DRUM_HERO_APPLICATION_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "ComponentDrums.h"
#include "EventHandable.h"
#include "UpdatableDrums.h"
#include "Note.h"
#include "Menu.h"
#include "DifficultySelector.h"
#include "HighWay.h"
#include "PauseMenu.h"


class Application {
private:
    bool partOfGame[6];
    sf::RenderWindow window;
    std::vector<ComponentDrums*> components;
    Menu menu;
    DifficultySelector difficultySelector, songEndMenu;
    HighWay highWay;
    PauseMenu pauseMenu;
    SongAudio songAudio;
    sf::Clock songClock;
    double songLength;
public:
    Application();
    void run();
    void addComponent(ComponentDrums& component);
    void removeComponent();

};


#endif //SFML_DRUM_HERO_APPLICATION_H
