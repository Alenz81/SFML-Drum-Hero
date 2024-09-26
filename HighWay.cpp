//
// Created by super on 4/12/2023.
//

#include "HighWay.h"


bool HighWay::pause = false;
sf::Clock HighWay::songTime;


HighWay::HighWay() : displayHighway(false), songLength(0), totalNotes(0), totalMissedNotes(0), pauseSongTime(0){
    loadTextures();
    fretBoard.setupFrets(fretSprites);
}

HighWay::HighWay(std::vector<Note> newNoteHighways[5]) {
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < newNoteHighways[i].size(); i++){
            noteHighways[i].push(newNoteHighways[i].at(j));
        }
    }
    loadTextures();
    fretBoard.setupFrets(fretSprites);
}

void HighWay::loadTextures() {
    if (!fretSprites.loadFromFile("images/fret sprites.png")){
        exit(25);
    }
    if (!noteSprites.loadFromFile("images/new note sprites.png")){
        exit(30);
    }
}

void HighWay::populateNoteHighways(int difficulty) {
    int startNoteNum = 12 * difficulty + 60;
    int endNoteNum = startNoteNum + 4;
    double offset;
    Note offsetNote;
    offset = offsetNote.calculateOffset();
    //std::cout << "offset " << offset;
    //std::cout << "startnum " << startNoteNum << std::endl;
    smf::MidiFile midiFile;
    midiFile.read("songs/" + Menu::selectedSong + "/notes.mid");
    midiFile.doTimeAnalysis();

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < midiFile[i].size(); j++){
            if (midiFile[i][j].isTempo()){
                tempos.push({midiFile[i][j].getTempoBPM(), midiFile[i][j].seconds});
            }
            if (midiFile[i][j].isNoteOn()){
                if (midiFile[i][j][1] >= startNoteNum && midiFile[i][j][1] <= endNoteNum){
                    noteHighways[midiFile[i][j][1] - startNoteNum].push(Note(Engine::noteSheet,  midiFile[i][j][1] - startNoteNum - 1, false, midiFile[i][j].seconds - offset));
                    totalNotes++;
                    //std::cout << "note value " << (int)midiFile[i][j][1] << std::endl;
                }
            }
        }
    }
}

void HighWay::emptyHighways() {
    for (int i = 0; i < 5; i++){
        while (!noteHighways[i].empty()){
            noteHighways[i].pop();
        }
        while (!notesToDraw[i].empty()){
            notesToDraw[i].pop_back();
        }
    }
    while(!tempos.empty()){
        tempos.pop();
    }
    while(!missedNotes.empty()){
        missedNotes.pop_back();
    }
    totalNotes = 0;
    totalMissedNotes = 0;
    pauseSongTime = 0;
}

void HighWay::checkNoteTime() {
    for (int i = 0; i < 5; i++){ //for (int i = 4; i >= 0; i--){
        if (!noteHighways[i].empty()) {
            if (noteHighways[i].front().getTime() <= songTime.getElapsedTime().asSeconds() + pauseSongTime) {
                //std::cout << "note time: " << noteHighways[i].front().getTime() << " Clock: " << songTime.getElapsedTime().asSeconds() << " Note color: " << noteHighways[i].front().getColor() << std::endl;
                drawNote(i);
            }
        }
    }
}

void HighWay::addNote(Note note) {
    if (note.getColor() != -1){
        noteHighways[note.getColor()].push(note);
    } else {
        noteHighways[4].push(note);
    }
}

int HighWay::getPercentNotesHit() {
    totalMissedNotes = missedNotes.size();
    //std::cout << "totalNotes: " << totalNotes << " missed notes " << totalMissedNotes << std::endl;
    return (100.0 * (totalNotes - totalMissedNotes)/totalNotes);
}

Note HighWay::drawNote(int highWay) {
    if (!noteHighways[highWay].empty()){
        Note temp = getNote(highWay);
        noteHighways[highWay].pop();
        if (notesToDraw[highWay].empty()){
            notesToDraw[highWay].push_back(temp);
        } else {
            notesToDraw[highWay].insert(notesToDraw[highWay].cbegin(), temp);
        }
        return temp;
    } else {
        exit(0);
    }
}

Note HighWay::getNote(int highWay) {
    if (!noteHighways[highWay].empty()){
        return noteHighways[highWay].front();
    } else {
        exit(1);
    }
}

void HighWay::eventHandler(sf::RenderWindow &window, sf::Event event) {
    if (displayHighway) {
        if (!pause) {
            fretBoard.eventHandler(window, event);
                for (int i = 0; i < 5; i++) {
                    if (isNoteKeysPressed(event) && !notesToDraw[i].empty()) {
                            //notesToDraw[i].back().eventHandler(window, event);
                            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) && !notesToDraw[1].empty() && notesToDraw[1].back().isValidHitWindow()) {
                                notesToDraw[1].pop_back();
                            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) ||
                                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) && !notesToDraw[2].empty() && notesToDraw[2].back().isValidHitWindow()) {
                                notesToDraw[2].pop_back();
                            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) ||
                                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && !notesToDraw[3].empty() && notesToDraw[3].back().isValidHitWindow()) {
                                notesToDraw[3].pop_back();
                            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) ||
                                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && !notesToDraw[4].empty() && notesToDraw[4].back().isValidHitWindow()) {
                                notesToDraw[4].pop_back();
                            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && !notesToDraw[0].empty() && notesToDraw[0].back().isValidHitWindow()) {
                                notesToDraw[0].pop_back();
                                //std::cout << "pop";
                            }
                        }
                }
            }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !pause) {
            pauseSongTime += songTime.getElapsedTime().asSeconds();
            pause = true;

        }
    }
}

void HighWay::update() {
    if (displayHighway && !pause) {
        checkNoteTime();
        for (int i = 0; i < 5; i++) {
            if (!notesToDraw[i].empty()) {
                for (int j = 0; j < notesToDraw[i].size(); j++) {
                    notesToDraw[i].at(j).update();
                    if (notesToDraw[i].back().isOffScreen()) {
                        missedNotes.push_back(notesToDraw[i].back());
                        notesToDraw[i].pop_back();
                    }
                }
            }
            fretBoard.update();
        }
        for (int i = 0; i < missedNotes.size(); i++){
            missedNotes.at(i).update();
        }
    }
}

void HighWay::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (displayHighway) {
        Sprite s = (*this);
        target.draw(s);
        fretBoard.draw(target, states);
        for (int i = 0; i < 5; i++) {
            if (!notesToDraw[i].empty()) {
                for (int j = 0; j < notesToDraw[i].size(); j++) {
                    notesToDraw[i].at(j).draw(target, states);
                }
            }
        }
        for (int i = 0; i < missedNotes.size(); i++){
            missedNotes.at(i).draw(target, states);
        }
    }
}

bool HighWay::isDisplayHighway() {
    return displayHighway;
}

void HighWay::setDisplayHighway(bool displayHighway) {
    HighWay::displayHighway = displayHighway;
}

void HighWay::restartSongTime() {
    songTime.restart();
}

int HighWay::getSongLength() const {
    return songLength;
}

void HighWay::setSongLength(int songLength) {
    HighWay::songLength = songLength;
}

bool HighWay::isNoteKeysPressed(sf::Event event) {
    return (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space));
}

bool HighWay::getPause() {
    return pause;
}

void HighWay::setPause(bool pause) {
    HighWay::pause = pause;
}

std::ostream &operator<<(std::ostream &out, HighWay highWay) {
    for (int i = 0; i < 5; i++){
        std::cout << "Line " << i << ":\n";
        while (!highWay.noteHighways[i].empty()){
            std::cout << highWay.noteHighways[i].front();
            highWay.noteHighways[i].pop();
        }
        std::cout << std::endl;
    }
    return out;
}
