//
// Created by super on 4/17/2023.
//

#include "BoxWithText.h"

BoxWithText::BoxWithText() {

}

BoxWithText::BoxWithText(std::string string, bool isMoving) : isMoving(isMoving){
    rect.setFillColor(sf::Color::Transparent);
    rect.setSize({14, 4});
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(5);


    text.setFont(Engine::font);
    text.setString(string);
    text.setFillColor(sf::Color::Black);
}

BoxWithText::BoxWithText(std::string string, int x, int y, bool isMoving) : isMoving(isMoving){
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(x, y);
    rect.setSize({static_cast<float>(Engine::windowWidth) - 200, 50});
    rect.setOutlineColor(sf::Color::Transparent); //Black
    rect.setOutlineThickness(5);
    rect.setPosition(x, y);

    text.setFont(Engine::font);
    text.setStyle(sf::Text::Bold | sf::Text::Italic);
    text.setCharacterSize(29);
    text.setPosition(x + 10, y + 5);
    text.setString(string);
    //std::cout << string << std::endl;
    text.setFillColor(sf::Color::Black);

}

int BoxWithText::getYPos() const {
    return rect.getGlobalBounds().top;
}

void BoxWithText::setSize(float width, float height, int charSize) {
    rect.setSize({width, height});
    text.setCharacterSize(charSize);
}

void BoxWithText::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (isMoving) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            rect.move(0, rect.getSize().y + 10);
            text.move(0, rect.getSize().y + 10);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            rect.move(0, -rect.getSize().y - 10);
            text.move(0, -rect.getSize().y - 10);
        }
    }
}

void BoxWithText::update() {

}

void BoxWithText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(rect);
    target.draw(text);

}
