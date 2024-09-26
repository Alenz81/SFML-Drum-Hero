//
// Created by super on 4/17/2023.
//

#include "Engine.h"
std::string projectPath = "\"C:\\Users\\super\\CLionProjects\\SFML Drum Hero\\";
int Engine::scale = 2;
int Engine::noteHeight = 11;
int Engine::noteWidth = 50;
int Engine::fretHeight = 11;
int Engine::fretWidth = 50;
int Engine::windowWidth = 1024;
int Engine::windowHeight = 720;
sf::Clock Engine::clock1;
sf::Font Engine::font;
sf::Texture Engine::noteSheet;
sf::Texture Engine::fretSheet;
sf::Texture Engine::menuBackGround;
sf::Texture Engine::selectBackGround;
sf::Texture Engine::defaultMenu;

Engine::Engine() {
    if (!font.loadFromFile("SitkaVF.ttf")){
        exit(200);
    }
    if (!noteSheet.loadFromFile("images/new note sprites.png")){
        exit(24);
    }
    if (!fretSheet.loadFromFile("images/fret sprites.png")){
        exit(24);
    }
    if (!menuBackGround.loadFromFile("images/parch paper.png")){
        exit(24);
    }
    if (!selectBackGround.loadFromFile("images/select background.png")){
        exit(24);
    }
    if (!defaultMenu.loadFromFile("images/defaultMenupng.png")){
        exit(24);
    }
}

void Engine::readFiles(std::string path, std::string fileName) {
    std::string command("dir /b > " + fileName + " \"C:\\Users\\super\\CLionProjects\\SFML Drum Hero\\" + path + "\"");
    const char* final_command = command.c_str();
    //std::cout << command << std::endl << std::endl << std::endl;
    system(final_command);
}

