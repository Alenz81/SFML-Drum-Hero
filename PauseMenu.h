//
// Created by super on 4/19/2023.
//

#ifndef SFML_DRUM_HERO_PAUSEMENU_H
#define SFML_DRUM_HERO_PAUSEMENU_H
#include "SFML/Graphics.hpp"
#include "ComponentDrums.h"
#include "Engine.h"
#include "HighWay.h"

class PauseMenu : public ComponentDrums{
private:
    sf::Text text[3];
    sf::RectangleShape pauseBox;

    bool paused, quit;
    int count;
public:
    PauseMenu();

    void initializeAllStrings();
    bool isPaused() const;
    void setPaused(bool paused);
    bool isQuit() const;
    void setQuit(bool quit);

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //SFML_DRUM_HERO_PAUSEMENU_H
