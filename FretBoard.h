//
// Created by super on 4/12/2023.
//

#ifndef SFML_DRUM_HERO_FRETBOARD_H
#define SFML_DRUM_HERO_FRETBOARD_H
#include "ComponentDrums.h"
#include <cmath>
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Fret.h"

class FretBoard : public ComponentDrums, public sf::Sprite{
private:
    Fret fretArray[5];
public:
    FretBoard();
    FretBoard(sf::Texture &texture);
    void setupFrets(sf::Texture &texture);
    void changeScale(int scale);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;

};


#endif //SFML_DRUM_HERO_FRETBOARD_H
