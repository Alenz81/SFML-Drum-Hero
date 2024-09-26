//
// Created by super on 4/12/2023.
//

#ifndef SFML_DRUM_HERO_FRET_H
#define SFML_DRUM_HERO_FRET_H
#include "ComponentDrums.h"
#include <cmath>
#include "SFML/Graphics.hpp"
#include <iostream>

class Fret : public ComponentDrums, public sf::Sprite {
private:
    sf::Clock clockActive, clockHeldDown;
    int color, x;
    bool active, isHeldDown;
    static int y;
    static float scale;
    sf::IntRect intRect;
    void setupIntRect(sf::Texture &texture);
public:
    Fret();
    Fret(sf::Texture &texture, int color);
    void setColor(int color, sf::Texture &texture);
    static float getScale();
    static int getY();
    void changeScale(float scale);
    void scaleFret();
    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;
    void animate();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};



#endif //SFML_DRUM_HERO_FRET_H
