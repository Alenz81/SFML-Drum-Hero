//
// Created by super on 4/12/2023.
//

#include "Note.h"

Note::Note() : color(0), isCymbal(false), time(0), x(0){}

Note::Note(sf::Texture &texture, int color, bool isCymbal, double time) : color(color), isCymbal(isCymbal), time(time), isVisible(true){
    setTexture(texture);
    setupIntRect();
    changeScale(scale);
    calculateSlope(Fret::getScale(), scale, y, Fret::getY());
}

int Note::getColor() const {
    return color;
}

double Note::getTime() const {
    return time;
}

bool Note::isValidHitWindow() {
    double fretY = Fret::getY();
    if (color == -1)
        getPosition().y;
    //std::cout << "Top " << getPosition().y << " Fret " << fretY << " Color " << color << std::endl;
    if ((getPosition().y < fretY + 30) && (getPosition().y > fretY - 30)){
        return true;
    } else {
        return false;
    }
}

bool Note::isOffScreen() {
    return getPosition().y > Fret::getY() + 20;
}

void Note::setIsVisible(bool visible) {
    isVisible = visible;
}

double Note::calculateOffset() {
    return (1.0 * Fret::getY() - y)/(((1.0 * Fret::getY() - y)/speed) * 120.0) - 0.2 + (0.3/speed);

}

void Note::setupIntRect() {
    int noteWidth(50);
    int noteHeight(11);
    if (color == -1){
        noteWidth = 214;
        x = 1024/2 - noteWidth/2 * scale;
        intRect.left = 0;
        intRect.top = noteHeight;
    } else {
        x = (1024/2 - (2 * noteWidth * scale)) + (color * noteWidth * scale);
        intRect.left = color * noteWidth;
        intRect.top = 0;
    }
    intRect.width = noteWidth;
    intRect.height = noteHeight;
    setTextureRect(intRect);
    setPosition(x, y);
}

void Note::eventHandler(sf::RenderWindow &window, sf::Event event) {
    /*
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) &&
    color == 0) {
        isVisible = false;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) && color == 1) {
        isVisible = false;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && color == 2) {
        isVisible = false;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && color == 3) {
        isVisible = false;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && color == -1) {
        isVisible = false;
    }
     */
}

void Note::calculateSlope(float fretScale, float startScale, int startY, int fretY) {
    int fretX(0);
    if (color == -1){
        fretX = (1024/2 - (2 * 50 * fretScale)) - (7 * fretScale);
    } else {
        fretX = (1024/2 - (2 * 50 * fretScale)) + (color * 50 * fretScale);
    }
    slopeY = fretY - startY;
    slopeX = fretX - x;
    double length = sqrt(pow(fretX - x, 2) + pow(fretY - startY, 2));
    scaleSlopeY = fretScale - startScale;
    scaleSlopeX = length;


}

void Note::changeScale(float scale) {
    this->scale = scale;
    setScale(scale, scale);
}

void Note::update() {
    move(slopeX / (speed / getScale().x), slopeY / (speed / getScale().y));
    setScale(getScale().x + scaleSlopeY * getScale().x / (speed), getScale().y + scaleSlopeY * getScale().y / (speed));
    if ((getGlobalBounds().top > Fret::getY() + 50) && isVisible) {
        if (color != -1){
            intRect.left = 5 * 50;
        } else {
            intRect.left = 214;
        }
        setTextureRect(intRect);
    }
}

/*
ove(slopeX / (speed), slopeY / (speed));
setScale(getScale().x + scaleSlopeY / (speed), getScale().y + scaleSlopeY / (speed));
*/

void Note::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (isVisible) {
        sf::Sprite s = (*this);
        target.draw(s);
    }
}

std::ostream &operator<<(std::ostream &out, Note note) {
    out << "Color: " << note.color << " Time: " << note.time << std::endl;
    return out;
}

/*
switch(color){
case 'g':
note = 0;
break;
case 'r':
note = 1;
break;
case 'y':
note = 2;
break;
case 'b':
note = 3;
break;
case 'o':
note = 6;
noteWidth = 235;
break;
}*/