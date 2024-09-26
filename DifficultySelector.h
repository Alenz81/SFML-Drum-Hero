//
// Created by super on 4/18/2023.
//

#ifndef SFML_DRUM_HERO_DIFFICULTYSELECTOR_H
#define SFML_DRUM_HERO_DIFFICULTYSELECTOR_H
#include "SFML/Graphics.hpp"
#include "ComponentDrums.h"
#include "Engine.h"
#include "HighWay.h"

class DifficultySelector : public ComponentDrums {
private:
    sf::Text difficulties[4];
    sf::Text percentText;
    sf::RectangleShape backGround;
    bool isDifficultySelected, isPercent, isSongOver;
    sf::Clock enterBuffer;
    int difficulty;
public:

    DifficultySelector();
    DifficultySelector(bool percent);

    void initializeAllText();
    void initializeText(sf::Text &text, int y);
    void restartClock();

    bool isDifficultySelected1();

    int getDifficulty();
    void setIsDifficultySelected(bool isDifficultySelected);

    void setIsPercent(bool percent);
    bool getIsSongOver();
    void setIsSongOver(bool isOver);
    void setPercentText(int percent);

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //SFML_DRUM_HERO_DIFFICULTYSELECTOR_H
