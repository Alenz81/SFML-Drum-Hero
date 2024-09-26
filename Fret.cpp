//
// Created by super on 4/12/2023.
//

#include "Fret.h"

float Fret::scale = 2;
int Fret::y = 600;

Fret::Fret() : color(0), x(1080/2), active(false), isHeldDown(false){}

Fret::Fret(sf::Texture &texture, int color) : color(color), x(1080/2), active(false), isHeldDown(false){
    setupIntRect(texture);
}

void Fret::setColor(int color, sf::Texture &texture) {
    this->color = color;
    setupIntRect(texture);
}

float Fret::getScale() {
    return scale;
}

int Fret::getY() {
    return y;
}

void Fret::scaleFret() {
    setScale(scale, scale);
    if (color != -1) {
        x = (1024 / 2 - (2 * 50 * scale)) + (color * 50 * scale);
    } else {
        x = (1024 / 2 - (2 * 50 * scale)) - (7 * scale);
    }
    setPosition(x, getGlobalBounds().top);
}


void Fret::changeScale(float scale) {
    this->scale = scale;
    scaleFret();
}


void Fret::setupIntRect(sf::Texture &texture) {
    setTexture(texture);
    int fretWidth(50);
    int fretHeight(11);

    if (color == -1){
        fretWidth = 7 * 2 + fretWidth * 4;
        x = 1024/2 - fretWidth/2 * scale;
        intRect.left = 0;
        intRect.top = fretHeight;
    } else {
        x = (1024/2 - (2 * fretWidth * scale)) + (color * fretWidth * scale);
        intRect.left = color * fretWidth;
        intRect.top = 0;
    }
    intRect.width = fretWidth;
    intRect.height = fretHeight;
    setTextureRect(intRect);
    setPosition(x, y);
}


void Fret::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) && color == 0 ) {
        active = true;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) && color == 1) {
        active = true;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && color == 2) {
        active = true;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && color == 3) {
        active = true;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && color == -1) {
        active = true;
    }
}

void Fret::update() {
    if (active /*&& !isHeldDown*/){
        animate();
        active = false;
        clockActive.restart();
    } else if (intRect.top - 11 * 2 >= 0 && clockActive.getElapsedTime().asMilliseconds() > 75
    ) {
        //std::cout << "false\n";
        intRect.top -= 11 * 2;
        setTextureRect(intRect);
        clockActive.restart();
    }
}

void Fret::animate() {
    if ((intRect.top + 11 * 2) < 11 * 4){
        intRect.top += 11 * 2;
        //std::cout << "active";
    }
    setTextureRect(intRect);
}

void Fret::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite s = (*this);
    target.draw(s);
}
