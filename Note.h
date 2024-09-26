//
// Created by super on 4/12/2023.
//

#ifndef SFML_DRUM_HERO_NOTE_H
#define SFML_DRUM_HERO_NOTE_H
#include "ComponentDrums.h"
#include <cmath>
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Fret.h"
#include "Engine.h"

class Note : public ComponentDrums, public sf::Sprite {
private:
    sf::Clock clock;
    int color;
    bool isCymbal, isStarPower, isVisible, isMissed;
    double time, offset;
    float slopeX, slopeY, scaleSlopeX, scaleSlopeY, x, y = 300, scale = 0.6;
    sf::IntRect intRect;
    float speed = 200;
    void setupIntRect();
    void calculateSlope(float fretScale, float startScale, int startY, int fretY);

public:
    Note();
    Note(sf::Texture &texture, int color, bool isCymbal, double time);
    int getColor() const;
    double getTime() const;
    bool isValidHitWindow();
    bool isOffScreen();
    void setIsVisible(bool visible);
    double calculateOffset();
    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void changeScale(float scale);

    friend std::ostream& operator <<(std::ostream& out, Note note);
};


#endif //SFML_DRUM_HERO_NOTE_H
