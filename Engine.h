//
// Created by super on 4/17/2023.
//

#ifndef SFML_DRUM_HERO_ENGINE_H
#define SFML_DRUM_HERO_ENGINE_H
#include <string>
#include "SFML/Graphics.hpp"
#include <iostream>

class Engine {
private:


public:
    Engine();
    static std::string projectPath;
    static int scale, noteHeight, noteWidth, fretHeight, fretWidth, windowHeight, windowWidth;
    static sf::Clock clock1;
    static sf::Font font;
    static sf::Texture noteSheet, fretSheet, menuBackGround, selectBackGround, defaultMenu;

    void update();


    static void readFiles(std::string path, std::string fileName);
};


#endif //SFML_DRUM_HERO_ENGINE_H
