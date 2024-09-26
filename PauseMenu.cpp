//
// Created by super on 4/19/2023.
//

#include "PauseMenu.h"

PauseMenu::PauseMenu() : count(1), paused(false), quit(false){
    pauseBox.setSize({300, 300});
    pauseBox.setPosition((Engine::windowWidth - pauseBox.getGlobalBounds().width)/2, (Engine::windowHeight - pauseBox.getGlobalBounds().height)/2);
    pauseBox.setTexture(&Engine::defaultMenu);
    initializeAllStrings();
}

void PauseMenu::initializeAllStrings() {
    text[0].setFont(Engine::font);
    text[0].setString("Paused");
    text[0].setCharacterSize(50);
    text[0].setPosition((Engine::windowWidth - text[0].getGlobalBounds().width)/2, pauseBox.getGlobalBounds().top + 50);
    text[0].setFillColor(sf::Color::White);
    text[1].setString("Resume");
    text[2].setString("Quit");
    for (int i = 1; i < 3; i++){
        text[i].setFont(Engine::font);
        text[i].setCharacterSize(40);
        text[i].setPosition((Engine::windowWidth - text[i].getGlobalBounds().width)/2, Engine::windowHeight/2 - text[i].getCharacterSize() + (i - 1) * text[1].getCharacterSize());
        text[i].setFillColor(sf::Color::White);
    }
}

void PauseMenu::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (paused && !quit) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && count > 1) {
            text[count].setFillColor(sf::Color::White);
            count--;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && count < 2) {
            text[count].setFillColor(sf::Color::White);
            count++;
        }
        text[count].setFillColor(sf::Color::Yellow);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            if (count == 1){
                paused = false;
                HighWay::setPause(false);
                HighWay::restartSongTime();
                SongAudio::playAllMusic();
                //std::cout << "pause";
            } else if (count == 2){
                quit = true;
            }
        }
    }
}

void PauseMenu::update() {

}

void PauseMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (paused) {
        target.draw(pauseBox);
        for (int i = 0; i < 3; i++) {
            target.draw(text[i]);
        }
    }
}

bool PauseMenu::isPaused() const {
    return paused;
}

void PauseMenu::setPaused(bool paused) {
    PauseMenu::paused = paused;
}

bool PauseMenu::isQuit() const {
    return quit;
}

void PauseMenu::setQuit(bool quit) {
    PauseMenu::quit = quit;
}
