//
// Created by super on 4/17/2023.
//

#ifndef SFML_DRUM_HERO_BOXWITHTEXT_H
#define SFML_DRUM_HERO_BOXWITHTEXT_H
#include "SFML/Graphics.hpp"
#include "ComponentDrums.h"
#include "Engine.h"

class BoxWithText : public ComponentDrums{
protected:
    sf::RectangleShape rect;
    sf::Text text;
    bool isMoving;
public:
    BoxWithText();
    BoxWithText(std::string string, bool isMoving);
    BoxWithText(std::string string, int x, int y, bool isMoving);

    int getYPos() const;
    void setSize(float width, float height, int charSize);

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //SFML_DRUM_HERO_BOXWITHTEXT_H
