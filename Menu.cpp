//
// Created by super on 4/14/2023.
//


#include "Menu.h"

std::string Menu::selectedSong = "Alice in Chains - Man in the Box"; //The Who - Won't Get Fooled Again

Menu::Menu() : count(0), songSelected(false) {
    getFileNames();
    initializeSongBoxes();
    initializeSelectorAndBackGround();
}

void Menu::initializeSelectorAndBackGround() {
    selector.setPosition(100, Engine::windowHeight/2);
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineColor(sf::Color::Black);
    selector.setOutlineThickness(5);
    selector.setSize({static_cast<float>(Engine::windowWidth - 200), 50});

    backGround.setPosition(0, 0);
    backGround.setSize({static_cast<float>(Engine::windowWidth), static_cast<float>(Engine::windowHeight) + 200});
    backGround.setTexture(&Engine::menuBackGround);
    /*
    backGround.left = 0;
    backGround.top = 0;
    backGround.width = Engine::windowWidth;
    backGround.height = Engine::windowHeight;*/


}

void Menu::getFileNames() {
    Engine::readFiles("songs\\", "SongFolders.txt");

    std::ifstream songName("SongFolders.txt");
    std::string nextLine;
    if (songName.is_open()) {
        while (songName) {
            std::getline (songName, nextLine);
            if (nextLine != ""){
                fileNames.push_back(nextLine);
            }
        }
    }
}

void Menu::initializeSongBoxes() {
    std::string nextLine, artist, name;
    for (int i = 0; i < fileNames.size(); i++){
        std::ifstream songName("songs/" + fileNames[i] + "/song.ini");
        while (songName) {
            std::getline (songName, nextLine);
            if (nextLine.substr(0, 7) == "name = "){
                name = nextLine.substr(7);
            }
            if (nextLine.substr(0, 9) == "artist = "){
                artist = nextLine.substr(9);
            }
        }
        songBoxes.push_back(BoxWithText(name + " By " + artist, 100, (Engine::windowHeight/2) + 60 * i, true));
    }
}

void Menu::restartClock() {
    enterBuffer.restart();
}

void Menu::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (!songSelected) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && count > 0) {
            count--;
            for (int i = 0; i < songBoxes.size(); i++) {
                songBoxes.at(i).eventHandler(window, event);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && count < songBoxes.size() - 1) {
            count++;
            for (int i = 0; i < songBoxes.size(); i++) {
                songBoxes.at(i).eventHandler(window, event);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && enterBuffer.getElapsedTime().asSeconds() > 0.3) {
            songSelected = true;
            selectedSong = fileNames.at(count);
            //std::cout << "AHHH";
        }
    }
    //std::cout << count;
}

void Menu::update() {

}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!songSelected) {
        target.draw(backGround);
        for (int i = 0; i < songBoxes.size(); i++) {
            if (songBoxes.at(i).getYPos() > 0 && songBoxes.at(i).getYPos() < Engine::windowHeight) {
                songBoxes.at(i).draw(target, states);
            }
        }
        target.draw(selector);
    }
}

void Menu::setSongSelected(bool songSelected) {
    Menu::songSelected = songSelected;
}

bool Menu::getSongSelected() {
    return songSelected;
}
