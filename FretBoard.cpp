//
// Created by super on 4/12/2023.
//

#include "FretBoard.h"

FretBoard::FretBoard() {}

FretBoard::FretBoard(sf::Texture &texture) {
    setupFrets(texture);
}

void FretBoard::setupFrets(sf::Texture &texture) {
    for (int i = 0; i < 4; i++){
        fretArray[i].setColor(i, texture);
        fretArray[i].scaleFret();
    }
    fretArray[4].setColor(-1,texture);
    fretArray[4].scaleFret();
}

void FretBoard::changeScale(int scale) {
    for (int i = 0; i < 4; i++){
        fretArray[i].changeScale(scale);
    }
}

void FretBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < 5; i++){
        fretArray[i].draw(target, states);
    }
}

void FretBoard::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)){
        fretArray[0].eventHandler(window, event);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)){
        fretArray[1].eventHandler(window, event);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        fretArray[2].eventHandler(window, event);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        fretArray[3].eventHandler(window, event);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        fretArray[4].eventHandler(window, event);
    }
}

void FretBoard::update() {
    for (int i = 0; i < 5; i++){
        fretArray[i].update();
    }
}

