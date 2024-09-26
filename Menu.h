//
// Created by super on 4/14/2023.
//

#ifndef SFML_DRUM_HERO_MENU_H
#define SFML_DRUM_HERO_MENU_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Engine.h"
#include "ComponentDrums.h"
#include "BoxWithText.h"


class Menu : public ComponentDrums{
private:
    sf::RectangleShape selector, backGround;
    std::vector<std::string> fileNames;
    std::vector<BoxWithText> songBoxes;
    bool songSelected;
    void initializeSelectorAndBackGround();
    int count;
    sf::Clock enterBuffer;

public:
    Menu();
    static std::string selectedSong;
    void getFileNames();
    void initializeSongBoxes();
    void setSongSelected(bool songSelected);
    bool getSongSelected();

    void restartClock();

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //SFML_DRUM_HERO_MENU_H
