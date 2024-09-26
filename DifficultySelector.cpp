//
// Created by super on 4/18/2023.
//

#include "DifficultySelector.h"




DifficultySelector::DifficultySelector() : difficulty(3), isDifficultySelected(true), isPercent(false), isSongOver(false){
    initializeAllText();

    backGround.setSize({238, 571});
    backGround.setPosition({(static_cast<float>(Engine::windowWidth) - backGround.getGlobalBounds().width)/2, (static_cast<float>(Engine::windowHeight) - backGround.getGlobalBounds().height)/2});
    backGround.setTexture(&Engine::selectBackGround);
    initializeText(percentText, Engine::windowHeight/2);
    percentText.setFillColor(sf::Color::Yellow);
}

DifficultySelector::DifficultySelector(bool percent) : isPercent(percent), isSongOver(false) {
    if (isPercent){
        initializeText(percentText, Engine::windowHeight/2);
    }
}

void DifficultySelector::initializeAllText() {
    difficulties[0].setString("Easy");
    difficulties[1].setString("Medium");
    difficulties[2].setString("Hard");
    difficulties[3].setString("Expert");
    int startHeight = Engine::windowHeight/2 - 2 * difficulties[0].getCharacterSize();
    for (int i = 0; i < 4; i++){
        difficulties[i].setCharacterSize(40);
        initializeText(difficulties[i], startHeight + i * difficulties[0].getCharacterSize());
    }
}

void DifficultySelector::initializeText(sf::Text &text, int y) {
    text.setFont(Engine::font);
    text.setFillColor(sf::Color::White);
    text.setPosition(Engine::windowWidth/2 - text.getGlobalBounds().width/2, y);
    text.setCharacterSize(40);
}

void DifficultySelector::restartClock() {
    enterBuffer.restart();
}

void DifficultySelector::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (!isPercent) {
        if (!isDifficultySelected) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && difficulty > 0) {
                difficulties[difficulty].setFillColor(sf::Color::White);
                difficulty--;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && difficulty < 3) {
                difficulties[difficulty].setFillColor(sf::Color::White);
                difficulty++;
            }
            difficulties[difficulty].setFillColor(sf::Color::Yellow);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) &&
                enterBuffer.getElapsedTime().asSeconds() > 0.01) {
                //std::cout << "difficulty";
                isDifficultySelected = true;
                enterBuffer.restart();
            }
        }
    } else if (isSongOver){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) &&
            enterBuffer.getElapsedTime().asSeconds() > 0.01) {
            //std::cout << "back to menu\n";
            isSongOver = false;
            enterBuffer.restart();
        }
    }
}

void DifficultySelector::update() {

}

void DifficultySelector::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!isDifficultySelected && !isPercent) {
        target.draw(backGround);
        for (int i = 0; i < 4; i++) {
            target.draw(difficulties[i]);
        }
    }
    if (isPercent && isSongOver){
        target.draw(backGround);
        target.draw(percentText);
    }
}

bool DifficultySelector::isDifficultySelected1() {
    return isDifficultySelected;
}

int DifficultySelector::getDifficulty() {
    return difficulty;
}

void DifficultySelector::setIsDifficultySelected(bool isDifficultySelected) {
    DifficultySelector::isDifficultySelected = isDifficultySelected;
}

bool DifficultySelector::getIsSongOver() {
    return isSongOver;
}

void DifficultySelector::setIsPercent(bool percent) {
    isPercent = percent;
}

void DifficultySelector::setIsSongOver(bool isOver) {
    isSongOver = isOver;
}

void DifficultySelector::setPercentText(int percent) {
    percentText.setString(std::to_string(percent) + "%");
    percentText.setPosition(Engine::windowWidth/2 - percentText.getGlobalBounds().width/2, percentText.getPosition().y);
}
