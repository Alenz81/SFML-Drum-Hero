//
// Created by super on 4/12/2023.
//

#ifndef SFML_DRUM_HERO_HIGHWAY_H
#define SFML_DRUM_HERO_HIGHWAY_H
#include <queue>
#include "Note.h"
#include "FretBoard.h"
#include "ComponentDrums.h"
#include "SongAudio.h"
#include "MidiFile.h"
#include "DifficultySelector.h"

struct Tempo{
    double tempo;
    double time;
};

class HighWay : public ComponentDrums, public sf::Sprite {
private:
    static sf::Clock songTime;
    sf::Texture fretSprites, noteSprites;
    std::queue<Note> noteHighways[5];
    std::vector<Note> notesToDraw[5];
    std::vector<Note> missedNotes;
    std::queue<Tempo> tempos;

    FretBoard fretBoard;
    void loadTextures();
    bool displayHighway;
    static bool pause;
    int songLength, totalNotes, totalMissedNotes;
    double pauseSongTime;



public:
    HighWay();
    HighWay(std::vector<Note> newNoteHighways[5]);

    void checkNoteTime();

    void populateNoteHighways(int difficulty);
    void emptyHighways();


    void addNote(Note note);
    Note drawNote(int highWay);
    Note getNote(int highWay);

    static void restartSongTime();
    bool isDisplayHighway();
    void setDisplayHighway(bool displayHighway);

    int getSongLength() const;
    void setSongLength(int songLength);
    int getPercentNotesHit();

    bool isNoteKeysPressed(sf::Event event);

    static bool getPause();
    static void setPause(bool pause);

    void eventHandler(sf::RenderWindow &window, sf::Event event) override;
    void update() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    friend std::ostream& operator <<(std::ostream& out, HighWay highWay);
};


#endif //SFML_DRUM_HERO_HIGHWAY_H
