//
// Created by super on 4/12/2023.
//

#ifndef SFML_DRUM_HERO_COMPONENTDRUMS_H
#define SFML_DRUM_HERO_COMPONENTDRUMS_H
#include <SFML/Graphics.hpp>
#include "UpdatableDrums.h"
#include "EventHandable.h"

class ComponentDrums : public UpdatableDrums, public sf::Drawable, public EventHandable {

};


#endif //SFML_DRUM_HERO_COMPONENTDRUMS_H
