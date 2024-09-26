//
// Created by super on 4/12/2023.
//

#ifndef SFML_DRUM_HERO_EVENTHANDABLE_H
#define SFML_DRUM_HERO_EVENTHANDABLE_H
#include "SFML/Graphics.hpp"

class EventHandable {
public:
    virtual void eventHandler(sf::RenderWindow &window, sf::Event event) = 0;
};

#endif //SFML_DRUM_HERO_EVENTHANDABLE_H
